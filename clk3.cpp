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

void RenderString(float x, float y, void *font, const unsigned char *str)
{
    char *c;
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

void draw(void)
{
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

    // Second
    float angle_s = second * 6;

    glRotatef(-angle_s, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2i(0, 0);
    glVertex2i(0, sy);
    glEnd();

    glLoadIdentity();

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

    // Minute
    float angle_m = minute * 6;

    glRotatef(-angle_m, 0.0f, 0.0f, 1.0f);

    glLineWidth(3); // Thinner line width
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex2i(0, 0);
    glVertex2i(0, my);
    glEnd();

    glLoadIdentity();

    // Hour
    float angle_h = (hour + minute / 60.0) * 30;

    glRotatef(-angle_h, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
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

void createMenu()
{
    int menu = glutCreateMenu(changeColor);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void resize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height)
        gluOrtho2D(-tam_x, tam_x, -tam_y * height / width, tam_y * height / width);
    else
        gluOrtho2D(-tam_x * width / height, tam_x * width / height, -tam_y, tam_y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void move(int n)
{
    time_t agora = time(0);
    struct tm *datahour = localtime(&agora);

    hour = datahour->tm_hour;
    minute = datahour->tm_min;
    second = datahour->tm_sec;

    glutPostRedisplay();
    glutTimerFunc(1000, move, 0);
}

void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Clock");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutTimerFunc(1000, move, 0);
    initialize();

    createMenu(); // Create the context menu

    glutMainLoop();
    return 0;
}

