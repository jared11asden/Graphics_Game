#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <Windows.h>

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
int health = 50;
const float pi = 3.14159265358979;
int phi = 0;
void timer(int time);
void drawTurtle();
void drawHealthBar(int health);
void drawDot(GLint x, GLint y)

{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

}

void drawWave() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawTurtle();
	drawHealthBar(health);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
	//for (int c = 0; c <= 10; c ++) {
	//glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_STRIP);
		for (GLfloat x = 0; x < screenWidth; x += 0.1)     // draw the plot
			glVertex2f(25 * x, 400 + 10 * sin((pi *x)+phi));
		cout << "PHi = " << phi;
		glEnd();
		//glFlush();
		glutSwapBuffers();
		phi++;
		glutTimerFunc(500, timer, 1);
		//Sleep(500);

	//}
}

void drawHealthBar(int health) {
	cout << "Health";
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8f, 0.1f, 0.0f);
	glRecti(screenWidth - 110, screenHeight - 40, screenWidth - 110 + health, screenHeight - 10);
	//glFlush();
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(screenWidth - 110, screenHeight - 40);
	glVertex2i(screenWidth - 110, screenHeight - 10);
	glVertex2i(screenWidth - 10, screenHeight - 10);
	glVertex2i(screenWidth - 10, screenHeight - 40);
	glEnd();
	//glFlush();
	//glutSwapBuffers();
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslated(400.0, screenHeight - 40.0, 1.0);
	glScaled(0.25, 0.25, 1.0);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'E');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
	glPopMatrix();
}

void drawTurtle() {
		fstream inStream;
		inStream.open("turtle.dat", ios::in);
		if (inStream.fail())
			return;
		//glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();
		glScaled(0.4, 0.4, 1.0);
		GLint numpolys, numLines, x, y;
		inStream >> numpolys;
		for (int j = 0; j < numpolys; j++) {
			inStream >> numLines;
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < numLines; i++) {
				inStream >> x >> y;
				glVertex2i(x, y);
			}
			glEnd();
		}
		glPopMatrix();
		//glFlush();
		//glutSwapBuffers();
		inStream.close();
}

void moveCharacter(int x, int y) {
	cout << "Move";
	glPushMatrix;
	glTranslated(x, y, 1);
	drawTurtle();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	//GLint x = mouseX;
	//GLint y = screenHeight - mouseY; // flip the y value as always
	switch (theKey)
	{
	case GLUT_KEY_LEFT:
		moveCharacter(-5, 0);
		break;
	case GLUT_KEY_RIGHT:
		moveCharacter(5, 0);
		break;
	case GLUT_KEY_DOWN:
		moveCharacter(0, -5);
		break;
	case GLUT_KEY_UP:
		moveCharacter(0, 5);
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

void timer(int time) {
	drawWave();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawHealthBar(health);
	drawTurtle();
	//glutTimerFunc(500, timer, 1);
	drawWave();
	//glutSwapBuffers();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Crash's Adventure");
	
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	//glutIdleFunc(myDisplay);
	myInit();
	glutMainLoop();
	return(0);
}