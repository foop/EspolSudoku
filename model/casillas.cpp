#include "casilla.h"

Casilla::Casilla()
{
    this->valor=0;
}

void Casilla::agregarAlternativa(const int k)
{
    this->valor= k;
}

int Casilla::getValor()
{
    return this->valor;
}
