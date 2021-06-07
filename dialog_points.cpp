#include "dialog_points.h"
#include "ui_dialog_points.h"

Dialog_points::Dialog_points(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_points)
{
    ui->setupUi(this);
    is_ok=false;
}

Dialog_points::~Dialog_points()
{
    delete ui;
}

void Dialog_points::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

bool Dialog_points::setValue(int kol, int *mas)
{
    is_ok=false;
    if ((kol<2)&&(kol>20))
        return(false);
    ui->spinBox->setValue(kol);

    if (mas!=NULL)
    {
        int i=0;
        for (int j=0;j<kol;j++)
        {
            if (ui->tableWidget->item(j,0)==NULL)
            {
                QTableWidgetItem * ti = new QTableWidgetItem;
                ui->tableWidget->setItem(j,0,ti);
            }
            ui->tableWidget->item(j,0)->setText(QString::number(mas[i]));
            i++;
            if (ui->tableWidget->item(j,1)==NULL)
            {
                QTableWidgetItem * ti = new QTableWidgetItem;
                ui->tableWidget->setItem(j,1,ti);
            }
            ui->tableWidget->item(j,1)->setText(QString::number(mas[i]));
            i++;
        }
    }

    return(true);
}


void Dialog_points::on_pushButton_Cancel_clicked()
{
    is_ok=false;
    close();
}

void Dialog_points::on_pushButton_OK_clicked()
{
    //проверка значений таблицы
    //если все хорошо, то
    {
        is_ok=true;
        close();
    }
    //иначе сообщения, подсветка красным и т.п.
}

bool Dialog_points::getValue(int &kol, int *&mas)
{
    if (!is_ok)
        return(false);

    kol=ui->spinBox->value();
    if (mas!=NULL)
        delete [] mas;

    mas = new int[kol+kol];
    int i=0;
    for (int j=0;j<kol;j++)
    {
        if (ui->tableWidget->item(j,0)==NULL)
            mas[i]=0;
        else
            mas[i]=ui->tableWidget->item(j,0)->text().toInt();
        i++;
        if (ui->tableWidget->item(j,1)==NULL)
            mas[i]=0;
        else
            mas[i]=ui->tableWidget->item(j,1)->text().toInt();
        i++;
    }
    return(true);

}
