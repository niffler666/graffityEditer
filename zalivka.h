#ifndef ZALIVKA_H
#define ZALIVKA_H
#include <QPainter>
#include <QImage>

class Zalivka
{
public:
    Zalivka();
    void setColorForZalivka(int red, int green, int blue);
    void setStyleForBrush(int style);
    virtual void drawWithZalivka(QImage &im)=0;
protected:
    QColor colorForZalivki;
    QBrush brush;

};

#endif // ZALIVKA_H
