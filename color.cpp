#include "color.h"

Color::Color()
{

}
Color::Color(int red, int green, int blue)
{
    this->red=red;
    this->green=green;
    this->blue=blue;
}
int Color::getRed()
{
    return this->red;
}
int Color::getGreen()
{
    return this->green;
}
int Color::getBlue()
{
    return this->blue;
}
