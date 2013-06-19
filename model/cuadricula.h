#ifndef CUADRICULA_H
#define CUADRICULA_H
#include "casilla.h"

class Cuadricula
{
private:
    Casilla *casilleros[3][3];
public:
    Cuadricula();
    bool buscarCasilla(int k);
    void modificarCasilla(int i, int f, int k);
    int obtenerValor(int i, int f);

};


#endif // CUADRICULA_H
