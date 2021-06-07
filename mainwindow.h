#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include "dialog.h"
#include "dialog_points.h"
#include <QFile>
#include <QMessageBox>
#include <tochka.h>
#include<objectfordrawing.h>

#define KOL_COL 7
#define FILE_NAME "save.dat"

namespace Ui {
    class MainWindow;
}

struct T_OBJ_DATA
{
    my_pen mpen;
    int kol;
    int * mas;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    T_OBJ_DATA * obj_data;


private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButtonSave_clicked();

    void on_pushButtonLoad_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;


protected slots:
    void Combo_click(int arg1);
    void color_click(void);
    void points_click(void);
};

#endif // MAINWINDOW_H
