#ifndef TABLERO_H
#define TABLERO_H
#include "cuadricula.h"

class Tablero
{
private:
    Cuadricula *cuadriculas[3][3];

public:
    Tablero();
    bool buscarCasilla(int k);
    void modificarCasilla(int i, int j, int k);
    int obtenerValor(int i, int f);

};

#endif // TABLERO_H
