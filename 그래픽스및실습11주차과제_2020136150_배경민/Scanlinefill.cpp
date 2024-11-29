#include<iostream>
#include<math.h>
using namespace std;

// x, y ��� ������ ����ü
struct Point2D { int x, y; };


struct EdgeRec {
	int yUpper;
	double xIntersect;
	double dxPerScan;
	EdgeRec* next; // EdgeRec ���� ����Ʈ�� �����ּ� ����

	EdgeRec() { next = NULL; }
	EdgeRec(Point2D* lower, Point2D* upper, int yComp) {
		dxPerScan = (double)(upper->x - lower->x) / (upper->y - lower->y); // Gradient
		xIntersect = lower->x; // x startpoint
		yUpper = (upper->y < yComp) ? upper->y - 1 : upper->y; // 
		next = NULL;
	}
	void AddNext(EdgeRec* e)
	{
		e->next = next;
		next = e;
	}
	void AddSorted(EdgeRec* edge) {
		EdgeRec* q = this;
		for (EdgeRec* p = next; p != NULL; q = p, p = p->next)
			if (edge->xIntersect < p->xIntersect)
				break;
		q->AddNext(edge);
	}
	void DeleteNext() {
		EdgeRec* p = next;
		next = p->next;
		delete p;
	}
	void DeleteAll() {
		while (next != NULL)
			DeleteNext();
	}
};


// global variance
static EdgeRec edges[4096];
static EdgeRec active;

// ��� ��ĵ���ο� ���� ���� ����Ʈ ����
static void buildEdgeList(int cnt, Point2D* pts) { // cnt = pts�� Length
	Point2D* v1 = &pts[cnt - 1]; // pts ������ ���� �ּҰ��� ����.
	int yPrev = pts[cnt - 2].y; // pts ������ y��(��, ���� ���� y��)�� yPrev�� ����.

	for (int i = 0; i < cnt; i++) {
		Point2D* v2 = &pts[i]; // pts �� �ϳ��ϳ� v2�� ����.
		cout << "x : " << v2->x << " y : " << v2->y << endl;
		if (v1->y != v2->y) {
			if (v1->y < v2->y) {
				int j = (i + 1) % cnt;
				while (pts[i].y == pts[j].y)
					j = (j + 1) % cnt;
				edges[v1->y].AddNext(new EdgeRec(v1, v2, pts[j].y));
			}
			else {
				edges[v2->y].AddNext(new EdgeRec(v2, v1, yPrev));
			}
			yPrev = v1->y;
			v1 = v2;
		}
	}
}
// active ����Ʈ�� ���� ��ĵ���� �߰�
static void buildActiveList(int scan)
{
	active.next = edges[scan].next;
}
static void updateActiveList(int scan)
{

}
static void resortActiveList() {}

#include<gl/glut.h>
static void fillScan(int scan)
{
	EdgeRec* p1 = active.next;
	cout << "first : " << p1->xIntersect;
	while (p1 != NULL) {
		EdgeRec* p2 = p1->next;
		cout << " second : " << p2->xIntersect;
		glBegin(GL_LINES);
		glVertex2i(round(p1->xIntersect), scan);
		glVertex2i(round(p2->xIntersect), scan);
		glEnd();
		p1 = p2-> next;
	}
}
void scanFill(int count, Point2D* points, int ww, int wh)
{
	buildEdgeList(count, points);
	for (int i = 0; i < wh; i++) {
		buildActiveList(i);
		if (active.next != NULL) {
			fillScan(i);
			return;

			//updateActiveList(i);
			//resortActiveList();
		}
	}
}
