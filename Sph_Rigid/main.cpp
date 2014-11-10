#include<list>
#include"sph.h"
#include"SphSystem.h"
#include "RigidBody.h"
#define HSML 0.000025 //kernel length
#define TS 0.0001 //timestep
int main() 
{
	
	int npx(41), npz(41);
	int count = npx * npz;
	double domain_length = (npx-1)*HSML + HSML; 
	double domain_height = (npz-1)*HSML + HSML;
/* this domain_length, height is when initial distance of nearest fp to bp is h/2
 * if the distance intial is h, then
 * domain_length = (npx-1)*HSML + 2*HSML;
 * domain_height = (npz-1)*HSML + 2*HSML;
 */
	int bc_count = 2* (npx*2+1 + npz*2+1) - 4; 

	int mvp_count = 24;
	SphSystem Project(count, bc_count, npx, npz,HSML, HSML);
	SphFluidSolver solver(HSML,TS);
	RigidBody RG(TS,mvp_count);

	//initial particles(fluid and bc);
	Project.init_sphsystem();

	//wall vector used in Boundary_force calculation
	Project.WallVector();

	list<Particle> fp_list = solver.init_particles(Project.InitParticles, count);
	list<Particle> bcp_list = solver.init_particles(Project.InitBcParticles,bc_count);

	RG.Init(); //initial moving boundary particles


	double simulation_time(0.01);
	int totsteps = int(simulation_time/TS);

	for(int i=0; i<totsteps; i++)
	{
		//fluid particle - fixed boundary particles
		solver.update_boundary_force(fp_list, bcp_list, Project.wall_tang, Project.wall_normal);
	 	list<Particle> mvp_list (RG.pVector.begin(), RG.pVector.end());
		RG.bgwall(); //update MovingBc normal vectors;
		//fluid particle-moving boundary particles
		solver.update_boundary_force(fp_list,mvp_list, RG.bg_tang, RG.bg_normal);
		solver.update(fp_list);
		RG.RigidBody_Update(mvp_list);
		if( (i%10)==0)
		{
			Project.display(i,fp_list,bcp_list);
			RG.plot(i);
		}
	}
	return 0;
}
