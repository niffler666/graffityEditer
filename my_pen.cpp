#include "my_pen.h"

my_pen::my_pen()
{
}

bool my_pen::SetStyle(int st)
{
    if ((st<0)||(st>KOL_STYLE))
        return(false);
    my_style=st;
    return(true);
}

int my_pen::GetStyle()
{
    return(my_style);
}
