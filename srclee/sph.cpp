#include "sph.h"
#include <cstdio>
#include <iostream>

using namespace std;

#define PI_FLOAT  3.141592653589793f
#define square(x)	  ((x)*(x))

inline float SphFluidSolver :: kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/square(h);
	const float q = length(r)/h;
	if(0<= q && q <= 2)
		return alpha * (3/16 * square(q) - 3/4 * q + 3/4);
	 else
		return 0;
}

inline Vector2f SphFluidSolver:: gradient_kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/square(h);
	const float q = length(r)/h;
	if(0<=q && q<= 2)
		return alpha*(3/8*q - 3/4)* r/ length(r);
	 else
		return Vector2f(0.0f);
}

inline void SphFluidSolver :: add_density(Particle &particle, Particle &neighbour){
	if(particle.id > neighbour.id)	return ;
 
	Vector2f r=particle.position - neighbour.position;

	if(dot(r,r) > square(hsml)) return ;
//shoud return 0 or not ?
	float common = kernel(r, hsml);
	particle.density += neighbour.mass*common;
	neighbour.density += particle.mass*common;
}

inline void SphFluidSolver::sum_all_densities(p_list, Particle &particle)
{
	for(list<Particle>::iterator piter = p_list.begin(); piter != p_list.end(); piter++)
	{
		add_density(particle,*piter);
	}
}


inline void SphFluidSolver::update_densities(p_list)
{
	for(list<Particle>::iterator piter = p_list.begin(); piter != p_list.end();piter++)
		sum_all_densities(p_list, *piter);
}

inline void SphFluidSolver::add_force(Particle &particle, Particle &neighbour)
{
	if(particle.id >= neighbour.id) return;
	Vector2f r = particle.position - particle.position;
	Vector2f v = particle.velocity - particle.velocity;
	if(dot(r,r)> square(hsml)) return;
/* compute pressrue force */
	Vector2f common = (neighbour.pressure / square(neighbour.density) + particle.pressure / square(particle.density)) * gradient_kernel(r, hsml);
	particle.force += -neighbour.mass*common;
	particle.pressure += -neighbour.mass*common.x; 
// wether pressure is scalar or vector?
	neighbour.force -= -particle.mass*common;
	neighbour.pressure -= -particle.mass*common.x;

/*compute viscosity force by artificial viscosity given by Monaghan 1992 */
        float const alpha = 0.1 ;
    	float const eta2 = 0.01 * square(hsml);
 	float mu = hsml*dot(v,r)/(dot(r,r) + eta2);
	float rhobar =(particle.density + neighbour.density)/2;

	float pi;
	if (dot(v,r) < 0.0)
		 pi = - alpha* vsp * mu / rhobar;
	else
		 pi = 0.0;

	common = pi*gradient_kernel(r,hsml);
	particle.force += -neighbour.mass * common;
	particle.viscosity += -neighbour.mass*common;
	neighbour.force -= -particle.mass*common;
	neighbour.viscosity -= -particle.mass*common;
	
/*gravity is not based on particle collection */
}


// this subroutine is used to calcualate forces acting on one particle
void SphFluidSolver::sum_all_forces(list<Particle> p_list, Particle &particle)
{
	for(list<Particle>::iterator piter =p_list.begin(); piter !=p_list.end(); piter++)
	{
		add_force(particle,*piter);
	}
}

// this subroutine calculate forces acting on all particles in the domain
void SphFluidSolver::update_forces(list<Particle> p_list)
{
	for (list<Particle>::iterator piter = p_list.begin(); piter != p_list.end(); piter++){
	sum_all_forces(p_list, *piter);
	}
}

void SphFluidSolver::update_particle(Particle &particle)
{	
	
	particle.velocity += timestep * particle.force;
	particle.position += timestep * particle.velocity;
}

void SphFluidSolver::update_particles()
{
	for(list<Particle>::iterator piter=p_list.begin(); piter != p_list.end(); piter++)
	{
		update_particle(*piter);
	}
}

	void SphFluidSolver::update(list<Particle> p_list)
{	
	update_densities(p_list);
	update_forces(p_list);
	update_particles();
}

list<Particle> SphFluidSolver :: init_particles(Particle *particles, int count)
{
	for(int i = 0; i <= count; i++)
	{       
		particles[i].id = i+1;	
		particles[i].force = Vector2f(0.0f);
		particles[i].viscosity = Vector2f(0.0f);
		particles[i].velocity = Vector2f(0.0f);
		pp_list.push_back(*particles);
		particles++;
	}
	return pp_list;
}
