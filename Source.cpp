#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>

using namespace std;

int	screenWidth = 640, screenHeight = 480;

struct GLintPoint {
	GLint x, y;
};

class Point2
{
public:
	float x, y;
	void set(float dx, float dy) { x = dx; y = dy; }
	void set(Point2& p) { x = p.x; y = p.y; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	Point2() { x = y = 0; }
};

void myInit(void) {
	glClearColor(0.0f, .55f, 0.62f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
}

Point2 mouseClick[2];
int health = 100;
const float pi = 3.14159265358979;

void drawDot(GLint x, GLint y)

{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

}

void drawWave() {
	//Sleep(1000);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(3.0);
	for (int c = 0; c <= 100; c += 10) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_STRIP);
		for (GLfloat x = 0; x < screenWidth; x += 0.1)     // draw the plot
			glVertex2f(c+ 25 * x, 400 + 10 * sin(pi * x));
		glEnd();
		glFlush();
		Sleep(1000);

	}
}

void drawHealthBar(int health) {
	cout << "Health";
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.8f, 0.1f, 0.0f);
	glRecti(screenWidth - 110, screenHeight - 40, screenWidth - 110 + health, screenHeight - 10);
	glFlush();
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(screenWidth - 110, screenHeight - 40);
	glVertex2i(screenWidth - 110, screenHeight - 10);
	glVertex2i(screenWidth - 10, screenHeight - 10);
	glVertex2i(screenWidth - 10, screenHeight - 40);
	glEnd();
	glFlush();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
}

void moveCharacter(int x, int y) {
	cout << "Move";
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	GLint x = mouseX;
	GLint y = screenHeight - mouseY; // flip the y value as always
	switch (theKey)
	{
	case GLUT_KEY_LEFT:
		moveCharacter(x, y);
		break;
	case 'E':
		exit(-1);		//terminate the program		
	default:
		break;		      // do nothing
	}
}

void myMouse(int button, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			glPointSize(6.0);
			mouseClick[0].x = x;
			mouseClick[0].y = screenHeight - y;
			glBegin(GL_POINTS); {
				glVertex2i(mouseClick[0].x, mouseClick[0].y);
			}
			glEnd();
			glFlush();

		}
	}

}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//drawWave();
	drawHealthBar(health);
	//glFlush();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Crash's Adventure");

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0, screenWidth, 0, screenHeight);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	drawWave();
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

}