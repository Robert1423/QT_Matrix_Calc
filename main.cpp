#include "mymatrix.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calcmat w;
    w.show();
    return a.exec();
}
