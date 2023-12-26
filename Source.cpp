#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int selectedOption = 1;
GLsizei windowWidth = 1000;
GLsizei windowHeight = 1000;
GLuint id;
GLubyte colours[6][3];
GLfloat angle = 60.0;
GLfloat size = 1.0;
GLboolean grow = true;
GLint a = 6;
GLint b = 90;
GLint radius = 20;

#define M_PI 3.14159265358979323846

void menu(int menuOption) {
	if (menuOption == 1) selectedOption = 1;
	if (menuOption == 2) selectedOption = 2;
	glutPostRedisplay();
}

void myinit(void)
{	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	
	for (int i = 0; i < 6; i++) {
		colours[i][0] = rand() % 255;
		colours[i][1] = rand() % 255;
		colours[i][2] = rand() % 255;
	}
	
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
	glEndList();

	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Spin around self (a)", 1);
	glutAddMenuEntry("Orbit (b)", 2);
	
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int newWidth, int newHeight) {
	glutReshapeWindow(1000, 1000);
}

void idle(void) {
	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	angle += 0.5f;
	if (angle > 360.0) {
		angle = 0.0;
	}
	if (size >= 2) {
		grow = false;
	}
	else if (size < 1) {
		grow = true;
	}
	if (grow) {
		size += 0.005f;
	}
	else {
		size -= 0.005f;
	}
	
	

	if (selectedOption == 1) {
		glTranslatef(0, 0, -b);
		glRotatef(angle, 1.0, 0.0, 1.0);
		glScalef(a * size, a * size, a * size);
	}
	
	if (selectedOption == 2) {
		glTranslatef(sin(angle * M_PI / 180) * radius, cos(angle * M_PI / 180) * radius, -2 * b / 10.0);
		glRotatef(angle, 1.0, 0.0, 1.0);
		//glTranslatef(0, 0, -8 * b / 10.0);
		glScalef(a * size, a * size, a * size);
	}
	
	glPushMatrix();//FRONT
	glColor3ub(colours[0][0], colours[0][1], colours[0][2]);
	glCallList(id);
	glPopMatrix();
	
	glPushMatrix();//RIGHT
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3ub(colours[1][0], colours[1][1], colours[1][2]);
	glCallList(id);
	glPopMatrix();

	glPushMatrix();//LEFT
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glColor3ub(colours[2][0], colours[2][1], colours[2][2]);
	glCallList(id);
	glPopMatrix();

	glPushMatrix();//UP
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3ub(colours[3][0], colours[3][1], colours[3][2]);
	glCallList(id);
	glPopMatrix();

	glPushMatrix();//DOWN
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glColor3ub(colours[4][0], colours[4][1], colours[4][2]);
	glCallList(id);
	glPopMatrix();

	glPushMatrix();//BACK
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glColor3ub(colours[5][0], colours[5][1], colours[5][2]);
	glCallList(id);
	glPopMatrix();

	glutSwapBuffers();
}

void main(int argc, char** argv)
{

	/* Standard GLUT initialization */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /* default, not needed */
	glutInitWindowSize(windowWidth, windowHeight); /* 500 x 500 pixel window */
	glutInitWindowPosition(0, 0); /* place window top left on display */
	glutCreateWindow("2nd_Project"); /* window title */

	glDrawBuffer(GL_BACK);
	myinit(); /* set attributes */
	glutDisplayFunc(display); /* display callback invoked when window opened */
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop(); /* enter event loop */
}