#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<iomanip>
#include "SphSystem.h"

using namespace std;

void SphSystem::display(int istep, list<Particle> particles, list<Particle> bcparticles )
{
	string file_name;

		if(istep<10)
			file_name = "PART_000" + to_string(istep) + ".vtu";
		else if( istep>=10 && istep<100)
			file_name = "PART_00" + to_string(istep) + ".vtu";
		else if(istep>=100 && istep<1000)
			file_name= "PART_0" + to_string(istep) + ".vtu";
		else
			file_name= "PART_"+ to_string(istep) + ".vtu";

// data need to read in, position, velocity, rho, pressure
	ofstream fid(file_name);
	
	//WRITE VTU FORMAT HEADER
	fid << "<?xml version=\"1.0\" ?>\r\n"<<endl;
	fid << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\r\n"<<endl;
	fid << "<UnstructuredGrid>\r\n"<<endl;
	fid << "<Piece NumberOfPoints= \" " + to_string(count+bc_count)+ " \" NumberOfCells=\" "+ to_string(count+bc_count) + " \">\r\n"<<endl;

	//write in pressure data
	fid << "<PointData Scalars=\"Pressure\" Vectors=\"Velocity\">\r\n"<<endl;;
	fid << "<DataArray type=\"Float32\" Name=\"Pressure\" format=\"ascii\">\r\n"<<endl;
	// pressure of fluid particles
	for(list<Particle>::iterator ip=particles.begin(); ip!=particles.end(); ip++)
	{
		
		fid<< setprecision(6)<< ip->pressure << " ";
	}
//	fid << "\r\n"<< endl;
	//presure of bc particles
	for(list<Particle>::iterator ip=bcparticles.begin(); ip!=bcparticles.end(); ip++)
	{
		
		fid<< setprecision(6)<<ip->pressure<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n"<<endl;

	//write density data
	fid << "<DataArray type=\"Float32\" Name=\"Density\" format=\"ascii\">\r\n";
	//density of fluid particles
	for(list<Particle>::iterator ip=particles.begin(); ip!=particles.end(); ip++)
	{
		fid << setprecision(6)<< ip->density<< " ";
	}
//	fid << "\r\n" << endl;
	//density of bc particles
	for(list<Particle>::iterator ip=bcparticles.begin(); ip!=bcparticles.end(); ip++)	
	{
		fid << setprecision(6)<< ip->density<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	
	//write velocity data
	fid << "<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\r\n";
	//veclotiy of fluid partilces
	for(list<Particle>::iterator ip=particles.begin(); ip!=particles.end(); ip++)	
	{
		fid << setprecision(8)<< ip->velocity.x << " " <<setprecision(8) << ip->velocity.z << " " << setprecision(8) << 0 << endl;
	}
//	fid <<"\r\n"<<endl;
	//velocity of bc particles
	for(int i=0; i<bc_count;i++)
	{
		fid << setprecision(8)<<0.0 <<" " << setprecision(8) << 0.0 << " " << setprecision(8) << 0 << endl;
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</PointData>\r\n";

	//write particle position data	
	fid << "<Points>\r\n" ;
	fid << "<DataArray type= \"Float32\" Name=\"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	//position for fluid particles
	for(list<Particle>::iterator ip=particles.begin(); ip!=particles.end(); ip++)	
	{
		 fid<<setprecision(8)<< ip->position.x << " "<<setprecision(8)<< ip->position.z << " "<< setprecision(8) << 0 << endl;
	}
//	fid << "\r\n" << endl;
	//position for bc particles
	for(list<Particle>::iterator ip=bcparticles.begin(); ip!=bcparticles.end(); ip++)	
	{
		 fid<<setprecision(8)<< ip->position.x << " "<<setprecision(8)<< ip->position.z << " "<< setprecision(8) << 0  << endl;
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Points>\r\n";

	//write cell data, cell type vertex
	fid << "<Cells>\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\r\n";
	//write connectivity of fluid particles
	for(int i=1;i<=count;i++)
	{
		fid<< (i-1)<< " ";
	}
//	fid << "\r\n" << endl;
	//write connectivity of bc particles
	for(int i=1;i<=bc_count;i++)
	{
		fid<< count + (i-1)<< " ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\r\n";
	//write offsets of fluid particles
	for(int i=1;i<=count;i++)
	{
		fid<<i<<" ";
	}
//	fid << "\r\n" << endl;
	//write offsets of bc particles
	for(int i=1;i<=bc_count;i++)
	{
		fid<<count+i<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "\r\n";
	fid << "<DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">\r\n";
	//write types of fluid particles
	for(int i=1;i<=count;i++)
	{
		fid<<1<<" ";
	}
//	fid << "\r\n" << endl;
	//write types of bc particles
	for(int i=1;i<=bc_count;i++)
	{
		fid<<2<<" ";
	}
	fid << "\r\n";
	fid << "</DataArray>\r\n";
	fid << "</Cells>\r\n";
	fid << "</Piece>\r\n";
	fid << "</UnstructuredGrid>\r\n";
	fid << "</VTKFile>";
	
	fid.close();
}

		
	


