#include "Box.h"

Box::Box(int size, int offsetX, int offsetY) :
    Figure(size, offsetX, offsetY)
{
}

void Box::draw()
{
}

bool Box::isInnerPoint(int x, int y)
{
	return false;
}
