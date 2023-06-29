#include <GL/glut.h>
#include <math.h>
#include <ctime>

const float PI = 3.14159265358979323846f;
const int REFRESH_TIME = 1000;
float speed = 1.0f; // the current speed of the clock

float angleHour, angleMin, angleSec, clockR = 80.0f, angle1min = PI / 30.0f, minStart = 0.9f, minEnd = 1.0f, stepStart = 0.8f, stepEnd = 1.0f;

void init() {
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-150, 150, -100, 100, -100, 100);
}

void numbers() {
    glRasterPos2i(58, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
    glRasterPos2i(0, -60);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
    glRasterPos2i(-62, -2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '9');
    glRasterPos2i(-2, 57);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
    glRasterPos2i(1, 57);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    for (int i = 0; i < 60; i++) {
        float c = cos(i * angle1min), s = sin(i * angle1min);
        if (i % 5) {
            if (i % 5 == 1)
                glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(clockR * minStart * c, clockR * minStart * s);
            glVertex2f(clockR * minEnd * c, clockR * minEnd * s);
        } else {
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(clockR * stepStart * c, clockR * stepStart * s);
            glVertex2f(clockR * stepEnd * c, clockR * stepEnd * s);
        }
    }
    glEnd();
    float angle1hr = PI / 6.0f;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    angleHour = (t->tm_hour + t->tm_min / 60.0f) * angle1hr;
    angleMin = t->tm_min * angle1min;
    angleSec = t->tm_sec * angle1min * speed; // multiply the angle by the current speed
	// Draw hour hand
glLineWidth(3);
glColor3f(0.0f, 0.0f, 1.0f);
glBegin(GL_LINES);
glVertex2f(0.0f, 0.0f);
glVertex2f(clockR * 0.5f * sin(angleHour), clockR * 0.5f * cos(angleHour));
glEnd();

// Draw minute hand
glLineWidth(2);
glColor3f(1.0f, 0.0f, 1.0f);
glBegin(GL_LINES);
glVertex2f(0.0f, 0.0f);
glVertex2f(clockR * 0.8f * sin(angleMin), clockR * 0.8f * cos(angleMin));
glEnd();

// Draw second hand
glLineWidth(1);
glColor3f(1.0f, 1.0f, 0.0f);
glBegin(GL_LINES);
glVertex2f(0.0f, 0.0f);
glVertex2f(clockR * 0.9f * sin(angleSec), clockR * 0.9f * cos(angleSec));
glEnd();

numbers();

glutSwapBuffers();
}

void Timer(int value) {
glutPostRedisplay();
glutTimerFunc(REFRESH_TIME, Timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
switch (key) {
case 'f':
speed *= 2.0f; // double the current speed
break;
case 's':
speed *= 0.5f; // half the current speed
break;
case 27: // ESC key
exit(0);
}
}

int main(int argc, char **argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(800, 600);
glutCreateWindow("Analog Clock");
init();
glutDisplayFunc(Display);
glutTimerFunc(REFRESH_TIME, Timer, 0);
glutKeyboardFunc(keyboard);
glutMainLoop();
return 0;
}

