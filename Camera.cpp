#include "stdafx.h"
#include "Camera.h"


void Camera :: setModelViewMatrix(void) 
{ // load modelview matrix with existing camera values 
	
	Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye  
	m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u); 
	m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v); 
	m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n); 
	m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0; 
	glMatrixMode(GL_MODELVIEW); 
	glLoadMatrixf(m); // load OpenGL’s modelview matrix 
} 
void Camera::pitch(float angle) 
{ 
	float cs = cos(3.14159265/180 * angle); 
	float sn = sin(3.14159265/180 * angle); 
	Vector3 t(v); // remember old u 
	v.set(cs*t.x + sn*n.x, cs*t.y + sn*n.y, cs*t.z + sn*n.z); 
	n.set(cs*n.x - sn*t.x, cs*n.y - sn*t.y, cs*n.z - sn*t.z); 
	setModelViewMatrix(); 
} 
void Camera::yaw(float angle) 
{ 
	float cs = cos(3.14159265/180 * angle); 
	float sn = sin(3.14159265/180 * angle); 
	Vector3 t(n); // remember old u 
	n.set(cs*t.x + sn*u.x, cs*t.y + sn*u.y, cs*t.z + sn*u.z); 
	u.set(cs*u.x - sn*t.x, cs*u.y - sn*t.y, cs*u.z - sn*t.z); 
	setModelViewMatrix(); 
} 
void Camera::slide(float delU, float delV, float delN) 
{ 
	eye.x+=delU*u.x+delV*v.x+delN*n.x; 
	eye.y+=delU*u.y+delV*v.y+delN*n.y; 
	eye.z+=delU*u.z+delV*v.z+delN*n.z; 
	setModelViewMatrix(); 
} 
void Camera::setShape(float vAng, float asp, float nearD, float farD) 
{   
   glMatrixMode( GL_PROJECTION ); 
  // glLoadIdentity(); 
   gluPerspective(vAng,asp,nearD,farD); 
} 
 
void Camera:: set(Point3 Eye, Point3 look, Vector3 up) 
{	// create a modelview matrix and send it to OpenGL 
	eye.set(Eye); // store the given eye position 
    n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z); // make n 
	u.set(up.cross(n)); // make u = up X n 
	n.normalize(); 
	u.normalize(); // make them unit length 
	v.set(n.cross(u));  // make v =  n X u 
	setModelViewMatrix(); // tell OpenGL  
} 
 
void Camera :: roll(float angle) 
{ // roll the camera through angle degrees 
	float cs = cos(3.14159265/180 * angle); 
	float sn = sin(3.14159265/180 * angle); 
	Vector3 t(u); // remember old u 
	u.set(cs*t.x +sn*v.x, cs*t.y + sn*v.y, cs*t.z + sn*v.z); 
	v.set(cs*v.x -sn*t.x, cs*v.y - sn*t.y, cs*v.z - sn*t.z); 
	setModelViewMatrix(); 
} 
float* Camera::getModelview(void){
	
	return m;
}