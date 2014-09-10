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
	float pressure;
	Vector2f position;
	Vector2f velocity;
	Vector2f force;	
	Vector2f viscosity;

	Particle(): mass(0.625e-6), density(1000.0), pressure(0.1)
	{
	}
};

/*struct Domain{
	list<Particle> particles;
};
*/

class SphFluidSolver {
//	const float domain_width;
//	const float domain_height;
	const float hsml;  // smoothed length
	const float timestep;
	const float vsp //velocity of sound speed

	public:
	list<Particle> particles_list; 	
/*SphFluidSolver( float domain_width, 
		float domain_height,
		float hsml,
		float timestep) 
: npx((int)( domain_width/hsml)+1),
  npz((int)( domain_height/hsml)+1),
  hsml(hsml),
  timestep(timestep)
  vsp(10.0)	{
  }
*/
SphFluidSolver(	float hsml,
		float timestep) 
 : hsml(hsml),
   timestep(timestep)
   vsp(10.0)	{
  }


/* npx is the number of particles in x direction
 * npz is the number of particles in z direction
 */

void update();

void init_particles(Particle *particles, int count);

template <typename Function>
	void foreach_particle(Function function){
		list<Particle> &plist = particles_list;
		for(list<Particle>::iterator piter = plist.begin(); piter !=plist.end(); piter++){
			function(*piter);
		}
	}

 private:

float kernel(const Vector2f &r, const float h);

Vector2f gradient_kernel(const Vector2f &r, const float h);

float add_density(Particle &particle, Particle &neighbour);

void update_densities();

void add_forces(Particle &particle, Particle &neighbour);

void update_forces();

void update_particle(Particle &particle);

void update_particles();

/*void reset_particle(Particle &particle);

void reset_particles():
*/
}
#endif


