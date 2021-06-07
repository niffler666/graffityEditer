#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setValue(my_pen n_pen)
{
    my_style=n_pen.GetStyle();
    n_pen.GetColor(alpha,red,green,blue);


    ui->lineEdit_r->setText(QString::number(red));
    ui->lineEdit_g->setText(QString::number(green));
    ui->lineEdit_b->setText(QString::number(blue));

    ui->comboBox->setVisible(styleVisible);
    ui->label_st->setVisible(styleVisible);
    ui->comboBox->setCurrentIndex(my_style);

}

void Dialog::setStyleVisible(bool fl)
{
    styleVisible=fl;
}

void Dialog::on_buttonBox_accepted()
{
    int r,g,b,st;

    red=ui->lineEdit_r->text().toInt();
    green=ui->lineEdit_g->text().toInt();
    blue=ui->lineEdit_b->text().toInt();


}
