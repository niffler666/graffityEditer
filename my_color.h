#ifndef MY_COLOR_H
#define MY_COLOR_H

class my_color
{
public:
    my_color();
protected:
    int red;
    int green;
    int blue;
    int alpha;

public:
    bool SetColor(int al,int r, int g, int b);
    void GetColor(int &al,int &r, int &g, int &b);
};


#endif // MY_COLOR_H
