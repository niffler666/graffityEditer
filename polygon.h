#ifndef POLYGON_H
#define POLYGON_H
#include <objectfordrawing.h>
#include <zalivka.h>
#include<array>


using namespace std;
class Polygon: public ObjectForDrawing, public Zalivka
{
public:
    Polygon();
    Polygon(QPolygonF qPointMas);
    void draw(QImage &im);
    virtual void drawWithZalivka(QImage &im) override;

protected:
    QPolygonF qPointMas;
};

#endif // POLYGON_H
