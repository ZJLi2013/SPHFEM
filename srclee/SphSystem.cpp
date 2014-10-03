#include "Vector.h"
#include "sph.h"
#include "SphSystem.h"

void SphSystem:: init_system()
{

	/* initial fluid partical */
	Particle *particles = new Particle[count];
	InitFluidPosition(*particles);
	
	/* initial bc particals */
	Particle *bcparticles = new Particle[bc_count];
	InitBCPosition(*bcparticles);
}

void SphSystem::InitFluidPosition()
{
//	int npz(41), npx(41);

	   for(int i=1; i<=npx; i++)
		   for(int j=1; j<=npz; j++)
		   {
		                particles++;     
		                int raw=(particles->id)%npx;
				int col=(int) floor((particles->id)/npx);
			if(raw==0)
			{
				particles->position.x = 0.001;
			        particles->position.z = (col-1)*dz;	
			}else
			{
				particles->position.x = (raw-1)*dx;
				particles->position.z = col*dz;
			}
		   }
}

void SphSystem::InitBCPosition()
{
	double bcdx = dx/2;
	double bcdz = dz/2;
	int bcnx = bc_count/bcdx/2;
	int bcnz = bc_count/bcdz/2;

	for(int i=1; i<=bcnx; i++)
		for(int j=1; j<=bcnz; j++)
		{
			bcparticles++;
			int raw = (bcparticles->id)&bcnx;
			int col = (int) floor((bcparticles->id)/bcnx);
// lack information
		}
}

