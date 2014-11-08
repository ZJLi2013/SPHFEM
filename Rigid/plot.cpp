#include<iostream>
#include<fstream>
#include<iomanip>
#include "RigidBody.h"

using namespace std;

void RigidBody::plot(string file_name)
{
/*	string file_name;
		if(istep<10)
			file_name = "PART_000" + to_string(istep) + ".vtu";
		else if( istep>=10 && istep<100)
			file_name = "PART_00" + to_string(istep) + ".vtu";
		else if(istep>=100 && istep<1000)
			file_name= "PART_0" + to_string(istep) + ".vtu";
		else
			file_name= "PART_"+ to_string(istep) + ".vtu";
*/

// data need to read in, position, velocity, rho, pressure
	ofstream fid(file_name);
	
	//WRITE VTU FORMAT HEADER
	fid << "<?xml version=\"1.0\" ?>\r\n"<<endl;
	fid << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\r\n"<<endl;
	fid << "<UnstructuredGrid>\r\n"<<endl;
	fid << "<Piece NumberOfPoints= \" " + to_string(Num)+ " \" NumberOfCells=\" "+ to_string(Num) + " \">\r\n"<<endl;
	fid << "<PointData Vectors=\"Velocity\">\r\n"<<endl;;
	//write velocity data
	fid << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\r\n";
	//veclotiy of fluid partilces
	for(vector<Particle>::iterator ip=pVector.begin(); ip!=pVector.end(); ip++)	
	{
		fid << setprecision(8)<< ip->velocity.x << " " <<setprecision(8) << ip->velocity.z << " " << setprecision(8) << 0 << endl;
	}

	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</PointData>\r\n";

	//write particle position data	
	fid << "<Points>\r\n" ;
	fid << "<DataArray type= \"Float32\" Name=\"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	//position for fluid pVector
	for(vector<Particle>::iterator ip=pVector.begin(); ip!=pVector.end(); ip++)	
	{
		 fid<<setprecision(8)<< ip->position.x << " "<<setprecision(8)<< ip->position.z << " "<< setprecision(8) << 0 << endl;
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Points>\r\n";

	//write cell data, cell type vertex
	fid << "<Cells>\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\r\n";
	//write connectivity of fluid pVector
	for(int i=1;i<=Num;i++)
	{
		fid<< (i-1)<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\r\n";
	//write offsets of fluid pVector
	for(int i=1;i<=Num;i++)
	{
		fid<<i<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">\r\n";
	//write types of fluid pVector
	for(int i=1;i<=Num;i++)
	{
		fid<<1<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Cells>\r\n";
	fid << "</Piece>\r\n";
	fid << "</UnstructuredGrid>\r\n";
	fid << "</VTKFile>";
	
	fid.close();
}

