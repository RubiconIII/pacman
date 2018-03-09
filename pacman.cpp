#include <GL/glut.h>
#include <cmath>
#include <iostream>

/* Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 600.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

int tick = 0;
const int REFRESH_MS = 5;
int direction = 0;

void displayFcn(void);
void pacMan(int);
void timer(int value);
void arrowFunc(int, int, int);
void init(void);
void winReshapeFcn(GLint newWidth, GLint newHeight);
void updatePos(int);

int xPos = 300;
int yPos = 300;


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pac Man");
	glutSpecialFunc(arrowFunc);

	init();

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}

void displayFcn(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(xPos, yPos, 0);

	pacMan(direction);
	updatePos(direction);

	glPopMatrix();
	glFlush();
	tick++;	

}

void timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(REFRESH_MS, timer, 0); // next timer call milliseconds later
}


void arrowFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		direction = 3;
		break;
	case GLUT_KEY_DOWN:
		direction = 1;
		break;
	case GLUT_KEY_LEFT:
		direction = 2;
		break;
	case GLUT_KEY_RIGHT:
		direction = 0;
		break;
	}
}


void init(void) {
	/* Set color of display window to white. */
	glClearColor(0.5, 0.5, 1, 0.0);
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

void updatePos(int direction) {
	const int SPEED = 1;
	switch (direction) {
	case 0:
		if(xPos < xwcMax) xPos += SPEED;
		break;
	case 1:
		if (yPos > 0) 	yPos -= SPEED;
		break;
	case 2:
		if (xPos > 0) xPos -= SPEED;
		break;
	case 3:
		if (yPos < ywcMax) yPos += SPEED;
		break;
	};
}

void pacMan(int direction) {
	int r = 50;

	glPushMatrix();
	while (direction--) {
		glRotatef(90, 0, 0, -1);
	}
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	int detail = 30;
	int startPoint = 15 * sin(tick / 15);
	for (int i = 0; i < detail; i++) {
		double deg = (i * (360 - 2 * startPoint) / detail) + startPoint;
		double x = r * cos(deg * 3.14 / 180);
		double y = r * sin(deg * 3.14 / 180);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}