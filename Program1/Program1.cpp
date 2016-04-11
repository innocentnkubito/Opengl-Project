// FINAL PROJECT
//INNOCENT NKUBITO
//12/14/15
#include <windows.h> 
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <GL/glui.h>
#include <iostream>
#include "Camera.h"
#include "Vector3D.h"
#include "Robot.h"

using namespace std;

int   SCREEN_WIDTH = 740;
int   SCREEN_HEIGHT = 580;
const int axisLength = 2;
bool turnOnAxes = true;

//Lookat variables
float cameraPos_x = -5, cameraPos_y = 5, cameraPos_z = 5;
float lookAt_x = 0, lookAt_y = 0, lookPos_z = 0;
float upVec_x = 0, upVec_y = 1, upVec_z = 0;

//Perspective variables
float fovy = 50.0;
float nearPlane = 1.0;
float farPlane = 60.0;
float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;


Camera cam(cameraPos_x, cameraPos_y, cameraPos_z, lookAt_x, lookAt_y, lookPos_z, upVec_x, upVec_y, upVec_z);
Robot robby;

// Init fn -------------------------------------------------------------------------------------
void myinit()
{
	
	float white[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float lightPos[] = { 4.5f, 4.5f, 4.5f, 1.0f };
	// turn on lighting/shading
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    

}
// Axis - ------------------------------------------------------------------------------------------------
void axis(double length)
{
	const float CONE_LENGTH = .09;
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();
	
	glTranslated(0, 0, length - CONE_LENGTH);

	glutSolidCone(CONE_LENGTH / 2, CONE_LENGTH, 10,5);

	glPopMatrix();
}

//cube with a textured top -------------------------------------------------------------------------
void cube()
{
	GLubyte texels[32] =
	{
		0, 0, 0, 255,
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 255, 255,
		255, 255, 0, 255,
		0, 255, 255, 255,
		255, 0, 255, 255,
	};

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(0.0, 1.0); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(1.0, 1.0); glVertex3f(.5f, .5f, -.5f);
	glTexCoord2f(1.0, 0.0); glVertex3f(.5f, .5f, .5f);


	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 1.0); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(0.0, 0.0); glVertex3f(-.5f, -.5f, -.5f);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(1.0, -2.0); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(-2.0, -2.0); glVertex3f(-.5f, -.5f, -.5f);
	glTexCoord2f(-2.0, 1.0); glVertex3f(-.5f, -.5f, .5f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2.0); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(2.0, 0.0); glVertex3f(.5f, -.5f, .5f);
	glTexCoord2f(0.0, -2.0); glVertex3f(-.5f, -.5f, .5f);
	glTexCoord2f(-2.0, 0.0); glVertex3f(-.5f, .5f, .5f);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(1.0, 0.0); glVertex3f(.5f, .5f, -.5f);
	glTexCoord2f(1.0, 1.0); glVertex3f(.5f, -.5f, -.5f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-.5f, -.5f, -.5f);
	glEnd();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-.5f, .5f, -.5f);
	glTexCoord2f(0, 1.0); glVertex3f(-.5f, .5f, .5f);
	glTexCoord2f(1.0, 1.0); glVertex3f(.5f, .5f, .5f);
	glTexCoord2f(1.0, 0.0); glVertex3f(.5f, .5f, -.5f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	
}


//----------------------------------Solid objects :: Cylinder & Textured Cube---------------------------------------------------------
void solidObjects()
{

	glPushMatrix();
	
	float Kolo[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kolo);

	glRotated(90, 1, 0, 0);
	glTranslated(3.5,-8.5, 1.3);
	GLUquadricObj * cyl;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluCylinder(cyl, .5, .5, 1.5, 10, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(.5, .5, .4);
	glTranslated(-1, -1, -1);
	float Kolor[] = { .79, .52, .09, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kolor);
	cube();
	glPopMatrix();

}

// Draw axes-------------------------------------------------------------------------------------

void drawAxes()
{
	glPushMatrix();

	float mat_redAmbient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_redAmbient);
	

	axis(axisLength);

	glRotated(90, 0, 1.0, 0);
	axis(axisLength);

	glRotated(-90.0, 1, 0, 0);
	axis(axisLength);

	glPopMatrix();
}

// -------------Draw Grid----------------------------------
void drawGrid()
{
	glPushMatrix();
	float mat_whiteAmbient[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_whiteAmbient);

	glColor3f(1.0, 1.0, 1.0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_LINES);
	for (GLfloat i = -15.5; i <= 15.5; i += 0.25) {
		glVertex3f(i, 0, 15.5); glVertex3f(i, 0, -15.5);
		glVertex3f(15.5, 0, i); glVertex3f(-15.5, 0, i);
	}
	glEnd();

	 
	glPopMatrix();
}

