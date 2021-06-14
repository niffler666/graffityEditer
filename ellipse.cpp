#include "ellipse.h"

Ellipse::Ellipse()
{

}

Ellipse::Ellipse(int x, int y, int radiusX, int radiusY)
{
    this->pointCenter.setX(x);
    this->pointCenter.setY(y);
    this->radiusX=radiusX;
    this->radiusY=radiusY;
}

void Ellipse::draw(QImage &im)
{
    QPainter painter(&im);
    painter.setPen(this->pen);
    painter.drawEllipse(this->pointCenter, this->radiusX, this->radiusY);
}

void Ellipse::drawWithZalivka(QImage &im)
{
    QPainter painter(&im);

    painter.setPen(this->pen);
    QBrush brush1;
    painter.setBrush(this->brush);
    painter.drawEllipse(this->pointCenter, this->radiusX, this->radiusY);
}
