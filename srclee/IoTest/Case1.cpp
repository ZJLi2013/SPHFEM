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
	int npz(41), npx(41);
	double dx=2.5e-5, dz=2.5e-5;
	int np = npx*npz;
	Particle *particles = new Particle[np];
	Particle *ptr = particles;
	string file_name = "Retangular.vtu";
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
	   
	   int index1=0;
	   for(int i=1; i<=npx; i++)
		   for(int j=1; j<=npz; j++)
		   {
		//	if( i!=left && i!=left+1 && i!=left+2 ) // ||  (j>height))
		//	{
		                particles++;     
		                int raw=(particles->id)%npx;
				int col=(int) floor((particles->id)/npx);
			if(raw==0)
			{
				particles->position.x = 0.001;
			        particles->position.z = (col-1)*dz;	
			}else
			{
				particles->position.x = (raw-1)*dx;
				particles->position.z = col*dz;
			}
                        fid <<setprecision(6)<< particles->position.x << " "<<setprecision(6)<< particles->position.z << " " << 0 << endl;
			index1++;
		//	}
		   }
	  cout << "index1 " << index1 << endl;

	  fid <<"</DataArray>\r\n";
	  fid << "\r\n";
	  fid << "</PointData>\r\n";

  	  fid << " \r\n";	  
	  fid << "<Points>\r\n" << endl;
	  fid << "<DataArray type= \"Float32\" Name = \"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	  fid << "\r\n";
	  int index2=0; 
	  for(int i=1; i<=npx; i++)
		   for(int j=1; j<=npz; j++)
		{
		//	if( (i != left) && (i != left+1) && (i != left+2) ) //||  (j > height)) 
		//		{
	      	   		ptr++;
				int raw = (ptr->id)%npx;
				int col = (int)floor((ptr->id)/npx);	

				if( raw ==0)
				{ 
					ptr->position.x = 0.001;
					ptr->position.z = (col-1)*dz;
				}else
				{	
				ptr->position.x = (raw-1)*dx; 
				ptr->position.z = col*dz;
				}
		        fid <<setprecision(6)<< ptr->position.x << " "<<setprecision(6)<< ptr->position.z << " " << 0 << endl;
           			index2++;
		//		}
		}
	  cout << "index2 " << index2 << endl;
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