//-------------Draw Robot------------------------------------------------------------
void drawRobot(){

	
	//TORSO
	glPushMatrix();
	float Kolo[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kolo);
	glTranslatef(0, 1.5, 0);
	robby.torso(); 
	glPopMatrix();

	//HEAD
	glPushMatrix();
	float Kol[] = { 0.0f, 0.8f, 0.6f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kol);
	glTranslatef(0, 2.4, 0);

	robby.head();
	glPopMatrix();

	glPushMatrix();
	
	// ARMS
	glRotated(-90, 0, 0,1 );
    glRotatef(robby.upperArmAngle, 0, 1, 0);
	glTranslatef(-1.5, .5, 0);
	robby.upperArm();
	glRotatef(1*robby.lowerArmAngle, 0, 1, 0);		
	glTranslatef(0.75,.05, 0);
	robby.lowerArm();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glRotatef(robby.upperArmAngle, 0, 1, 0);
	glTranslatef(1.5, .5, 0);
	robby.upperArm();
	glRotatef(-1 * robby.lowerArmAngle, 0, 1, 0);
	glTranslatef(-0.75, .05, 0);
	robby.lowerArm(); 
	glPopMatrix();
	
	//LEGS
	glPushMatrix();
	float Kols[] = { 0.5f, 0.8f, 0.6f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kols);
	glRotated(90, 0, 0, 1);
	glRotatef(robby.upperLegAngle, 0, 1,0);
	glTranslatef(.55, 0.25, 0);
	robby.upperLeg();
	float Kolso[] = { 0.9f, 0.5f, 0.6f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kolso);
	glRotatef(robby.lowerLegAngle, 0, 1, 0);
	glTranslatef(-.45, 0, 0.0);
	robby.lowerLeg();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kols);
	glRotated(90, 0, 0, 1);
	glRotatef(-robby.upperLegAngle, 0, 1, 0);
	glTranslatef(.55, -0.25, 0);
	robby.upperLeg();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Kolso);
	glRotatef(-robby.lowerLegAngle, 0, 1, 0);
	glTranslatef(-.45, 0,0 );
	robby.lowerLeg();
	glPopMatrix();


	
}


//---------------------display------------------------------
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, nearPlane, farPlane); // set camera shape


	
	cam.setViewMatrixInOpenGL();
	glPushMatrix();
	drawGrid();
	if (turnOnAxes)
		drawAxes();

	solidObjects();
	
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(robby.robot_position);
	glEnable(GL_DEPTH_TEST);
	drawRobot();

	glDisable(GL_DEPTH_TEST);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

// ASCII keyhandler function
void keyboard (GLubyte key, GLint x, GLint y){
	float rollAngle = 135;
	float pitchAngle = 45;
	float yawAngle = 1;
	float slideUnits = .5f;
	switch (key)
	{
	case 'r':
			cam.roll(rollAngle);
			glutPostRedisplay(); // trigger the screen redisplay
	
		break;
	 case 'p':
		 cam.pitch(pitchAngle);
		 glutPostRedisplay(); // trigger the screen redisplay
		 break;
	 case 'y':
		 cam.yaw(yawAngle);
		 glutPostRedisplay(); // trigger the screen redisplay
		 break;
	 case 's':
		 cam.slide(slideUnits, 0, 0);
		 glutPostRedisplay();
		 break;
	 case 'd':
		 cam.slide(0,slideUnits, 0);
		 glutPostRedisplay();
		 break;
	 case 'f':
		 cam.slide(0,0,slideUnits);
		 glutPostRedisplay();
		 break;
	 case 'g':
		 cam.slide(-slideUnits, 0, 0);
		 glutPostRedisplay();
		 break;
	 case 'h':
		 cam.slide(0, -slideUnits, 0);
		 glutPostRedisplay();
		 break;
	 case 'j':
		 cam.slide(0, 0, -slideUnits);
		 glutPostRedisplay();
		 break;

	 case 'o':
		 turnOnAxes = false;
		 glutPostRedisplay();
		 break;
	 case 'n':
		 turnOnAxes = true;
		 glutPostRedisplay();
		 break;

	

	  default:
		  ;
	}
}

//Arrow keyhandler function

