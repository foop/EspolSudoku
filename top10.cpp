#include "top10.h"
#include "ui_top10.h"

Top10::Top10(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Top10)
{
    ui->setupUi(this);
}


void Top10::addEntry(QString string) {
    ui->textEdit->append(string);
}


Top10::~Top10()
{
    delete ui;
}
