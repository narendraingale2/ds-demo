
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

#define DEV_MODE

extern GLuint texture_coco_tree;
extern GLuint texture_water;
extern GLuint texture_ground;
extern GLuint texture_wall_stone;
extern GLuint texture_roof;
extern GLuint texture_butter_fly;
extern GLuint texture_background_mountain;
extern GLuint texture_house_door;
extern GLuint texture_wooden_grill;
extern GLuint texture_grass;
extern GLuint texture_big_grass;

extern GLfloat points[45][45][3];
extern GLfloat hold;    
extern GLfloat xrot;
extern GLfloat yrot;
extern GLfloat zrot;
extern GLfloat location[16];
extern FILE *gpFile;
extern GLfloat angleHouse;
extern GLfloat xLookAt;
extern GLfloat yLookAt;
extern GLfloat zLookAt;
point_t* grass_cordinates;
point_t* bigGrass_cordinates;
int numGrass = 500;
int numBigGrass = 500;


void drawMoon()
{

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	glPushMatrix();
    	glTranslatef(5.0f, 4.5f, -13.0f);
		glColor4f(1.0f, 1.0f, 1.0f,1.0f);
		gluSphere(quadric, 0.5, 50, 50);
		glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(quadric, GL_FALSE);
	glPopMatrix();
}

void drawColoredTree(GLfloat x, GLfloat y, GLfloat z, GLuint texture)
{
	    
    // face
	glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(1.2f, 1.2f, 1.0f);
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
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

		glRotatef(90, 0.0f, 1.0f, 0.0f);
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
    glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_coco_tree);
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
	static BOOL initialized = FALSE;
	
	if(initialized == FALSE)
	{
		for(int x = 0; x < 44; x++)
		{
			for(int y=0; y<45; y++)
			{
				points[x][y][0] = (float)((x/5.0)-5.0f);
				points[x][y][1] = (float)((y/5.0)-4.5f);
				points[x][y][2] = (float)(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f))*0.2;
			}
		}

	}

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
    glPushMatrix();
		glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, texture_ground);
    	glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); 	   		
			glVertex3f(8.0f, -1.2f, -10.0f);
	   		glTexCoord2f(0.0, 1.0); 
	   		glVertex3f(-8.0f, -1.2f, -10.0f);
	   		glTexCoord2f(0.0, 0.0); 
	   		glVertex3f(-8.0f, -1.2f, 0.0f);
	   		glTexCoord2f(1.0, 0.0);
	   		glVertex3f(8.0f, -1.2f, 0.0f);
    	glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

}

void drawHouse()
{

	void drawHouseMain(BOOL);
	void drawHouseUpper();
	static GLfloat angle=0.0f;

	glPushMatrix();
		glTranslatef(0.0f, -1.0f, -8.0f);
		glScalef(0.3f, 0.2f, 0.3f);

		glPushMatrix();
			glScalef(5.0f, 1.0f, 3.0f);
			drawHouseMain(TRUE);
		glPopMatrix();

		glPushMatrix();
			glScalef(4.0f, 1.0f, 1.5f);
			glTranslatef(0.0f, 2.8f, 0.0f);
			drawHouseUpper();
		glPopMatrix();
	glPopMatrix();
	angle = angle + 1.0f;
}

