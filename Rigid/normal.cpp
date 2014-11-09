#include "RigidBody.h"
#include <assert.h>
#include <numeric>
#include <iostream>
using namespace std;

#include "Vector.h"
class MinusClass
{
	public:
		Vector2f operator() (Vector2f p1, Vector2f p2) const {return p1-p2;};
};


void RigidBody::bgwall()
{

	
	vector<Particle> TmpVector (pVector.begin(), pVector.end());
	vector<Particle>::iterator TmpIter = TmpVector.begin();
	TmpVector.insert(TmpIter,*(--pVector.end()));
	TmpVector.push_back(*pVector.begin());


	assert(TmpVector.size()==Num+2);

	vector<Vector2f> PositionVector;
	for(vector<Particle>::iterator TmpIter=TmpVector.begin(); TmpIter != TmpVector.end(); TmpIter++)
	{
		PositionVector.push_back(TmpIter->position);
	}


	 vector<Vector2f> NextPos (PositionVector.begin()+1, PositionVector.end());
	 vector<Vector2f> LastPos (PositionVector.begin(),PositionVector.end()-1);

	assert(NextPos.size()==Num+1);
	assert(LastPos.size()==Num+1);

	transform(LastPos.begin(), LastPos.end(), NextPos.begin(), LastPos.begin(), MinusClass());

	for(vector<Vector2f>::iterator iter=LastPos.begin(); iter != LastPos.end(); iter++)
	{
		if(iter->x==0.0 && iter->z > 0.0)
		{
			bg_tang.push_back(Vector2f(0,1.));
			bg_normal.push_back(Vector2f(-1.0,0));
		}
		else if(iter->x==0.0 && iter->z < 0.0)
		{
			bg_tang.push_back(Vector2f(0,-1.0));
			bg_normal.push_back(Vector2f(1.0,0));
		}
		else
		{
		float slope = (iter->z)/(iter->x);
		bg_tang.push_back(normalize(Vector2f(1,slope)));
		bg_normal.push_back(normalize(Vector2f(-slope,1)));
		}
	}

	 NextPos.clear();
	 LastPos.clear();
	 PositionVector.clear();
}

