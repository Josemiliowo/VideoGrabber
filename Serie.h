//
// Created by joserangel on 8/06/24.
//

#ifndef SERIE_H
#define SERIE_H
#include "Video.h"


class Serie : public Video{
public:
    Serie();
    Serie(int temporadas, int capitulos, float duracion, float calificacion, std::string genero, std::string nombre);
    ~Serie() = default;

    int get_temporadas();
    bool set_temporas(int temporadas);
    int get_capitulos();
    bool set_capitulos(int capitulos);
    void print() override;

private:
    int temporadas;
    int capitulos;
};



#endif //SERIE_H
