#include "mymatrix.h"
#include <algorithm>

string test;
QString calc;

double calcdet(vector<vector<double>> mat); //funkcja rekurencyjna do obliczania wyznacznika
vector<vector<double>> cut(vector<vector<double>> v, int n, int m);//do wyznacznika, wycina podany wiersz i kolumne

MyMatrix::MyMatrix(vector<vector<double>> m)//konstruktor inicjowany vectorem macierzy
{
    copy(m.begin(),m.end(),mat.begin());
    row=mat.size();
    col=mat[0].size();
    result="";
    calcValue="";
}

MyMatrix::MyMatrix(const MyMatrix &rhs) //kopiujący
{
    row=rhs.row;
    col=rhs.col;
    mat=rhs.mat;
    result=rhs.result;
    calcValue=rhs.calcValue;
}

void MyMatrix::Fill(QLineEdit *tab[], Calcmat * cUi) //wczytywanie wartości do macierzy
{
    mat.erase(mat.begin(),mat.end());
    int count=0; //do sprawdzania pozycji QLineEdit
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
                x = temp.toDouble(&ok); //sprawdza czy udało się skonwertować wartość z QLineEdit na double
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
        if (count!=4||count!=8||count!=12) //do sterowania pozycją w tablicy
        {
            if (i==0) count=4;
            if (i==1) count=8;
            if (i==2) count=12;
        }
    }
    row=mat.size();
    col=mat[0].size();
}

void MyMatrix::Show(QTextBrowser * display, QTextEdit * calcs)
{
    if (row!=0&&col!=0)
    {
        for (int i=0; i<row; i++)
        {
            result+="";
            for (int j=0; j<col; j++)
            {
                result+=QString::number(mat[i][j]);
                if (col-j>1)
                    result+="\t";
            }
            result+="\n";
        }
        display->setText(result);
        calcs->setText("");
    }
    else
        calcs->setText("Pusta");
}

void MyMatrix::Add(MyMatrix &B, Calcmat * cUi)
{
    result="";
    calcValue="";
    if (row==B.row&&col==B.col)
    {
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                result+=QString::number(mat[i][j]+B.mat[i][j]);
                calcValue+=QString::number(i+1) + "x" + QString::number(j) + ": " +
                        QString::number(mat[i][j]) + " + " + QString::number(B.mat[i][j]);
                if (col-j>1)
                    result+="\t";
                calcValue+="\n";
            }
            result+="\n";
        }

    }
    else
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne wymiary!\nNie zdefiniowano działania!");
}

void MyMatrix::Sub(MyMatrix &B, Calcmat * cUi)
{
    result="";
    calcValue="";
    if (row==B.row&&col==B.col)
    {
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                result+=QString::number(mat[i][j]-B.mat[i][j]);
                calcValue+=QString::number(i+1) + "x" + QString::number(j) + ": " +
                        QString::number(mat[i][j]) + " - " + QString::number(B.mat[i][j]);
                if (col-j>1)
                    result+="\t";
                calcValue+="\n";
            }
            result+="\n";
        }

    }
    else
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne wymiary!\nNie zdefiniowano działania!");
}

void MyMatrix::Mul(MyMatrix &B, Calcmat * cUi)
{
    result="";
    calcValue="";
    if (col==B.row)
    {
        for (int i=0; i<row; i++)
        {
            for (int k=0; k<B.col; k++)
            {
                calcValue+="Wymnażanie wiersza " + QString::number(i+1) + " przez kolumne " + QString::number(k+1) + ":\n";
                double t=0;
                for (int j=0; j<B.row; j++)
                {
                    t+=mat[i][j]*B.mat[j][k];
                    calcValue+=QString::number(mat[i][j]) + " * " + QString::number(B.mat[j][k]);
                    if (B.row-j>1)
                        calcValue+=" + ";
                }
                calcValue += "\n";
                result+= QString::number(t);
                if (B.col-k>1)
                    result+="\t";
            }
            result+="\n";
        }
    }
    else
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne wymiary!\nNie zdefiniowano działania!");
}

