#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx; ny = _ny; nz = _nz;

    if(nx < 0 or ny < 0 or nz < 0)
    {
        nx = 0; ny = 0; nz = 0;
    }

    //allocates X
    v = new Voxel**[nx];
    //verifies if X has been allocated
    if(v == nullptr)
    {
        cout<<"Error allocating the lines of the voxel matrix"<<endl;
        exit(0);
    }

    //allocates X's collumns
    v[0] = new Voxel*[nx*ny];
    //verifies if X[0] has been allocated
    if(v[0] == nullptr)
    {
        cout<<"Error allocating the columns of the voxel matrix"<<endl;
        exit(0);
    }

    //allocates X's planes
    v[0][0] = new Voxel[nx*ny*nz];
    //verifies if X[0] has been allocated
    if(v[0][0] == nullptr)
    {
        cout<<"Error allocating the planes of the voxel matrix"<<endl;
        exit(0);
    }


    //indexing X's collumns
    for(int i = 1; i<nx; i++){
        v[i] = v[i-1] + ny;
    }

    //indexing X's planes
    for(int i = 1; i<nx*ny; i++){
        v[0][i] = v[0][i-1] + nz;
    }

    //making every voxel invisible so we have a clean canvas
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                v[i][j][k].isOn = false;
                v[i][j][k].r = 255;
                v[i][j][k].g = 255;
                v[i][j][k].b = 255;
            }
        }
    }
}

Sculptor::~Sculptor()
{
    if(nx < 0 or ny < 0 or nz < 0)
    {
        return;
    }

    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

Voxel& Sculptor::operator ()(int i, int j, int k)
{
    if( i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
        return v[i][j][k]; //returns the address of the voxel so that we can operate on it's atributes
    }
    else{
        exit(0);
    }

}

void Sculptor::print()
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                //cout<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].r<<"  ";
                cout<<v[i][j][k].isOn<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }
}


void Sculptor::setColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;

}

void Sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = false;

}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(i>=x0 && i<=x1 &&
                   j>=y0 && j<=y1 &&
                   k>=z0 && k<=z1){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(i>=x0 && i<=x1 &&
                   j>=y0 && j<=y1 &&
                   k>=z0 && k<=z1){
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(
                        ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter)) <= radius*radius
                        ){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if( ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter)) <= radius*radius ){
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if( (((i - xcenter)*(i - xcenter))/(float)(rx*rx) + ((j - ycenter)*(j - ycenter))/(float)(ry*ry) + ((k - zcenter)*(k - zcenter))/(float)(rz*rz)) <= 1 ){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if( (((i - xcenter)*(i - xcenter))/(float)(rx*rx) + ((j - ycenter)*(j - ycenter))/(float)(ry*ry) + ((k - zcenter)*(k - zcenter))/(float)(rz*rz)) <= 1 ){
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
}

void Sculptor::writeOFF(string filename)
{
    ofstream fout;


    fout.open("./"+filename+".off");
    if(fout.is_open() == false)
    {
        cout << "arquivo nao foi aberto\n";
        exit(1);
    }

    fout<<"OFF"<<endl;

    int nvoxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    nvoxels = nvoxels+1;
                }
            }
        }
    }
    fout<<nvoxels*8<<" "<<nvoxels*6<<" 0"<<endl;

    //printing the (x,y,z) position of every vertex (there will be 8 vertices for each voxel)
    //the position of each vertex is shifted by a factor defined below (vRadius)
    //so that the total lenght of one side of the voxel is defined by vRadius*2
    //In the end, we will have each of our voxels separated by a 0.10 length gap from eachother
    float vRadius=0.45f;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<(float)i-vRadius<<" "<<(float)j+vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j-vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j-vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j+vRadius<<" "<<(float)k-vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j+vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i-vRadius<<" "<<(float)j-vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j-vRadius<<" "<<(float)k+vRadius<<endl;
                    fout<<(float)i+vRadius<<" "<<(float)j+vRadius<<" "<<(float)k+vRadius<<endl;
                }
            }
        }
    }

    fout << std::setprecision(1) << fixed;

    //printing the order of connection of 4 vertices to define a face (there will be 6 faces for each voxel)
    int vcn = 0; //vertex count for each activated vertex
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    //int vcn = vc*8; //vertex count multipled by 8, so that we jump 8 vertices in our printing every time we change voxel

                    fout<<"4 "<<vcn+0<<" "<<vcn+3<<" "<<vcn+2<<" "<<vcn+1<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+4<<" "<<vcn+5<<" "<<vcn+6<<" "<<vcn+7<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+0<<" "<<vcn+1<<" "<<vcn+5<<" "<<vcn+4<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+0<<" "<<vcn+4<<" "<<vcn+7<<" "<<vcn+3<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+3<<" "<<vcn+7<<" "<<vcn+6<<" "<<vcn+2<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<"4 "<<vcn+1<<" "<<vcn+2<<" "<<vcn+6<<" "<<vcn+5<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;

                    vcn = vcn+8;
                }
            }
        }
    }
}

void Sculptor::writeVECT(string filename)
{
    ofstream fout;

    fout.open("./"+filename+".vect");
    if(fout.is_open() == false)
    {
        cout << "arquivo nao foi aberto\n";
        exit(1);
    }

    fout<<"VECT"<<endl;

    int nvoxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    nvoxels = nvoxels+1;
                }
            }
        }
    }
    fout<<nvoxels<<" "<<nvoxels<<" "<<nvoxels<<endl;

    for(int i = 1; i<nvoxels; i++){
        fout<<"1 ";
    }
    fout<<"1"<<endl;

    for(int i = 1; i<nvoxels; i++){
        fout<<"1 ";
    }
    fout<<"1"<<endl;

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<i<<" "<<j<<" "<<k<<endl;
                }
            }
        }
    }

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                }
            }
        }
    }

}
