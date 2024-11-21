#include<iostream>
#include<math.h>
#include<gl/glut.h>

using namespace std;

inline int abs(int k) { return (k >= 0) ? k : -k; } // 절댓값 반환
inline int max(int i, int j) { return (i > j) ? i : j; } // 최댓값 반환
inline int ROUND(double v) { return (int)(v + 0.5); } // 반올림 반환
inline double dist(double dx, double dy) { 
	return sqrt(dx * dx + dy * dy); // 제곱한 값을 더해서 반환
}
inline void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static int winW = 500, winH = 500;
static int nGrid = 30;
static double pixelW, pixelH;
static int px, py, qx, qy;
static int mode = 0;

void draw2DGrid() {
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = 0; i <= nGrid; i++) {
		glVertex2d(i * pixelW, 0);
		glVertex2d(i * pixelW, winH);
		glVertex2d(0, i * pixelH);
		glVertex2d(winW, i * pixelH);
	}
	glEnd();
}

void DrawPixel(GLint x, GLint y) {
	int xi = x * pixelW;
	int yi = y * pixelH;
	glRectd(xi, yi, xi + pixelW, yi + pixelH);
}

void LineBasic(GLint x1, GLint y1, GLint x2, GLint y2) {
	float y, m;
	int dx, dy;
	dx = x2 - x1;
	dy = y2 - y1;
	m = dy / dx;
	for (float x = x1; x <= x2; x++) {
		y = m * (x - x1) + y1;
		DrawPixel(x, ROUND(y));
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);

	draw2DGrid();
	glColor3f(0.0, 0.0, 0.0);

	switch (mode) {
		case 1 : LineBasic(px / pixelW, qx / pixelW, qy / pixelH, py / pixelH);
			break;
	}
	
	/*switch (mode) {
	case 1: LineBasic(px / pixelW, qx / pixelW, qy / pixelH, py / pixelH);
		break;
	case 2: LineDDA(px / pixelW, py / pixelH, qx / pixelW, qy / pixelH);
		break;
	case 3: LineBresenham(px / pixelW, py / pixelH, qx / pixelW, py / pixelH);
		break;
	case 4: int radius = ROUND(dist(px / pixelW - qx / pixelW, py / pixelH - qy / pixelH));
		CircleMidPoint(radius);
		break;

	}*/

	
	glColor3f(1.0, 0.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(px, py);
		glVertex2f(qx, qy);
	glEnd();
	glFlush();
}

void mouseClick(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		px = x;
		py = winH - y;
	}
}

void mouseMotion(GLint x, GLint y) {
	qx = x;
	qy = (winH - y);
	glutPostRedisplay();
}

static bool bSwapXY = false;
void displayPixel(int x, int y) {
}

void LineBresenham(GLint x1, GLint y1, GLint x2, GLint y2)
{
	int dx, dy, incrE, incrNE, D, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	D = 2 * dy - dx;
	incrE = 2 * dy;
	incrNE = 2 * dy - 2 * dx;
	x = x1;
	y = y1;
	DrawPixel(x, y);
	while (x < x2) {
		if (D <= 0) {
			D += incrE;
			x++;
			y++;
		}
		else {
			D += incrNE;
			x++;
			y++;
		}
		DrawPixel(x, y);
	}
}
void LineDDA(GLint x1, GLint y1, GLint x2, GLint y2) {}

void CircleMidPoint(GLint radius) {}
void drawCirclePoint(int x, int y){}

void keyboard(unsigned char key, int x, int y) {
	if (key >= '0' && key <= '9')
		mode = key - '0';
	else if (key == 'q') exit(0);
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("Midpoint Circle Drawing");
	//glutCreateWindow("Bresham Drawing");

	pixelW = winW / nGrid;
	pixelH = winH / nGrid;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, 0, winH, -1, 1);

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
