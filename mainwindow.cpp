#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(KOL_COL);
    ui->tableWidget->setRowCount(0);
    obj_data=NULL;
    ui->widget->create_image(ui->widget->width(), ui->widget->height());
    //    ui->tableWidget->setColumnWidth(1,30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int need_rows = arg1*2;
    // на графический элемент по 2 строки
    int cur_rows=ui->tableWidget->rowCount();
    int old_val=cur_rows/2;
    if (cur_rows<0)
        cur_rows=0;

    if (need_rows>cur_rows) //добавляем строки
    {
        ui->tableWidget->setRowCount(need_rows);
        int i =cur_rows;
        QTableWidgetItem * twi;
        QComboBox * cb;
        while (i<need_rows)
        {
            twi = new QTableWidgetItem;
            twi->setText("Объект");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,0,twi);

            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Цвет точки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->setItem(i,3,twi);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->setItem(i,j,twi);
            }

            i++;

            cb =  new QComboBox;
            cb->addItem("Точка");
            cb->addItem("Линия");
            cb->addItem("Прямоугольник");
            cb->addItem("Круг");
            cb->addItem("Эллипс");
            cb->addItem("Дуга");
            cb->addItem("Ломанная");
            cb->addItem("многоугольник");

            cb->setProperty("row",i);

            connect(cb,SIGNAL(activated(int)),this,SLOT(Combo_click(int)));
            connect(cb,SIGNAL(currentIndexChanged(int)),this,SLOT(Combo_click(int)));

            ui->tableWidget->setCellWidget(i,0,cb);

            //потому что по умолчанию выбирается режим точка
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->setItem(i,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->setItem(i,2,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",i);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->setCellWidget(i,3,pb);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->setItem(i,j,twi);
            }



            i++;
        }
    }
    else //удаляем строки
    {
        ui->tableWidget->setRowCount(need_rows);
    }

    if (arg1<=0)
    {
        delete [] obj_data;
        obj_data=NULL;
    }
    else
    {
        if ((old_val==0)||(obj_data==NULL))
            obj_data=new T_OBJ_DATA[arg1];
        //!!!!        else //Убрано, так как нужно проводить инициализацию!
        {
            if (old_val<arg1)
            {
                //добавляем;
                T_OBJ_DATA * n_obj_data=obj_data; //сохранили старое значение
                obj_data=new T_OBJ_DATA[arg1]; //выделили память под новые данные
                memcpy(obj_data,n_obj_data,old_val*sizeof(T_OBJ_DATA));
                //выше cкопировали старые данные
                delete [] n_obj_data;
                //инициализация значений
                for (int i=old_val;i<arg1;i++)
                {
                    obj_data[i].kol=0;
                    obj_data[i].mas=NULL;
                    obj_data[i].objectForDrawing.setColor(0,0,0);
                    obj_data[i].objectForDrawing.setStyle(1);
                    obj_data[i].objectForDrawing.setWeigt(1);

                    //.....
                }
            }
            else
            {
                //удалям
                T_OBJ_DATA * n_obj_data=obj_data; //сохранили старое значение
                obj_data=new T_OBJ_DATA[arg1]; //выделили память под новые данные
                memcpy(obj_data,n_obj_data,arg1*sizeof(T_OBJ_DATA));
                //выше cкопировали старые данные

                for (int i=arg1;i<old_val;i++)
                {
                    //освобождение памяти внутри ненужных структур
                    if (n_obj_data[i].kol>0)
                        delete [] n_obj_data[i].mas;
                }
                delete [] n_obj_data;
            }
        }
    }


}


