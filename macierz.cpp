#include "macierz.h"

Macierz::Macierz(const Macierz &rhs)
{
    row=rhs.row;
    col=rhs.col;
    mat=rhs.mat;
}

void Macierz::Fill(QLineEdit *tab[], Calcmat * cUi)
{
    mat.erase(mat.begin(),mat.end());
    int count=0;
    for (int i=0; i<4; i++)
    {
        QString temp=tab[count]->text();
        if (temp=="") break;
        vector<double> tempRow;
        for (int j=0; j<4; j++)
        {
            temp=tab[count]->text();
            if (temp=="") break;
            count++;
            if (temp!="")
            {
                double x;
                bool ok;
                x = temp.toDouble(&ok);
                if (ok==false) {
                    QMessageBox::warning(cUi,"Błąd","Błędne dane w pozycji "+
                                         QString::number(i+1)+"x"
                                         +QString::number(j+1)+"!");
                    mat.erase(mat.begin(),mat.end());
                    return;
                }
                tempRow.push_back(x);
            }
        }
        mat.push_back(tempRow);
        if (count!=4||count!=8||count!=12)
        {
            if (i==0) count=4;
            if (i==1) count=8;
            if (i==2) count=12;
        }
    }
    row=mat.size();
    col=mat[0].size();
    QMessageBox::information(cUi,"Koniec","Sczytano");
}

Macierz::~Macierz()
{

}
