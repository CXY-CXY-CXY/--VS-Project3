#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

#define WindowSIZE 200

int num = 20;
int is_get = 0;
int STEP = 100;

typedef struct Point
{
	float x, y;
}Point;

Point* P = new Point[num];

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
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < num; i++)
	{
		glVertex2f(P[i].x, P[i].y);
	}
	glEnd();

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
		cout << i << "\t" << x << "\t" << y << endl;
	}
	glEnd();
}

void myDisplay(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	if (is_get == num)
	{
		Bezier();
	}
	else
	{
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < is_get; i++)
		{
			glVertex2f(P[i].x, P[i].y);
		}
		glEnd();

		glPointSize(3);
		glBegin(GL_POINTS);
		for (int i = 0; i < is_get; i++)
		{
			glVertex2f(P[i].x, P[i].y);
		}
		glEnd();
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (is_get != num)
			{
				P[is_get].x = x - WindowSIZE;
				P[is_get].y = WindowSIZE - y;
				cout << P[is_get].x << "\t" << P[is_get].y << endl;
				is_get++;
			}
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