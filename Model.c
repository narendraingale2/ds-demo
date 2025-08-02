
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

//#define DEV_MODE

extern GLuint texture_colured_tree;
extern GLuint texture_coco_tree;
extern GLuint texture_water;
extern GLuint texture_ground;
extern GLuint texture_wall_stone;
extern GLuint texture_roof;
extern GLuint texture_butter_fly;
extern GLuint texture_background_mountain;

extern GLfloat points[45][45][3];
extern GLfloat hold;    
extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;
extern GLfloat location[16];
extern FILE *gpFile;
extern GLfloat angleHouse;

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	glGetFloatv(GL_MODELVIEW_MATRIX, location);
	for(int i = 0; i<16; i++)
		fprintf(gpFile,"Moon location[%d] = %f\n",i, location[i]);
	gluSphere(quadric, 0.5, 50, 50);
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(quadric, GL_FALSE);
}

void drawColoredTree()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // face
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_colured_tree);
    glPushMatrix();
	//fprintf(gpFile, "Printing Model view metrix Before drwing colored Tree");
	glGetFloatv(GL_MODELVIEW_MATRIX, location);
	//for(int i = 0; i<16; i++)
		//fprintf(gpFile,"location[%d] = %f\n",i, location[i]);

	glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);

	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawCocoTree()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texture_coco_tree);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPushMatrix();
	glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.3f, 0.5f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.3f, -0.5f, 0.0f);

	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawWater()
{
	//glPolygonMode(GL_BACK, GL_FILL );

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
	glShadeModel(GL_SMOOTH);

	int x, y;
	float float_x, float_y, float_xb, float_yb;

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -8.0f);
	glTranslatef(0.0f, -2.5f, 0.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glRotatef(-80,1.0f,0.0f,0.0f);             // Rotate On The X Axis
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture_water);

	//glColor3f(0.05f, 0.05f, 0.2f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glScalef(3, 0.4f, 1.0f);
	glBegin(GL_QUADS);

	for(x = 0; x < 40; x++)
	 {
		for(y = 0; y < 44; y++)
		{
			float_x = ((float) x)/44.0f;
			float_y = ((float) y)/44.0f;
			float_xb = ((float) x + 1)/44.0f;
			float_yb = ((float) y + 1)/44.0f;

			glTexCoord2f(float_x, float_y);
			glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

			glTexCoord2f(float_x, float_yb);
			glVertex3f(points[x][y + 1][0], points[x][y+1][1], points[x][y+1][2]);

			glTexCoord2f(float_xb, float_yb);
			glVertex3f(points[x + 1][y + 1][0], points[x+1][y+1][1], points[x+1][y+1][2]);

			glTexCoord2f(float_xb, float_yb);
			glVertex3f(points[x + 1][y ][0], points[x+1][y][1], points[x+1][y][2]);
		}
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawGround()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_ground);
    glPushMatrix();
		drawQuad();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawHouse()
{
	void drawRoof();


	#ifdef DEV_MODE
	glRotatef(angleHouse, 0.0f, 1.0f, 0.0f);
	#endif
	// main house
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture_wall_stone);
		glScalef(3.0f, 1.6f, 1.2f);
		drawCube();
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	// drawing roof
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture_roof);
		glTranslatef(0.0f, 8.0f, 0.0f);
		glScalef(6.0f, 4.0f, 1.0f);
		drawRoof();
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

}

void drawRoof()
{
	glBegin(GL_QUADS);
	
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		// This is special requirement of drwaing quad
		// hence drawQuad function was not used
		// Quad1
        glTexCoord2f(1.0, 1.0); // right-right
		glVertex3f(-1.0f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
		glVertex3f(1.0f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
		glVertex3f(1.0f, -1.0f, 3.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
		glVertex3f(-1.0f, -1.0f, 3.0f);

		// QUAD2
        glTexCoord2f(1.0, 1.0); // right-right
		glVertex3f(-1.0f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
		glVertex3f(1.0f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
		glVertex3f(1.0f, -1.0f, -3.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
		glVertex3f(-1.0f, -1.0f, -3.0f);
	glEnd();
}

void drawAnimatedButterfly()
{
	static GLfloat butterflyAngle = -20.0f;
	static BOOL positiveCounter = TRUE;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0,1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_butter_fly);

	glRotatef(-660, 1.0f, 0.0f, 0.0f);
	glScalef(2.0f, 2.0f, 1.0f);

	glTranslatef(0.1f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, 0.0f);
		glRotatef(-butterflyAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);
			drawButterFlyQuad();
	glPopMatrix();

	glTranslatef(-0.1f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(1.0f, 0.0f, 0.0f);
		glRotatef(butterflyAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(-1.0f, 0.0f, 0.0f);
		glScalef(-1.0f, 1.0f, 1.0f);
			drawButterFlyQuad();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	
	if(positiveCounter == TRUE)
		butterflyAngle = butterflyAngle + 1;
	else
		butterflyAngle = butterflyAngle - 1;
	
	if(butterflyAngle >= 30.0f)
	{
		positiveCounter = FALSE;		
	}

	if(butterflyAngle <= -20.0f)
	{
		positiveCounter = TRUE;
	}



}

void drawBackgroundMountain()
{

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_background_mountain);
    glPushMatrix();
		drawQuad();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}