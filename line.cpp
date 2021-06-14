#include "line.h"

Line::Line()
{

}

Line::Line(int x1, int y1, int x2, int y2)
{
    this->point1.setX(x1);
    this->point1.setY(y1);
    this->point2.setX(x2);
    this->point2.setY(y2);
}

void Line::draw(QImage &im)
{
    QPainter painter(&im);
    painter.setPen(pen);
    painter.drawLine(this->point1, this->point2);
}