void MainWindow::Combo_click(int arg1)
{

    int row;
    QComboBox *cbox = qobject_cast<QComboBox*>(sender());

    if (cbox!=NULL)
    {
        row = cbox->property("row").toInt();
        QTableWidgetItem * twi;

        //инициализация значений
        int indx = (row-1)/2;
        if (obj_data[indx].kol>0)
            delete [] obj_data[indx].mas;
        obj_data[indx].kol=0;
        obj_data[indx].mas=NULL;
        obj_data[indx].objectForDrawing.setColor(0,0,0);
        obj_data[indx].objectForDrawing.setStyle(1);
        obj_data[indx].objectForDrawing.setWeigt(1);


        switch (arg1)
        {

        case 0: //точка
        {
            int rowm=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Цвет точки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }


            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setCellWidget(row,3,pb);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 1: //линия
        {
            int rowm=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("X2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,4);
            ui->tableWidget->setItem(rowm,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Цвет линии");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,5);
            ui->tableWidget->setItem(rowm,5,twi);


            for (int j=6; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }


            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            for (int j=6; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 2: //прямоугольник
        {
            int rowm=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("X2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y2");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,4);
            ui->tableWidget->setItem(rowm,4,twi);

            for (int j=5; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }


            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);


            for (int j=5; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 3: // эллипс
        {
            int rowm=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("R");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Параметры границы");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm, 4);
            ui->tableWidget->setItem(rowm,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Параметры заливки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,5);
            ui->tableWidget->setItem(rowm,5,twi);


            for (int j=6; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }
            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);


            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setCellWidget(row,4,pb);

            pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_br_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            for (int j=6; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 4: // эллипс
        {
            int rowm=row-1;

            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Гор. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,4);
            ui->tableWidget->setItem(rowm,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Параметры границы");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm, 5);
            ui->tableWidget->setItem(rowm,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Параметры заливки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,6);
            ui->tableWidget->setItem(rowm,6,twi);

            for (int j=7; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }
            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0"); //или убираем
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setCellWidget(row,5,pb);

            pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_br_click()));

            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setCellWidget(row,6,pb);

            for (int j=7; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 5: // Дуга
        {
            int rowm=row-1;
            //строка подписей
            twi = new QTableWidgetItem;
            twi->setText("X1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Y1");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Гор. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("Верт. радиус");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,4);
            ui->tableWidget->setItem(rowm,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("Нач. угол");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,5);
            ui->tableWidget->setItem(rowm,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("Угловая длина");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,6);
            ui->tableWidget->setItem(rowm,6,twi);

            twi = new QTableWidgetItem;
            twi->setText("Параметры границы");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,7);
            ui->tableWidget->setItem(rowm,7,twi);

            //строка значений
            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setItem(row,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setItem(row,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setItem(row,3,twi);

            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,4);
            ui->tableWidget->setItem(row,4,twi);

            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,5);
            ui->tableWidget->setItem(row,5,twi);

            twi = new QTableWidgetItem;
            twi->setText("0");
            ui->tableWidget->removeCellWidget(row,6);
            ui->tableWidget->setItem(row,6,twi);

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,7);
            ui->tableWidget->setCellWidget(row,7,pb);


            break;
        }
        case 6: //Ломанная
        {
            int rowm=row-1;


            twi = new QTableWidgetItem;
            twi->setText("Цвет линии");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);

            twi = new QTableWidgetItem;
            twi->setText("Массив точек");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            for (int j=3; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setCellWidget(row,1,pb);

            pb = new QPushButton(this);
            pb->setText("Точки");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(points_click()));

            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setCellWidget(row,2,pb);

            for (int j=3; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }

            break;
        }
        case 7: // Полигон
        {
            int rowm=row-1;
            twi = new QTableWidgetItem;
            twi->setText("Цвет линии");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,1);
            ui->tableWidget->setItem(rowm,1,twi);


            twi = new QTableWidgetItem;
            twi->setText("Параметры заливки");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,2);
            ui->tableWidget->setItem(rowm,2,twi);

            twi = new QTableWidgetItem;
            twi->setText("Массив точек");
            twi->setFlags(twi->flags()&0xfffffffd);
            ui->tableWidget->removeCellWidget(rowm,3);
            ui->tableWidget->setItem(rowm,3,twi);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(rowm,j);
                ui->tableWidget->setItem(rowm,j,twi);
            }

            QPushButton * pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_click()));

            ui->tableWidget->removeCellWidget(row,1);
            ui->tableWidget->setCellWidget(row,1,pb);

            pb = new QPushButton(this);
            pb->setText("Задать");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(color_br_click()));

            ui->tableWidget->removeCellWidget(row,2);
            ui->tableWidget->setCellWidget(row,2,pb);

            pb = new QPushButton(this);
            pb->setText("Точки");
            pb->setProperty("row",row);
            connect(pb,SIGNAL(clicked()),this,SLOT(points_click()));

            ui->tableWidget->removeCellWidget(row,3);
            ui->tableWidget->setCellWidget(row,3,pb);

            for (int j=4; j<KOL_COL;j++)
            {
                twi = new QTableWidgetItem;
                twi->setText("---");
                twi->setFlags(twi->flags()&0xffffffdd);
                ui->tableWidget->removeCellWidget(row,j);
                ui->tableWidget->setItem(row,j,twi);
            }
            break;
        }
        }

    }
}


