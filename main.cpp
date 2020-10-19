#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double px=0.39;
double py=0.33;

void line(std::ofstream& file, string layer, int color, double x1, double y1, double z1, double x2, double y2, double z2)
{// file, fólia, szín, koordináták
	file <<
	"\n  0\n"<<
	"LINE\n" <<
	"  8\n"	 << layer <<
	"\n 62\n"<< color <<
	"\n 10\n"<< x1 <<
	"\n 20\n"<< y1 <<
	"\n 30\n"<< z1 <<
	"\n 11\n"<< x2 <<
	"\n 21\n"<< y2 <<
	"\n 31\n"<< z2;
	return;
}

double xf(double a, int i, int n) {return i*a/n-a/2;}
double yf(double b, int j, int m) {return j*b/m-b/2;}
double zf(double a, double b, double c, double x, double y) {return (2*c)/(a*b)*x*y;}
double xoff(double x, double y, double off, double a, double b, double c) {return x            -(y*2*c/(a*b)/sqrt((4*c*c)/(a*a*b*b)*(x*x+y*y)+1))*off;}
double yoff(double x, double y, double off, double a, double b, double c) {return y            -(x*2*c/(a*b)/sqrt((4*c*c)/(a*a*b*b)*(x*x+y*y)+1))*off;}
double zoff(double x, double y, double off, double a, double b, double c) {return zf(a,b,c,x,y)+(          1/sqrt((4*c*c)/(a*a*b*b)*(x*x+y*y)+1))*off;}

