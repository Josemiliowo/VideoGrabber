//
// Created by joserangel on 8/06/24.
//

#ifndef VIDEO_H
#define VIDEO_H
#include <string>

class Video {
public:
    float get_duracion() const;
    bool set_duracion(float duracion);
    float get_calificacion() const;
    bool set_calificacion(float calificacion);
    std::string get_genero() const;
    bool set_genero(const std::string &genero);
    std::string get_nombre() const;
    bool set_nombre(const std::string &nombre);


protected:
    Video(float duracion, float calificacion, std::string genero, std::string nombre);
    Video();
    ~Video()= default;
    virtual void print();

private:
    float duracion;
    float calificacion;
    std::string genero;
    std::string nombre;

};



#endif //VIDEO_H
