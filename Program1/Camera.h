#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3D.h"


class Camera {
	
public:
	    Vector3D n, u, v,eye;
		
		
		Camera(float, float, float, float, float, float,float,float,float);

		void setViewMatrixInOpenGL();

		void roll(float);

		void pitch(float);

		void yaw(float);

		void slide(float,float,float);



};












#endif