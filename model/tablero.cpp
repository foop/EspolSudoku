#include "tablero.h"
#include "cuadricula.h"

Tablero::Tablero()
{
    for(int fila=0; fila<3;fila++){
        for(int col=0;col<3;col++){
            this->cuadriculas[fila][col] = new Cuadricula();
        }
    }
}


int Tablero::obtenerValor(int i, int j)
{
    if(i<3){
        if(j<3){
            return this->cuadriculas[0][0]->obtenerValor(i,j);
        }else if(j<6){
            return this->cuadriculas[0][1]->obtenerValor(i,j-3);
        }else if(j<9){
            return this->cuadriculas[0][2]->obtenerValor(i,j-6);
        }
    }else if(i<6){
        if(j<3){
            return this->cuadriculas[1][0]->obtenerValor(i-3,j);
        }else if(j<6){
            return this->cuadriculas[1][1]->obtenerValor(i-3,j-3);
        }else if(j<9){
            return this->cuadriculas[1][2]->obtenerValor(i-3,j-6);
        }
    }else if(i<9){
        if(j<3){
            return this->cuadriculas[2][0]->obtenerValor(i-6,j);
        }else if(j<6){
            return this->cuadriculas[2][1]->obtenerValor(i-6,j-3);
        }else if(j<9){
            return this->cuadriculas[2][2]->obtenerValor(i-6,j-6);
        }
    }
    return -1;
}


void Tablero::modificarCasilla(int i, int j, int k)
{
    if(i<3){
        if(j<3){
            this->cuadriculas[0][0]->modificarCasilla(i,j,k);
        }else if(j<6){
            this->cuadriculas[0][1]->modificarCasilla(i,j-3,k);
        }else if(j<9){
            this->cuadriculas[0][2]->modificarCasilla(i,j-6,k);
        }
    }else if(i<6){
        if(j<3){
            this->cuadriculas[1][0]->modificarCasilla(i-3,j,k);
        }else if(j<6){
            this->cuadriculas[1][1]->modificarCasilla(i-3,j-3,k);
        }else if(j<9){
            this->cuadriculas[1][2]->modificarCasilla(i-3,j-6,k);
        }
    }else if(i<9){
        if(j<3){
            this->cuadriculas[2][0]->modificarCasilla(i-6,j,k);
        }else if(j<6){
            this->cuadriculas[2][1]->modificarCasilla(i-6,j-3,k);
        }else if(j<9){
            this->cuadriculas[2][2]->modificarCasilla(i-6,j-6,k);
        }
    }
}
