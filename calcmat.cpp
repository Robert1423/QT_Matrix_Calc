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
//Można przerobić te sloty na jedną funkcje.
void Calcmat::on_Add_released() //Co ma robić po wciśnięciu A+B
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    addTrig=true;
}

void Calcmat::on_Sub_released() //Co ma robić po wciśnięciu A-B
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    subTrig=true;
}

void Calcmat::on_MulMat_released() //Co ma robić po wciśnięciu A*B
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    mulTrig=true;
}

void Calcmat::on_MulX_released() //Co ma robić po wciśnięciu A*x
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    skalTrig=true;
}

void Calcmat::on_Transp_released() //Co ma robić po wciśnięciu A^T
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    transpTrig=true;
}

void Calcmat::on_Det_released() //Co ma robić po wciśnięciu det(A)
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    detTrig=true;
}

void Calcmat::on_DopA_released() //Co ma robić po wciśnięciu A^D
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    adTrig=true;
}

void Calcmat::on_Inverse_released() //Co ma robić po wciśnięciu A^-1
{
    checkElems(elems,this);
    A.Fill(elems,this);
    for (int i=0; i<16; i++)
        elems[i]->setText("");
    inverseTrig=true;
}
