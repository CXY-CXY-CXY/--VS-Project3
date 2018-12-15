#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

#define WindowSIZE 200

int num = 0;
int is_get = -1;
int STEP = 1000;
bool is_draw = false;

typedef struct Point
{
	float x, y;
}Point;

Point* P = new Point[num];

void change(void)
{
	Point* temp = new Point[num + 1];
	for (int i = 0; i < num; i++)
	{
		temp[i] = P[i];
	}
	delete[]P;
	num++;
	is_get = num - 1;
	P = temp;
}

float C(int n, int k)
{
	float temp, temp1 = 1, temp2 = 1;
	for (int i = n; i > n - k; i--)
	{
		temp1 *= i;
	}
	for (int i = k; i >= 1; i--)
	{
		temp2 *= i;
	}
	temp = temp1 / temp2;
	return temp;
}

void Bezier(void)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= STEP; i++)
	{
		float u = (float)i / (float)STEP;
		float x = 0, y = 0, n = num - 1;

		for (int k = 0; k < num; k++)
		{
			x += C(n, k) * pow(u, k) * pow(1 - u, n - k) * P[k].x;
			y += C(n, k) * pow(u, k) * pow(1 - u, n - k) * P[k].y;
		}

		glVertex2f(x, y);
	}
	glEnd();
}

void myDisplay(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < num; i++)
	{
		glVertex2f(P[i].x, P[i].y);
	}
	glEnd();

	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i < num; i++)
	{
		glVertex2f(P[i].x, P[i].y);
	}
	glEnd();

	if (is_get == num)
	{
		Bezier();
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (is_draw)
			{
				num = 0;
				is_get = -1;
				is_draw = false;
			}
			change();
			P[is_get].x = x - WindowSIZE;
			P[is_get].y = WindowSIZE - y;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			is_get = num;
			is_draw = true;
		}
	}

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		glOrtho(-WindowSIZE, WindowSIZE, -WindowSIZE * (GLfloat)h / (GLfloat)w, WindowSIZE*(GLfloat)h / (GLfloat)w, -WindowSIZE, WindowSIZE);
	}
	else
	{
		glOrtho(-WindowSIZE * (GLfloat)w / (GLfloat)h, WindowSIZE*(GLfloat)w / (GLfloat)h, -WindowSIZE, WindowSIZE, -WindowSIZE, WindowSIZE);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(2 * WindowSIZE, 2 * WindowSIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);

	glutMainLoop();
}