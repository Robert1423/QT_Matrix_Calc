#ifndef CALCMAT_H
#define CALCMAT_H

#include <QMainWindow>
#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Calcmat;}
QT_END_NAMESPACE

using namespace std;

class Calcmat : public QMainWindow
{
    Q_OBJECT

public:
    Calcmat(QWidget *parent = nullptr);
    ~Calcmat();

protected:
    Ui::Calcmat *ui;
private slots:
    void on_Result_released();
    void on_Clear_released();
    void on_Add_released();
    void on_Sub_released();
    void on_MulMat_released();
    void on_MulX_released();
    void on_Transp_released();
    void on_Det_released();
    void on_DopA_released();
    void on_Inverse_released();
};

#endif // CALCMAT_H
