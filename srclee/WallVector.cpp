#include "SphSystem.h"
#include "Vector.h"
#include <algorithm>
// anti-clockwise + 

#define root2 1.4142135623730951


void SphSystem::WallVector()
{
	Vector2f TAO, NORMAL;	

	for(int i=1; i < bc_count-1; i++)
	{

		float next_x = BcVector[i+1].position.x;
		float next_z = BcVector[i+1].position.z;
		float front_x = BcVector[i-1].position.x;
		float front_z = BcVector[i-1].position.z;
	
		float center_x = bc_count/4*dx/2/2;
		float center_z = center_x;

		if((next_z - front_z) ==0.0 && next_x > front_x) //bottom wall
		{
			TAO.x = 1.0;
			TAO.z = 0.0;
			NORMAL.x = 0.0;
			NORMAL.z = 1.0;
			wall_tang.push_back(TAO);
			wall_normal.push_back(NORMAL);
		}
		else if((next_x - front_x) == 0.0 && next_z > front_z)  //right wall
		{	
			TAO.x = 0.0; 
			TAO.z = 1.0;
			NORMAL.x = -1.0;
			NORMAL.z = 0.0;
			wall_tang.push_back(TAO);
			wall_normal.push_back(NORMAL);
		}
		else if((next_z - front_z) == 0.0 && next_x < front_x) //top wall
		{
			TAO.x = -1.; 
			TAO.z = 0.; 
			NORMAL.x = 0.; 
			NORMAL.z = -1.0 ;
			wall_tang.push_back(TAO);
			wall_normal.push_back(NORMAL);
		}
		else if((next_x - front_x)==0.0 && next_z < front_z ) //left wall
		{
			TAO.x = 0.0;
			TAO.z = -1.0; 
			NORMAL.x = 1.0;
			NORMAL.z = 0.0;
			wall_tang.push_back(TAO);
			wall_normal.push_back(NORMAL);
		}
		else {						   // corner points
			
			if( BcVector[i].position.x < center_x && BcVector[i].position.z < center_z ) // left_low CP, normal vector positive
			{ 	
				NORMAL.x = 1.0/root2;
				NORMAL.z = 1.0/root2; 
				wall_normal.push_back(NORMAL);
				TAO.x = 1.0/root2;
				TAO.z = -1.0/root2;
				wall_tang.push_back(TAO);
			}
			else if( BcVector[i].position.x > center_x && BcVector[i].position.z < center_z ) // right_low CP, normal.x - , normal.z +
			{
				NORMAL.x = -1.0;
				NORMAL.z = 1.0;
				wall_normal.push_back(NORMAL/root2);
				TAO.x = 1.0;
				TAO.z = 1.0; 
				wall_tang.push_back(TAO/root2);
			}
			else if(BcVector[i].position.x > center_x && BcVector[i].position.z > center_z) // right_high CP, normal.x-, normal.z-
			{
				NORMAL.x = -1.0;
				NORMAL.z = -1.0; 
				wall_normal.push_back(NORMAL/root2);
				TAO.x = -1.0;
				TAO.z = 1.0; 
				wall_tang.push_back(TAO/root2);
			}
			else // left_high CP, normal.x +, normal.z -
			{
				NORMAL.x = 1.0 ;
				NORMAL.z = -1.0; 
				wall_normal.push_back(NORMAL/root2);
				TAO.x = -1.0;
				TAO.z = -1.0; 
				wall_tang.push_back(TAO/root2);
			}
		}
		}
	
		// adding first BC point
		Vector2f tmp_normal(1.0, 1.0);
		Vector2f tmp_tang(1.0, -1.0);
		wall_normal.insert(wall_normal.begin(), tmp_normal/root2);
		wall_tang.insert(wall_tang.begin(), tmp_tang/root2);
		//adding last BC point
		tmp_tang.x =0.;
	        tmp_tang.z =-1.0;
		tmp_normal.x = 1.0;
	       	tmp_normal.z =0.0;
		wall_normal.insert(wall_normal.end(), tmp_normal);
		wall_tang.insert(wall_tang.end(), tmp_tang);
}
	
