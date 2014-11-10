#include "sph.h"
#include <cstdio>
#include <iostream>
#include <list>
#include <math.h> //pow
using namespace std;

#define PI_FLOAT  3.141592653589793f
#define square(x)	  ((x)*(x))

inline float SphFluidSolver :: kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/square(h);
	const float q = length(r)/h;
	if(0<= q && q <= 2)
		return alpha * (3./16 * square(q) - 3./4 * q + 3./4);
	 else
		return 0;
}

inline Vector2f SphFluidSolver:: gradient_kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/square(h);
	const float q = length(r)/h;
	if(0<q && q<= 2)
		return alpha*(3./8*q - 3./4)* r/ length(r);
	 else
		return Vector2f(0.0f);
}

inline void SphFluidSolver :: add_density(Particle &particle, Particle &neighbour){
	if(particle.id > neighbour.id)	return ;
 
	Vector2f r=particle.position - neighbour.position;
	Vector2f dv=particle.velocity - neighbour.velocity;

	if(dot(r,r) > square(hsml)) return ;
	float common = dot(gradient_kernel(r, hsml), dv);
	particle.drho += neighbour.mass*common;
	neighbour.drho += particle.mass*common;

}

inline void SphFluidSolver::sum_all_densities(list<Particle>& pp_list, Particle &particle)
{
	for(list<Particle>::iterator piter = pp_list.begin(); piter != pp_list.end(); piter++)
	{
		add_density(particle,*piter);
	}
}


inline void SphFluidSolver::update_densities(list<Particle>& pp_list)
{
	for(list<Particle>::iterator piter = pp_list.begin(); piter != pp_list.end();piter++)
		sum_all_densities(pp_list, *piter);
}

inline void SphFluidSolver::add_force(Particle &particle, Particle &neighbour)
{
	if(particle.id >= neighbour.id) return;
	Vector2f r = particle.position - neighbour.position;
	Vector2f v = particle.velocity - neighbour.velocity;
	if(dot(r,r)> square(hsml)) return;
/* compute pressrue force */	
	Vector2f common = (neighbour.pressure / square(neighbour.density) + particle.pressure / square(particle.density)) * gradient_kernel(r, hsml);
	particle.force += -neighbour.mass*common;
	neighbour.force -= -particle.mass*common;

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
	neighbour.force -= -particle.mass*common;

/*gravity is not based on particle collection */

}

void SphFluidSolver::sum_all_forces(list<Particle>& pp_list, Particle &particle)
{
	for(list<Particle>::iterator piter =pp_list.begin(); piter !=pp_list.end(); piter++)
	{
		add_force(particle,*piter);
	}
}

void SphFluidSolver::update_forces( list<Particle>& pp_list)
{
	for (list<Particle>::iterator piter = pp_list.begin(); piter != pp_list.end(); piter++){
	sum_all_forces(pp_list, *piter);
	}
}

void SphFluidSolver::update_particle(Particle &particle)
{	

 	particle.density += timestep * particle.drho;	
	particle.velocity += timestep * particle.force;
	particle.position += timestep * particle.velocity;
	particle.pressure = EoS(particle);	
}

float SphFluidSolver::EoS(const Particle& particle)
{
	int gamma = 7;
	float rho0 = 1000.0;
	float rho = particle.density;
	float B = vsp*vsp*rho0/gamma;
	float pressure = B * ( pow((rho/rho0), gamma) -1);
	return pressure;
}	

void SphFluidSolver::update_particles( list<Particle>& pp_list)
{
	for(list<Particle>::iterator piter=pp_list.begin(); piter != pp_list.end(); piter++)
	{
		update_particle(*piter);
	}
}

	void SphFluidSolver::update(list<Particle>& pp_list)
{	
	update_densities(pp_list);
	update_forces(pp_list);
	update_particles(pp_list);
	reset_particles(pp_list);
}

list<Particle> SphFluidSolver :: init_particles(Particle *particles, int count)
{
	list<Particle> pp_list;

	for(int i =0; i <count; i++)
	{       
//		particles[i].id = i+1;	
		particles[i].force = Vector2f(0.0f);
		particles[i].velocity = Vector2f(0.0f);
	// 	pp_list.push_back(*particles);
	// 	modify Oct 9
		pp_list.push_back(particles[i]);
//		particles++;
	}
	return pp_list;
}

void SphFluidSolver::reset_particles(list<Particle>& pp_list)
{
	for(list<Particle>::iterator piter=pp_list.begin(); piter != pp_list.end(); piter++)
	{
		reset_particle(*piter);
	}
}

inline void SphFluidSolver::reset_particle(Particle &particle)
{
	particle.drho = 0.0f;
	particle.force = Vector2f(0.0f);
}
