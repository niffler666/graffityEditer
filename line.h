#ifndef LINE_H
#define LINE_H
#include <objectfordrawing.h>


class Line: public ObjectForDrawing
{
public:
    Line();
    Line(int x1, int y1, int x2, int y2);
    void draw(QImage &im);

private:
    QPoint point1,point2;


};

#endif // LINE_H
