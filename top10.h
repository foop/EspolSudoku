#ifndef TOP10_H
#define TOP10_H

#include <QDialog>

namespace Ui {
class Top10;
}

class Top10 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Top10(QWidget *parent = 0);
    void registerController(QWidget* &parent);
    ~Top10();

public slots:
     void addEntry(QString string);

private:
    Ui::Top10 *ui;
};

#endif // TOP10_H
