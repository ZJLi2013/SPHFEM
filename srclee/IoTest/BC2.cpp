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
//	int npz(15), npx(13), width(3), height(6);
	int npz(83), npx(81), width(5), height(43);
	double dx=1.25e-5, dz=1.25e-5;
	double side = dx*npx; 
	int halfx = (npx - width -2)/2;
	int np = (halfx + height + npz)*2 + width + npx;
	Particle *particles = new Particle[np];
	Particle *ptr = particles;
	string file_name = "BC2.vtu";
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
		   if(i< halfx)//bottom_left
		   {
		   	particles->position.z = -0.0000125;
	   	   	particles->position.x = (particles->id -1) * dx; //starting from (0, -0.0000125)
		   } else if( i < halfx+height) //height_left
		   {
			   particles->position.x = halfx * dx;
			   particles->position.z = (particles->id -1 - halfx )*dz -dz;
		   }else if( i < halfx+height+width) //mid 5
		   {
			   particles->position.x = (particles->id  - height)*dx;
			   particles->position.z = (height-1)*dz -dz;
		   }else if(i < halfx + width + height*2) //height_right
		   {
			   particles->position.x = (halfx+width + 1) * dx;
			   particles->position.z = (halfx+width + height*2 - particles->id)*dz -dz;
		   }else if(i< halfx*2 + width + height*2) //bottom_right
		   {
			   particles->position.x = (particles->id - height*2 + 1) * dx;
			   particles->position.z = -0.0000125;
		   }else if(i< npx-2+height*2 + npz) //right
		   {
			   particles->position.x =  side;
			   particles->position.z = (particles->id - height*2 - npx) * dz;
		   }else if( i< 2*npx+npz+height*2-2) //top
		   { 
			   particles->position.z = side;
			   particles->position.x = (2*npx+npz+height*2 - particles->id -2) *dx;
		   } else  
		   { 	
			   particles->position.x = -0.0000125;
			   particles->position.z = (np - particles->id -1) * dz;
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

	
		   if(i< halfx)//bottom_left
		   {
		   	ptr->position.z = -0.0000125;
	   	   	ptr->position.x = (ptr->id -1) * dx; //starting from (0, -0.0000125)
		   } else if( i < halfx+height) //height_left
		   {
			   ptr->position.x = halfx * dx;
			   ptr->position.z = (ptr->id -1 - halfx )*dz -dz;
		   }else if( i < halfx+height+width) //mid 5
		   {
			   ptr->position.x = (ptr->id  - height)*dx;
			   ptr->position.z = (height-1)*dz -dz;
		   }else if(i < halfx + width + height*2) //height_right
		   {
			   ptr->position.x = (halfx+width + 1) * dx;
			   ptr->position.z = (halfx+width + height*2 - ptr->id)*dz -dz;
		   }else if(i< halfx*2 + width + height*2) //bottom_right
		   {
			   ptr->position.x = (ptr->id - height*2 + 1) * dx;
			   ptr->position.z = -0.0000125;
		   }else if(i< npx-2+height*2 + npz) //right
		   {
			   ptr->position.x =  side;
			   ptr->position.z = (ptr->id - height*2 - npx) * dz;
		   }else if( i< 2*npx+npz+height*2-2) //top
		   { 
			   ptr->position.z =  side;
			   ptr->position.x = (2*npx+npz+height*2 - ptr->id -2) *dx;
		   }  else 
		   { 	
			   ptr->position.x = -0.0000125;
			   ptr->position.z = (np - ptr->id -1) * dz;
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

