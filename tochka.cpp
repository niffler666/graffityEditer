#include "tochka.h"

Tochka::Tochka()
{

}

Tochka:: Tochka(int x, int y)
{
    this->x=x;
    this->y=y;

}
void Tochka::draw(QImage &im)
{
    QPainter painter(&im);
    this->pen.setColor(this->color);
    pen.setWidth(this->weight);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPoint(this->x, this->y);
}
