#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class inputDialog: public QDialog
{

private:
    QPushButton *botonAceptar, *botonCancelar;
    QLineEdit *campoUsuario;

public:
    inputDialog(QWidget *parent=0);

private slots:
    void certificarNumero();
};

#endif // INPUTDIALOG_H
