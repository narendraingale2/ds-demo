
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"
extern GLuint texture_colured_tree;
extern GLuint texture_coco_tree;
extern GLuint texture_water;
extern GLfloat points[45][45][3];
extern GLfloat hold;    
extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;

void drawMoon()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	glBindTexture(GL_TEXTURE_2D, texture_moon);
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
	glDepthMask(GL_FALSE); 
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
	glDepthMask(GL_TRUE); 
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawCocoTree()
{
	glDepthMask(GL_FALSE); 
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
	glDepthMask(GL_TRUE);

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
	glTranslatef(0.0f, -2.0f, 0.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glRotatef(-80,1.0f,0.0f,0.0f);             // Rotate On The X Axis
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture_water);
	glDepthMask(GL_FALSE); 

	//glColor3f(0.05f, 0.05f, 0.2f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glScalef(1.8, 1.0f, 1.0f);
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
	glDepthMask(GL_TRUE); 
}

void drawTerrain()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

void drawHouse()
{
	glBegin(GL_QUADS);
	
	// front face
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// right face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// back face
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// left face
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// top face
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// bottom face
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

}