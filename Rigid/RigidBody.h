#include "sph.h"
#include <vector>
#include <string>

using namespace std;

class RigidBody
{
	private:
	double Mass, Inertia;
	double angular_acc;
	double CenterOmega;
	Vector2f linear_acc;
	Vector2f CenterPosition, CenterVelocity;
	double dt;
	int Num;
	Particle* rgp;
	vector<Particle> pVector; 
	vector<Vector2f> bg_tang, bg_normal;

	public:
	RigidBody(double dt, int Num)
		: dt(dt),
		  Num(Num)
	{
		linear_acc = Vector2f(0.0f);
		angular_acc = 0.0;
		Inertia = 0.0;
		Mass = 0.0;
	}

	void Init(); //particles position, Mass, Inertia, 

	void collect_force();

	void update_center();

	void update_particles();

	void bgwall();

	void plot(string filename); 


};
