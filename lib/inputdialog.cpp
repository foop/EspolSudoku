#include "inputdialog.h"
//#include <QApplication>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>


inputDialog::inputDialog(QWidget *parent)
    : QDialog(parent)
{
    QFormLayout *layoutPrincipal = new QFormLayout;
    QHBoxLayout *layoutBotones = new QHBoxLayout;

    botonAceptar = new QPushButton(trUtf8("Aceptar"));
    botonCancelar = new QPushButton(trUtf8("Cancelar"));

    campoUsuario = new QLineEdit();

    layoutBotones->addStretch();
    layoutBotones->addWidget(botonAceptar);
    layoutBotones->addWidget(botonCancelar);

    layoutPrincipal->addRow(trUtf8("Digite el valor:"), campoUsuario);
    layoutPrincipal->addRow(layoutBotones);

    setLayout(layoutPrincipal);

    connect(botonAceptar, SIGNAL(clicked()), this, SLOT(certificarNumero()));
    connect(botonCancelar,SIGNAL(clicked()),this, SLOT(close()));

}

void inputDialog::certificarNumero()
{
    if(this->campoUsuario->text().toInt()<10 && this->campoUsuario->text().toInt()>0)
        QMessageBox::information(this,"",trUtf8("Everything ok."));//debería entregar al controlador el número que desea incluir.
    else
        return;
}
