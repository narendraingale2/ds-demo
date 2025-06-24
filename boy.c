
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"

extern GLuint texture_eye;
extern GLuint texture_mouth;
extern GLuint texture_head;
extern GLuint texture_hair;
extern GLuint texture_shirt;
extern GLuint texture_face;

void drawBoy(void)
{
    // Torso

    // Torso
    //glColor3f(0.0, 0.4, 0.8);
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glScalef(1.2f, 1.0f, 1.0f);
	    glBindTexture(GL_TEXTURE_2D, texture_shirt);
	    gluQuadricTexture(quadric, GL_TRUE); 
        gluCylinder(quadric, 0.4, 0.4, 1.5, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // shoulder1
    //glColor3f(0.0, 0.4, 0.8);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glScalef(4.0f, 1.0f, 1.0f);
        gluSphere(quadric, 0.21, 30, 30);
	    glBindTexture(GL_TEXTURE_2D, 0);
	    gluQuadricTexture(quadric, GL_FALSE); 
    glPopMatrix();

    // Neck
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
	    glBindTexture(GL_TEXTURE_2D, texture_face);
	    gluQuadricTexture(quadric, GL_TRUE); 
        gluCylinder(quadric, 0.2, 0.2, 0.3, 20, 20);  // top radius, bottom, height
	    glBindTexture(GL_TEXTURE_2D, 0);
	    gluQuadricTexture(quadric, GL_FALSE); 
    glPopMatrix();

    // Arm1
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(-0.88f, 1.05f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef( 15, 0.0f, 1.0f, 0.0f);
	    glBindTexture(GL_TEXTURE_2D, texture_shirt);
	    gluQuadricTexture(quadric, GL_TRUE); 
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // Arm2
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0.88f, 1.05f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef( -15, 0.0f, 1.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
    glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(quadric, GL_FALSE); 
    
    // waist
    glColor3f(0.4, 0.2, 0.0);
    glPushMatrix();
        glTranslatef(0.0f, 0.47f, 0.0f);
        glScalef(2.3f, 1.0f, 2.0f);
        gluSphere(quadric, 0.21, 30, 30);
    glPopMatrix();


    // Leg 1
    glColor3f(0.4, 0.2, 0.0);
    glPushMatrix();
        glTranslatef(-0.3f, -0.5f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // Leg 2
    glColor3f(0.4, 0.2, 0.0);
    glPushMatrix();
        glTranslatef(0.3f, -0.5f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // Head
    //glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
	    gluQuadricTexture(quadric, GL_TRUE); 
        glTranslatef(0.0f, 2.7f, 0.0f);  // above torso
        glScalef(1.0f, 1.2f, 1.0f);
        glColor3f(1.0, 1.0, 1.0);
	    glBindTexture(GL_TEXTURE_2D, texture_face);
        gluSphere(quadric, 0.4, 20, 20);
	    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // hairs
    //glColor3f(0.1f, 0.1f, 0.1f); 
    glPushMatrix();
        glTranslatef(0.0f, 2.85f, 0.0f); // position on top of head
        glScalef(1.2f, 0.92f, 1.1f);      // flatten to make it cap-like
	    glBindTexture(GL_TEXTURE_2D, texture_hair);
	    gluQuadricTexture(quadric, GL_TRUE); 
        gluSphere(quadric, 0.35, 20, 20);
	    gluQuadricTexture(quadric, GL_FALSE); 
	    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

//    glPushMatrix();
//
//        glTranslatef(2.5f, 2.85f, 0.0f); // position on top of head
//        gluSphere(quadric, 0.35, 20, 20);
//    glPopMatrix(); 

    // Left Eyebrow
    glColor3f(0.1f, 0.1f, 0.1f); // dark color for eyebrow
    glPushMatrix();
        glTranslatef(-0.155f, 2.68f, 0.39f); // slightly above the left eye
        glScalef(0.1f, 0.02f, 0.02f);      // flatten to make it eyebrow-shaped
        gluSphere(quadric, 1.0, 10, 10);
    glPopMatrix();
    
    
    // Right Eyebrow
    glPushMatrix();
        glTranslatef(0.155f, 2.68f, 0.39f);
        glScalef(0.1f, 0.02f, 0.02f);
        gluSphere(quadric, 1.0, 10, 10);
    glPopMatrix();


    // eyes
    glColor3f(1.0f, 1.0f, 1.0f); // white sclera
    glPushMatrix();
        glTranslatef(-0.15f, 2.6f, 0.35f);
        glScalef(2.2f, 1.5f, 1.0f);
        gluSphere(quadric, 0.04, 30, 30); // larger eye
    glPopMatrix();


    // pupil1
    glColor3f(0.2f, 0.1f, 0.0f); // brown iris
    glPushMatrix();
        glTranslatef(-0.15f, 2.58, 0.38f);
        gluSphere(quadric, 0.03, 30, 30);
    glPopMatrix();
    

    glColor3f(1.0f, 1.0f, 1.0f); // white sclera
    glPushMatrix();
        glTranslatef(0.14f, 2.6f, 0.35f);
        glScalef(2.2f, 1.5f, 1.0f);
        gluSphere(quadric, 0.04, 20, 20); // larger eye
    glPopMatrix();

    // pupil1
    glColor3f(0.2f, 0.1f, 0.0f); // brown iris
    glPushMatrix();
        glTranslatef(0.15f, 2.58f, 0.38f);
        gluSphere(quadric, 0.03, 20, 20);
    glPopMatrix();

    // Nose (cone)
    //glColor3f(1.0f, 0.8f, 0.4f);
    glColor3f(0.9f, 0.7f, 0.5f);
    glPushMatrix();
        glTranslatef(0.0f, 2.45f, 0.38f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f); // point outward
        gluCylinder(quadric, 0.05, 0.0, 0.2, 10, 10); // small cone
    glPopMatrix();


    // mouth
    glColor3f(1.0f, 0.0f, 0.0f); // skin tone
    glPushMatrix();
        glTranslatef(0.0f, 2.38f, 0.3f);
        glScalef(3.0f, 1.0f, 1.0f);
        gluSphere(quadric, 0.05, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 0.8f, 0.6f); // skin tone
    glPushMatrix();
        glTranslatef(-0.45f, 2.70f, 0.0f); // position to the side of the head
        glRotatef(90, 0.0f, 1.0f, 0.0f);   // rotate to point outward
        glRotatef(-20, 0.0f, 0.0f, 1.0f);  // tilt slightly upward
        gluCylinder(quadric, 0.1, 0.1, 0.3, 10, 10); // cone shape
    glPopMatrix();
    
    // Right Elf Ear
    glPushMatrix();
        glTranslatef(0.45f, 2.7f, 0.0f);
        glRotatef(-90, 0.0f, 1.0f, 0.0f);
        glRotatef(20, 0.0f, 0.0f, 1.0f);
        gluCylinder(quadric, 0.1, 0.1, 0.3, 10, 10);
    glPopMatrix();

    

}