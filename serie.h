//
// Created by joserangel on 8/06/24.
//

#ifndef SERIE_H
#define SERIE_H
#include "video.h"


class serie : public video{
public:
    serie();
    serie(int temporadas,  int capitulos);

    int get_temporadas();
    bool set_temporas(int temporadas);
    int get_capitulos();
    bool set_capitulos(int capitulos);

private:
    int temporadas;
    int capitulos;
};



#endif //SERIE_H
