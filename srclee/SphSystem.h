#include "Vector.h"
#include "sph.h"

class SphSystem{

	 private:
	const int count, bc_count; 
	const int npx, npz;
	const double dx, dz;
//	Particle* particles;
//	Particle* bcparticles;

	void InitFluidPosition(Particle*); //particles

	void InitBCPosition(Particle*); //bcparticles


	 public:
	Particle* InitParticles;
	Particle* InitBcParticles;

	SphSystem(	int count,
		int bc_count,
		int npx,
		int npz,
		double dx,
		double dz)
	:count(count),
	 bc_count(bc_count),
	 npx(npx),
	 npz(npz),
	 dx(dx),
	 dz(dz){
	 }

	void init_sphsystem();

	void display(int istep, list<Particle>  particles, list<Particle> bcparticles);
};