void keyboardfunc(GLint key, GLint x, GLint y)
{
	float translateUnits = 0.1;
	float rotateUnits = 1;

	switch (key)
	{
	 case GLUT_KEY_DOWN :
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(robby.robot_position);
		glTranslatef(0, 0, translateUnits);
		glGetFloatv(GL_MODELVIEW_MATRIX, robby.robot_position);
		glPopMatrix();
		if (robby.upperArmAngle < 5 || robby.lowerArmAngle <5 || robby.upperLegAngle < 15 || robby.lowerLegAngle < 15)
		{
			robby.upperArmAngle += robby.angInc;
			robby.lowerArmAngle += robby.angInc;
			robby.upperLegAngle += robby.angInc;
			robby.lowerLegAngle += robby.angInc;
		}
		else
		{
			robby.upperArmAngle = 0;
			robby.lowerArmAngle = 0;
			robby.upperLegAngle = 0;
			robby.lowerLegAngle = 0;
		}


		glutPostRedisplay();
		break; 
	 case GLUT_KEY_UP:
		 glMatrixMode(GL_MODELVIEW);
		 glPushMatrix();
		 glLoadMatrixf(robby.robot_position);
		 glTranslatef(0, 0, -translateUnits);
		 glGetFloatv(GL_MODELVIEW_MATRIX, robby.robot_position);
		 glPopMatrix();
		 if (robby.upperArmAngle < 5 || robby.lowerArmAngle <5 || robby.upperLegAngle < 15 || robby.lowerLegAngle < 15)
		 {
			 robby.upperArmAngle += robby.angInc;
			 robby.lowerArmAngle += robby.angInc;
			 robby.upperLegAngle += robby.angInc;
			 robby.lowerLegAngle += robby.angInc;
		 }
		 else
		 {
			 robby.upperArmAngle = 0;
			 robby.lowerArmAngle = 0;
			 robby.upperLegAngle = 0;
			 robby.lowerLegAngle = 0;
		 }
		 glutPostRedisplay();
		 break;
	 case GLUT_KEY_RIGHT:
		 glMatrixMode(GL_MODELVIEW);
		 glPushMatrix();
		 glLoadMatrixf(robby.robot_position);
		 glRotatef(rotateUnits,0, 1, 0);
		 glGetFloatv(GL_MODELVIEW_MATRIX, robby.robot_position);
		 glPopMatrix();
		 glutPostRedisplay();
		 break;
	 case GLUT_KEY_LEFT:
		 glMatrixMode(GL_MODELVIEW);
		 glPushMatrix();
		 glLoadMatrixf(robby.robot_position);
		 glRotatef(-rotateUnits, 0, 1, 0);
		 glGetFloatv(GL_MODELVIEW_MATRIX, robby.robot_position);
		 glPopMatrix();
		 glutPostRedisplay();
		 break;

	  default:;

	}
}


void callBack(int id)
{
	/*switch (id)
	{
		default;
	}*/
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	int mainWindow= glutCreateWindow("FINAL PROJECT");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background white
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	

	
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardfunc);
	

	GLUI *gluiMaster = GLUI_Master.create_glui("Controls", 0.0, 855, 300);
	GLUI_Panel *pnl = new GLUI_Panel(gluiMaster, "Perspective");
	GLUI_EditText *nearPlan = new GLUI_EditText(pnl, "Near Plane", GLUI_EDITTEXT_FLOAT,&nearPlane,5,(GLUI_Update_CB)callBack);
	GLUI_EditText *farPlan = new GLUI_EditText(pnl, "Far Plane", GLUI_EDITTEXT_FLOAT, &farPlane, 6, (GLUI_Update_CB)callBack);
	GLUI_EditText *viewAngle = new GLUI_EditText(pnl, "View Angle", GLUI_EDITTEXT_FLOAT, &fovy, 7, (GLUI_Update_CB)callBack);
	GLUI_StaticText *b = new GLUI_StaticText(pnl, "Press r key to roll");
	GLUI_StaticText *c = new GLUI_StaticText(pnl, "Press p key to pitch");
	GLUI_StaticText *d = new GLUI_StaticText(pnl, "Press y key to yaw");
	GLUI_StaticText *e = new GLUI_StaticText(pnl, "Press s,d,f,g,h,j to slide");
	GLUI_StaticText *f = new GLUI_StaticText(pnl, "Press o to turn off axes");
	GLUI_StaticText *g = new GLUI_StaticText(pnl, "Press n to turn o axes");




	gluiMaster->set_main_gfx_window(mainWindow);

	glutMainLoop();
}