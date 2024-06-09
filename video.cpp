//
// Created by joserangel on 8/06/24.
//

#include "video.h"

video::video() {
    duracion = 0;
    calificacion = 0;
    genero = "NA";
}

video::video(float duracion, float calificacion, std::string genero) {
    this->duracion = duracion;
    this->calificacion = calificacion;
    this->genero = genero;
}

float video::get_duracion() const {
    return duracion;
}

bool video::set_duracion(float duracion) {
    this->duracion = duracion;
}

float video::get_calificacion() const {
    return calificacion;
}

bool video::set_calificacion(float calificacion) {
    this->calificacion = calificacion;
}

std::string video::get_genero() const {
    return genero;
}

bool video::set_genero(const std::string &genero) {
    this->genero = genero;
}