void MyMatrix::MulNum(double x)
{
    result="";
    calcValue="";
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            result+=QString::number(mat[i][j]*x);
            calcValue+=QString::number(i+1) + "x" + QString::number(j+1) + ": " +
                    QString::number(mat[i][j]) + " * " + QString::number(x) + "\n";
            if (col-j>1)
                result+='\t';
        }
        result+="\n";
    }
}

double MyMatrix::Det(Calcmat * cUi)
{
    calc="";
    if (row==col)
    {
        vector<vector<double>> v=mat;
        double res;
            res = calcdet(v);
        calcValue=calc;
        return res;
    }
    else
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne wymiary");
    return 1;
}

void MyMatrix::Transpone()
{
    vector<vector<double>> temp;
    for (int i=0; i<col; i++)
    {
        vector<double> matRow;
        for (int j=0; j<row; j++)
        {
            matRow.push_back(mat[j][i]);
        }
        temp.push_back(matRow);
    }
    mat.erase(mat.begin(),mat.end());
    mat=temp;
    row=mat.size();
    col=mat[0].size();
    result="";
    calcValue="";
}

vector<vector<double>> MyMatrix::Admat(Calcmat * cUi)
{
    if (row==col)
    {
        result="";
        vector<vector<double>> ad=mat;
        vector<vector<double>> res;
        for (int i=0; i<row; i++)
        {
            vector<double> temp;
            for (int j=0; j<col; j++)
            {
                calc="";
                int m=pow(-1,(i+j+2));
                double d=calcdet(cut(ad,i,j));
                result+=QString::number(m*d)+"\t";
                temp.push_back(m*d);
                calcValue+="("+QString::number(-1)+")^("+QString::number(i+1)+
                        QString::number(j+1)+") * "+QString::number(d);
            }
            result+="\n";
            res.push_back(temp);
        }
        return res;
    }
    else
    {
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne rozmiary!");
        return mat;
    }
}

void MyMatrix::Invers(Calcmat * cUi)
{
    if (row==col)
    {
        result="";
        vector<vector<double>> nmat=mat;
        double d=calcdet(nmat);
        if (d==0)
            QMessageBox::information(cUi,"Błąd!","Wyznacznik = 0\nMacierz odwrotna nie istnieje");
        else
        {
            vector<vector<double>> ad=Admat(cUi);
            calcValue=QString::number(1)+" / "+QString::number(d) + " * (A^D)^T";
            mat=ad;
            Transpone();
            MulNum(1/d);
        }
    }
    else
        QMessageBox::warning(cUi,"Błąd!","Niepoprawne rozmmiary!");
}

MyMatrix::~MyMatrix()
{

}

vector<vector<double>> cut(vector<vector<double>> v, int n, int m)
{
    vector<vector<double>> temp;
    for (int i = 0; i < (int)v.size(); i++)
    {
        vector<double> row;
        if (n == i)
            continue;
        for (int j = 0; j < (int)v[i].size(); j++)
        {
            if (m == j)
                continue;
            row.push_back(v[i][j]);
        }
        temp.push_back(row);
    }
    return temp;
}

double calcdet(vector<vector<double>> mat)
{
        double d = 0;
        if (mat.size() == 1 && mat[0].size() == 1)
            return mat[0][0];
        else
        {
            int mn = -1;
            for (int j = 0; j < (int)mat[0].size(); j++)
            {
                double x = calcdet(cut(mat, 0, j));
                d += pow(mn, 0 + j) * mat[0][j] * x;
                calc+= "("+QString::number(mn) + ")^(" + QString::number(1) + "+" + QString::number(j+1)
                        + ") *" + QString::number(mat[0][j]) + "*" + QString::number(x);
                if (mat[0].size()-j>1)
                    calc+=" + \n";
            }
            return d;
        }
}
