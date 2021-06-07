#include "objectfordrawing.h"

ObjectForDrawing::ObjectForDrawing()
{

}
void ObjectForDrawing:: setX(int newX)
{
this->x=newX;
}
void ObjectForDrawing:: setY(int newY)
{
    this->y=newY;
}

//void ObjectForDrawing::setColor(Color color)
//{
//    this->color=color;
//}

//Color ObjectForDrawing::getColor()
//{
//    return this->color;
//}

int ObjectForDrawing::getWeight()
{
    return  this->weight;
}

void ObjectForDrawing::setWeigt(int weight)
{
    this->weight=weight;
    this->pen.setWidth(this->weight);
}

QPen ObjectForDrawing::getPen()
{
    return this->pen;
}

QColor ObjectForDrawing::getColor()
{
    return this->color;
}

void ObjectForDrawing::setColor(int red, int green, int blue)
{
    this->color.setRed(red);
    this->color.setGreen(green);
    this->color.setBlue(blue);
    this->color.setAlpha(255);
    this->pen.setColor(this->color);
}
int ObjectForDrawing:: getX()
{
    return this->x;
}
int ObjectForDrawing:: getY()
{
    return this->y;
}