void MainWindow::color_click()
{
    QPushButton * pb = qobject_cast<QPushButton *>(sender());
    int row=pb->property("row").toInt();
    int indx=(row-1)/2;

    Dialog dial;

    QComboBox * cb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(row,0));

    dial.setStyleVisible(cb->currentIndex()!=0);
    //получить предыдущие значения стиля
//    obj_data[indx].objectForDrawing.getColor();
//    obj_data[indx].objectForDrawing.getPen().style();
    dial.setValue(obj_data[indx].objectForDrawing);

    dial.exec();

    //сохранить значения из dial

    //dial->GetColor(____);


    //dial.GetColor(a,r,g,b);
    obj_data[indx].objectForDrawing=dial.getObjectForDrawing();

}

void MainWindow::points_click()
{
    QPushButton * pb = qobject_cast<QPushButton *>(sender());
    int row=pb->property("row").toInt();

    int indx=(row-1)/2;

    Dialog_points dial;


    //получить предыдущие значения стиля


    dial.setValue(obj_data[indx].kol,obj_data[indx].mas);


    //    dial.setValue(pen);

    dial.exec();

    //сохранить значения из dial

    dial.getValue(obj_data[indx].kol,obj_data[indx].mas);



    // ui->tableWidget->item(row,1)->setText(QString::number(r));

    // delete [] dial;
}

