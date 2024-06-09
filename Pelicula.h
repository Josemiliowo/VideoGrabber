//
// Created by joserangel on 8/06/24.
//

#ifndef PELICULA_H
#define PELICULA_H
#include "Video.h"


class Pelicula : public Video{
public:
    Pelicula();
    Pelicula(int nominaciones);
    int get_nominaciones();
    bool set_nominaciones(int nominaciones);
    void print() override;

private:
    int nominaciones;
};



#endif //PELICULA_H
