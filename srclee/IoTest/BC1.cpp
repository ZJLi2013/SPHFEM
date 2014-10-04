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
		Vector2f position;
};

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<math.h>

using namespace std;

int main()
{
	int npz(80), npx(80);
	double dx=1.25e-5, dz=1.25e-5;
	int np = 2*(npx+npz);
	Particle *particles = new Particle[np];
	Particle *ptr = particles;
	string file_name = "BC1.vtu";
	ofstream fid(file_name);

	   	for(int i=1; i<=np; i++)
	{
		particles[i].id = i;
	}


	   fid << "<?xml version=\"1.0\" ?>\r"<<endl;
           fid << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\r"<<endl;
           fid << "<UnstructuredGrid>\r"<<endl;
           fid << "<Piece NumberOfPoints= \" " +  to_string(np)+ " \"  NumberOfCells= \" " + to_string(np) + "\"  >\r"<<endl;
	  
	   fid << "<PointData Vectors=\"Position\">\r\n"<<endl;	   
	   fid << "<DataArray type= \"Float32\" Name = \"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	   fid << "\r\n";	 
	  
	   for( int i=0; i< np; i++)
	 {
		   particles++;		 
		   if(i<np/4)//bottom
		   {
		   	particles->position.z = 0.0;
	   	   	particles->position.x = (particles->id -1) * dx;
		   } else if( i < np/2) //left side
		   {
			   particles->position.x = 0.001;
			   particles->position.z = (particles->id-1 - np/4 )*dz;
		   }else if( i< 3*np/4) //top
		   { 
			   particles->position.z = 0.001;
			   particles->position.x = (3*np/4 - particles->id) *dx;
		   } else 
		   { 	
			   particles->position.x = 0.000;
			   particles->position.z = (np - particles->id) * dz;
		  }
		  fid << setprecision(6) << particles->position.x << " " << setprecision(6) << particles->position.z << " " << 0 << endl;
		 
	}
	  fid <<"</DataArray>\r\n";
	  fid << "\r\n";
	  fid << "</PointData>\r\n";
  	  fid << " \r\n";	  

	  fid << "<Points>\r\n" << endl;
	  fid << "<DataArray type= \"Float32\" Name = \"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	  fid << "\r\n";

	   for( int i=0; i< np; i++)
	 {		
		   ptr++;	 
		   if(i<np/4)//bottom
		   {
		   	ptr->position.z = 0.0;
	   	   	ptr->position.x = (ptr->id -1) * dx;
		   } else if( i < np/2) //left side
		   {
			   ptr->position.x = 0.001;
			   ptr->position.z = (ptr->id-1 - np/4)*dz;
		   }else if( i< 3*np/4) //top
		   { 
			   ptr->position.z = 0.001;
			   ptr->position.x = (3*np/4 - ptr->id) *dx;
		   } else 
		   { 	
			   ptr->position.x = 0.000;
			   ptr->position.z = (np - ptr->id) * dz;
		   }
		   fid << setprecision(6) << ptr->position.x << " " << setprecision(6) << ptr->position.z << " " << 0 << endl;
 	 } 


	  fid << "\r\n";
          fid << "</DataArray>\r\n";
	  fid << "</Points>\r\n";
	 
	  fid << "\r\n";
	  //write cell data, 
	  fid << "<Cells>\r\n";
	  fid << "<DataArray type = \"Int32\" Name= \"connectivity\" format = \"ascii\" >\r\n";
	  for (int i=1; i<=np; i++)
		  fid << i-1 << " ";
	  fid << "\r\n";
	  fid << "</DataArray>\r\n";
	  fid <<"\r\n";

	  //WRITE offsite
	  fid << "<DataArray type =\"Int32\" Name=\"offsets\" format=\"ascii\">\r\n";
	  for(int i=1; i<=np; i++)
		  fid<<i<< " ";
	  fid << "\r\n";
	  fid << "</DataArray>\r\n";
	  fid << "\r\n";
	  
	  //write types
	  fid <<"<DataArray type= \"Int32\" Name = \"types\" format = \"ascii\">\r\n";
	  for(int i=1; i<=np; i++)
		  fid << 1 << " ";
	  fid << "\r\n";
	  fid << "</DataArray>\r\n";
	  
	  fid << "</Cells>\r\n";
	  fid << "</Piece>\r\n";
	  fid << "</UnstructuredGrid>\r\n";
	  fid << "</VTKFile>";
	  return 0;
}

