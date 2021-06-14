#ifndef POLYLINE_H
#define POLYLINE_H
#include <polygon.h>


class Polyline: public Polygon
{
public:
    Polyline();
    Polyline(QPolygonF qPointMas);


    void draw(QImage &im);
    virtual void drawWithZalivka(QImage &im) override;
};

#endif // POLYLINE_H
