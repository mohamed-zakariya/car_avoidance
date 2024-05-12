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
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <random>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iomanip> // For std::setw
#include <sstream> // For std::ostringstream
#include <ctime>
#include "way.h"
#include "CarEnemy.h"

using namespace std;

static int slices = 16;
static int stacks = 16;

int phyWidth= 550;
int phyHeight= 650;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2;
int centerY=logHeight/2;
int heroX = 50;
int heroY = 15;
int sqWid= 10;
int alphaX=0; int alphaY=0;


int status=0;
int cx1=50,cy1=40,cx2=50,cy2=50,cx3=50,cy3=60;
int mouseX,mouseY;


Way wayL[15], wayR[15];
CarEnemy carEnemy[10];
bool firstFrame = true;
bool firstFrameCarEnemy = true;

int score = 0;
int lifes = 3;
int enemyX = 22;
int enemyY = 85;
int enemyShiftX = 0;
int enemyShiftY = 10;

int minutes = 1;
int seconds = 0;
/* GLUT callback Handlers */

// Function to be called repeatedly

void updateTimer() {
    if(seconds == 0 && minutes == 0){
        status = 5;
    }
    if (seconds == 0) {
        if (minutes > 0) {
            minutes--;
            seconds = 59;
        }
    } else {
        seconds--;
    }
}

// Function to format the timer as a string
string formatTimer() {
    ostringstream oss;
    oss << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
    return oss.str();
}

void timer2(int value) {
    updateTimer(); // Update the timer
    glutTimerFunc(1000, timer2, 0); // Register the timer again for the next second (1000 milliseconds)
}


void timer(int value) {
    // Do something
    if(status == 3){
        score++;
    }
    glutPostRedisplay(); // Trigger redisplay
    glutTimerFunc(30, timer, 0); // Register the timer again for the next second (1000 milliseconds)
}


void printSome(char *str,int x,int y) {
 glColor3f (1.0, 1.0, 1.0);
 glRasterPos2d(x,y);
 for (int i=0;i<strlen(str);i++)
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
 glFlush();
}
void mouseClick(int btn, int state, int x, int y)
{if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
{ mouseX = x;
mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
mouseY = phyHeight - y;
mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
if( mouseX>=(cx1-sqWid/2) && mouseX<=(cx1+sqWid/2) && mouseY >=(cy1-sqWid/2) && mouseY <=(cy1+sqWid/2))
{
status=1;
}
if( mouseX>=(cx2-sqWid/2) && mouseX<=(cx2+sqWid/2) && mouseY >=(cy2-sqWid/2) && mouseY <=(cy2+sqWid/2))
{
status=2;
}
if( mouseX>=(cx3-sqWid/2) && mouseX<=(cx3+sqWid/2) && mouseY >=(cy3-sqWid/2) && mouseY <=(cy3+sqWid/2))
{
status=3;
}
}
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
status=0;
}
glutPostRedisplay();
}


void drawSquares(){
glColor3f(0.949, 0.02, 0.235);
glBegin(GL_POLYGON);
glVertex2f(cx1-sqWid-2, cy1-sqWid/2); // x, y
glVertex2f(cx1+sqWid+2, cy1-sqWid/2); // x, y
glVertex2f(cx1+sqWid+2, cy1+sqWid/2); // x, y
glVertex2f(cx1-sqWid-2, cy1+sqWid/2); // x, y
glEnd();

glColor3f(0.02, 0.902, 0.949); //
glBegin(GL_POLYGON);
glVertex2f(cx3-sqWid-2, cy3-sqWid/2); // x, y
glVertex2f(cx3+sqWid+2, cy3-sqWid/2); // x, y
glVertex2f(cx3+sqWid+2, cy3+sqWid/2); // x, y
glVertex2f(cx3-sqWid-2, cy3+sqWid/2); // x, y
glEnd();

glColor3f(0,0,0);
printSome("Start Game", cx3-8, cy3);
//printSome("How to Play?", cx2-10, cy2);
printSome("EXIT", cx1-4, cy1);

}

