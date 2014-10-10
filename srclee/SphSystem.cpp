#include <math.h>  // floor fun
#include "sph.h"
#include "SphSystem.h"
//#include <iostream>
//using namespace std;

void SphSystem:: init_sphsystem()
{

	/* initial fluid partical */
	Particle* particles = new Particle[count];
	InitParticles = particles; // this pointer will be send to sphsolver;
	InitFluidPosition(particles);
	
	/* initial bc particals */
	Particle* bcparticles = new Particle[bc_count];
	InitBcParticles = bcparticles;
	InitBCPosition(bcparticles);
}
void SphSystem::InitFluidPosition(Particle* particles)
{	
	for(int i =0; i <count; i++)
	{       
		particles[i].id = i+1;	
 	}		
	//npz(41), npx(41)
	   #ifdef CASE2	
	{ //case2:: rectangular with shallow
	int  width(3), height(21);
	int left = (npx-width)/2 + 1;
//	int np = npx*npz - width*height;
	// Particle *particles = new Particle[np];
	
	int np = count; //for case 2, count = npx*npz - width*height;

       	int raw1=0, col1=0;
	   for(int j=1; j<=npx; j++)
		   for(int i=1; i<=npz; i++)
		   {
			if( i!=left && i!=left+1 && i!=left+2  ||  (j>height))
			{
				if(j<=height)
				{
		                	 raw1=(particles->id+1)%(npx-width);
					 col1=(int) floor((particles->id)/(npx-width));
				}
				else
				{	  raw1=(particles->id - height*(npx-width))%npx;
					  col1=(int) floor((particles->id - height*(npx-width))/npx) + height;
				}
			if(raw1==0)
			{
				particles->position.x = 0.001;
			        particles->position.z = col1*dz;	
			}else
			{ 
				if(j<=height && i >= left+3)
				{
					particles->position.x = (raw1-1)*dx+ dx*(width);
					particles->position.z = col1*dz;
				}
				else{	
					particles->position.x = (raw1-1)*dx;
					particles->position.z = col1*dz;
				    }	
			}
		        particles++;     	
			}
		   }

	   }
	  #else
	{  //case 1::rectangular
	  	int np=count;
		int raw=0,  col=0; 
	       	for(int i=1; i<=npx; i++)
		   for(int j=1; j<=npz; j++)
		   {
		         //Oct 8, should put it at last line
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
				//test Oct 8 ( partilcles->position should be correct)
				//cout << " particle->position ( " << particles->position.x << ", " << particles->position.z << " )" << endl;	
			}
		   }
	}
	#endif
}

void SphSystem::InitBCPosition(Particle* bcparticles)
{

	for(int i =0; i < bc_count; i++)
	{       
		bcparticles[i].id = i+1;	
 	}		
	
	#ifdef CASE2
	{	
	//	int npz(83), npx(81), width(5), height(43);
	int bcnpz = npz*2+1, bcnpx = npx*2-1, bcwidth= 5, bcheight=43; 
	//	double dx=1.25e-5, dz=1.25e-5;
	double bcdx = dx/2, bcdz = dz/2;
	double side = bcdx*bcnpx; 
	int bchalfx = (bcnpx - bcwidth -2)/2;
//	int bcnp = (bchalfx + bcheight + bcnpz)*2 + bcwidth + bcnpx;
//	Particle *particles = new Particle[bcnp];
  	
	int bcnp = bc_count; //for case 2 bc_count = (bchalfx + bcheight + bcnpz)*2 + bcwidth + bcnpx;

	   for( int i=0; i< bcnp; i++)
	 {
		   bcparticles++;		 
		   if(i< bchalfx)//bottom_left
		   {
		   	bcparticles->position.z = -0.0000125;
	   	   	bcparticles->position.x = (bcparticles->id -1) * bcdx; 
		   } else if( i < bchalfx+ bcheight) //height_left
		   {
			   bcparticles->position.x = bchalfx * bcdx;
			   bcparticles->position.z = (bcparticles->id -1 - bchalfx )* bcdz - bcdz;
		   }else if( i < bchalfx+ bcheight+ bcwidth) //mid 5
		   {
			   bcparticles->position.x = (bcparticles->id  - bcheight)*bcdx;
			   bcparticles->position.z = (bcheight-1)*bcdz -bcdz;
		   }else if(i < bchalfx + bcwidth + bcheight*2) //height_right
		   {
			   bcparticles->position.x = (bchalfx+ bcwidth + 1) * bcdx;
			   bcparticles->position.z = (bchalfx+ bcwidth + bcheight*2 - bcparticles->id)* bcdz -bcdz;
		   }else if(i< bchalfx*2 + bcwidth + bcheight*2) //bottom_right
		   {
			   bcparticles->position.x = (bcparticles->id - bcheight*2 + 1) * bcdx;
			   bcparticles->position.z = -0.0000125;
		   }else if(i< bcnpx-2+ bcheight*2 + bcnpz) //right
		   {
			   bcparticles->position.x =  side;
			   bcparticles->position.z = (bcparticles->id - bcheight*2 - bcnpx) * bcdz;
		   }else if( i< 2*bcnpx+ bcnpz+ bcheight*2-2) //top
		   { 
			   bcparticles->position.z = side;
			   bcparticles->position.x = (2*bcnpx+bcnpz+ bcheight*2 - bcparticles->id -2) *bcdx;
		   } else  
		   { 	
			   bcparticles->position.x = -0.0000125;
			   bcparticles->position.z = (bcnp - bcparticles->id -1) * bcdz;
		  }
		 
	}
	
	#else
	{
	int bcnpz(npz*2-1), bcnpx(npz*2-1);
	double bcdx=dx/2, bcdz=dz/2;
	int bcnp = 2*(bcnpx+ bcnpz);
	//Particle *particles = new Particle[np];
   	
	for( int i=0; i< bcnp; i++)
	 {
		   bcparticles++;		 
		   if(i< bcnp/4)//bottom
		   {
		   	bcparticles->position.z = 0.0;
	   	   	bcparticles->position.x = (bcparticles->id -1) * bcdx;
		   } else if( i < bcnp/2) //left side
		   {
			   bcparticles->position.x = 0.001;
			   bcparticles->position.z = (bcparticles->id-1 - bcnp/4 )* bcdz;
		   }else if( i< 3* bcnp/4) //top
		   { 
			   bcparticles->position.z = 0.001;
			   bcparticles->position.x = (3*bcnp/4 - bcparticles->id) * bcdx;
		   } else 
		   { 	
			   bcparticles->position.x = 0.000;
			   bcparticles->position.z = (bcnp - bcparticles->id) * bcdz;
		  }
		 
	}
	}
	#endif
}




	



