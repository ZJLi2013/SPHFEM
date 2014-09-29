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
	int npz(41), npx(41), width(3), height(21);
	double dx=2.5e-5, dz=2.5e-5;
	int left = (npx-width)/2 + 1;
	int np = npx*npz - width*height;
	Particle *particles = new Particle[np];
	Particle *ptr = particles;
	string file_name = "Case241.vtu";
	ofstream fid(file_name);


	for(int k=1; k<=np; k++)
	{
		particles[k].id = k;
	//	cout<<"pid at "<< k << "is " << particles[k].id << endl;
	}


	   fid << "<?xml version=\"1.0\" ?>\r"<<endl;
           fid << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\r"<<endl;
           fid << "<UnstructuredGrid>\r"<<endl;
           fid << "<Piece NumberOfPoints= \" " +  to_string(np)+ " \"  NumberOfCells= \" " + to_string(np) + "\"  >\r"<<endl;
	  
	   fid << "<PointData Vectors=\"Position\">\r\n"<<endl;	   
	   fid << "<DataArray type= \"Float32\" Name = \"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	   fid << "\r\n";	 

	   int index1=0;
	   int raw1=0, col1=0;
	   for(int j=1; j<=npx; j++)
		   for(int i=1; i<=npz; i++)
		   {
			if( i!=left && i!=left+1 && i!=left+2  ||  (j>height))
			{
				index1++;
				cout << "particles id" << particles->id<<endl;
				if(j<=height)
				{
		                	 raw1=(particles->id+1)%(npx-width);
					 col1=(int) floor((particles->id)/(npx-width));
				}
				else
				{	  raw1=(particles->id - height*(npx-width))%npx;
					  col1=(int) floor((particles->id - height*(npx-width))/npx) + height;
				}
				cout << "i, j " << i << " " << j << " " << "raw, col " << raw1 << " " << col1 << endl;
			if(raw1==0)
			{
				particles->position.x = 0.001;
			        particles->position.z = col1*dz;	
			}else
			{ 
				if(j<=height && i >= left+3)
				{
					particles->position.x = (raw1-1)*dx+ dx*(width);
					particles->position.z = col1*dz;
				}
				else{	
					particles->position.x = (raw1-1)*dx;
					particles->position.z = col1*dz;
				    }	
			}
                        fid <<setprecision(6)<< particles->position.x << " "<<setprecision(6)<< particles->position.z << " " << 0 << endl;
//			cout<<"INDEX " << index1 << "pid" << particles->id << endl; 
		        particles++;     	
			}
		   }

	  fid <<"</DataArray>\r\n";
	  fid << "\r\n";
	  fid << "</PointData>\r\n";
  	  fid << " \r\n";	  
	  fid << "<Points>\r\n" << endl;
	  fid << "<DataArray type= \"Float32\" Name = \"Position\"  NumberOfComponents= \"3\" format=\"ascii\">\r\n";
	  fid << "\r\n";
	  int index2=0; 
	  int raw2=0, col2=0;
	  for(int j=1; j<=npx; j++)
		   for(int i=1; i<=npz; i++)
		{
			if( (i != left) && (i != left+1) && (i != left+2) ||  (j > height)) 
			{
				
				index2++;
				if(j<=height)
				{
		                	 raw2=(ptr->id +1)%(npx-width);
					 col2=(int) floor((ptr->id)/(npx-width));
				}else{
			     		  raw2=(ptr->id - height*(npx-width))%npx;
					  col2=(int) floor((ptr->id - height*(npx-width))/npx) + height;
				}

				if( raw2 ==0)
				{ 
					ptr->position.x = 0.001;
					ptr->position.z = (col2)*dz;
				}else
				{	if(j<=height && i >= left+3)
					{
					ptr->position.x = (raw2-1)*dx+ dx*(width);
					ptr->position.z = col2*dz;
					}
					else{	
					ptr->position.x = (raw2-1)*dx;
					ptr->position.z = col2*dz;
				    	}	
				}
		         fid <<setprecision(6)<< ptr->position.x << " "<<setprecision(6)<< ptr->position.z << " " << 0 << endl;
   //        		 cout<<"INDEX " << index2 << "pid" << ptr->id << endl; 
			 ptr++;	
			}

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


/*	  for(int i=1; i<=npx; i++)
		  for(int j=1; j<=npz; j++)
		  {
		  	if(i==left-1 || i==left+3)
			{
				fid << i + (width+1) << " ";
	                	cout << "offest of point at i " << i << " " << j << " is +4 "<<endl; 
			}else{
				fid << i << " ";
			        cout<<"offset of point at i" << i << " " << j << endl;
		  	      }
		  }
	  fid<<"\r\n";
	  fid<<"</DataArray>\r\n";
	  fid<<"\r\n";
*/
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

