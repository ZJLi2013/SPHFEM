#include "RigidBody.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

#define square(x) ((x)*(x))
#define	dx 1.25e-5
#define dz 1.25e-5

void RigidBody::Init()
{
	int nx = Num/4+1;
	int nz = Num/4-1;

	//starting position of rigidbody	
	double starting_z = Num/4 * dz;
	//initial cental velocity
	double starting_center_velocity = dx*100;

	rgp = new Particle[Num];
	rel_pos = new Vector2f[Num]; 
	for(int i=0; i<Num; i++)
	{
		rgp[i].id = i;
	}

	for(int i=0; i<Num; i++)
	{
		if(i<nx)
		{
			rgp[i].position.z = 0.0 - dz - starting_z ;
			rgp[i].position.x = rgp[i].id *dx - dx;
		}
		else if( i < Num/2)
		{
			rgp[i].position.x = (nx-1)*dx - dx;
			rgp[i].position.z = (rgp[i].id - nx)*dz - starting_z;
		}
		else if( i < Num - nx+1)
		{
			rgp[i].position.z = (nz+1)*dz - dz - starting_z;
			rgp[i].position.x = (3*Num/4 - rgp[i].id -1)*dx;
		}
		else
		{
			rgp[i].position.x = 0.0 - dx;
			rgp[i].position.z = (Num - rgp[i].id -1)*dz - starting_z;
		}
		pVector.push_back(rgp[i]);
	}


	Vector2f TmpX(0.0f);
	for(int i=0; i<Num; i++)
	{
		Mass += rgp[i].mass;
		TmpX += rgp[i].mass * rgp[i].position;	
		Inertia += rgp[i].mass * square(length(rgp[i].position));
	}
	CenterPosition = TmpX/Mass;
	CenterVelocity=Vector2f(starting_center_velocity);
}

void RigidBody::RigidBody_Update(list<Particle>& mvp_list)
{
	pVector.clear();
	for(list<Particle>::iterator iter = mvp_list.begin(); iter != mvp_list.end(); iter++)
	{
		pVector.push_back(*iter);
	}
	RigidBody_Update();
}

void RigidBody::RigidBody_Update()
{
	collect_force();
	update_center();
	update_particles();
}

void RigidBody::collect_force()
{
	Vector2f TmpF(0.0f);
	float TmpJ(0.0f);
	int index=0;
	for(vector<Particle>::iterator piter=pVector.begin(); piter !=pVector.end(); piter++)
	{
 		TmpF += piter->force * piter->mass;
		rel_pos[index++]=piter->position - CenterPosition;
		//	TmpJ += dot(piter->force,piter->rel_pos); for discrete system
	}
	linear_acc = TmpF/Mass;
	TmpJ = Mass * (square(dx) + square(dz))/12.; //for continous system
	angular_acc = TmpJ/Inertia;
}

void RigidBody::update_center()
{
	CenterVelocity += linear_acc * dt;
	CenterPosition += CenterVelocity*dt;
	CenterOmega += angular_acc * dt;
}

void RigidBody::update_particles()
{
	int index=0;
	for(vector<Particle>::iterator piter=pVector.begin(); piter !=pVector.end(); piter++)	
	{
		Vector2f tmp_rel_pos = rel_pos[index++];
		piter->velocity = CenterVelocity + tmp_rel_pos * CenterOmega;
		piter->position = CenterPosition + tmp_rel_pos;
	}

}


	
