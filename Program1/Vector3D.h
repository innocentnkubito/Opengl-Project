#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

using namespace std;
class Vector3D {

public:
	float x;
	float y;
	float z;

	Vector3D();

	Vector3D(float, float, float);

	Vector3D operator-(const Vector3D &);

	float dotProd(const Vector3D &);

	Vector3D crossProduct(const Vector3D &);



};

ostream& operator<<(ostream& out, Vector3D vec);

#endif
