#include "arc.h"

Arc::Arc()
{

}

Arc::Arc(int x, int y, int radiusX, int radiusY, int startAngle, int spanAngle)
{
    this->pointCenter.setX(x);
    this->pointCenter.setY(y);
    this->radiusX=radiusX;
    this->radiusY=radiusY;
    this->startAngle=startAngle*16;
    this->spanAngle=spanAngle*16;
}

void Arc::draw(QImage &im)
{
    QPainter painter(&im);
    painter.setPen(this->pen);
    painter.drawArc(this->pointCenter.x()-this->radiusX,
                    this->pointCenter.y()-this->radiusY,
                    this->radiusX*2,
                    this->radiusY*2,
                    this->startAngle,
                    this->spanAngle );
}

void Arc::drawWithZalivka(QImage &im)
{

}