void MainWindow::on_pushButtonSave_clicked()
{
//    QFile file;
//    char * mas = new char[sizeof(int)];
//    file.setFileName(FILE_NAME);
//    file.open(QIODevice::WriteOnly);


//    QComboBox * cb;
//    int val;
//    int val2;
//    bool flag;
//    int indx;
//    int size_tabl=ui->spinBox->value()*2;
//    for (int i=1; i<size_tabl;i=i+2)
//    {
//        cb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(i,0));
//        val=cb->currentIndex();
//        memcpy(mas,&val,sizeof(int));
//        file.write(mas,sizeof(int));

//        switch (val)
//        {
//        case 0: //точка
//        {
//            val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //X
//            file.write(mas,sizeof(int));

//            val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //Y
//            file.write(mas,sizeof(int));

//            indx=(i-1)/2;
//            int a,r,g,b,st;
//            obj_data[indx].mpen.GetColor(a,r,g,b);
//            memcpy(mas,&a,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&r,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&g,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&b,sizeof(int));
//            file.write(mas,sizeof(int));
//            break;
//        }
//        case 1: //Линия
//        {
//            val2=ui->tableWidget->item(i,1)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //X1
//            file.write(mas,sizeof(int));

//            val2=ui->tableWidget->item(i,2)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //Y1
//            file.write(mas,sizeof(int));

//            val2=ui->tableWidget->item(i,3)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //X2
//            file.write(mas,sizeof(int));

//            val2=ui->tableWidget->item(i,4)->text().toInt(&flag);
//            if (!flag)
//            {
//                QMessageBox::information(this,"Ошибка","Неверные значения координат");
//                delete [] mas;
//                file.close();
//                file.remove();
//                return;
//            }
//            memcpy(mas,&val2,sizeof(int)); //Y2
//            file.write(mas,sizeof(int));

//            indx=(i-1)/2;
//            int a,r,g,b,st;
//            obj_data[indx].mpen.GetColor(a,r,g,b);
//            memcpy(mas,&a,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&r,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&g,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&b,sizeof(int));
//            file.write(mas,sizeof(int));

//            st=obj_data[indx].mpen.GetStyle();
//            memcpy(mas,&st,sizeof(int));
//            file.write(mas,sizeof(int));
//            break;
//        }

//        case 3: //ломаная
//        {


//            indx=(i-1)/2;
//            int a,r,g,b,st;
//            obj_data[indx].mpen.GetColor(a,r,g,b);
//            memcpy(mas,&a,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&r,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&g,sizeof(int));
//            file.write(mas,sizeof(int));
//            memcpy(mas,&b,sizeof(int));
//            file.write(mas,sizeof(int));

//            st=obj_data[indx].mpen.GetStyle();
//            memcpy(mas,&st,sizeof(int));
//            file.write(mas,sizeof(int));

//            val2=obj_data[indx].kol;
//            memcpy(mas,&val2,sizeof(int));
//            file.write(mas,sizeof(int));
//            int kol2=val2+val2;
//            for (int j=0;j<kol2;j++)
//            {
//                val2=obj_data[indx].mas[j];
//                memcpy(mas,&val2,sizeof(int));
//                file.write(mas,sizeof(int));
//            }


//            break;
//        }

//        }
//    }

//    file.close();
//    delete [] mas;
}

void MainWindow::on_pushButtonLoad_clicked()
{
//    QFile file;
//    char * mas = new char[sizeof(int)];
//    file.setFileName(FILE_NAME);
//    file.open(QIODevice::ReadOnly);


//    int val;
//    int val2;
//    int indx=0;
//    int row=0;
//    QComboBox * cb;
//    ui->spinBox->setValue(0);
//    while (!file.atEnd())
//    {
//        file.read(mas,sizeof(int));
//        memcpy(&val,mas,sizeof(int));

//        row = indx+indx+1;
//        ui->spinBox->setValue(indx+1);
//        cb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(row,0));

//        cb->setCurrentIndex(val);

//        switch (val)
//        {
//        case 0: //точка
//        {
//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //X
//            ui->tableWidget->item(row,1)->setText(QString::number(val2));

//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //Y
//            ui->tableWidget->item(row,2)->setText(QString::number(val2));


//            int a,r,g,b,st;
//            file.read(mas,sizeof(int));
//            memcpy(&a,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&r,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&g,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&b,mas,sizeof(int));
//            obj_data[indx].mpen.SetColor(a,r,g,b);
//            break;
//        }
//        case 1: //Линия
//        {
//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //X1
//            ui->tableWidget->item(row,1)->setText(QString::number(val2));

//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //Y1
//            ui->tableWidget->item(row,2)->setText(QString::number(val2));

//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //X2
//            ui->tableWidget->item(row,3)->setText(QString::number(val2));

//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int)); //Y2
//            ui->tableWidget->item(row,4)->setText(QString::number(val2));

//            int a,r,g,b,st;
//            file.read(mas,sizeof(int));
//            memcpy(&a,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&r,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&g,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&b,mas,sizeof(int));
//            obj_data[indx].mpen.SetColor(a,r,g,b);
//            file.read(mas,sizeof(int));
//            memcpy(&st,mas,sizeof(int));
//            obj_data[indx].mpen.SetStyle(st);
//            break;

//        }

//        case 3: //ломанная
//        {
//            int a,r,g,b,st;
//            file.read(mas,sizeof(int));
//            memcpy(&a,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&r,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&g,mas,sizeof(int));
//            file.read(mas,sizeof(int));
//            memcpy(&b,mas,sizeof(int));
//            obj_data[indx].mpen.SetColor(a,r,g,b);
//            file.read(mas,sizeof(int));
//            memcpy(&st,mas,sizeof(int));
//            obj_data[indx].mpen.SetStyle(st);


//            file.read(mas,sizeof(int));
//            memcpy(&val2,mas,sizeof(int));
//            obj_data[indx].kol=val2;


//            if (val2>0)
//            {
//                int kol2=val2+val2;

//                obj_data[indx].mas = new int[kol2];
//                for (int j=0;j<kol2;j++)
//                {
//                    file.read(mas,sizeof(int));
//                    memcpy(&val2,mas,sizeof(int));
//                    obj_data[indx].mas[j]=val2;
//                }
//            }

//            break;

//        }

//        }
//        indx++;
//    }
//    file.close();
//    delete [] mas;


}

