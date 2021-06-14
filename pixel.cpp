#include "pixel.h"

Pixel::Pixel()
{

}

Pixel:: Pixel(int x, int y)
{
    this->point.setX(x);
    this->point.setY(y);


}
void Pixel::draw(QImage &im)
{
    QPainter painter(&im);
    this->pen.setStyle(Qt::DotLine);
    painter.setPen(this->pen);
    painter.drawPoint(this->point);
}
