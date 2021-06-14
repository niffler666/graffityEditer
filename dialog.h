#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "my_pen.h"
#include <objectfordrawing.h>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setStyleVisible(bool fl);
    ObjectForDrawing getObjectForDrawing();
    void setValue(ObjectForDrawing n_pen);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    bool styleVisible;
    ObjectForDrawing objectForDrawing;
};

#endif // DIALOG_H
