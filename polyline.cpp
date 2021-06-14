#include "polyline.h"

Polyline::Polyline()
{

}

Polyline::Polyline(QPolygonF qPointMas)
{
    this->qPointMas=qPointMas;
}

void Polyline::draw(QImage &im)
{
    QPainter painter(&im);
    painter.setPen(this->pen);
    painter.drawPolyline(this->qPointMas);
}

void Polyline::drawWithZalivka(QImage &im)
{

}
