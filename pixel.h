#ifndef TOCHKA_H
#include <objectfordrawing.h>
#define TOCHKA_H


class Pixel: public ObjectForDrawing
{
public:
    Pixel();
    Pixel(int x,int y);



    void draw(QImage &im);
protected:
        QPoint point;

};

#endif // TOCHKA_H
