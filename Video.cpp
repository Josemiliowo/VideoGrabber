//
// Created by joserangel on 8/06/24.
//

#include <iostream>
#include "Video.h"

Video::Video() {
    duracion = 0;
    calificacion = 0;
    genero = "NA";
    nombre = "NA";
}

Video::Video(float duracion, float calificacion, std::string genero, std::string nombre) {
    this->duracion = duracion;
    this->calificacion = calificacion;
    this->genero = genero;
    this->nombre = nombre;
}

float Video::get_duracion() const {
    return duracion;
}

bool Video::set_duracion(float duracion) {
    this->duracion = duracion;
    return true;
}

float Video::get_calificacion() const {
    return calificacion;
}

bool Video::set_calificacion(float calificacion) {
    this->calificacion = calificacion;
    return true;
}

std::string Video::get_genero() const {
    return genero;
}

bool Video::set_genero(const std::string &genero) {
    this->genero = genero;
    return true;
}

std::string Video::get_nombre() const {
    return nombre;
}

bool Video::set_nombre(const std::string &nombre) {
    this->nombre = nombre;
    return true;
}

void Video::print() {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Genero: " << genero << std::endl;
    std::cout << "Duracion: " << duracion << std::endl;
}
