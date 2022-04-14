#include "calcmat.h"
#include "ui_calcmat.h"
#include "mymatrix.h"

QLineEdit *elems[16]; //tablica na QLineEdit do sczytywania wartości

//globalnie bool wartości wciśniętego przycisku
bool addTrig, subTrig, mulTrig, skalTrig, detTrig, transpTrig, adTrig, inverseTrig = false;

MyMatrix A;
MyMatrix B;

void checkElems(QLineEdit * tab[], Calcmat * cUi);
Calcmat::Calcmat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calcmat)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(615, 440));
    //połączenie przycisków ze slotem
    connect(ui->Add,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->Sub,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->MulMat,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->MulX,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->Transp,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->Det,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->DopA,SIGNAL(released()),this,SLOT(Pressed()));
    connect(ui->Inverse,SIGNAL(released()),this,SLOT(Pressed()));
}

Calcmat::~Calcmat()
{
    delete ui;
}

void Calcmat::on_Result_released()//po wciśnięciu przycisku równa się, wykonuje działania w zależności od wybranego przycisku
{
    checkElems(elems,this);
    if (addTrig)
    {
        B.Fill(elems,this);
        A.Add(B,this);
        ui->Display->setText(A.Res());
        ui->Calculates->setText(A.CalcV());
        addTrig=false;
    }
    else if (subTrig)
    {
        B.Fill(elems,this);
        A.Sub(B,this);
        ui->Display->setText(A.Res());
        ui->Calculates->setText(A.CalcV());
        subTrig=false;
    }
    else if (mulTrig)
    {
        B.Fill(elems,this);
        A.Mul(B,this);
        ui->Display->setText(A.Res());
        ui->Calculates->setText(A.CalcV());
        mulTrig=false;
    }
    else if (skalTrig)
    {
        QString skalarString=ui->e0x0->text();
        bool isnumber;
        double skalar = skalarString.toDouble(&isnumber);
        if (isnumber)
        {
            A.MulNum(skalar);
            ui->Display->setText(A.Res());
            ui->Calculates->setText(A.CalcV());
        }
        else
            QMessageBox::warning(this,"Błąd!", "Niepoprawne dane!");
        skalTrig=false;
    }
    else if (transpTrig)
    {
        A.Transpone();
        MyMatrix AT(A);
        AT.Show(ui->Display,ui->Calculates);
        transpTrig=false;
    }
    else if (detTrig)
    {
        double detValue;
        detValue=A.Det(this);
        ui->Display->setText(QString::number(detValue));
        ui->Calculates->setText(A.CalcV());
        detTrig=false;
    }
    else if (adTrig)
    {
        A.Admat(this);
        ui->Display->setText(A.Res());
        ui->Calculates->setText(A.CalcV());
        adTrig=false;
    }
    else if (inverseTrig)
    {
        A.Invers(this);
        ui->Display->setText(A.Res());
        ui->Calculates->setText(A.CalcV());
        inverseTrig=false;
    }
    else //jeżeli nie został wciśnięty inny przycisk wyświetla wprowadzoną macierz
    {
        checkElems(elems,this);
        A.Fill(elems,this);
        A.Show(ui->Display,ui->Calculates);
    }
}
//sprawdza czy tablica nie jest pusta i wypełnia ją
void checkElems(QLineEdit * tab[],Calcmat * cUi)
{
    if (tab[0]==nullptr)
    {
        int count=0;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                QString lineName="e"+QString::number(i)+"x"+QString::number(j);
                tab[count]=cUi->findChild<QLineEdit *>(lineName);
                count++;
            }
        }
    }
}
//czyszczenie wszystkich widżetów
void Calcmat::on_Clear_released()
{
    ui->Display->setText("");
    ui->Calculates->setText("");
    checkElems(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
}

//Po wcisńieciu przycisku program sprawdza stan tablicy elems, czy ma wczytane wskaźniki na QLineEdit's i jeżeli jest puty wypełnia go
//Następnie sczytuje wartości z obiektów QLineEdit do macierzy, czyści je i ustawia wartość bool przypisaną do przycisku na true
void Calcmat::Pressed()
{
    addTrig=subTrig=mulTrig=skalTrig=detTrig=transpTrig=adTrig=inverseTrig = false;
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"A + B",Qt::CaseInsensitive)==0)
        addTrig=true;
    else if(QString::compare(butVal,"A - B",Qt::CaseInsensitive)==0)
        subTrig=true;
    else if(QString::compare(butVal,"A * B",Qt::CaseInsensitive)==0)
        mulTrig=true;
    else if(QString::compare(butVal,"A * x",Qt::CaseInsensitive)==0)
        skalTrig=true;
    else if(QString::compare(butVal,"Det(A)",Qt::CaseInsensitive)==0)
        detTrig=true;
    else if(QString::compare(butVal,"A^T",Qt::CaseInsensitive)==0)
        transpTrig=true;
    else if(QString::compare(butVal,"A^D",Qt::CaseInsensitive)==0)
        adTrig=true;
    else if(QString::compare(butVal,"A^-1",Qt::CaseInsensitive)==0)
        inverseTrig=true;
}
