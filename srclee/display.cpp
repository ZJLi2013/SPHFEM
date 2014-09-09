#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

//#include"Vector.h"

using namespace std;

int main()
{

	string file_name;
// define the directory path if need

	int totstep(200);
	int np(40);

/*the following pressure, velocity, posisiton are only test data 	
struct Particle	{
	float density(1000.0);
	float pressure(0.0);
	Vector2f position;
	Vector2f velocity;
};

	Particle* ptest = new Particle[np];

	Particle* piter = ptest;

 for(int count=1; count<=np;count++)
{
	piter->position.x = rand()%20+1;
	piter->position.z = rand()%100+10;
	piter->velocity.x = rand();
	piter->velocity.z = rand();
	piter++;
}

the above is only test data */


	for( int istep=1;istep <= totstep; istep++)
	{
		if(istep<10)
			file_name = "PART_000" + to_string(istep) + ".vtu";
		else if( istep>=10 && istep<100)
			file_name = "PART_00" + to_string(istep) + ".vtu";
		else if(istep>=100 && istep<1000)
			file_name= "PART_0" + to_string(istep) + ".vtu";
		else
			file_name= "PART_"+ to_string(istep) + ".vtu";
	}

// data need to read in, position, velocity, rho, pressure

	ofstream fid(file_name);
	
	//WRITE VTU FORMAT HEADER
	fid << "<?xml version=\"1.0\" ?>\r\n"<<endl;
	fid << "<VTKF<=type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\r\n"<<endl;
	fid << "<UnstructuredGrid>\r\n"<<endl;
	fid << "<Piece NumberOfPoints=" + to_string(np)+"NumberOfCells=" + to_string(np) +">\r\n"<<endl;

	//write in pressure data
	fid << "<PointData Scalars=\"Pressure\" Vectors=\"Velocity\">\r\n"<<endl;;
	fid << "<DataArray type=\"Float32\" Name=\"Pressure\" format=\"ascii\">\r\n"<<endl;
	for(int i=1;i<=np;i++)
	{
//		fid<< setprecision(6)<<particle(i).pressure<< " ";
		fid<< setprecision(6)<< 10.0 << " ";

	}

	fid << "\r\n";
	fid << "</DataArray>\r\n"<<endl;

	//write density data
	fid << "<DataArray type=\"Float32\" Name=\"Density\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{
	//	fid << setprecision(6)<< particle(i).density<< " ";
		fid << setprecision(6)<< 1000.0<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	
	//write velocity data
	fid << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{
//		fid << setprecision(8)<<particle(i).velocity.x <<setprecision(8) << particle(i).velocity.z << " ";

		fid << setprecision(8)<< rand() <<setprecision(8) << rand() << " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</PointData>\r\n";

	//write parti<=position data	
	fid << "<Points>\r\n" ;
	fid << "<DataArray type= \"Float32\" NumberOfComponents= \"2\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{

//		 fid<<setprecision(8)<<position.x <<setprecision(8)<< position.z << " ";
		 fid<<setprecision(8)<< rand() <<setprecision(8)<< rand() << " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Points>\r\n";

	//write cell data, cell type vertex
	fid << "<Cells>\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{
		fid<< (i-1)<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{
		fid<<i<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">\r\n";
	for(int i=1;i<=np;i++)
	{
		fid<<1<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Cells>\r\n";
	fid << "</Piece>\r\n";
	fid << "</UnstructuredGrid>\r\n";
	fid << "</VTKF<=";
	
	fid.close();
	return 0;
}

		
	


