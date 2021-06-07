#ifndef DIALOG_POINTS_H
#define DIALOG_POINTS_H

#include <QDialog>

namespace Ui {
    class Dialog_points;
}

class Dialog_points : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_points(QWidget *parent = 0);
    ~Dialog_points();
    bool setValue(int kol, int * mas);
    bool getValue(int &kol, int * &mas);

private slots:
    void on_spinBox_valueChanged(int arg1);



    void on_pushButton_Cancel_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::Dialog_points *ui;
    bool is_ok;
};

#endif // DIALOG_POINTS_H
