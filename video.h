//
// Created by joserangel on 8/06/24.
//

#ifndef VIDEO_H
#define VIDEO_H
#include <string>

class video {
protected:
    video(float duracion, float calificacion, std::string genero);
    video();

    float get_duracion() const;
    bool set_duracion(float duracion);
    float get_calificacion() const;
    bool set_calificacion(float calificacion);
    std::string get_genero() const;
    bool set_genero(const std::string &genero);

private:
    float duracion;
    float calificacion;
    std::string genero;

};



#endif //VIDEO_H
