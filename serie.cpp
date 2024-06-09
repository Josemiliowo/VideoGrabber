//
// Created by joserangel on 8/06/24.
//

#include "serie.h"

serie::serie() {
    temporadas = 0;
    capitulos = 0;
}
serie::serie(int temporadas,  int capitulos) {
    this->temporadas = temporadas;
    this->capitulos = capitulos;
}

int serie::get_temporadas() {
    return temporadas;
}
bool serie::set_temporas(int temporada) {
    if(typeid(temporada) == typeid(int)) {
        
    }
}
int serie::get_capitulos();
bool serie::set_capitulos();
