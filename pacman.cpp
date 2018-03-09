#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <iostream>

/* Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 600.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

int tick = 0;
const int REFRESH_MS = 5;
int direction = 0;
bool wrapAround = false;

void displayFcn(void);
void pacMan(int);
void timer(int value);
void arrowFunc(int, int, int);
void keyboardFunc(unsigned char, int, int);
void init(void);
void winReshapeFcn(GLint newWidth, GLint newHeight);
void updatePos(int);
void parseArgs(int argc, char **argv);


int xPos = 300;
int yPos = 300;


int main(int argc, char **argv) {
    parseArgs(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Pac Man");
    glutKeyboardFunc(keyboardFunc);
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

void keyboardFunc(unsigned char Key, int x, int y) {
    switch (Key) {
    case 'w':
        wrapAround = !wrapAround;
        std::cout << "Wraparound set to " << ((wrapAround) ? "true" : "false") << std::endl;
        break;
    };
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
    glClearColor(0, 0, 0, 0.0);
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
        if (xPos < xwcMax + 2 || wrapAround)
            xPos += SPEED;
        break;
    case 1:
        if (yPos > -2 || wrapAround)
            yPos -= SPEED;
        break;
    case 2:
        if (xPos > -2 || wrapAround)
            xPos -= SPEED;
        break;
    case 3:
        if (yPos < ywcMax + 2 || wrapAround)
            yPos += SPEED;
        break;
    };
    if (wrapAround) {
        xPos = (xPos + 600) % 600;
        yPos = (yPos + 600) % 600;
    }
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

void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0) {
            std::cout << "Wraparound enabled" << std::endl;
            wrapAround = true;
        } else {
            std::cout << "Unrecognized option: " << argv[i] << std::endl;
        }
    }
}