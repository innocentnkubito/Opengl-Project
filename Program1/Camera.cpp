#include <windows.h> 
#include "Vector3D.h"
#include "Camera.h"
#include "Math.h"
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

using namespace std;

Camera::Camera(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	Vector3D N, V;
	float normalN, normalVxn;
	//eye
	eye.x = a;
	eye.y = b;
	eye.z = c;
	//V
	V.x = g;
	V.y = h;
	V.z = i;

	// N
	N.x = a - d;
	N.y = b - e;
	N.z = c - f;

	// |N|
	normalN = sqrt((N.x*N.x) + (N.y*N.y) + (N.z*N.z));

	// vector n
	n.x = N.x / normalN;
	n.y = N.y / normalN;
	n.z = N.z / normalN;

	// V x n
	normalVxn= sqrt((V.crossProduct(n).x*V.crossProduct(n).x) + (V.crossProduct(n).y*V.crossProduct(n).y)
		+ (V.crossProduct(n).z*V.crossProduct(n).z));
	
	// u 
	u.x = V.crossProduct(n).x / normalVxn;
	u.y = V.crossProduct(n).y / normalVxn;
	u.z = V.crossProduct(n).z / normalVxn;

	// v
	v.x = n.crossProduct(u).x;
	v.y = n.crossProduct(u).y;
	v.z = n.crossProduct(u).z;


}

void Camera::setViewMatrixInOpenGL()
{
	float m[16];
	Vector3D eVec(eye.x, eye.y, eye.z); //eye
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eVec.dotProd(u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eVec.dotProd(v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -eVec.dotProd(n);
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);

}


void Camera::roll(float angle)
{
	float angleInRad = (angle*3.14159265359) / 180;
	float cs = cos(angleInRad);
	float sn = sin(angleInRad);

	Vector3D temp(u.x, u.y, u.z); //remember old u

	//set u
	u.x = cs*temp.x + sn*v.x;
	u.y = cs*temp.y + sn*v.y;
	u.z = cs*temp.z + sn*v.z;

	//set v
	v.x = cs*temp.x - sn*v.x;
	v.y = cs*temp.y - sn*v.y;
	v.z = cs*temp.z - sn*v.z;

	setViewMatrixInOpenGL();

}
void Camera::pitch(float angle)
{
	float angleInRad = (angle*3.14159265359) / 180;
	float cs = cos(angleInRad);
	float sn = sin(angleInRad);

	Vector3D temp(n.x, n.y, n.z); // remember old n

	//set n
	n.x = cs*temp.x + sn*v.x;
	n.y = cs*temp.y + sn*v.y;
	n.z = cs*temp.z + sn*v.z;

	//set v
	v.x = cs*temp.x - sn*v.x;
	v.y = cs*temp.y - sn*v.y;
	v.z = cs*temp.z - sn*v.z;

	setViewMatrixInOpenGL();

}
void Camera::yaw(float angle)
{
	float angleInRad = (angle*3.14159265359) / 180;
	float cs = cos(angleInRad);
	float sn = sin(angleInRad);

	Vector3D temp(u.x, u.y, u.z); //remember old u

	//set u
	u.x = cs*temp.x + sn*n.x;
	u.y = cs*temp.y + sn*n.y;
	u.z = cs*temp.z + sn*n.z;

	//set n
	n.x = cs*n.x - sn*temp.x;
	n.y = cs*n.y - sn*temp.y;
	n.z = cs*n.z - sn*temp.z;

	setViewMatrixInOpenGL();

}

void Camera::slide(float delU, float delV, float delN)
{
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	setViewMatrixInOpenGL();
}