struct Vector2f
{
	float x, z;
	inline Vector2f():x(0) , z(0)
	{
	}
	inline Vector2f(float x, float z)
	{
		this->x = x;
		this->z = z;
	}

};

struct Particle
{
	int id;
	float density;
	Vector2f position;
	Particle() : density(1000.0) {
	}
	
};

#include<list>
struct Domain{
	std::list<Particle> particles;
};

#include<iostream>
using namespace std;

int main()
{
	int np(4);
	Domain*	Field = new Domain[1];
		
	/*
	cout << "sizeof int=4 " << sizeof(int) << "sizeof(float) =4 "<<sizeof(float)<<"sizeof(Particle)=8 " << sizeof(Particle) << endl;
	cout << "sizeof *Field " << sizeof(*Field)<<endl; 24	
	cout << " sizeof &Field " << sizeof(&Field) << endl; 8
*/

	Particle* ptr = new Particle[np];

	for(int i=1; i<=np; i++)
	{
		Field->particles.push_back(*ptr);
		ptr++;
	}


	std::list<Particle>::iterator iter=Field->particles.begin();

	cout << "length of the list " << Field->particles.size() << endl;

	while(iter != Field->particles.end())
	{	
		cout<< "density output" << iter->density << endl;
		++iter;
	}	
	return 0;
}	




