
#include<stdio.h>
#include "model.h"
#include "utility.h"
#include "shape.h"

void drawBoy(void)
{
    // Torso
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Torso
    glColor3f(0.0, 0.4, 0.8);
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadric, 0.6, 0.6, 1.5, 20, 20);  // top radius, bottom, height
        glColor3f(1.0f, 0.0f, 0.0);
    glPopMatrix();

    // Neck
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 0.3, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // Arm1
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(-0.88f, 1.05f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef( 15, 0.0f, 1.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
    glPopMatrix();

    // shoulder1
    glColor3f(0.0, 0.4, 0.8);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f);
        glScalef(4.0f, 1.0f, 2.1f);
        gluSphere(quadric, 0.21, 30, 30);
    glPopMatrix();
    
    // waist
    //glColor3f(1.0f, 0.8, 0.6);
    glColor3f(0.4, 0.2, 0.0);
    glPushMatrix();
        glTranslatef(0.0f, 0.47f, 0.0f);
        glScalef(2.6f, 1.0f, 2.1f);
        gluSphere(quadric, 0.21, 30, 30);
    glPopMatrix();

    // Arm2
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0.88f, 1.05f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef( -15, 0.0f, 1.0f, 0.0f);
        gluCylinder(quadric, 0.2, 0.2, 1.0, 20, 20);  // top radius, bottom, height
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
    glColor3f(1.0, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0.0f, 2.7f, 0.0f);  // above torso
        glScalef(1.0f, 1.2f, 1.0f);
        gluSphere(quadric, 0.4, 20, 20);
    glPopMatrix();

}