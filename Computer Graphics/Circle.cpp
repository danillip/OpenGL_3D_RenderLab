#include "Circle.h"
#include <math.h>

Circle::Circle(int size, int offsetX, int offsetY) :
    Figure(size, offsetX, offsetY)
{
}

void Circle::draw()
{

}

bool Circle::isInnerPoint(int x, int y)
{
    return true;
}
