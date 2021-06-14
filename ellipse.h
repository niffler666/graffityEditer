#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <objectfordrawing.h>
#include <zalivka.h>

class Ellipse: public ObjectForDrawing, public Zalivka
{
public:
    Ellipse();
    Ellipse(int x, int y, int radiusX, int radiusY);
    void draw(QImage &im);
    virtual void drawWithZalivka(QImage &im) override;
protected:
    int radiusX;
    int radiusY;
    QPoint pointCenter;
};

#endif // ELLIPSE_H
