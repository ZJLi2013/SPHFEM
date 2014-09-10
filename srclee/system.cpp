#include<iostream>
#include<cstdio>

#include "sph.h"
#include "system.h"
using namespace std;

#define Width 0.001
#define Height 0.001
#define HSML 0.000025
#define TS   0.0001

SphFluidSolver solve(HSML, TS);

void init_system()
{
	/* initial partical distribution*/
	int npx = (int)WIDTH/HSML+1;
	int npz = (int)HEIGHT/HSML+1;
	double dx = HSML;  
	double dz = HSML;

	Particle *particles = new Particle[particle_count];
	Particle *particle_iter = particles;

	solver.init_particles(particles, particle_count);	
		
	/* initial partical postion */
	particle_iter->position.x = ((particle_iter->id)%npx -1) * dx;
	particle_iter->position.z = (particle_iter->id)/npx *dz;
	particle_iter++;
	}
}

void add_gravity(Particle &particle)
{
	particle.force += gravit*gravity_direction;
}

void add_global_forces()
{
	solver.foreach_particle(add_gravity_force):
}

// void boundaryforce

void boundarycollision(Particle &particle)
{
	float &px = particle.position.x;
	float &pz = particle.position.z;

	float &vx = particle.velocity.x;
	float &vz = particle.velocity.z;

	if(px<0 || px>Width){
		px = min(max(px,0.0f), Width);
		vx *= -collision_restitution;
	}
	if(py<0 || py>Height){
		py=min(max(py,0.0f),Height);
		vy *= -collision_restituion;
	}

}

void handle_collisions(){
	solver.foreach_particle(boundarycollision);
}

void gravity_direction(){
	gravity_direction.x = - rotation_matrix[1];
	gravity_direction.z = - rotation_matrix[4];
	gravity_direction = normalize(gravity_direction);
}

void integration()
{
	float simulation_time = 0.4;
	float timestep = 0.0001;
	int totsteps = simulation_time/timestep;
	
	for(int i=0; i< totsteps; i++)
	{
		add_global_forces();
		solver.update();
		display(i,particle_count);
	}
}

