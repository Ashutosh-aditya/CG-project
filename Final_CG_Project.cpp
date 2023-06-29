#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <string>
#include <cstring>

const GLfloat tam_x = 50.0f;
const GLfloat tam_y = 50.0f;

const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

int hour;
int minute;
int second;
int currentColor = 0; // 0: Red, 1: Green, 2: Blue
bool useRomanNumerals = false; // Flag to determine whether to use Roman numerals or digits

void RenderString(float x, float y, void* font, const unsigned char* str)
{
    char* c;
    glColor3ub(0, 0, 0); // Black color for numbers
    glRasterPos2f(x, y);
    glutBitmapString(font, str);
}

void circle(GLfloat xc, GLfloat yc, GLfloat raio, bool fill)
{
    const GLfloat c = 3.14169f / 180.0f;
    GLint i;

    glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);

    for (i = 0; i <= 360; i += 2)
    {
        float a = i * c;
        glVertex2f(xc + sin(a) * raio, yc + cos(a) * raio);
    }

    glEnd();
}

void drawDigits()
{
    unsigned char time_1[4] = "1";
    unsigned char time_2[4] = "2";
    unsigned char time_3[4] = "3";
    unsigned char time_4[4] = "4";
    unsigned char time_5[4] = "5";
    unsigned char time_6[4] = "6";
    unsigned char time_7[4] = "7";
    unsigned char time_8[4] = "8";
    unsigned char time_9[4] = "9";
    unsigned char time_10[4] = "10";
    unsigned char time_11[4] = "11";
    unsigned char time_12[4] = "12";

    RenderString(-2, 40, GLUT_BITMAP_TIMES_ROMAN_24, time_12);
    RenderString(0, -40, GLUT_BITMAP_TIMES_ROMAN_24, time_6);
    RenderString(40, 0, GLUT_BITMAP_TIMES_ROMAN_24, time_3);
    RenderString(-40, 0, GLUT_BITMAP_TIMES_ROMAN_24, time_9);

    RenderString(-35, 20, GLUT_BITMAP_TIMES_ROMAN_24, time_10);
    RenderString(35, 20, GLUT_BITMAP_TIMES_ROMAN_24, time_2);
    RenderString(35, -20, GLUT_BITMAP_TIMES_ROMAN_24, time_4);
    RenderString(-35, -20, GLUT_BITMAP_TIMES_ROMAN_24, time_8);

    RenderString(-20, 35, GLUT_BITMAP_TIMES_ROMAN_24, time_11);
    RenderString(20, 35, GLUT_BITMAP_TIMES_ROMAN_24, time_1);
    RenderString(20, -35, GLUT_BITMAP_TIMES_ROMAN_24, time_5);
    RenderString(-20, -35, GLUT_BITMAP_TIMES_ROMAN_24, time_7);
}

void drawRomanNumerals()
{
    const char* romanNumerals[12] = {
    "XII", "XI", "X", "IX", "VIII", "VII", "VI", "V", "IV", "III", "II", "I"
    };

    const GLfloat distanceFromBoundary = 15.0f; // Adjust this value to increase/decrease the distance

    for (int i = 0; i < 12; i++)
    {
        float angle = i * 30;
        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        RenderString(0, tam_x - distanceFromBoundary, GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char*>(romanNumerals[i]));
        glPopMatrix();
    }
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-tam_x, tam_x, -tam_y, tam_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void draw(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-tam_x, tam_x, -tam_y, tam_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);

    // Color selection based on currentColor
    if (currentColor == 0)
        glColor3ub(249, 168, 37); // Red
    else if (currentColor == 1)
        glColor3ub(0, 255, 0); // Green
    else if (currentColor == 2)
        glColor3ub(0, 0, 255); // Blue

    circle(0, 0, tam_x, true);

    // Outer boundary
    glColor3ub(0, 0, 0); // Black
    circle(0, 0, tam_x - 0.5f, false);

    // Inner boundary
    glColor3ub(255, 255, 255); // White
    circle(0, 0, tam_x - 1.5f, false);

    if (useRomanNumerals)
        drawRomanNumerals();
    else
        drawDigits();

    // Second
    float angle_s = second * 6;

    glRotatef(-angle_s, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2i(0, 0);
    glVertex2i(0, sy);
    glEnd();

    glLoadIdentity();

    // Minute
    float angle_m = minute * 6;

    glRotatef(-angle_m, 0.0f, 0.0f, 1.0f);

    glLineWidth(3); // Thinner line width
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f); // Green
    glVertex2i(0, 0);
    glVertex2i(0, my);
    glEnd();

    glLoadIdentity();

    // Hour
    float angle_h = (hour + minute / 60.0) * 30;

    glRotatef(-angle_h, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue
    glVertex2i(0, 0);
    glVertex2i(0, hy);
    glEnd();

    glLoadIdentity();

    glFlush();
}

void changeColor(int option)
{
    currentColor = option;
    glutPostRedisplay();
}

void toggleNumerals(int option)
{
    useRomanNumerals = !useRomanNumerals;
    glutPostRedisplay();
}

void createMenu()
{
    int colorMenu = glutCreateMenu(changeColor);
    glutAddMenuEntry("Orange", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);

    int numeralMenu = glutCreateMenu(toggleNumerals);
    glutAddMenuEntry("Toggle Numerals", 0);

    glutCreateMenu(changeColor);
    glutAddSubMenu("Change Color", colorMenu);
    glutAddSubMenu("Options", numeralMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void updateClock(int value)
{
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    hour = localTime->tm_hour;
    minute = localTime->tm_min;
    second = localTime->tm_sec;

    glutPostRedisplay();
    glutTimerFunc(1000, updateClock, 0);
}


void WelcomeDisplay()
{
glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(75.0f, 1, 0.0f, 35.0f);
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0,0,1);
    //glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1,1,1);
	
	glRasterPos2f(-1.2,+1.5);
	char msg1[]="WELCOME TO THE ANALOG CLOCK";
	for(int i=0;i<strlen(msg1);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[i]);
		
	glRasterPos2f(-1.8,-0.7);
	char msg2[]="Submitted by :-";
	for(int i=0;i<strlen(msg2);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg2[i]);

	glColor3f(0.217,0.132,0.9);
	glRasterPos2f(-1.5,-1);
	char msg3[]="Ashutosh Aditya (1JS20CS038)";
	for(int i=0;i<strlen(msg3);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg3[i]);
		
	glRasterPos2f(-1.5,-1.25);
	char msg4[]="Abhinav Akarsh (1JS20CS004)";
	for(int i=0;i<strlen(msg4);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg4[i]);
		
	glColor3f(0,0.5,0);
	glRasterPos2f(-0.9,-1.8);
	char msg5[]="Press X to continue";
	for(int i=0;i<strlen(msg5);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg5[i]);
		
	glutSwapBuffers();
}


void keys(unsigned char key,int x,int y)
{
	if(key=='x' || key=='X')
	{
	glutInitWindowSize(700,700);
		glutDisplayFunc(draw);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    gluOrtho2D(-tam_x, tam_x, -tam_y, tam_y);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Analog Clock");
    glutInitWindowSize(700,700);
    glutDisplayFunc(WelcomeDisplay);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    createMenu();
    updateClock(0);
    glutMainLoop();
    return 0;
}

