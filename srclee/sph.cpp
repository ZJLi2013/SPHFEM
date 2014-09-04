#include "sph.h"
// #include <sys/time.h>
#include <cstdio>

#include <iostream>

using namespace std;

#define PI_FLOAT  3.141592653589793f
#define sqr(x)	  ((x)*(x))

inline float SphFluidSolver :: kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/sqr(h);
	const float q = length(r)/h;
	if(0 .le. q && q .le. 2)
	{
	return alpha * (3/16 * sqr(q) - 3/4 * q + 3/4);
	} else
		return 0;
}

inline Vector2f SphFluidSolver:: gradient_kernel(const Vector2f &r, const float h)
{
	const float alpha = 2/PI_FLOAT/sqr(h);
	const float q = length(r)/h;
	if(0 .le. q && q .le. 2)
	{
		return alpha*(3/8*q - 3/4)* r/ length(r);
	} else
		return 0;
}

inline float SphFluidSolver :: add_density(Particle &particle, Particle &neighbour){
	if(particle.id > neighbour.id)	return;

	Vector2f r=particle.position - neighbour.position;

	if(dot(r,r) > sqr(hsml)) return;

	float common = kernel(r, hsml);
	particle.density += neighbour.mass*common;
	neighbour.density += particle.mass*common;
}

inline void SphFluidSolver::update_densities() {
	list<Particle> &plist = domain.particles;
	for(list<Particle>::iterator piter = plist.begin(); piter != plist.end();piter++)
		add_density(particle, *piter);
}


inline void SphFluidSolver::add_forces(Particle &particle, Particle &neighbour){
	if(particle.id >= neighbour.id) return;
	Vector2f r = particle.position - particle.position;
	Vector2f v = particle.velocity - particle.velocity;
	if(dot(r,r)> sqr(hsml)) return;
/* compute pressrue force */
	Vector2f common = (neighbour.pressure_force / sqr(neighbour.density) + particle.pressure_force / sqr(particle.density)) * gradient_kernel(r, hsml);
	particle.force += -neighbour.mass*common;
	partilce.pressure_force += -neighbour.mass*common;
	neighbour.force -= -particle.mass*common;
	neighbour.pressure_force -= -particle.mass*common;

/*compute viscosity force by artificial viscosity given by Monaghan 1992 */
        float const alpha = 0.1 ;
    	float const sqreta = 0.01 * sqr(hsml);
 	float mu = hsml*dot(v,r)/(dot(r) + sqreta);
	float rhobar =(particle.density + neighbour.density)/2;

	if (dot(v,r) < 0)
		float pi = - alpha* vsp * mu / rhobar;
	else
		pi = 0;

	common = pi*gradient_kernel(r,hsml);
	particle.force += -neighbour.mass * common;
	particle.viscosity_force += -neighbour.mass*common;
	neighbour.force -= -particle.mass*common;
	neighbour.viscosity_force -= -particle.mass*common;

/*gravity is not based on particle collection */
}
		
void SphFluidSolver::update_forces()
{
	list<Particle> &plist = domain.particles;
	for (list<Particle>::iterator piter = plist.begin(); piter != plist.end(); piter++){
	add_forces(particle, *piter);
	}

void SphFluidSolver::update_particle(Particle &particle)
{	
	particle.velocity += timestep * particle.force;
	particle.position += timestep * particle.velocity;
}

void SphFluidSolver::update_particles()
{
	list<Particle> &plist = domain.particles;
	for(list<Particle>::iterator piter=plist.begin(); piter != plist.end(); piter++)
	{
		update_particle(*piter);
	}
}

void SphFluidSolver::reset_particle(Particle &particle)
{
	particle.density = 0.0f;
	particle.force = Vector2f(0.0f);
	particle.viscosity_force = Vector2f(0.0f);
	particle.pressure_force = Vector2f(0.0f);
}

void SphFluidSovler::reset_particles(){
	list<Particle> &plist = domain.particles;
	for(list<Particle>::iterator piter = plist.begin(); piter ! = plist.end(); piter++)
	{
		reset_particle(*piter);
	}
}

void SphFluidSolver::update()
{	
	reset_particles();
	update_densities();
	update_forces();

}

void SphFluidSolver :: init_particles(Particle *particles, int count)
{
	domain = new Domain[npx*npz];	
	for(int i = 0; i < count; i++)
	{
		particles[i].id = i;
	}
}

