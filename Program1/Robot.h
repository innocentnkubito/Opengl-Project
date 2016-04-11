#ifndef ROBOT_H
#define ROBOT_H


class Robot {

public:

	float armAngle;
	float angInc ;
	float robot_position[16];
	const float TORSO_WIDTH = 5, TORSO_HEIGHT=10;
	const float HEAD_SIZE=2.5;
	const float MAX_ARM_ANGLE= 15 ;
	const float UPPER_ARM_LEN=5, UPPER_ARM_THICK=1.5, LOWER_ARM_LEN=5, LOWER_ARM_THICK= 1.25;
	const float UPPER_LEG_LEN = 3, UPPER_LEG_THICK = 1.5, LOWER_LEG_LEN = 3.0, LOWER_LEG_THICK = 1.5;
	float lowerArmAngle, upperArmAngle, lowerLegAngle, upperLegAngle;


	Robot();
	void square();
	void torso();
	void head();
	void upperArm();
	void lowerArm();
	void upperLeg();
	void lowerLeg();
	


};





#endif