void dxf_generator( double a, double b, double c, int n, int m)
{
	stringstream par;
    par
    << "a=" << a << "_b=" << b << "_c=" << c << "_n=" << n << "_m=" << m;
	ofstream f((par.str()+".dxf").c_str());
	//ifstream eleje; eleje.open("dxf_eleje.txt"); char ch; while(eleje.get(ch)) f << ch; eleje.close();
	f << "  0\nSECTION\n  2\nENTITIES";
	for(int i=0; i<=n ; i++)
	{
		for(int j=0; j<=m ; j++)
		{
			double x=xf(a,i,n);
			double y=yf(b,j,m);
			double z1=zf(a,b,c,x,y);
			double z2=zf(a,b,c,x    ,y+b/m);
			double z3=zf(a,b,c,x+a/n,y    );
			double z4=zf(a,b,c,x+a/n,y+b/m);

			if(j==0 || j==m)
				if(j==0)
				{line(f, "per_x_m",9,x,y-px,z1,/**/x    ,y,   z1);}
				else
				{line(f, "per_x_m",9,x,y+px,z1,/**/x    ,y,   z1);}
			if(i!=n)
			{
				if(j==0 || j==m)
					if(j==0)
					{line(f, "0"      ,4,x,y   ,z1,/**/x+a/n,y   ,z3);
					 line(f, "perem_x",5,x,y-px,z1,/**/x+a/n,y-px,z3);}

					else
					{line(f, "0"      ,4,x,y   ,z1,/**/x+a/n,y   ,z3);
					 line(f, "perem_x",5,x,y+px,z1,/**/x+a/n,y+px,z3);}
				else
				{
				line(f, "0"      ,4,xoff(x,y,0    ,a,b,c), yoff(x,y,    0,a,b,c), zoff(x,y,0    ,a,b,c),/**/xoff(x+a/n,y,    0,a,b,c),yoff(x+a/n,y,    0,a,b,c),zoff(x+a/n,y,    0,a,b,c));
				line(f, "x"      ,0,xoff(x,y,-0.03,a,b,c), yoff(x,y,-0.03,a,b,c), zoff(x,y,-0.03,a,b,c),/**/xoff(x+a/n,y,-0.03,a,b,c),yoff(x+a/n,y,-0.03,a,b,c),zoff(x+a/n,y,-0.03,a,b,c));
				line(f, "x_t"      ,0,xoff(x,y, 0.09,a,b,c), yoff(x,y, 0.09,a,b,c), zoff(x,y, 0.09,a,b,c),/**/xoff(x+a/n,y, 0.09,a,b,c),yoff(x+a/n,y, 0.09,a,b,c),zoff(x+a/n,y, 0.09,a,b,c));
				}
			}
			if(i==0 || i==n)
				if(i==0)
				{line(f, "per_y_m",9,x-py,y,z1,/**/x   ,y    ,z1);}
				else
				{line(f, "per_y_m",9,x+py,y,z1,/**/x   ,y    ,z1);}			
			if( j!=m)
			{
				if(i==0 || i==n)
					if(i==0)
					{line(f, "0"      ,4,x   ,y,z1,/**/x   ,y+b/m,z2);
					 line(f, "perem_y",5,x-py,y,z1,/**/x-py,y+b/m,z2);}
					else
					{line(f, "0"      ,4,x   ,y,z1,/**/x   ,y+b/m,z2);
					 line(f, "perem_y",5,x+py,y,z1,/**/x+py,y+b/m,z2);}
				else
				{
				line(f, "0"      ,4,xoff(x,y,    0,a,b,c), yoff(x,y,    0,a,b,c), zoff(x,y,    0,a,b,c),/**/xoff(x,y+b/m,    0,a,b,c), yoff(x,y+b/m,    0,a,b,c), zoff(x,y+b/m,    0,a,b,c));
				line(f, "y"      ,2,xoff(x,y, 0.03,a,b,c), yoff(x,y, 0.03,a,b,c), zoff(x,y, 0.03,a,b,c),/**/xoff(x,y+b/m, 0.03,a,b,c), yoff(x,y+b/m, 0.03,a,b,c), zoff(x,y+b/m, 0.03,a,b,c));
				line(f, "y"      ,2,xoff(x,y,-0.09,a,b,c), yoff(x,y,-0.09,a,b,c), zoff(x,y,-0.09,a,b,c),/**/xoff(x,y+b/m,-0.09,a,b,c), yoff(x,y+b/m,-0.09,a,b,c), zoff(x,y+b/m,-0.09,a,b,c));
				}
			}

			if(i!=n && j!=m)
			{
				line(f, "0"      ,4,xoff(x,y,          0,a,b,c), yoff(x,y,          0,a,b,c), zoff(x,y,          0,a,b,c),/**/xoff(x+a/n,y+b/m,      0,a,b,c), yoff(x+a/n,y+b/m,      0,a,b,c), zoff(x+a/n,y+b/m,      0,a,b,c));
				line(f, "kotel"  ,3,xoff(x,y,    -5*0.03,a,b,c), yoff(x,y,    -5*0.03,a,b,c), zoff(x,y,    -5*0.03,a,b,c),/**/xoff(x+a/n,y+b/m,-5*0.03,a,b,c), yoff(x+a/n,y+b/m,-5*0.03,a,b,c), zoff(x+a/n,y+b/m,-5*0.03,a,b,c));
				line(f, "kotel"  ,3,xoff(x,y+b/m,-5*0.03,a,b,c), yoff(x,y+b/m,-5*0.03,a,b,c), zoff(x,y+b/m,-5*0.03,a,b,c),/**/xoff(x+a/n,y,    -5*0.03,a,b,c), yoff(x+a/n,y,    -5*0.03,a,b,c), zoff(x+a/n,y,    -5*0.03,a,b,c));
			}
				
			if(j!=0 && j!=m)
			{
				line(f, "csavar_1",1,xoff(x,y, 3*0.03,a,b,c), yoff(x,y, 3*0.03,a,b,c), zoff(x,y, 3*0.03,a,b,c),/**/xoff(x,y, 2*0.03,a,b,c), yoff(x,y, 2*0.03,a,b,c), zoff(x,y, 2*0.03,a,b,c));
				line(f, "csavar_2",1,xoff(x,y, 2*0.03,a,b,c), yoff(x,y, 2*0.03,a,b,c), zoff(x,y, 2*0.03,a,b,c),/**/xoff(x,y, 1*0.03,a,b,c), yoff(x,y, 1*0.03,a,b,c), zoff(x,y, 1*0.03,a,b,c));
			}

			if(!((i==0 && (j==0 || j==m)) || (i==n && (j==0 || j==m))))
				line(f, "csavar_3",1,xoff(x,y, 1*0.03,a,b,c), yoff(x,y, 1*0.03,a,b,c), zoff(x,y, 1*0.03,a,b,c),/**/xoff(x,y, 0*0.03,a,b,c), yoff(x,y, 0*0.03,a,b,c), zoff(x,y, 0*0.03,a,b,c));
																					
				line(f, "csavar_4",1,xoff(x,y,-1*0.03,a,b,c), yoff(x,y,-1*0.03,a,b,c), zoff(x,y,-1*0.03,a,b,c),/**/xoff(x,y, 0*0.03,a,b,c), yoff(x,y, 0*0.03,a,b,c), zoff(x,y, 0*0.03,a,b,c));

				line(f, "csavar_5",1,xoff(x,y,-2*0.03,a,b,c), yoff(x,y,-2*0.03,a,b,c), zoff(x,y,-2*0.03,a,b,c),/**/xoff(x,y,-1*0.03,a,b,c), yoff(x,y,-1*0.03,a,b,c), zoff(x,y,-1*0.03,a,b,c));
				line(f, "csavar_6",1,xoff(x,y,-3*0.03,a,b,c), yoff(x,y,-3*0.03,a,b,c), zoff(x,y,-3*0.03,a,b,c),/**/xoff(x,y,-2*0.03,a,b,c), yoff(x,y,-2*0.03,a,b,c), zoff(x,y,-2*0.03,a,b,c));
														
				line(f, "csavar_0",1,xoff(x,y,-5*0.03,a,b,c), yoff(x,y,-5*0.03,a,b,c), zoff(x,y,-5*0.03,a,b,c),/**/xoff(x,y,-3*0.03,a,b,c), yoff(x,y,-3*0.03,a,b,c), zoff(x,y,-3*0.03,a,b,c));
		}

	}
	f << "\n  0\nENDSEC\n  0\nEOF";
	f.close();
	return;
}
int main (void)
{
	double a=14.4; double b=10.8;
	for(double c=5;c<6; c+=1)
	{
		for (int n=16;n<17;n++)
		{ if(n!=16 && n!=16 && n!=16) {continue;}
			for (int m=12;m<17;m++)
			{ if(m!=12 && m!=12 && m!=12) {continue;}
				dxf_generator(a,b,c,n,m);
			}
		}
	}
	return 1;
}