void carPlayer(){
    // chassis
    glColor3f(0.016, 0.353, 0.671);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-6 + alphaX, heroY- 11 + alphaY);
        glVertex2f(heroX+9 + alphaX, heroY- 11 + alphaY);
        glVertex2f(heroX+9 + alphaX, heroY+ 10 + alphaY);
        glVertex2f(heroX-6 + alphaX, heroY+ 10 + alphaY);
    glEnd();

    // front window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-5 + alphaX, heroY + 8 + alphaY);
        glVertex2f(heroX+8 + alphaX, heroY + 8 + alphaY);
        glVertex2f(heroX+7 + alphaX, heroY + 5 + alphaY);
        glVertex2f(heroX-4 + alphaX, heroY + 5 + alphaY);
    glEnd();

    // left up window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-5 + alphaX, heroY + 4 + alphaY);
        glVertex2f(heroX-3 + alphaX, heroY + 2 + alphaY);
        glVertex2f(heroX-3 + alphaX, heroY - 2 + alphaY);
        glVertex2f(heroX-5 + alphaX, heroY - 2 + alphaY);
    glEnd();
    // left down window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-5 + alphaX, heroY - 3 + alphaY);
        glVertex2f(heroX-3 + alphaX, heroY - 3 + alphaY);
        glVertex2f(heroX-3 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX-5 + alphaX, heroY - 7 + alphaY);
    glEnd();

    // right up window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX+8 + alphaX, heroY + 4 + alphaY);
        glVertex2f(heroX+6 + alphaX, heroY + 2 + alphaY);
        glVertex2f(heroX+6 + alphaX, heroY - 2 + alphaY);
        glVertex2f(heroX+8 + alphaX, heroY - 2 + alphaY);
    glEnd();
    // right down window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX+8 + alphaX, heroY - 3 + alphaY);
        glVertex2f(heroX+6 + alphaX, heroY - 3 + alphaY);
        glVertex2f(heroX+6 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX+8 + alphaX, heroY - 7 + alphaY);
    glEnd();

    // bottom window
    glColor3f(0.027, 0.875, 0.98);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-5 + alphaX, heroY - 10 + alphaY);
        glVertex2f(heroX+8 + alphaX, heroY - 10 + alphaY);
        glVertex2f(heroX+7 + alphaX, heroY - 8 + alphaY);
        glVertex2f(heroX-4 + alphaX, heroY - 8 + alphaY);
    glEnd();
    // left upper wheels
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-7 + alphaX, heroY + 6 + alphaY);
        glVertex2f(heroX-6 + alphaX, heroY + 6 + alphaY);
        glVertex2f(heroX-6 + alphaX, heroY + 4 + alphaY);
        glVertex2f(heroX-7 + alphaX, heroY + 4 + alphaY);
    glEnd();
    // left down wheels
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(heroX-7 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX-6 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX-6 + alphaX, heroY - 4 + alphaY);
        glVertex2f(heroX-7 + alphaX, heroY - 4 + alphaY);
    glEnd();

    // right upper wheels
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(heroX+9 + alphaX, heroY + 6 + alphaY);
        glVertex2f(heroX+10 + alphaX, heroY + 6 + alphaY);
        glVertex2f(heroX+10 + alphaX, heroY + 4 + alphaY);
        glVertex2f(heroX+9 + alphaX, heroY + 4 + alphaY);
    glEnd();
    // right down wheels
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2f(heroX+9 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX+10 + alphaX, heroY - 6 + alphaY);
        glVertex2f(heroX+10 + alphaX, heroY - 4 + alphaY);
        glVertex2f(heroX+9 + alphaX, heroY - 4 + alphaY);
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
void showCarEnemy(){

    float heroLeft = centerX - 6 + alphaX;
    float heroRight = centerX + 9 + alphaX;
    float heroTop = heroY + 10 + alphaY;
    float heroBottom = heroY- 11 + alphaY;


    if(firstFrameCarEnemy){

        carEnemy[0].setEnemyY(110);
        carEnemy[1].setEnemyY(160);
        carEnemy[2].setEnemyY(210);
        carEnemy[0].draw(enemyX, carEnemy[0].getEnemyY(), enemyShiftX, enemyShiftY);
        carEnemy[1].draw(enemyX, carEnemy[1].getEnemyY(), enemyShiftX, enemyShiftY);
        carEnemy[2].draw(enemyX, carEnemy[2].getEnemyY(), enemyShiftX, enemyShiftY);
        firstFrameCarEnemy = false;
    }
    else{

        for(int i = 0; i <= 2; i++){

            float enemyLeft = carEnemy[i].getEnemyX() - 4 + carEnemy[i].getRandomNumber();
            float enemyRight = carEnemy[i].getEnemyX() + 4 +carEnemy[i].getRandomNumber(); // Assuming enemy is 3 units wide
            float enemyTop = carEnemy[i].getEnemyY() + 5;   // Assuming enemy is 3 units tall
            float enemyBottom = carEnemy[i].getEnemyY() - 4.5;
            // Generate a random number between 0 and 2 to select one of the three values
            if(carEnemy[i].getRandomNumber() == 100){

                int randomIndex = rand() % 3; // Generates 0, 1, or 2

                int randomNumber;

                // Map the random index to the desired number
                if (randomIndex == 0) {
                    randomNumber = 0;
                } else if (randomIndex == 1) {
                    randomNumber = 30;
                } else {
                    randomNumber = 60;
                }
                carEnemy[i].setRandomNumber(randomNumber);
            }
            if(carEnemy[i].getEnemyY() == -10 || carEnemy[i].getEnemyY() == -50){
                carEnemy[i].setEnemyY(120);
                carEnemy[i].setRandomNumber(100);
            }
            if(!(heroLeft > enemyRight || heroRight < enemyLeft || heroTop < enemyBottom || heroBottom > enemyTop)){
                carEnemy[i].setEnemyY(-15);
                carEnemy[i].setEnemyY(carEnemy[i].getEnemyY()-1);
                lifes--;

                continue;
            }

           carEnemy[i].draw(enemyX, carEnemy[i].getEnemyY(), enemyShiftX+carEnemy[i].getRandomNumber(), enemyShiftY);
           carEnemy[i].setEnemyY(carEnemy[i].getEnemyY()-1);

        }
    }

}
void specialKeyboard(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            if (alphaX == 0 || alphaX == 30)
                alphaX -= 30;
            break;
        case GLUT_KEY_RIGHT:
            if (alphaX == -30 || alphaX == 0)
                alphaX += 30;
            break;
    }
    //glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y) {
     if(key == 'a' && (alphaX == 0 || alphaX == 30))
        alphaX -= 30;
     if(key == 'd' && (alphaX == -30 || alphaX == 0))
        alphaX += 30;
   //  glutPostRedisplay();
 }

