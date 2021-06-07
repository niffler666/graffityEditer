#ifndef M_WIDGET_H
#define M_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPaintDevice>
class m_widget : public QWidget
{
    Q_OBJECT
public:
    explicit m_widget(QWidget *parent = nullptr);
    QImage im;
    void create_image(int size_x, int size_y);
private:
    bool im_created;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // M_WIDGET_H
