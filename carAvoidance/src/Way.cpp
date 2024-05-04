#include "Way.h"

Way::Way()
{
    //ctor
    x = 0;
    y = 0;
    counter = 0;
}

Way::~Way()
{
    //dtor
}

int Way::getX(){
    return this->x;
}
int Way::getY(){
    return this->y;
}
int Way::getCounter(){
    return this->counter;
}
void Way::setX(int x){
    this->x = x;
}
void Way::setY(int y){
    this->y = y;
}
void Way::setCounter(int counter){
    this->counter = counter;
}
void Way::decCounter(){
    this->counter -= 1;
}
void Way::draw(int x, int y){
    glColor3f(1, 0.835, 0.071);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+7);
        glVertex2f(x+2,y+7);
        glVertex2f(x+2,y);
    glEnd();
}