void ScoreFn(){
    string scoreString = "Score: " + to_string(score);
    // Call printSome with the string and coordinates
    printSome(const_cast<char*>(scoreString.c_str()), 77, 95);
}
void lifesfn(){
    string lifeString = "Lifes: " + to_string(lifes);
    // Call printSome with the string and coordinates
    printSome(const_cast<char*>(lifeString.c_str()), 10, 95);
}
void finalScene(){
    string scoreString = "your score is " + to_string(score);
    printSome(const_cast<char*>(scoreString.c_str()), 38, 60);
    printSome("Game Over", 42, 45);
}
void winScene(){
    printSome("You Win!", 42, 50);
}
void showTimer(){
    string timerString = formatTimer();
    printSome(const_cast<char*>(timerString.c_str()), 11, 90);
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(status == 0){
        glClearColor(0, 0, 0, 1);
        drawSquares();
    }
    else if(status == 1){
        exit(EXIT_SUCCESS);
    }

    else if(status == 3){
        glClearColor(0.49, 0.471, 0.471, 1);
        pavements();
        way();
        //carEnemy();
        showCarEnemy();
        carPlayer();
        ScoreFn();
        lifesfn();
        showTimer();
        if(lifes == 0){
            status = 4;
        }
    }
    else if(status == 4){
        glClearColor(0, 0, 0, 1);
        finalScene();
    }
    else if (status == 5){
        glClearColor(0, 0, 0, 1);
        winScene();
    }


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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth,phyHeight);
    glutInitWindowPosition(350,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Car Avoidance");

    init2D();

    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouseClick);


    // glutKeyboardFunc(Keyboard);
    glutTimerFunc(0.1, timer, 0.1);
    glutTimerFunc(1000, timer2, 0); // Start the timer




    glutMainLoop();

    return EXIT_SUCCESS;
}