void MainWindow::on_pushButton_clicked()
{
    QComboBox * cb;
    bool fl_glory = true, fl;
    int val;
    int size = ui->spinBox->value() * 2;
    for (int i = 1; i < size; i = i + 2)
    {
        cb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(i, 0));
        val = cb->currentIndex();
        switch(val)
        {
        case 0: // точка
        {
            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        }
        case 1: // линия
        {
            ui->tableWidget->item(i, 4)->text().toInt(&fl);
            if (!fl)
                fl_glory= false;
            ui->tableWidget->item(i, 3)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        }
        case 2: // прямоугольник
            ui->tableWidget->item(i, 4)->text().toInt(&fl);
            if (!fl)
                fl_glory= false;
            ui->tableWidget->item(i, 3)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        case 3: //Окружность
        {
            ui->tableWidget->item(i, 3)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        }
        case 4: // эллипс
        {
            ui->tableWidget->item(i, 4)->text().toInt(&fl);
            if (!fl)
                fl_glory= false;
            ui->tableWidget->item(i, 3)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        }

        case 5: // дуга
        {
            ui->tableWidget->item(i, 6)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;

            ui->tableWidget->item(i, 5)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;

            ui->tableWidget->item(i, 4)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;

            ui->tableWidget->item(i, 3)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;

            ui->tableWidget->item(i, 2)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;

            ui->tableWidget->item(i, 1)->text().toInt(&fl);
            if (!fl)
                fl_glory = false;
            break;
        }
        }
    }
    if (fl_glory)
    {
        for (int i = 0; i < ui->spinBox->value(); i++) //рисуем все-все фигурки
        {
            cb = qobject_cast<QComboBox *>(ui->tableWidget->cellWidget(i*2+1, 0)); //берем комбо бокс ячейки
            val = cb->currentIndex(); //берем индекс комбо бокса

            switch (val)
            {
            case 0: //Пиксель
            {
                Pixel pixel=Pixel(ui->tableWidget->item(i*2+1, 1)->text().toInt(),ui->tableWidget->item(i*2+1, 2)->text().toInt());
                ObjectForDrawing obj=this->obj_data[i].objectForDrawing;
                pixel.setPen(this->obj_data[i].objectForDrawing.getPen());
                pixel.draw(ui->widget->im);
                update();
                break;
            }
            case 1://линия
            {
                Line line=Line(ui->tableWidget->item(i*2+1, 1)->text().toInt(), ui->tableWidget->item(i*2+1, 2)->text().toInt(), ui->tableWidget->item(i*2+1, 3)->text().toInt(), ui->tableWidget->item(i*2+1, 4)->text().toInt());
                line.setPen(this->obj_data[i].objectForDrawing.getPen());
                line.draw(ui->widget->im);
                update();
            }
            case 2://прямоугольник
            {
                Rectangle rectangle=Rectangle(ui->tableWidget->item(i*2+1, 1)->text().toInt(),ui->tableWidget->item(i*2+1, 2)->text().toInt(),ui->tableWidget->item(i*2+1, 3)->text().toInt(), ui->tableWidget->item(i*2+1, 4)->text().toInt());
                rectangle.setPen(this->obj_data[i].objectForDrawing.getPen());
                rectangle.setColorForZalivka(255,0,255);
                rectangle.setStyleForBrush(4);
                update();
                break;
            }
            case 3://круг
            {
                Ellipse ellipse=Ellipse(ui->tableWidget->item(i*2+1, 1)->text().toInt(), ui->tableWidget->item(i*2+1, 2)->text().toInt(), ui->tableWidget->item(i*2+1, 3)->text().toInt(), ui->tableWidget->item(i*2+1, 3)->text().toInt());
                ellipse.setPen(this->obj_data[i].objectForDrawing.getPen());
                ellipse.setColorForZalivka(255,0,0);
                ellipse.setStyleForBrush(3);
                ellipse.drawWithZalivka(ui->widget->im);
                update();
                break;
            }
            case 4:
            {
                Ellipse ellipse=Ellipse(ui->tableWidget->item(i*2+1, 1)->text().toInt(), ui->tableWidget->item(i*2+1, 2)->text().toInt(), ui->tableWidget->item(i*2+1, 3)->text().toInt(),ui->tableWidget->item(i*2+1, 4)->text().toInt());
                ellipse.setPen(this->obj_data[i].objectForDrawing.getPen());
                ellipse.setColorForZalivka(255,0,0);
                ellipse.setStyleForBrush(3);
                ellipse.drawWithZalivka(ui->widget->im);
                update();
                break;
            }
//            case 7:
//            {













            }
        }
    }
        //    QPoint *qPointMas=new QPoint[6];
        //    qPointMas[0]=QPoint(0,0);
        //    qPointMas[1]=QPoint(200,0);
        //    qPointMas[2]=QPoint(200,200);
        //    qPointMas[3]=QPoint(0,200);
        //    qPointMas[4]=QPoint(50,70);
        //    qPointMas[5]=QPoint(30,40);
