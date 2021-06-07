#ifndef TOCHKA_H
#include <objectfordrawing.h>
#define TOCHKA_H


class Tochka: public ObjectForDrawing
{
public:
    Tochka();
    Tochka(int x, int y );
    virtual void draw(QImage &im) override;
};

#endif // TOCHKA_H
