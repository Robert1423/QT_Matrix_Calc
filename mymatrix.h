#ifndef MYMATRIX_H
#define MYMATRIX_H
#include "calcmat.h"
#include <QTextBrowser>

class MyMatrix
{
protected:
    int row;
    int col;
    vector<vector<double>> mat;
    QString result;
    QString calcValue;
   // Calcmat * ui;
public:
    MyMatrix() : row(0), col(0), result(""), calcValue("") {};
    MyMatrix(int r, int c) : row(r), col(c), result(""), calcValue("") {};
    MyMatrix(vector<vector<double>> m);
    MyMatrix(const MyMatrix &);
    //void SetUi(Calcmat * temp);
    void Fill(QLineEdit *tab[], Calcmat * cUi);//wczytanie macierzy
    void Show(QTextBrowser * display, QTextEdit * calcs);//wyswietlenie macierzy
    void Add(MyMatrix &B, Calcmat * cUi);//dodawanie
    void Sub(MyMatrix &B, Calcmat * cUi);//odejmowanie
    void Mul(MyMatrix &B, Calcmat * cUi);//mnozenie macierzy
    void MulNum(double x);  //mnozenie przez liczbe
    double Det(Calcmat * cUi); //wyznacznik
    vector<vector<double>> retMat(){return mat;}
    void Transpone();//transpozycja
    vector<vector<double>> Admat(Calcmat * cUi);//macierz dopelnien algebraicznych
    void Invers(Calcmat * cUi);//macierz odwrotna
    QString Res() {return result;}
    QString CalcV() {return calcValue;}
    double skalar(int n, int m) {return mat[n][m];}
    int Row() {return row;}
    int Col() {return col;}
    ~MyMatrix();
//    friend void cut(vector<vector<double>> & v, int n, int m); //do wyznacznika, wycina wiersze i kolumny z macierzy
//    friend double & calcdet(vector<vector<double>> mat, MyMatrix & M); //obliczenia wyznacznika
};

#endif // MYMATRIX_H
