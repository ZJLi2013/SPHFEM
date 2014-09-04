#include<iostream>
#include<cstdio>

#include "sph.h"
#include "system.h"
using namespace std;

#define Width 20
#define Height 20

SphFluidSolver solver(Width, Height, 1.1f, 0.01f);

void init_system()
{
	Particle *particles = new Particle[particle_count];
	Particle *particle_iter = particles;

	while(true){
		if(count-- == 0){
			solver.init_particles(particles,particle_count);
			return;
		}

		particle_iter->position.x = rand(particle.id);
		particle_iter->position.z = rand(particle.id);
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


