#ifndef OBJECTFORDRAWING_H
#include<weight.h>
#include <QImage>
#include <QPainter>
#define OBJECTFORDRAWING_H


class ObjectForDrawing
{
public:


    virtual void draw(QImage &im)=0;
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    //void setColor(Color color);
    //Color getColor();
    int getWeight();
    void setWeigt(int weight);
    QPen getPen();
    QColor getColor();
    void setColor(int red,int green, int blue);





protected:
    int x;
    int y;
    ObjectForDrawing();
    //Color color;
    int weight;
    QPen pen;
    QColor color;


};

#endif // OBJECTFORDRAWING_H
