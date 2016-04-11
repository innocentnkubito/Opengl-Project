#include <iostream>
#include "Vector3D.h"

using namespace std;

Vector3D::Vector3D(){
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

float  Vector3D::dotProd(const Vector3D &vec)
{
	float result;
	result = (x*vec.x) + (y*vec.y) + (z*vec.z);

	return result;
}

Vector3D Vector3D::crossProduct(const Vector3D &vec){
	Vector3D vect;
	vect.x = (y * vec.z) - (z * vec.y);
	vect.y = (z * vec.x) - (x * vec.z);
	vect.z = (x * vec.y) - (y * vec.x);
	/*vect.x = ((vec.y*this->z) - (vec.z*this->y));
	vect.y = ((vec.z*this->x) - (vec.x*this->z));
	vect.z = ((vec.x*this->y) - (vec.y*this->x));*/
	return vect;
}

Vector3D Vector3D:: operator-(const Vector3D&vec)
{
	Vector3D vect;
	vect.x = (x - vec.x);
	vect.y = (y - vec.y);
	vect.z = (z - vec.z);
	return vect;
}

ostream& operator<<(ostream& out, Vector3D vec)
{
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

