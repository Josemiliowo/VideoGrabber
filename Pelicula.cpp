//
// Created by joserangel on 8/06/24.
//

#include "Pelicula.h"
#include <iostream>

Pelicula::Pelicula() {
    nominaciones = 0;
}

Pelicula::Pelicula(int nominaciones, float duracion, float calificacion, std::string genero, std::string nombre)
        : Video(duracion, calificacion, genero, nombre), nominaciones(nominaciones) {
    this->nominaciones = nominaciones;
}

int Pelicula::get_nominaciones() {
    return nominaciones;
}

bool Pelicula::set_nominaciones(int nominaciones) {
    if (nominaciones > 0) {
        this->nominaciones = nominaciones;
        return true;
    }
    std::cout << "El numero de nominaciones no puede ser negativo o cero" << std::endl;
    return false;
}

void Pelicula::print() {
    Video::print();
    std::cout << "Nominaciones: " << nominaciones << std::endl;
}

