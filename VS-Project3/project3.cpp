#include <GL/glut.h>
#include <cmath>

#define WindowSIZE 200

int n = 1;
float SCALE = 1.0;
float tran_x = 0, tran_y = 0;
float length = 300;

struct Point
{
	double x;
	double y;
};

void koch(Point left, Point right, int level)
{
	if (level == n)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(left.x, left.y);
		glVertex2f(right.x, right.y);
		glEnd();
	}
	else
	{
		Point P0, P1, P2;

		P0.x = left.x + (right.x - left.x) / 3;
		P0.y = left.y + (right.y - left.y) / 3;

		P2.x = left.x + 2 * (right.x - left.x) / 3;
		P2.y = left.y + 2 * (right.y - left.y) / 3;

		P1.x = P0.x + 0.5 * (P2.x - P0.x) - sqrt(3) * 0.5 * (P2.y - P0.y);
		P1.y = P0.y + sqrt(3) * 0.5 * (P2.x - P0.x) + 0.5 * (P2.y - P0.y);

		level++;

		koch(left, P0, level);
		koch(P0, P1, level);
		koch(P1, P2, level);
		koch(P2, right, level);
	}
}

void myDisplay(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glScalef(SCALE, SCALE, SCALE);

	glTranslatef(tran_x, tran_y, 0);

	Point trangle1, trangle2, trangle3;

	trangle1.x = -length / 2;
	trangle1.y = -(length * sqrt(3) / 2) / 3;

	trangle2.x = length / 2;
	trangle2.y = -(length * sqrt(3) / 2) / 3;

	trangle3.x = 0;
	trangle3.y = (length * sqrt(3) / 2) * 2 / 3;

	koch(trangle1, trangle3, 1);
	koch(trangle3, trangle2, 1);
	koch(trangle2, trangle1, 1);

	glPopMatrix();

	glFlush();
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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	{
		SCALE = SCALE * 0.9;
		break;
	}
	case 'e':
	{
		SCALE = SCALE * 10 / 9;
		break;
	}
	case 'w':
	{
		tran_y += 5 / SCALE;
		break;
	}
	case 's':
	{
		tran_y -= 5 / SCALE;
		break;
	}
	case 'a':
	{
		tran_x -= 5 / SCALE;
		break;
	}
	case 'd':
	{
		tran_x += 5 / SCALE;
		break;
	}
	case 'x':
	{
		tran_x = 0;
		tran_y = 0;
		SCALE = 1;
	}
	case ' ':
	{
		n = 1;
	}
	}

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		n ++;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		if (n > 1) n--;
		break;
	}
	}

	glutPostRedisplay();
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
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}