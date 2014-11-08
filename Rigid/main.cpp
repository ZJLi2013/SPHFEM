#include "RigidBody.h"
#include <string>

using namespace std;

int main()
{
	double dt=0.01;
	int Num=24;
	double time=1.;
	int tot = time/dt;
	string filename;

	RigidBody RB(dt, Num);

	RB.Init();

	for(int istep=0; istep< tot; istep++)
	{
		filename = "PART_"+to_string(istep)+".vtu";
		RB.collect_force();
		RB.update_center();
		RB.update_particles();
		if(istep%5==0)
			RB.plot(filename);
	}
	return 0;
}

