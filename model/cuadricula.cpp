#include "cuadricula.h"
#include "casilla.h"

Cuadricula::Cuadricula()
{
    for(int fila=0; fila<3;fila++){
        for(int col=0;col<3;col++){
            this->casilleros[fila][col] = new Casilla();
        }
    }
}

bool Cuadricula::buscarCasilla(int k)
{
    for(int fila=0; fila<3;fila++){
        for(int col=0;col<3;col++){
            if (this->casilleros[fila][col]->getValor()==k){
                return true;
            }
        }
    }
    return false;
}

void Cuadricula::modificarCasilla(int i, int f, int k)
{
    if(!(this->buscarCasilla(k))){
        this->casilleros[i][f]->agregarAlternativa(k);
    }
}

int Cuadricula::obtenerValor(int i, int f)
{
    return this->casilleros[i][f]->getValor();
}
