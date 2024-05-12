#include "CarEnemy.h"

CarEnemy::CarEnemy()
{
    //ctor
    enemyX = 18;
    enemyY = 0;
    randomNumber = 100;
}

CarEnemy::~CarEnemy()
{
    //dtor
}

int CarEnemy::getEnemyX(){
    return this->enemyX;
}
int CarEnemy::getEnemyY(){
    return this->enemyY;
}
int CarEnemy::getEnemyShiftX(){
    return this->enemyShiftX;
}
int CarEnemy::getEnemyShiftY(){
    return this->enemyShiftY;
}
int CarEnemy::getRandomNumber(){
    return this->randomNumber;
}

void CarEnemy::setRandomNumber(int randomNumber){
    this->randomNumber = randomNumber;
}

void CarEnemy::setEnemyX(int enemyX){
    this->enemyX = enemyX;
}
void CarEnemy::setEnemyY(int enemyY){
    this->enemyY = enemyY;
}
void CarEnemy::setEnemyShiftX(int enemyShiftX){
    this->enemyShiftX = enemyShiftX;
}
void CarEnemy::setEnemyShiftY(int enemyShiftY){
    this->enemyShiftY = enemyShiftY;
}
void CarEnemy::draw(int enemyX, int enemyY, int enemyShiftX, int enemyShiftY){
    // chassis
    glBegin(GL_POLYGON);
        glColor3f(0, 0.965, 1);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY + 5 +enemyShiftY);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY + 5 +enemyShiftY);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY - 3  +enemyShiftY);
        glVertex2f(enemyX + 2 +enemyShiftX, enemyY - 4.5 +enemyShiftY);
        glVertex2f(enemyX - 2 +enemyShiftX, enemyY - 4.5 +enemyShiftY);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY - 3 +enemyShiftY);
    glEnd();

    // back chassis
    glBegin(GL_POLYGON);
        glColor3f(0.239, 0.349, 0.294);
        glVertex2f(enemyX - 3.5 +enemyShiftX, enemyY + 4.5 +enemyShiftY);
        glVertex2f(enemyX + 3.5 +enemyShiftX, enemyY + 4.5 +enemyShiftY);
        glVertex2f(enemyX + 3.5 +enemyShiftX, enemyY + 1 +enemyShiftY);
        glVertex2f(enemyX - 3.5 +enemyShiftX, enemyY + 1 +enemyShiftY);
    glEnd();

    // right window
    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(enemyX + 2.5 +enemyShiftX, enemyY + 0.5 +enemyShiftY);
        glVertex2f(enemyX + 3.5 +enemyShiftX, enemyY + 0.5 +enemyShiftY);
        glVertex2f(enemyX + 3.5 +enemyShiftX, enemyY - 2 +enemyShiftY);
        glVertex2f(enemyX + 2.5 +enemyShiftX, enemyY - 1 +enemyShiftY);
    glEnd();

    // left window
    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(enemyX - 2.5 +enemyShiftX, enemyY + 0.5 +enemyShiftY);
        glVertex2f(enemyX - 3.5 +enemyShiftX, enemyY + 0.5 +enemyShiftY);
        glVertex2f(enemyX - 3.5 +enemyShiftX, enemyY - 2 +enemyShiftY);
        glVertex2f(enemyX - 2.5 +enemyShiftX, enemyY - 1 +enemyShiftY);
    glEnd();

    // center window
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);
        glVertex2f(enemyX - 2 +enemyShiftX, enemyY + 1 +enemyShiftY);
        glVertex2f(enemyX + 2 +enemyShiftX, enemyY + 1 +enemyShiftY);
        glVertex2f(enemyX + 2 +enemyShiftX, enemyY - 1 +enemyShiftY);
        glVertex2f(enemyX - 2 +enemyShiftX, enemyY - 1 +enemyShiftY);
    glEnd();

    // front window
    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f(enemyX - 2 +enemyShiftX, enemyY - 1 +enemyShiftY);
        glVertex2f(enemyX + 2 +enemyShiftX, enemyY - 1 +enemyShiftY);
        glVertex2f(enemyX + 3.3 +enemyShiftX, enemyY - 2.7 +enemyShiftY);
        glVertex2f(enemyX - 3.3 +enemyShiftX, enemyY - 2.7 +enemyShiftY);
    glEnd();

    // left upper wheel
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY + 4 + enemyShiftY);
        glVertex2f(enemyX - 5 +enemyShiftX, enemyY + 4 + enemyShiftY);
        glVertex2f(enemyX - 5 +enemyShiftX, enemyY + 2 + enemyShiftY);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY + 2 + enemyShiftY);
    glEnd();

    // left down wheel
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY - 2 + enemyShiftY);
        glVertex2f(enemyX - 5 +enemyShiftX, enemyY - 2 + enemyShiftY);
        glVertex2f(enemyX - 5 +enemyShiftX, enemyY  +enemyShiftY);
        glVertex2f(enemyX - 4 +enemyShiftX, enemyY  +enemyShiftY);
    glEnd();

    // right upper wheel
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY + 4 + enemyShiftY);
        glVertex2f(enemyX + 5.1 +enemyShiftX, enemyY + 4 + enemyShiftY);
        glVertex2f(enemyX + 5.1 +enemyShiftX, enemyY + 2 + enemyShiftY);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY + 2 + enemyShiftY);
    glEnd();

    // right down wheel
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY - 2 + enemyShiftY);
        glVertex2f(enemyX + 5.1 +enemyShiftX, enemyY - 2 + enemyShiftY);
        glVertex2f(enemyX + 5.1 +enemyShiftX, enemyY  +enemyShiftY);
        glVertex2f(enemyX + 4 +enemyShiftX, enemyY  +enemyShiftY);
    glEnd();
}
