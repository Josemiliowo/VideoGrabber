//
// Created by joserangel on 8/06/24.
//

#ifndef PELICULA_H
#define PELICULA_H
#include "video.h"


class pelicula : public video{
public:
    pelicula();
    pelicula(int nominaciones);

private:
    int nominaciones;
};



#endif //PELICULA_H
