/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <ctime>
#include "way.h"

static int slices = 16;
static int stacks = 16;

int phyWidth= 550;
int phyHeight= 650;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2;
int centerY=logHeight/2;
int sqWid= 10;
int alphaX=0; int alphaY=0;
Way wayL[15], wayR[15];
bool firstFrame = true;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
// Function to be called repeatedly
void timer(int value) {
    // Do something
    glutPostRedisplay(); // Trigger redisplay
    glutTimerFunc(30, timer, 0); // Register the timer again for the next second (1000 milliseconds)
}
void carPlayer(){
    // chassis
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(centerX-6 + alphaX, centerY- 10 + alphaY);
        glVertex2f(centerX+9 + alphaX, centerY- 10 + alphaY);
        glVertex2f(centerX+9 + alphaX, centerY+ 10 + alphaY);
        glVertex2f(centerX-6 + alphaX, centerY+ 10 + alphaY);
    glEnd();

    // front window
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(centerX-5 + alphaX, centerY + 8 + alphaY);
        glVertex2f(centerX+8 + alphaX, centerY + 8 + alphaY);
        glVertex2f(centerX+7 + alphaX, centerY + 5 + alphaY);
        glVertex2f(centerX-4 + alphaX, centerY + 5 + alphaY);
    glEnd();

    // left window
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(centerX-5 + alphaX, centerY + 8 + alphaY);
        glVertex2f(centerX+8 + alphaX, centerY + 8 + alphaY);
        glVertex2f(centerX+7 + alphaX, centerY + 5 + alphaY);
        glVertex2f(centerX-4 + alphaX, centerY + 5 + alphaY);
    glEnd();
}

void yellowPavement(int x, int y){
    glColor3f(1, 0.835, 0.071);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+5);
        glVertex2f(x+4,y+7);
        glVertex2f(x+4,y+2);
    glEnd();
}
void blackPavement(int x, int y){
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+5);
        glVertex2f(x+4,y+7);
        glVertex2f(x+4,y+2);
    glEnd();
}
void pavements(){

    // left yellow

    for(int y = 1; y <= 100; y = y + 10){
        yellowPavement(0, y);
    }
    // left black
    for(int y = -4; y <= 100; y = y + 10){
        blackPavement(0, y);
    }
    // right yellow
    for(int y = 1; y <= 100; y = y + 10){
        yellowPavement(96, y);
    }
    // right black
    for(int y = -4; y <= 100; y = y + 10){
        blackPavement(96, y);
    }
}
void smallWay(int x, int y){
    glColor3f(1, 0.835, 0.071);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+7);
        glVertex2f(x+2,y+7);
        glVertex2f(x+2,y);
    glEnd();

}
void way(){

    if(firstFrame){
        for(int y = 5, i = 0; y <= 150; y = y + 10, i++){
            wayL[i].setX(33);
            wayL[i].setY(y);
            wayR[i].setX(67);
            wayR[i].setY(y);
            wayL[i].draw(wayL[i].getX(), wayL[i].getY()+wayL[i].getCounter());
            wayR[i].draw(wayR[i].getX(), wayR[i].getY()+wayR[i].getCounter());
            wayL[i].decCounter();
            wayR[i].decCounter();
        }
        firstFrame = false;
    }
    else{
        for(int i = 0; i<15 ;i++){
            if((wayL[i].getY() + wayL[i].getCounter() + 7) < -10){
                wayL[i].setY(103);
                wayL[i].setCounter(0);
                wayR[i].setY(103);
                wayR[i].setCounter(0);
            }

            wayL[i].draw(wayL[i].getX(), wayL[i].getY()+wayL[i].getCounter());
            wayR[i].draw(wayR[i].getX(), wayR[i].getY()+wayR[i].getCounter());

            wayL[i].decCounter();
            wayR[i].decCounter();

        }
    }

}
void Keyboard(unsigned char key, int x, int y) {
     if(key == 'w')
        alphaY += 5;
     if(key == 's')
        alphaY -= 5;
     if(key == 'a')
        alphaX -= 5;
     if(key == 'd')
        alphaX += 5;
     glutPostRedisplay();
 }

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pavements();
    way();
    carPlayer();


    glutSwapBuffers();
    glFlush();
}

void init2D()
{
    glClearColor(0.49, 0.471, 0.471, 1);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}



static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth,phyHeight);
    glutInitWindowPosition(350,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Car Avoidance");

    init2D();

    glutDisplayFunc(display);

    // glutKeyboardFunc(Keyboard);
    glutTimerFunc(0.1, timer, 0.1);


    glutMainLoop();

    return EXIT_SUCCESS;
}
