//
//  main.cpp
//  1102144004
//
//  Created by JaeseopKim on 2021/06/10.
//
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "imageloader.h"

GLUquadricObj* qobj = gluNewQuadric();
float pitch, yaw, roll;

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Clear the background
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);//Clear the colour buffer
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
    glEnable(GL_TEXTURE_2D);

    glRotatef(pitch, 1.0f, 0.0f, 0.0f); // Rotate our object around the y
    glRotatef(yaw, 0.0f, 1.0f, 0.0f); // Rotate our object around the y
    //printf("yaw : %f\n", yaw);
    //glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotate our object around the y

    glColor3f(1.0f, 1.0f, 1.0f);

    //gluCylinder(qobj,0.5f,0.5f,0.2f,100,100); // quad, base, top, height, slices, stacks
    
    Image *image = loadBMP("./bitcoin_24.bmp");
    
    glBindTexture(GL_QUADS, loadTexture(image));
    glPushMatrix();
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0, 0);
    glVertex3d(-0.5, -0.5, 0.0);
    
    glTexCoord2f(0, 1);
    glVertex3d(-0.5, 0.5, 0.0);
    
    glTexCoord2f(1, 1);
    glVertex3d(0.5, 0.5, 0.0);
    
    glTexCoord2f(1, 0);
    glVertex3d(0.5, -0.5, 0.0);
     
    glEnd();
    
    glPushMatrix();
    glPopMatrix();
    
    
    glutSwapBuffers();
    
    glFlush(); // Flush the OpenGL buffers to the window
    //glEnd();
}

void special(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        yaw += 1.0;
    }
    else if (key == GLUT_KEY_RIGHT) {
        yaw -= 1.0;
    }
    else if (key == GLUT_KEY_UP) {
        pitch += 1.0;
    }
    else if (key == GLUT_KEY_DOWN) {
        pitch -= 1.0;
    }
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("1102144004");
    glutDisplayFunc(display);
    
    glutSpecialFunc(special);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    
    return 0;
}
