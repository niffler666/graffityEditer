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

void Dialog::setValue(ObjectForDrawing objectForDrawong)
{
    ui->lineEdit_r->setText(QString::number(objectForDrawong.getColor().red()));
    ui->lineEdit_g->setText(QString::number(objectForDrawong.getColor().green()));
    ui->lineEdit_b->setText(QString::number(objectForDrawong.getColor().blue()));

    ui->comboBox->setVisible(styleVisible);
    ui->label_st->setVisible(styleVisible);
    ui->comboBox->setCurrentIndex(objectForDrawong.getPen().style());

}

void Dialog::setStyleVisible(bool fl)
{
    styleVisible=fl;
}

ObjectForDrawing Dialog::getObjectForDrawing()
{
    return this->objectForDrawing;
}

void Dialog::on_buttonBox_accepted()
{
    objectForDrawing.setColor(
                ui->lineEdit_r->text().toInt(),
                ui->lineEdit_g->text().toInt(),
                ui->lineEdit_b->text().toInt());
    this->objectForDrawing.setStyle(ui->comboBox->currentIndex());
    this->objectForDrawing.setWeigt(ui->spinBox->value());
}
