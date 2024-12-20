#include "Figure.h"

Figure::Figure(int size, int offsetX, int offsetY) :
    m_size(size),
    m_offsetX(offsetX),
    m_offsetY(offsetY),
    m_isDragging(false),
    m_previousX(0),
    m_previousY(0)
{
}

void Figure::moveTo(int x, int y)
{

}

void Figure::move(int x, int y)
{
    m_offsetX = x;
    m_offsetY = y;
}

void Figure::startDragging(int x, int y)
{

}

void Figure::drag(int x, int y)
{

}

bool Figure::isDragging() const
{
    return m_isDragging;
}

void Figure::stopDragging(int x, int y)
{
    m_isDragging = false;
}
