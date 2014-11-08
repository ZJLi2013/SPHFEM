#include "RigidBody.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

#define square(x) ((x)*(x))


void RigidBody::Init()
{
	int nx = Num/4+1;
	int nz = Num/4-1;
	double dx=0.125;
	double dz=0.125;

	rgp = new Particle[Num];
	for(int i=0; i<Num; i++)
	{
		rgp[i].id = i;
	}

	for(int i=0; i<Num; i++)
	{
		if(i<nx)
		{
			rgp[i].position.z = 0.0 - dz;
			rgp[i].position.x = rgp[i].id *dx - dx;
		}
		else if( i < Num/2)
		{
			rgp[i].position.x = (nx-1)*dx - dx;
			rgp[i].position.z = (rgp[i].id - nx)*dz;
		}
		else if( i < Num - nx+1)
		{
			rgp[i].position.z = (nz+1)*dz - dz;
			rgp[i].position.x = (3*Num/4 - rgp[i].id -1)*dx;
		}
		else
		{
			rgp[i].position.x = 0.0 - dx;
			rgp[i].position.z = (Num - rgp[i].id -1)*dz;
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
	CenterVelocity=Vector2f(0.0f);
}


void RigidBody::collect_force()
{
	Vector2f TmpF(0.0f);
	float TmpJ(0.0f);
	
	float random_force = static_cast<float> (rand())/ static_cast<float>(RAND_MAX);

	for(vector<Particle>::iterator piter=pVector.begin(); piter !=pVector.end(); piter++)
	{
		piter->force = Vector2f(random_force);
		TmpF += piter->force;
		piter->rel_pos = piter->position - CenterPosition;
		TmpJ += dot(piter->force,piter->rel_pos);
/*	cout << " ------------------------------------" << endl;
	cout << "TmpJ " << TmpJ << endl; 
	cout << piter->rel_pos.x << " " << piter->rel_pos.z << endl;
	cout << " -------------------------------------" << endl;
*/	}
	linear_acc = TmpF/Mass;
	angular_acc = TmpJ/Inertia;
	//cout<< "linear_acc " << length(linear_acc) << " " << "angular_acc " << angular_acc << endl;
}

void RigidBody::update_center()
{
	CenterVelocity += linear_acc * dt;
	CenterPosition += CenterVelocity*dt;
	CenterOmega += angular_acc * dt;
}

void RigidBody::update_particles()
{
	for(vector<Particle>::iterator piter=pVector.begin(); piter !=pVector.end(); piter++)	
	{
		piter->velocity = CenterVelocity + piter->rel_pos * CenterOmega;
		piter->position = CenterPosition + piter->rel_pos;
	}
}


	
