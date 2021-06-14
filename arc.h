#ifndef ARC_H
#define ARC_H

#include <ellipse.h>


class Arc:  public Ellipse
{
public:
    Arc();
    Arc(int x, int y, int radiusX, int radiusY, int startAngle, int spanAngle );
    void draw(QImage &im);
    virtual void drawWithZalivka(QImage &im) override;
private:
    int startAngle, spanAngle;

};

#endif // ARC_H
