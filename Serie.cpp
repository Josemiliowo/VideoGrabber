//
// Created by joserangel on 8/06/24.
//

#include <iostream>
#include "Serie.h"

Serie::Serie() {
    temporadas = 0;
    capitulos = 0;
}
Serie::Serie(int temporadas, int capitulos) {
    this->temporadas = temporadas;
    this->capitulos = capitulos;
}

int Serie::get_temporadas() {
    return temporadas;
}
bool Serie::set_temporas(int temporada) {
    if (temporada > 0) {
        this->temporadas = temporada;
        return true;
    }
    std::cout << "El numero de temporadas no puede ser negativo o cero" << std::endl;
    return false;
}
int Serie::get_capitulos(){
    return capitulos;
}
bool Serie::set_capitulos(int capitulos){
    if (capitulos > 0) {
        this->capitulos = capitulos;
        return true;
    }
    std::cout << "El numero de capitulos no puede ser negativo o cero" << std::endl;
    return false;
}

void Serie::print() {
    Video::print();
    std::cout << "Temporadas: " << temporadas << std::endl;
    std::cout << "Capitulos: " << capitulos << std::endl;
}
