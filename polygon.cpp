#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(QPolygonF qPointMas)
{
    this->qPointMas=qPointMas;
}

//Polygon::Polygon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
//{
//    QPoint point1, point2, point3, point4;
//    point1.setX(x1);
//    point1.setY(y1);
//    point2.setX(x2);
//    point2.setY(y2);
//    point3.setX(x3);
//    point3.setY(y3);
//    point4.setX(x4);
//    point4.setY(y4);
//    this->qPointMas = new QPoint[4];
//    this->qPointMas[0]=point1;
//    this->qPointMas[1]=point2;
//    this->qPointMas[2]=point3;
//    this->qPointMas[3]=point4;
//}

void Polygon::draw(QImage &im)
{
    QPainter painter(&im);
    painter.setPen(this->pen);
    painter.drawPolygon(this->qPointMas);
}

void Polygon::drawWithZalivka(QImage &im)
{
    QPainter painter(&im);
    painter.setBrush(this->brush);
//    int i=std::size(qPointMas);
    painter.drawPolygon(this->qPointMas);
}
