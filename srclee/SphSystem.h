#include "Vector.h"
#include "sph.h"

class SphSystem{

	 private:
	const int count, bc_count; 
	const int npx, npz;
	const double dx, dz;

	void InitFluidPosition();

	void InitBCPosition();


	 public:
	Particle* particles, bcparticles;

	SphSystem(	int count,
		int bc_count,
		int npx,
		int npz,
		int dx,
		int dz)
	:count(count),
	 bc_count(bc_count),
	 npx(npx),
	 npz(npz),
	 dx(dx),
	 dz(dz){
	 }

	void init_sphsystem();

	void display(int istep, Particle *particles, Particle *bcparticles);
}



