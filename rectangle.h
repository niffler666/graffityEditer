#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <polygon.h>



class Rectangle: public Polygon
{
public:
    Rectangle();
    Rectangle(int x1, int y1, int x2, int y2);
//    virtual void draw(QImage &im) override;
//    virtual void drawWithZalivka(QImage &im) override;


};

#endif // RECTANGLE_H
