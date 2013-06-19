#ifndef CASILLA_H
#define CASILLA_H
#include <QList>

class Casilla
{
public:
    Casilla();
private:
    int valor;
    QList<int> *alternativas;

public:
    void agregarAlternativa(const int k);
    int getValor();
};

#endif // CASILLA_H
