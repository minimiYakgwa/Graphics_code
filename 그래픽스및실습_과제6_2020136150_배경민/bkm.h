#pragma once
#include<stdio.h>
#include<gl/glut.h>
#include<memory.h>
#include<cmath>

#define _USE_MATH_DEFINES // M, PI를 사용하기 위해 정의함.
#include <math.h>
#define SIN(x) sin(x*M_PI / 180.)
#define COS(x) cos(x*M_PI / 180.) // degree 각도를 이용하여 삼각함수 사용.

inline void bkmMatSet(double* m, // m은 1차원 배열임.
	double m00, double m01, double m02, double m03,
	double m04, double m05, double m06, double m07,
	double m08, double m09, double m10, double m11,
	double m12, double m13, double m14, double m15)
{
	double mat[16] = { m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15 };
	memcpy(m, mat, sizeof(double) * 16); // mat의 주소를 m에 대입함.
}

inline void bkmMatMult(double* m1, double* m2) {
	double n[16];
	
	for (int k = 0; k < 16; k++) {
		n[k] = 0;
		double* p = m1 + (k / 4) * 4;
		double* q = m2 + k % 4;
		
		for (int i = 0; i < 4; i++) {
			n[k] += p[i] * q[i*4];
		}

	}
	memcpy(m1, n, sizeof(double) * 16);
}

inline void bkmMatPrint(double* m) {
	for (int i = 0; i < 4; i++) {
		printf("[");
		for (int j = 0; j < 4; j++) {
			printf("%6.2f", m[i * 4 + j]);
		}
		printf("]\n");
	}
	printf("\n");

}

inline void bkmMatIdentity(double* m) {
	bkmMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatTrans(double* m, double tx, double ty, double tz) {
	bkmMatSet(m, 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
}

inline void bkmMatScale(double* m, double sx, double sy, double sz) {
	bkmMatSet(m, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}

inline void bkmMatRotateZ(double* m, double seta) {
	bkmMatSet(m, COS(seta), -SIN(seta), 0, 0, SIN(seta), COS(seta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatRotateX(double* m, double seta) {
	bkmMatSet(m, 1, 0, 0, 0, 0, COS(seta), -SIN(seta), 0, 0, SIN(seta), COS(seta), 0, 0, 0, 0, 1);
}

inline void bkmMatRotateY(double* m, double seta) {
	bkmMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, COS(seta), -SIN(seta), 0, 0, SIN(seta), COS(seta));
}

inline void bkmMatShearX(double* m, double dy, double dz) {
	bkmMatSet(m, 1, dy, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatShearY(double* m, double dx, double dz) {
	bkmMatSet(m, 1, 0, 0, 0, dx, 1, dz, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatShearZ(double* m, double dx, double dy) {
	bkmMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, dx, dy, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatReflectXY(double* m) {
	bkmMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1);
}

inline void bkmMatReflectYZ(double* m) {
	bkmMatSet(m, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

inline void bkmMatReflectXZ(double* m) {
	bkmMatSet(m, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

//inline double getDistance(double x1, double y1, double x2, double y2) {
//	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
//}
//
//inline double getAngleInRadians(double x1, double y1, double x2, double y2) {
//	return std::atan2(y2 - y1, x2 - x1);
//}

inline double radiansToDegrees(double radians) {
	return radians * (180.0 / M_PI);
}

inline void bkmTransform(double* m, double* p, double* q) {
	q[0] = q[1] = q[2] = q[3] = 0;
	for (int i = 0; i < 4; i++) {
		q[0] += m[i] * p[i];
		q[1] += m[i + 4] * p[i];
		q[2] += m[i + 8] * p[i];
		q[3] += m[i + 12] * p[i];
	}
}

inline void bkmLine(double x1, double y1, double z1, double x2, double y2, double z2) {
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}

inline void bkmTriangle4d(double* p) {
	glBegin(GL_TRIANGLES);
	glVertex4dv(p);
	glVertex4dv(p + 4);
	glVertex4dv(p + 8);
	glEnd();
}

inline void bkmCoord() {
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); glVertex3d(-0.1, 0, 0); glVertex3d(1, 0, 0);
	glColor3d(0, 1, 0); glVertex3d(0, -0.1, 0); glVertex3d(0, 1, 0);
	glColor3d(0, 0, 1); glVertex3d(0, 0, -0.1); glVertex3d(0, 0, 1);
	glEnd();
}



