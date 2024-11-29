#include<iostream>
#include<math.h>
using namespace std;

// x, y 묶어서 정의한 구조체
struct Point2D { int x, y; };


struct EdgeRec {
	int yUpper;
	double xIntersect;
	double dxPerScan;
	EdgeRec* next; // EdgeRec 연결 리스트의 시작주소 저장

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

// 모든 스캔라인에 대해 엣지 리스트 생성
static void buildEdgeList(int cnt, Point2D* pts) { // cnt = pts의 Length
	Point2D* v1 = &pts[cnt - 1]; // pts 마지막 값의 주소값을 대입.
	int yPrev = pts[cnt - 2].y; // pts 마지막 y값(즉, 가장 높은 y값)을 yPrev에 대입.

	for (int i = 0; i < cnt; i++) {
		Point2D* v2 = &pts[i]; // pts 값 하나하나 v2에 대입.
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
// active 리스트에 대항 스캔라인 추가
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
