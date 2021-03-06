#include <pch.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

typedef long double ld;
using namespace std;

const ld PI = acos(-1);
int vert;
ld angle, x, y, m;

void render() {
	if (vert)	cout << vert << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_POLYGON);

	angle = 90.0;
	x = 0.0, y = 1.0;

	for (int i = 0; i < vert; i++) {
		glVertex2d(x, y);

		angle += (360.0 / vert);
		if (angle >= 360)	angle -= 360;

		if (angle == 90)	x = 0.0, y = 1.0;
		else if (angle == 270)	x = 0.0, y = -1.0;
		else {
			m = tanl(angle*PI / 180.0);
			x = abs(sqrtl(1.0 / (1 + m * m)));
			if (angle > 90 && angle < 270)
				x *= -1;
			y = x * m;
		}
	}

	glEnd();
	glutSwapBuffers();
}

void handleKeyPress(unsigned char key, int x, int y) {
	if (key == 27)	exit(0);	//Escape will terminate the program

	if (key >= '3' && key <= '9')	vert = key - '0';//a number will draw a polygon of 'key' vertices 
	else if (key >= 'a' && key <= 'z')	vert = key - 'a' + 10;//a small character will draw a polygon of 10 or more vertices 
	else	return;// unvalid key press won't do anything

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Assignment 1");
	glutKeyboardFunc(handleKeyPress);
	glutDisplayFunc(render);
	glutMainLoop();
}