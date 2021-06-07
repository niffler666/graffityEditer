#include "my_color.h"

my_color::my_color()
{


}

bool my_color::SetColor(int al, int r, int g, int b)
{
    if ((al<0)||(al>255)||(r<0)||(r>255)||(g<0)||(g>255)||(b<0)||(b>255))
        return (false);
    alpha=al;
    red=r;
    green=g;
    blue=b;
    return (true);
}

void my_color::GetColor(int &al, int &r, int &g, int &b)
{
    al=alpha;
    r=red;
    g=green;
    b=blue;
}
