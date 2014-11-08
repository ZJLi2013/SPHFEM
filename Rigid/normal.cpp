#include "RigidBody.h"
using namespace std;

void RigidBody::bgwall()
{

	vector<Particle> TmpVector = {*pVector.end(), pVector, *pVector.begin()};

	for(vector<Particle>::iterator iter=TmpVector.begin()+1; iter != TmpVector.end()-1; iter++)
	{
		iter_next = iter+1;
		iter_last = iter-1;

		Vector2f next_position = iter_next->position;
		Vector2f last_position = iter_last->position;

		float slope = (next_position.z - last_position.z)/(next_position.x - last_position.x);
		bg_tang.push_back(normalize(Vector2f(1,slope)));
		bg_normal.push_back(normalize(Vector2f(-slope,1)));
	}
}

