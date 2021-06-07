#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    Color();
    Color(int red, int green, int blue);
    int getRed();
    int getGreen();
    int getBlue();
protected:
    int red;
    int green;
    int blue;

};

#endif // COLOR_H
