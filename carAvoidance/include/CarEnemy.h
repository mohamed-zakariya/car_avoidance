#ifndef CARENEMY_H
#define CARENEMY_H

#include <GL/glut.h>


class CarEnemy
{
    public:
        CarEnemy();
        virtual ~CarEnemy();

        void setEnemyX(int enemyX);
        void setEnemyY(int enemyY);
        void setEnemyShiftX(int enemyShiftX);
        void setEnemyShiftY(int enemyShiftY);
        void setRandomNumber(int randomNumber);

        int getEnemyX();
        int getEnemyY();
        int getEnemyShiftX();
        int getEnemyShiftY();
        int getRandomNumber();

        void draw(int enemyX, int enemyY, int enemyShiftX, int enemyShiftY);

    protected:

    private:
        int enemyX;
        int enemyY;
        int enemyShiftX;
        int enemyShiftY;
        int randomNumber;
};

#endif // CARENEMY_H