//            QPolygonF qPointsMas=QPolygonF();
//            qPointsMas.push_back(QPoint(0,0));
//            qPointsMas.push_back(QPoint(200,0));
//            qPointsMas.push_back(QPoint(200,200));
//            qPointsMas.push_back(QPoint(50,70));
//            qPointsMas.push_back(QPoint(30,40));
//            qPointsMas.push_back(QPoint(0,200));
        //    Polygon polygon=Polygon(qPointsMas);
        //    polygon.setColor(0,0,0);
        //    polygon.setStyle(5);
        //    polygon.setWeigt(6);
        //    polygon.setColorForZalivka(255,0,0);
        //    polygon.setStyleForBrush(8);
        //    polygon.drawWithZalivka(ui->widget->im);
        //    Rectangle rectangle=Rectangle(10,10, 100, 100);
        //    rectangle.setColor(128, 0, 128);
        //    rectangle.setColorForZalivka(255,0,255);
        //    rectangle.setStyle(3);
        //    rectangle.setWeigt(5);
        //    rectangle.setStyleForBrush(4);
        //    rectangle.draw(ui->widget->im);
        //    Ellipse ellipse=Ellipse(70, 70, 50, 50);
        //    ellipse.setColor(0, 255, 0);
        //    ellipse.setStyle(3);
        //    ellipse.setWeigt(3);
        //    ellipse.setColorForZalivka(255,0,0);
        //    ellipse.setStyleForBrush(3);
        //    ellipse.drawWithZalivka(ui->widget->im);
//    Arc arc=Arc(50, 40, 40, 50, 0, 120);
//    arc.setColor(255, 0 ,0);
//    arc.setStyle(3);
//    arc.setWeigt(5);
//    arc.draw(ui->widget->im);
//    Polyline polyline=Polyline(qPointsMas);
//    polyline.setColor(0, 0, 128);
//    polyline.setStyle(1);
//    polyline.setWeigt(5);
//    polyline.draw(ui->widget->im);
//        update();


//    }}



}
