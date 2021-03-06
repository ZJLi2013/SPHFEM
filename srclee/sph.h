#include<list>
#include<vector>

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
	float drho;
	Vector2f position;
	Vector2f velocity;
	Vector2f force;	

	Particle(): mass(0.625e-6), density(1000.0), drho(0.0), pressure(0.1)
	{
	}
};

class SphFluidSolver {
	private:
	const float hsml;  // smoothed length
	const float timestep;
	const float vsp; //velocity of sound speed

/*	public:
	list<Particle> p_list; 
*/
	public:
SphFluidSolver(	float hsml,
		float timestep) 
 : hsml(hsml),
   timestep(timestep),
   vsp(30.0)	{
  }

void update(list<Particle>& p_list);

list<Particle> init_particles(Particle *particles, int count);

void update_boundary_force(list<Particle>& p_list, list<Particle>& bcp_list, vector<Vector2f>& wall_tang, vector<Vector2f>& wall_normal);

template <typename Function>
	void foreach_particle(Function function, list<Particle>& p_list){
		list<Particle> &plist = p_list;
		for(list<Particle>::iterator piter = plist.begin(); piter !=plist.end(); piter++){
			function(*piter);
		}
	}

 private:

float kernel(const Vector2f &r, const float h);

Vector2f gradient_kernel(const Vector2f &r, const float h);

void add_density(Particle &particle, Particle &neighbour);

void sum_all_densities(list<Particle>&, Particle &particle);

void update_densities(list<Particle>&);

void add_force(Particle &particle, Particle &neighbour);

void sum_all_forces(list<Particle>& , Particle &particle);

void update_forces(list<Particle>& p_list);

void boundary_force(Particle &particle, list<Particle>& bcp_list, vector<Vector2f>& wall_tang, vector<Vector2f>& wall_normal);

void update_particle(Particle &particle);
float EoS(const Particle& particle);
void update_particles(list<Particle>& p_list);
void reset_particles(list<Particle>& p_list);
void reset_particle(Particle& particle);

};
#endif


