
#include "Robot.h"
#include <windows.h> 
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

//-----Constructor----
 Robot::Robot()
{
	 armAngle = 0;
	 angInc = 1.0f;
	 lowerArmAngle = 0;
	 lowerLegAngle = 0;
	 upperArmAngle = 0;
	 upperLegAngle = 0;
	 robot_position[0] = 1.0; robot_position[4] = 0; robot_position[8] = 0; robot_position[12] = 0;
	 robot_position[1] = 0; robot_position[5] = 1.0; robot_position[9] = 0; robot_position[13] = 0;
	 robot_position[2] = 0; robot_position[6] = 0; robot_position[10] = 1.0; robot_position[14] = 0;
	 robot_position[3] = 0; robot_position[7] = 0; robot_position[11] = 0; robot_position[15] = 1.0;

  
}


 void Robot::square()
 {
	 glutSolidCube(0.15);
 }

 void Robot::torso()
 {
	 glPushMatrix();
	 glScalef(TORSO_WIDTH, TORSO_HEIGHT, 2);
	 square();
	 glPopMatrix();
 }

 void Robot::head()
 {
	 glPushMatrix();
	 float mat_redAmbient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_redAmbient);
	 glScalef(HEAD_SIZE, HEAD_SIZE, 1.0 );
	 square();
	 glPopMatrix();
 }

 void Robot::upperArm()
 {
	 glPushMatrix();

	glScalef(UPPER_ARM_LEN, UPPER_ARM_THICK,1.5 );
	square();
	glPopMatrix();

 }
 
 void Robot::lowerArm()
 {
	 glPushMatrix();

	 glScalef(LOWER_ARM_LEN, LOWER_ARM_THICK, 1);	
	 square();
	 glPopMatrix(); 

 }

 void Robot::lowerLeg()
 {

	 glPushMatrix();

	 glScalef(LOWER_LEG_LEN, LOWER_LEG_THICK, 1.1);
	 square();
	 glPopMatrix();
 }
 
 void Robot::upperLeg()
 {
	 glPushMatrix();

	 glScalef(UPPER_LEG_LEN, UPPER_LEG_THICK, 1.5);
	 square();
	 glPopMatrix();
 }


