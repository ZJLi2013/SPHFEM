#include<list>
#include"sph.h"
#include"SphSystem.h"
#define HSML 0.000025 //kernel length
#define TS 0.0001 //timestep
int main() 
{
	int count(1681), bc_count(328), npx(41), npz(41);

	SphSystem Project(count, bc_count, npx, npz,HSML, HSML);
	SphFluidSolver solver(HSML,TS);

	//initial particles(fluid and bc);
	Project.init_sphsystem();

	//wall vector used in Boundary_force calculation
	Project.WallVector();

	list<Particle> fp_list = solver.init_particles(Project.InitParticles, count);
	list<Particle> bcp_list = solver.init_particles(Project.InitBcParticles,bc_count);
	
	double simulation_time(0.003);
	int totsteps = int(simulation_time/TS);

	for(int i=0; i<totsteps; i++)
	{
		solver.update_boundary_force(fp_list, bcp_list, Project.wall_tang, Project.wall_normal);
		solver.update(fp_list);

		if( (i%10)==0)
			Project.display(i,fp_list,bcp_list);
	}
	return 0;
}
