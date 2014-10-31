#include "Vector.h"
#include "sph.h"
#include<cmath> // cos, sqrt fabs
using namespace std;
#define PI 3.1415926535897

void SphFluidSolver::boundary_force(Particle &particle,list<Particle>& bcp_list, vector<Vector2f>& wall_tang, vector<Vector2f>& wall_normal ) {

	int index(0);
	for(list<Particle>::iterator bcpiter=bcp_list.begin(); bcpiter != bcp_list.end(); bcpiter++)
{	
	
	Vector2f bc_force(0.0f);
	Vector2f wall_N = wall_normal[index];
	Vector2f wall_T = wall_tang[index];

	Vector2f dr = particle.position - bcpiter->position;
//normal projection length(\psi) 
	float psi = dot(dr, wall_N); 
//tangential vector
	Vector2f tang_dr = dr - psi*wall_N;
//tangent projection length(\xi)
	float xi = dot(tang_dr, wall_T);

	float deltapp= hsml;
	float q = 0.0;

	if(psi>0.0)
		 q = psi/hsml/2; //paramter in R
	else if(psi<0.0)
		q = 0.2*fabs(psi)/hsml/2;
	else
		q = 0.5e-3; //correcting for zero distance from wall

	if(q <1.0 && psi > 0.0 && fabs(xi) < deltapp)
{   	
		Vector2f dv = bcpiter->velocity - particle.velocity;
		float u_normal = dot(dv, wall_N);
/* u_normal < 0 , particles are approaching
 * u_normal > 0 , particles are moving apart
 */	
		float App = 0.0;

		if(u_normal > 0.0)
			 App =( 0.01*vsp*vsp - vsp*u_normal)/hsml;
		else
			App = 0.01*vsp*vsp/hsml;

		float magnitude_force = 0.5*(1.0+ cos(2*PI*fabs(xi)/deltapp))*(1.0 - q)/sqrt(q)*App;

		 bc_force = wall_N*magnitude_force;
}       else
		 bc_force = Vector2f(0.0f);
	
	particle.force -=bc_force* bcpiter->mass; 
	index++;
	}
		}


void SphFluidSolver::update_boundary_force(list<Particle>& p_list,list<Particle>& bcp_list, vector<Vector2f>& wall_tang, vector<Vector2f>& wall_normal)
{
	for(list<Particle>::iterator piter = p_list.begin(); piter !=p_list.end(); piter++)
	{
		boundary_force(*piter,  bcp_list, wall_tang, wall_normal);
	}
}
