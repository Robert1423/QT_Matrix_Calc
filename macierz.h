#ifndef MACIERZ_H
#define MACIERZ_H
#include "calcmat.h"

class Macierz
{
private:
    int row;
    int col;
    vector<vector<double>> mat;
public:
    Macierz() : row(0), col(0) {};
    Macierz(int r, int c) : row(r), col(c) {};
    Macierz(const Macierz &);
    void Fill(QLineEdit *tab[], Calcmat * cUi);//wczytanie macierzy
    void Show();//wyswietlenie macierzy
    Macierz &operator+(Macierz &B);//dodawanie
    Macierz &operator-(Macierz &B);//odejmowanie
    Macierz &operator*(Macierz &B);//mnozenie macierzy
    Macierz &operator*(double x);  //mnozenie przez liczbe
    void Transpone();//transpozycja
    void Admat();//macierz dopelnien algebraicznych
    void Invers();//macierz odwrotna
    ~Macierz();
};

#endif // MACIERZ_H
