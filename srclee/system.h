#include "Vector.h"
#include "sph.h"

class system{

Vector2f gravity_direction;
const int particle_count = 1600;
float rotation_matrix[4];
const float gravity = 9.81f;
float collision_restitution = 1.0f;

	public:

system() {}

void init_system();

void add_gravity(Particle &particle);

void add_global_forces();

void boundarycollision(Particle &particle);

void handle_collisions();

void gravity_direction();

}

