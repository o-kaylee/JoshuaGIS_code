#include <math.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
class Point3 
{ 
public: 
	double x; 
	double y; 
	double z; 
	void set(Point3 a) 
	{ 
		x=a.x; 
		y=a.y; 
		z=a.z; 
	} 
	Point3(double x1=0,double y1=0,double z1=0) 
	{ 
		x=x1; 
		y=y1; 
		z=z1; 
	} 
	void setPoint3(double x1=0,double y1=0,double z1=0){

		x=x1; 
		y=y1; 
		z=z1; 
	}
}; 
 
 
class Vector3 
{ 
public: 
	Vector3(double x1=0,double y1=0,double z1=0) 
	{ 
		x=x1; 
		y=y1; 
		z=z1; 
	} 
	Vector3(Vector3 &Exa) 
	{ 
		x=Exa.x; 
		y=Exa.y; 
		z=Exa.z; 
	} 
	double x; 
	double y; 
	double z; 
	double dot(Vector3 a) 
	{ 
		return(x*a.x+y*a.y+z*a.z); 
	} 
public: 
	void set(double a,double b,double c) 
	{ 
		x=a; 
		y=b; 
		z=c; 
	} 
	void set(Vector3 a) 
	{ 
		x=a.x; 
		y=a.y; 
		z=a.z; 
	} 
	Vector3 cross(Vector3 a) 
	{ 
		Vector3 m(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x); 
		return m; 
	} 
	void normalize() 
	{ 
		double m=sqrt(x*x+y*y+z*z); 
		x=x/m; 
		y=y/m; 
		z=z/m; 
	} 
}; 
 
 
 
class Camera{ 
  private: 
	Point3 eye; 
	Vector3 u,v,n; 
	double viewAngle, aspect, nearDist, farDist; // view volume shape 
	void setModelViewMatrix(void); // tell OpenGL where the camera is 
	float m[16]; 
  public: 
	Camera() 
	{ 
	}// default constructor 
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt() 
	void roll(float angle);// roll it  Ò¡°Ú½Ç  ÈÆn 
	void pitch(float angle); // increase pitch  Ñö½Ç  ÈÆu 
	void yaw(float angle); // yaw it Æ«º½½Ç   ÈÆv 
	void slide(float delU, float delV, float delN); // slide it 
	void setShape(float vAng, float asp, float nearD, float farD); 
	float* Camera::getModelview(void);
}; 
 
