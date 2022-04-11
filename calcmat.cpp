#include "calcmat.h"
#include "ui_calcmat.h"
#include "macierz.h"

Calcmat::Calcmat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calcmat)
{
    ui->setupUi(this);
}

Calcmat::~Calcmat()
{
    delete ui;
}

void Calcmat::on_Result_released()
{
    QLineEdit *elems[16];
    int count=0;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            QString lineName="e"+QString::number(i)+"x"+QString::number(j);
            //QMessageBox::information(this,"Koniec",lineName);
            elems[count]=Calcmat::findChild<QLineEdit *>(lineName);
            count++;
        }
    }
    Macierz A;
    A.Fill(elems,this);
}

