#include "m_widget.h"

m_widget::m_widget(QWidget *parent) : QWidget(parent)//Конструктор
{
    im_created=false;
}

void m_widget::paintEvent(QPaintEvent *){ //PaintEvent
    if(im_created){
    QPainter painter(this);
    painter.drawImage(0,0,im);
    }
}

void m_widget::create_image(int size_x, int size_y){ //Создание изображения
    im= QImage(size_x,size_y,QImage::Format_ARGB32_Premultiplied);
    im_created=true;
}
