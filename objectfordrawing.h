#ifndef OBJECTFORDRAWING_H
#include<weight.h>
#include <QImage>
#include <QPainter>
#define OBJECTFORDRAWING_H


class ObjectForDrawing
{
public:


    void draw(QImage &im);

    //void setColor(Color color);
    //Color getColor();
    int getWeight();
    void setWeigt(int weight);
    QPen getPen();
    QColor getColor();
    void setColor(int red,int green, int blue);
    void setStyle(int style);
    void setPen(QPen pen);
    ObjectForDrawing();





protected:
    QPen pen;


};

#endif // OBJECTFORDRAWING_H
