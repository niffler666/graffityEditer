#include "rectangle.h"

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(int x1, int y1, int x2, int y2)
{
//    QPoint *points=new QPoint[4];
//    points[0]=QPoint(x1, y1);
//    points[1]=QPoint(x2,y1);
//    points[2]=QPoint(x2,y2);
//    points[3]=QPoint(x1,y2);


    this->qPointMas.push_back(QPoint(x1, y1));
    this->qPointMas.push_back(QPoint(x2, y1));
    this->qPointMas.push_back(QPoint(x2, y2));
    this->qPointMas.push_back(QPoint(x1, y2));
//    this->qPointMas = new QPoint[4];
//    this->qPointMas[0]=QPoint(x1, y1);
//    this->qPointMas[1]=QPoint(x2,y1);
//    this->qPointMas[2]=QPoint(x2,y2);
//    this->qPointMas[3]=QPoint(x1,y2);

}

