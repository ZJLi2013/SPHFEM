#include<list>

using namespace std;

class SphFluidSolver;

struct Particle;

#ifndef _SPH_H_
#define _SPH_H_

#include "Vector.h"

struct Particle {
	int id;
	float mass;
	float density;
	Vector2f position;
	Vector2f velocity;
	Vector2f force;
	
	Vector2f viscosity_force;
	Vector2f pressure_force;

//	Particle()
};

struct Domain{
	list<Particle> particles;
};

class SphFluidSolver {
	const float domain_width;
	const float domain_height;
	const float hsml;  // smoothed length
	const float timestep;
	const float vsp //velocity of sound speed
//	vsp = 10.0

	public:
SphFluidSolver( float domain_width, 
		float domain_height,
		float hsml,
		float timestep) 
: npx((int)( domain_width/hsml)+1),
  npz((int)( domain_height/hsml)+1),
  hsml(hsml),
  timestep(timestep) {}


void update();

void init_particles(Particle *particle, int count);

template <typename Function>
	void foreach_particle(Function function){
		list<Particle> &plist = particles;
		for(list<Particle>::iterator piter = plist.begin(); piter !=plist.end(); piter++){
			function(*piter);
		}
	}

 private:

float kernel(const Vector2f &r, const float h);

Vector2f gradient_kernel(const Vector2f &r, const float h);

float add_density(Particle &particle, Particle &neighbour);

void update_density(Particle &particle);

void add_forces(Particle &particle, Particle &neighbour);

void update_forces(Particle &particle);

//void update_forces();

void update_particle(Particle &particle);

void update_particles();

void reset_particle(Particle &particle);

void reset_particles():
}
#endif


