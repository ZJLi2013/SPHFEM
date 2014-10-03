
#include"sph.h"
#include"SphSytem.h"
#define HSML 0.000025 //kernel length
#define TS 0.0001 //timestep
int main() 
{
	int count(1600), bc_count(320), npx(40), npz(40),

	SphSystem Project(count, bc_count, npx, npz,HSML, HSML);
	SphFluidSolver solver(HSML,TS);

	//initial particles(fluid and bc);
	Project.ini_sphsystem();
	Particle* particles = SphSystem.particles;
	Particle* bcparticles = SphSystem.bcparticles;

	list<Particle> fp_list = solver.ini_particles(particles, count);
	list<Particle> bcp_list = solver.ini_particles(bcparticles,bc_count);

	
	double simulation_time(0.1);
	int totsteps = int(simulation_time/TS);

	for(int i=0; i<totsteps; i++)
	{
		solver.update_boundary_force(list<Particle>fp_list, list<Particle> bcp_list);
		solver.update(fp_list);
		
		if( (i%10)==0)
			Project.display(i,particles,bcparticles);
	}
}
