#pragma once
#include "Mesh.h"

class Robot {
public:
	Mesh Head, Body, RightArm, RightHand, LeftArm, LeftHand;
	Mesh RightLeg, RightFoot, LeftLeg, LeftFoot;
	float scale;


	Robot() {
		scale = 100;

		printf("Loading Robot Models....\n");
		Head.readAse("S_Head.ASE"); printf("   loading Head.......... OK. \n");
		Body.readAse("S_Body.ASE"); printf("   loading Body.......... OK. \n");
		RightArm.readAse("S_RightArm.ASE"); printf("   loading RightArm.......... OK. \n");
		RightHand.readAse("S_RightHand.ASE"); printf("   loading RightHand.......... OK. \n");
		LeftArm.readAse("S_LeftArm.ASE"); printf("   loading LeftArm.......... OK. \n");
		LeftHand.readAse("S_LeftHand.ASE"); printf("   loading LeftHand.......... OK. \n");
		RightLeg.readAse("S_RightLeg.ASE"); printf("   loading RightLeg.......... OK. \n");
		RightFoot.readAse("S_RightFoot.ASE"); printf("   loading RightFoot.......... OK. \n");
		LeftLeg.readAse("S_LeftLeg.ASE"); printf("   loading LeftLeg.......... OK. \n");
		LeftFoot.readAse("S_LeftFoot.ASE"); printf("   loading LeftFoot.......... OK. \n");
	}

	void draw() {
		Body.draw(0.1, 0.1, 0.1, scale, true);

		glPushMatrix();
			glTranslated(0.0, 0.45, -0.07);
			glScalef(1.1f, 1.1f, 1.1f);
			Head.draw(1.0, 1.0, 1.0, scale);
		glPopMatrix();

		glPushMatrix();
			glTranslated(-0.25, 0.32, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			RightArm.draw(0.4, 0.4, 0.8, scale);

			glPushMatrix();
				glTranslated(-0.05, -0.3, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				RightHand.draw(0.4, 0.4, 0.8, scale);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0.25, 0.32, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			LeftArm.draw(0.4, 0.4, 0.8, scale);

			glPushMatrix();
				glTranslated(0.05, -0.3, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				RightHand.draw(0.4, 0.4, 0.8, scale);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-0.13, -0.09, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			RightLeg.draw(0.4, 0.4, 0.8, scale);

			glPushMatrix();
				glTranslated(-0.01, -0.40, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				RightFoot.draw(0.4, 0.4, 0.8, scale);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0.13, -0.09, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			LeftLeg.draw(0.4, 0.4, 0.8, scale);

			glPushMatrix();
				glTranslated(0.01, -0.40, 0.0);
				glScalef(1.0f, 1.0f, 1.0f);
				LeftFoot.draw(0.4, 0.4, 0.8, scale);
			glPopMatrix();
		glPopMatrix();

	}
};
