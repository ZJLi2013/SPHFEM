#include "SphSystem.h"

void SphSystem::WallVector()
{
	
	Vector2f TAO(0., 1.), NORMAL(-1.,0.);

	for(int i=1; i < bc_count-1; i++)
	{
		float next_x = BcVector[i+1].position.x;
		float front_x = BcVector[i-1].position.x;

		float next_z = BcVector[i+1].position.z;
		float front_z = BcVector[i-1].position.z;

		float k = (next_z - front_z)/(next_x - front_x);

		Tao.x = k;
		Vector2f tao = normalize(TAO);
		wall_tang.push_back(tao);
		NORMAL.z = k;
	        Vector2f normal = normalize(NORMAL);
		wall_normal.push_back(normal);
	}
	
	//for BcVector[0]
	float k0 = (BcVector[1].position.z - BcVector[bc_count-1].position.z)/(BcVector[1].position.x - BcVector[bc_count-1].position.x);
	Vector2f tao0 = normalize(Vector2f(k0,1.));
	Vector2f normal0 = normalize(Vector2f(-1., k0));
	//for BcVector[bc_count-1]
	float k1 = (BcVector[0].position.z - BcVector[bc_count-2].position.z)/(BcVector[0].position.x - BcVector[bc_count-2].position.x);
	Vector2f tao1 = normalize(Vector2f(k1,1.));
	Vector2f normal1 = normalize(Vector2f(-1., k1));

	//add tang[0], tang[end], normal[0], normal[end] to vectors
	std::vector<Vector2f>::iterator it_tang, it_normal;
	it_tang = wall_tang.begin();
	it_tang = wall_tang.insert(it_tang,tao0);
	wall_tang.push_back(tao1);
	
	it_normal = wall_normal.begin();
	it_normal = wall_normal.insert(it_normal,normal0);
	wall_normal.push_back(normal1);

}
	
