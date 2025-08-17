#include<stdio.h>

#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLfloat cameraZ;
extern FILE *gpFile;
extern point_t point_vertices[100];
extern BOOL gbRotateBoy;
extern GLfloat boyAngle;
extern GLfloat location[16];
extern GLuint texture_inner_wall;
extern BOOL animateEye;
extern BOOL rotate_left;

extern GLfloat xLook;
extern GLfloat yLook;
extern GLfloat zLook;
extern GLfloat xLookAt;
extern GLfloat yLookAt;
extern GLfloat zLookAt;

extern GLuint texture_colured_tree;
extern GLuint texture_coco_tree;
extern GLuint texture_big_tree;
extern point_t* tree_cordinates;
extern int numTrees;
GLfloat camX=5.0f, camY=4.5f, camZ=-8.0f;

GLfloat fadeOutScene1 = 0.0f;
GLfloat fadeInScene2  = 1.0f; 
GLfloat fadeOutScene2 = 0.0f;
GLfloat fadeInScene3 = 1.0f; 
GLfloat fadeOutScene3 = 0.0f;

void drawScene1()
{
    void initializeTreePoints(); 
    void fadeOutOfScene(GLfloat*);

    static BOOL startMovingInside = FALSE;
    static BOOL sceneCompleted = FALSE;

    static int waitCounter = 0;
    
    if(tree_cordinates == NULL)
    {
       initializeTreePoints(); 
    }

    gluLookAt(camX + xLook, camY + yLook, camZ + zLook, 
            camX + xLook, camY + yLook, camZ-1 + zLook, 
            0.0f, 1.0f, 0.0f);

    // Drawing stars
    // x = 12 - -12
    // y = 2.5 - 7
    // z = -15 - -22
    drawPoints(1000);

    // Drawing moon
    // x=5 y=4.5 z=-13
    drawMoon();

    // Draw background of mountainsl
    // x=0 y=0 z=-10
    drawBackgroundMountain();
	
    // Draw ground 
    // x = -8, 8 y = -1.2 z= -10, 0
    drawGround();

	drawHouse(FALSE);
    
    glPushMatrix();
        glTranslatef(4.0f, -1.0f, -9.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -9.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -5.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -5.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-2.0f, -1.0f, -9.5f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    drawGrass();

    drawBigGrass();

	drawColoredTree(2.0f, -0.7f, -7.0f, texture_colured_tree);

	drawColoredTree(-5.0f, -0.62f, -8.0f, texture_coco_tree);
	
    drawColoredTree(-4.0f, -0.62f, -7.0f, texture_coco_tree);
    
    drawColoredTree(-3.0f, -0.62f, -8.0f, texture_coco_tree);
	

	drawColoredTree(5.5f, -0.62f, -8.0f, texture_coco_tree);
	
    drawColoredTree(5.0f, -0.62f, -7.0f, texture_coco_tree);
    
   
    // Big tree
    drawColoredTree(4.0f, -0.62f, -8.0f, texture_big_tree);

    //drawCocoTree();
    
   // Camera movements  
    if(camZ < 0.0f && startMovingInside == FALSE)
    {
        camX -= 5.0f * 0.001f;
        camY -= 4.5f * 0.001f;
        camZ += 8.0f * 0.001f;
        //camX -= 5.0f * 0.1f;
        //camY -= 4.5f * 0.1f;
        //camZ += 8.0f * 0.1f;
    }
    else if(camZ > 0.0f && startMovingInside == FALSE)
    {
        if(waitCounter <= 500)
            waitCounter = waitCounter + 1.0f;
        else
        {

            startMovingInside = TRUE;
            waitCounter = 0;
        }
        
    }
    else if(startMovingInside == TRUE && camZ > -5.7f)
    {
        camZ -= 8.0f * 0.001f;
        camY -= 0.5f * 0.001f;
    }
    else if(sceneCompleted == FALSE && camZ< -5.7f)
    {
        if(waitCounter <= 500)
            waitCounter = waitCounter + 1.0f;
        else
        {
            sceneCompleted = TRUE;
            waitCounter = 0;
        }
    }
    else if(sceneCompleted == TRUE)
    {
        fadeOutOfScene(&fadeOutScene1);
    }

}

void initializeTreePoints()
{    
    tree_cordinates = (point_t*)malloc(sizeof(point_t) * numTrees);

    for(int i = 0; i<numTrees; i++)	
    {
    	tree_cordinates[i].x = getRandomCoord(-5.0f, 5.0f);
    	tree_cordinates[i].y = -0.77f; 
    	tree_cordinates[i].z = getRandomCoord(-5.0f, -10.0f);
    }


}

void drawScene2()
{
    void fadeInScene(GLfloat*);
    static GLfloat girl_walk_z = -3.0f;
    static GLfloat girl_walk_y = -1.1f;
    // back wall
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glPushMatrix();
		glTranslatef(0.0f, 0.0f, -16.0f);
        glScalef(20.0f, 10.0f, 1.0f);
        //glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture_inner_wall);
        drawQuad();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(-10.0f, 0.0f, -6.0f);
        glScalef(8.0f, 8.0f, 1.0f);
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // side wall
    glPushMatrix();
		glTranslatef(10.0f, 0.0f, -6.0f);
        glScalef(8.0f, 8.0f, 1.0f);
        glRotatef(-75.0f, 0.0f, 1.0f, 0.0f);
        glColor4f(166.0f/255.0f, 194.0f/255.0f, 170.0f/255.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // floor
    glPushMatrix();
		glTranslatef(0.0f, -5.0f, -8.0f);
        glScalef(20.0f, 40.0f, 1.0f);
        glRotatef(-88.0f, 1.0f, 0.0f, 0.0f);
        glColor4f(150.0f/255.0f, 75.0f/255.0f, 0.0f, 1.0f);
        drawQuad();
    glPopMatrix();

    // draw girl
    glPushMatrix();
		glTranslatef(2.0f, -2.0f, -6.2f);
        glScalef(0.4f, 0.5f, 1.0f);
        glTranslatef(0.0f, girl_walk_y, girl_walk_z);
        if(animateEye == TRUE)
            drawGirl(TRUE);
        else 
            drawGirl(FALSE);
    glPopMatrix();

    glPopMatrix();
    fprintf(gpFile, "FadeIn scene2 = %f\n", fadeInScene2);

    if(fadeInScene2 < 0.0f)
    {
        
        if(girl_walk_z <= 9.0f)
            girl_walk_z = girl_walk_z + 0.01f;
        else
            fadeOutOfScene(&fadeOutScene2);
    }
    else
    {
        camX = 0.0f;
        camY = 0.0f;
        camZ = 0.0;
        fadeInScene(&fadeInScene2);
    }

}

void drawScene3()
{
    camX = 0;
    camY = 0;
    camZ = 0;
    gluLookAt(camX + xLook, camY + yLook, camZ + zLook, 
            camX + xLook, camY + yLook, camZ-1 + zLook, 
            0.0f, 1.0f, 0.0f);
    // Drawing stars
    // x = 12 - -12
    // y = 2.5 - 7
    // z = -15 - -22
    drawPoints(1000);

    // Drawing moon
    // x=5 y=4.5 z=-13
    drawMoon();

    // Draw background of mountainsl
    // x=0 y=0 z=-10
    drawBackgroundMountain();
	
    // Draw ground 
    // x = -8, 8 y = -1.2 z= -10, 0
    drawGround();
    
    glPushMatrix();
        glTranslatef(4.0f, -1.0f, -9.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -9.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -5.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-5.0f, -1.0f, -5.0f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-2.0f, -1.0f, -9.5f);
        glScalef(1.0f, 0.2f, 0.5f);
        drawHouseMain(FALSE);
    glPopMatrix();
    
    drawGrass();

    drawBigGrass();

	drawColoredTree(2.0f, -0.7f, -7.0f, texture_colured_tree);

	drawColoredTree(-5.0f, -0.62f, -8.0f, texture_coco_tree);
	
    drawColoredTree(-4.0f, -0.62f, -7.0f, texture_coco_tree);
    
    drawColoredTree(-3.0f, -0.62f, -8.0f, texture_coco_tree);
	

	drawColoredTree(5.5f, -0.62f, -8.0f, texture_coco_tree);
	
    drawColoredTree(5.0f, -0.62f, -7.0f, texture_coco_tree);
    
   
    // Big tree
    drawColoredTree(4.0f, -0.62f, -8.0f, texture_big_tree);
    
    glPushMatrix();
        glTranslatef(0.2f, -1.0f, -2.0f);
        glScalef(0.05f, 0.05f, 1.0f);
        if(animateEye == TRUE)
            drawGirl(TRUE);
        else 
            drawGirl(FALSE);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-1.0f, -1.0f + yLookAt, -4.0f + zLookAt);
        glScalef(0.2f, 0.2f, 1.0f);
        fprintf(gpFile, "Girl position yLookAt = %f", yLookAt);
        drawAnimatedButterfly();
    glPopMatrix();

    if(fadeInScene3 > 0.0f)
    {
       fadeInScene(&fadeInScene3); 
    }
}

void fadeOutOfScene(GLfloat* fadeOutAlpha)
{

	//static GLfloat fadeOut = 0;

	glColor4f(0.0f, 0.0f, 0.0f, *fadeOutAlpha);
	glBegin(GL_QUADS);
		glVertex3f(camX + 1.0f, camY + 1.0f, camZ -0.1f);
		glVertex3f(camX -1.0f,  camY + 1.0f, camZ -0.1f);
		glVertex3f(camX -1.0f, 	camY  - 1.0f, camZ -0.1f);
		glVertex3f(camX + 1.0f, camY - 1.0f, camZ -0.1f);
	glEnd();

	if(*fadeOutAlpha <= 1.0f)
    {
		*fadeOutAlpha = *fadeOutAlpha + 0.003f;
    }
    else
    {
        camX = 0.0f;
        camY = 0.0f;
        camZ = 0.0;
    }
}

void fadeInScene(GLfloat* fadeInAlpha)
{
    fprintf(gpFile, "Alphs = %f Camaer positions camX = %f, camy = %f, camz = %f\n", *fadeInAlpha, camX, camY, camZ);
	glColor4f(0.0f, 0.0f, 0.0f, *fadeInAlpha);
	glBegin(GL_QUADS);
		glVertex3f(camX + 1.0f, camY + 1.0f, camZ -0.1f);
		glVertex3f(camX -1.0f,  camY + 1.0f, camZ -0.1f);
		glVertex3f(camX -1.0f, 	camY  - 1.0f, camZ -0.1f);
		glVertex3f(camX + 1.0f, camY - 1.0f, camZ -0.1f);
	glEnd();

	if(*fadeInAlpha >= 0.0f)
    {
		*fadeInAlpha = *fadeInAlpha - 0.003f;
    }

}
