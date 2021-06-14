#include "zalivka.h"

Zalivka::Zalivka()
{

}

void Zalivka::setColorForZalivka(int red, int green, int blue)
{
    this->colorForZalivki.setRed(red);
    this->colorForZalivki.setGreen(green);
    this->colorForZalivki.setBlue(blue);
    this->brush.setColor(this->colorForZalivki);
}

void Zalivka::setStyleForBrush(int style)
{
    this->brush.setStyle(Qt::BrushStyle(style));
}