void drawHouseMain(BOOL isMain)
{
	void drawRoof();
	static GLfloat angle = 0.0f;
	
	glPushMatrix();
		glPushMatrix();
			glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, texture_wall_stone);
			glBegin(GL_QUADS);
				// Front
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, 1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f( 1.0f, 1.0f, 1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f( 1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, 1.0f);

	 	       	// Back
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f( 1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f( 1.0f, -1.0f, -1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, -1.0f);


	 	       // Left
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f,  1.0f);

	 	       // Right
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f(1.0f, -1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(1.0f, 1.0f,  1.0f);

	 	   	glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			if(isMain == TRUE)
			{
				glBindTexture(GL_TEXTURE_2D, texture_house_door);
				glBegin(GL_QUADS);
					// Front
					glTexCoord2f(1.0, 1.0); // right-right
					glVertex3f(-0.8f, 1.0f, 1.0f);
					glTexCoord2f(0.0, 1.0); // right-right
	 	 	 		glVertex3f( 0.8f, 1.0f, 1.0f);
					glTexCoord2f(0.0, 0.0); // right-right
					glVertex3f( 0.8f, -1.0f, 1.0f);
					glTexCoord2f(1.0, 0.0); // right-right
					glVertex3f(-0.8f, -1.0f, 1.0f);
					glEnd();
				glBindTexture(GL_TEXTURE_2D, 0);

			}
		glPopMatrix();

		// Draw roof
		glPushMatrix();
			glColor3f(0.7f, 0.7f, 0.7f);
			glBindTexture(GL_TEXTURE_2D, texture_roof);
			glTranslatef(0.0f, 1.82f, 0.0f);
			glBegin(GL_QUADS);
	 	       	glTexCoord2f(0.25f, 1.0); // right-right
	 	       	glVertex3f(-0.5f, 1.0f, 0.0f);
			    glTexCoord2f(1.0f, 1.0); // right-right
	 	       	glVertex3f( 0.5f, 1.0f, 0.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f( 1.1f, -1.0f, -1.1f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(-1.1f, -1.0f, -1.1f);

	 	       	glTexCoord2f(0.25 * 4.0f, 1.0); // right-right
	 	       	glVertex3f(-0.5f, 1.0f, 0.0f);
			    glTexCoord2f(0.75 * 4.0f, 1.0); // right-right
	 	       	glVertex3f( 0.5f, 1.0f, 0.0f);
			    glTexCoord2f(1.0 * 4.0f, 0.0); // right-right
	 	       	glVertex3f( 1.1f, -1.0f, 1.1f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(-1.1f, -1.0f, 1.1f);
			glEnd();
	
			glBegin(GL_TRIANGLES);
	 	       	glTexCoord2f(0.5, 0.5); // right-right
				glVertex3f(-0.5f, 1.0f, 0.0f);
	 	       	glTexCoord2f(0.0, 0.0); // right-right
				glVertex3f(-1.1f, -1.0f, -1.1f);
	 	       	glTexCoord2f(1.0, 0.0); // right-right
				glVertex3f(-1.1f, -1.0f, 1.1f);
			glEnd();

			glBegin(GL_TRIANGLES);
	 	       	glTexCoord2f(0.5, 0.5); // right-right
				glVertex3f(0.5f, 1.0f, 0.0f);
	 	       	glTexCoord2f(0.0, 0.0); // right-right
				glVertex3f(1.1f, -1.0f, -1.1f);
	 	       	glTexCoord2f(1.0, 0.0); // right-right
				glVertex3f(1.1f, -1.0f, 1.1f);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();	
	glPopMatrix();

	angle = angle + 1.0f;
}

void drawHouseUpper()
{
	void drawRoof();
	static GLfloat angle = 0.0f;
	
	glPushMatrix();
		glPushMatrix();
			
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, texture_wooden_grill);
			glBegin(GL_QUADS);
				// Front
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, 1.001f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f( 1.0f, 1.0f, 1.001f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f( 1.0f, -1.0f, 1.001f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, 1.001f);
			glEnd();
			//glBindTexture(GL_TEXTURE_2D, texture_wooden_grill);
			glBindTexture(GL_TEXTURE_2D, texture_wall_stone);
			glBegin(GL_QUADS);
			
				// Front
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, 1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f( 1.0f, 1.0f, 1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f( 1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, 1.0f);
			glEnd();
				//glBindTexture(GL_TEXTURE_2D, 0);

			glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
			glBegin(GL_QUADS);
	 	       	// Back
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f( 1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f( 1.0f, -1.0f, -1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, -1.0f);


	 	       // Left
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(-1.0f, 1.0f,  1.0f);

	 	       // Right
	 	       	glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(1.0f, 1.0f, -1.0f);
			    glTexCoord2f(0.0, 1.0); // right-right
	 	       	glVertex3f(1.0f, -1.0f, -1.0f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(1.0f, -1.0f, 1.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f(1.0f, 1.0f,  1.0f);

	 	   	glEnd();
		glPopMatrix();

		// Draw roof
		glPushMatrix();
			glColor3f(0.7f, 0.7f, 0.7f);
			glBindTexture(GL_TEXTURE_2D, texture_roof);
			glTranslatef(0.0f, 1.82f, 0.0f);
			glBegin(GL_QUADS);
	 	       	glTexCoord2f(0.25f, 1.0); // right-right
	 	       	glVertex3f(-0.5f, 1.0f, 0.0f);
			    glTexCoord2f(0.75f, 1.0); // right-right
	 	       	glVertex3f( 0.5f, 1.0f, 0.0f);
			    glTexCoord2f(1.0, 0.0); // right-right
	 	       	glVertex3f( 1.1f, -1.0f, -1.1f);
			    glTexCoord2f(1.0, 1.0); // right-right
	 	       	glVertex3f(-1.1f, -1.0f, -1.1f);

	 	       	//glTexCoord2f(1.0, 1.0); // right-right
	 	       	glTexCoord2f(0.25f * 4.0f, 1.0 *1.0f); // right-right
	 	       	glVertex3f(-0.5f, 1.0f, 0.0f);
			    glTexCoord2f(0.75f * 4.0f, 1.0 * 1.0f); // right-right
	 	       	glVertex3f( 0.5f, 1.0f, 0.0f);
			    glTexCoord2f(1.0 * 4.0f, 0.0); // right-right
	 	       	glVertex3f( 1.1f, -1.0f, 1.1f);
			    glTexCoord2f(0.0, 0.0); // right-right
	 	       	glVertex3f(-1.1f, -1.0f, 1.1f);
			glEnd();
	
			glBegin(GL_TRIANGLES);
	 	       	glTexCoord2f(0.5, 0.5); // right-right
				glVertex3f(-0.5f, 1.0f, 0.0f);
	 	       	glTexCoord2f(0.0, 0.0); // right-right
				glVertex3f(-1.1f, -1.0f, -1.1f);
	 	       	glTexCoord2f(1.0, 0.0); // right-right
				glVertex3f(-1.1f, -1.0f, 1.1f);
			glEnd();

			glBegin(GL_TRIANGLES);
	 	       	glTexCoord2f(0.5, 0.5); // right-right
				glVertex3f(0.5f, 1.0f, 0.0f);
	 	       	glTexCoord2f(0.0, 0.0); // right-right
				glVertex3f(1.1f, -1.0f, -1.1f);
	 	       	glTexCoord2f(1.0, 0.0); // right-right
				glVertex3f(1.1f, -1.0f, 1.1f);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();	
	glPopMatrix();

	angle = angle + 1.0f;
}

void drwaPyramidRoof()
{

}

void drawRoof()
{
	glBegin(GL_QUADS);
	
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		// This is special requirement of drwaing quad
		// hence drawQuad function was not used
		// Quad1
        glTexCoord2f(1.0, 1.0); // right-right
		glVertex3f(-0.5f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
		glVertex3f(0.5f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
		glVertex3f(1.0f, -1.0f, 3.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
		glVertex3f(-1.0f, -1.0f, 3.0f);

		// QUAD2
        glTexCoord2f(1.0, 1.0); // right-right
		glVertex3f(-0.5f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
		glVertex3f(0.5f, 0.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
		glVertex3f(1.0f, -1.0f, -3.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
		glVertex3f(-1.0f, -1.0f, -3.0f);

	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, 0.0f, 0.0);
		glVertex3f(-1.0f, -1.0f, -3.0);
		glVertex3f(-1.0f, -1.0f, 3.0);
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

	glRotatef(-60, 1.0f, 0.0f, 0.0f);
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
    glPushMatrix();
    
	glTranslatef(0.0f, 0.0f, -10.0f);
    glScalef(8.0f, 2.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_background_mountain);

    glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0, 1.0); // right-right
	    glVertex3f(1.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
	    glVertex3f(-1.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
	    glVertex3f(-1.0f, -1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
	    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}


void drawBigGrass()
{

	void initializeBigGrassPoints();

	if(bigGrass_cordinates == NULL)
	{
		initializeBigGrassPoints();
	}

	for(int i=0; i<numBigGrass; i++)
	{
    	glPushMatrix();
    
		glTranslatef(bigGrass_cordinates[i].x, bigGrass_cordinates[i].y, bigGrass_cordinates[i].z);
    	glScalef(0.025f, 0.5f, 0.025f);
		glBindTexture(GL_TEXTURE_2D, texture_big_grass);

    	glBegin(GL_QUADS);
        	glTexCoord2f(1.0, 1.0); // right-right
	    	glVertex3f(1.0f, 0.2f, 0.0f);
	    	glTexCoord2f(0.0, 1.0); // right-right
	    	glVertex3f(-1.0f, 0.2f, 0.0f);
	    	glTexCoord2f(0.0, 0.0); // right-right
	    	glVertex3f(-1.0f, -0.2f, 0.0f);
	    	glTexCoord2f(1.0, 0.0); // right-right
	    	glVertex3f(1.0f, -0.2f, 0.0f);
    	glEnd();

		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    	glBegin(GL_QUADS);
        	glTexCoord2f(1.0, 1.0); // right-right
	    	glVertex3f(1.0f, 0.2f, 0.0f);
	    	glTexCoord2f(0.0, 1.0); // right-right
	    	glVertex3f(-1.0f, 0.2f, 0.0f);
	    	glTexCoord2f(0.0, 0.0); // right-right
	    	glVertex3f(-1.0f, -0.2f, 0.0f);
	    	glTexCoord2f(1.0, 0.0); // right-right
	    	glVertex3f(1.0f, -0.2f, 0.0f);
    	glEnd();
		

	/*glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); // right-right
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
	    glVertex3f(-1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
	    glVertex3f(-1.0f, -1.0f, 0.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
	    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
	*/

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	}
}


void initializeBigGrassPoints()
{

    bigGrass_cordinates = (point_t*)malloc(sizeof(point_t) * numBigGrass);

    for(int i = 0; i<numBigGrass; i++)	
    {
    	bigGrass_cordinates[i].x = getRandomCoord(-5.5f, 5.5f);
    	bigGrass_cordinates[i].y = -1.15f; 
    	bigGrass_cordinates[i].z = getRandomCoord(-3.0f, -10.0f);
    }
}

void drawGrass()
{

	void initializeGrassPoints();

	if(grass_cordinates == NULL)
	{
		initializeGrassPoints();
	}

	for(int i=0; i<numGrass; i++)
	{
    	glPushMatrix();
    
		glTranslatef(grass_cordinates[i].x, grass_cordinates[i].y, grass_cordinates[i].z);
    	glScalef(0.025f, 0.035f, 0.025f);
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, texture_grass);

    	glBegin(GL_QUADS);
        	glTexCoord2f(1.0, 1.0); // right-right
	    	glVertex3f(1.0f, 1.0f, 0.0f);
	    	glTexCoord2f(0.0, 1.0); // right-right
	    	glVertex3f(-1.0f, 1.0f, 0.0f);
	    	glTexCoord2f(0.0, 0.0); // right-right
	    	glVertex3f(-1.0f, -1.0f, 0.0f);
	    	glTexCoord2f(1.0, 0.0); // right-right
	    	glVertex3f(1.0f, -1.0f, 0.0f);
    	glEnd();

	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); // right-right
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 1.0); // right-right
	    glVertex3f(-1.0f, 1.0f, 0.0f);
	    glTexCoord2f(0.0, 0.0); // right-right
	    glVertex3f(-1.0f, -1.0f, 0.0f);
	    glTexCoord2f(1.0, 0.0); // right-right
	    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
	

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	}
}

void initializeGrassPoints()
{    
    grass_cordinates = (point_t*)malloc(sizeof(point_t) * numGrass);

    for(int i = 0; i<numGrass; i++)	
    {
    	grass_cordinates[i].x = getRandomCoord(-5.5f, 5.5f);
    	grass_cordinates[i].y = -1.18f; 
    	grass_cordinates[i].z = getRandomCoord(-3.0f, -10.0f);
    }


}
