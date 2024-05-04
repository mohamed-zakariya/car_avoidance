#ifndef WAY_H
#define WAY_H

#include <GL/glut.h>

class Way
{
    public:
        Way();
        virtual ~Way();

        int getX();
        int getY();
        int getCounter();

        void setX(int x);
        void setY(int y);
        void setCounter(int counter);
        void decCounter();

        void draw(int x, int y);


    protected:

    private:
        int x;
        int y;
        int counter;
};

#endif // WAY_H
