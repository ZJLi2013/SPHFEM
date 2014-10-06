#include "Vector.h"
#include "sph.h"
#include<list>
#include<cmath> // cos, sqrt fabs
using namespace std;
#define PI 3.1415926535897

void SphFluidSolver::boundary_force(Particle &particle,list<Particle> bcp_list) {

	for(list<Particle>::iterator bcpiter=bcp_list.begin(); bcpiter != bcp_list.end(); bcpiter++)
{	
	Vector2f bc_force(0.0f);
	Vector2f wall_normal(0.0f); // need data or call a function 
	Vector2f wall_tang(0.0f); //need data

	Vector2f dr = particle.position - bcpiter->position;
//normal projection length(\psi) 
	float psi = dot(dr, wall_normal); 
//tangential vector
	Vector2f tang_dr = dr - psi*wall_normal;
//tangent projection length(\xi)
	float xi = dot(tang_dr, wall_tang);

	float deltapp= hsml;
/*
	 if(xi > 0.0) 
  		deltapp = bp2(bc_particle,2) ;
	 else
	 deltapp = bp2(bc_particle, 1) ;
*/
       	//bp2,2 neighbour boundar particle distance(left neighbour, right neighbour) 

/* P(xi) = 0.5(1.0+cos(pi*fabs(xi)/deltapp) xi==projection length on x
 * R(psi) = A (1-q)/sqrt(t)
 * App = 0.01c^2/h
 * Appc = App* (epsilon_z + epsilon_dyn)
 */

	float q = 0.0;

	if(psi>0.0)
		 q = psi/hsml/2; //paramter in R
	else if(psi<0.0)
		q = 0.2*fabs(psi)/hsml/2;
	else
		q = 0.5e-3; //correcting for zero distance from wall

	if(q <1.0 && psi > 0.0 && fabs(xi) < deltapp)
{   	
		Vector2f dr = bcpiter->position - particle.position;
		float u_normal = dot(dr, wall_normal);
/* u_normal < 0 , particles are approaching
 * u_normal > 0 , particles are moving apart
 */	
		float App = 0.0;

		if(u_normal > 0.0)
			 App =( 0.01*vsp*vsp - vsp*u_normal)/hsml;
		else
			App = 0.01*vsp*vsp/hsml;

		float magnitude_force = 0.5*(1.0+ cos(2*PI*fabs(xi)/deltapp))*(1.0 - q)/sqrt(q)*App;

		 bc_force = wall_normal*magnitude_force;
}       else
		 bc_force = Vector2f(0.0f);
	
	particle.force -=bc_force; 
	}
		}


void SphFluidSolver::update_boundary_force(list<Particle> p_list,list<Particle> bcp_list)
{
	for(list<Particle>::iterator piter = p_list.begin(); piter !=p_list.end(); piter++)
	{
		boundary_force(*piter,  bcp_list);
	}
}
