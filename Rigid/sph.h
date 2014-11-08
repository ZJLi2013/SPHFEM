#ifndef _SPH_H_
#define _SPH_H_

#include "Vector.h"

struct Particle {
	int id;
	float mass;
	Vector2f position;
	Vector2f rel_pos;
	Vector2f velocity;
	Vector2f force;	
	Particle(): mass(1.0)
	{
	}
};

#endif


