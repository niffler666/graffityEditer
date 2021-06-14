#include "objectfordrawing.h"

ObjectForDrawing::ObjectForDrawing()
{

}


//void ObjectForDrawing::setColor(Color color)
//{
//    this->color=color;
//}

//Color ObjectForDrawing::getColor()
//{
//    return this->color;
//}

void ObjectForDrawing::draw(QImage &im)
{

}

int ObjectForDrawing::getWeight()
{
    return  this->pen.width();
}

void ObjectForDrawing::setWeigt(int weight)
{
    this->pen.setWidth(weight);
}

QPen ObjectForDrawing::getPen()
{
    return this->pen;
}

QColor ObjectForDrawing::getColor()
{
    return this->pen.color();
}

void ObjectForDrawing::setColor(int red, int green, int blue)
{
    this->pen.setColor(QColor(red,green,blue,255));
}

void ObjectForDrawing::setStyle(int style)
{
    this->pen.setStyle(Qt::PenStyle(style));
}

void ObjectForDrawing::setPen(QPen pen)
{
    this->pen=pen;
}


