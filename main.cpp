#include "macierz.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calcmat w;
    Macierz A;
    Macierz B;
    w.show();
    return a.exec();
}
