#include <iostream>
#include <gl/glut.h>
#include <math.h>

static int winW = 500, winH = 500;
static int mode = 0;
static bool bFill = false;

struct Point2D {
	int x, y;
	Point2D(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	void Set(int x, int y) { this->x = x; this->y = y; }
};

inline double area(double sx, double sy, double tx, double ty) {
	return sx * ty - sy * tx;
}

inline bool isCross() {}

struct Polygon2D {
	int nTotal;
	int nPt;
	Point2D* pt;
	Polygon2D(int npt = 10) : nTotal(npt), nPt(0) {
		pt = new Point2D[npt];
	}
	~Polygon2D() { delete pt; }
	void reset() { nPt = 0; }
	void addPoint(int x, int y) { pt[nPt++].Set(x, y); }
	void draw(bool bFill = false) {
		glBegin(bFill ? GL_POLYGON : GL_LINE_LOOP);
		for (int i = 0; i < nPt; i++) {
			glVertex3d(pt[i].x, pt[i].y, 0);
		}
		glEnd();
	}
	void drawStrip() {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < nPt; i++) {
			glVertex3d(pt[i].x, pt[i].y, 0);
		}
		glEnd();
	}
	bool testInOut(int x, int y) {
		int count = 0;
		//Point2D* p(x, y), q(100000, y);
		for (int i = 0; i < nPt; i++) {
			//if (isCross(p, q, pt[i], pt[(i + 1) % nPt])) count++;
		}
		return false;
	}
	bool testInOut2(int x, int  y) {
		return false;
	}
};

extern void scanFill(int cout, Point2D* points, int ww, int wh);

static Polygon2D polygon(100);
static  bool bAddPoint = false;

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, 0, winH, -1, 1);

	glColor3f(0, 0, 0);
	if (bFill) {
		scanFill(polygon.nPt, polygon.pt, winW, winH);
	}
	else if (bAddPoint) {
		polygon.drawStrip();;
	}
	else
		polygon.draw();

	glFlush();
}
void mouseClick(GLint button, GLint state, GLint x, GLint y) {

	// 지정한 좌표에 선분 그리기
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		if (bAddPoint) {
			polygon.addPoint(x, winH - y);
		}
	} // 시작 지점과 마지막 지점을 선분으로 이어주기.
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		bAddPoint = false;
	}
	else {
			polygon.testInOut(x, winH - y);
			polygon.testInOut2(x, winH - y);
	}
	
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'p') {
		polygon.reset();
		bAddPoint = true;
		bFill = false;
	}
	else if (key == 'f') {
		bFill = !bFill;
	}
	else if (key == 'q') exit(0);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("Fill Polygon");

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}