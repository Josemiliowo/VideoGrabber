#include <iostream>
#include <fstream>
#include <sstream>
#include "Pelicula.h"
#include "Serie.h"

#define VIDEOS "C:/Users/coshe/CLionProjects/SPPOO2/videos.csv"
#define ATTRIBUTES 7

using namespace std;

int countDataLinesInCSV(const string& fileName) {
    ifstream    file(fileName);
    int         lineCount = 0;
    string      line;

    // Contar la cantidad de líneas en el archivo csv
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return -1;
    }

    // skip header
    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return -1;
    }

    // Contar lineas
    while(getline(file, line)) {
        lineCount++;
    }

    file.close();
    return(lineCount);
}

bool loadVideoFromCSV(const string& fileName, Video **videoArray, unsigned int arraySize) {
    ifstream file(fileName);
    string line;


    videoArray = new(nothrow) Video* [arraySize];
    if (videoArray == nullptr) {
        cout << "No hay memoria para las figuras\n";
        return 0;
    }

    for (unsigned int i = 0; i < arraySize; i++) {
        videoArray[i] = nullptr;
    }

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    // skip header
    if (!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while (getline(file, line)) {

        stringstream ss(line);
        string cell;
        int campo = 0, errores = 0;
        int sizeArray = 0;
        int element = 0;

        while (getline(ss, cell, ',')) {
            if (!cell.length())
                errores++;

            bool flagSerie = false;
            bool flagPelicula = false;

            string nombre = "NA";
            string genero = "NA";
            float duracion = 0;
            float calificacion = 0;
            int nominaciones = 0;
            int capitulos = 0;
            int temporadas =  0;

            switch(campo) {
                case 0:
                    if(cell == "serie") {
                        flagSerie = true;
                    } else if(cell == "pelicula") {
                        flagPelicula = true;
                    }
                    //cout << cell << endl;
                    //cout << flagPelicula << " " << flagSerie << endl;
                    break;
                case 1:
                    if(typeid(*videoArray[element]) == typeid(Serie)){
                        nombre = cell;
                    } else if(typeid(*videoArray[element]) == typeid(Pelicula)){
                        nombre = cell;
                    }
                    //cout << cell << endl;
                    break;
                case 2:
                    if(typeid(*videoArray[element]) == typeid(Serie)){
                        duracion = stof(cell);
                    } else if(typeid(*videoArray[element]) == typeid(Pelicula)){
                        duracion = stof(cell);
                    }
                    break;
                case 3:
                    if(typeid(*videoArray[element]) == typeid(Serie)){
                        calificacion = stof(cell);
                    } else if(typeid(*videoArray[element]) == typeid(Pelicula)){
                        calificacion = stof(cell);
                    }
                    //cout << cell << endl;
                    break;
                case 4:
                    if(typeid(*videoArray[element]) == typeid(Serie)){
                        genero = cell;
                    } else if(typeid(*videoArray[element]) == typeid(Pelicula)){
                        genero = cell;
                    }
                    //cout << cell << endl;
                    break;
                case 5:
                    if(typeid(*videoArray[element]) == typeid(Pelicula)) {
                        nominaciones = (stoi(cell));
                    } else if(typeid(*videoArray[element]) == typeid(Serie)){
                        capitulos = (stoi(cell));
                    }
                    //cout << cell << endl;
                    break;
                case 6:
                    if(typeid(*videoArray[element]) == typeid(Serie)){
                        temporadas = (stoi(cell));
                    //cout << cell << endl;
                    break;
                default:
                    errores ++;
                    break;
            }

            campo ++;

        }
        // Comparar si son 7 campos, aqui depende de cuantas
        // entradas tiene cada clase
        if(errores || campo != ATTRIBUTES) {
            cerr << "Error en la linea: " << endl << line << endl;
            file.close();
            return false;
        }


        if((element < arraySize) && flagSerie) {
            videoArray[element] = new Serie(temporadas, capitulos, duracion, calificacion, genero, nombre);
            element ++;
        } else if((element < arraySize) && flagPelicula) {
            videoArray[element] = new Pelicula(nominaciones, duracion, calificacion, genero, nombre);
            element ++;
        } else if((element) >= arraySize){
            cerr << "Error, el arreglo es muy pequeño" << endl;
            file.close();
            return false;
        }

    }
    file.close();

    return true;
}

int main(){

    Video *arrayVideos = nullptr;
    int dataSize = 0;
    bool menu = true;
    bool archivoCargado = false;

    while(menu) {
        cout << "1. Cargar archivo\n"
                "2. Menu peliculas\n"
                "3. Menu series\n"
                "4. Salir\n";

        int opcion;
        cin >> opcion;

        switch(opcion){
            case 1: {
                cout << "Insertar nombre del archivo en la carpeta: " << endl;
                string archivo;
                cin >> archivo;
                archivo = "C:/Users/josem/CLionProjects/SPPOO2/" + archivo;

                dataSize = countDataLinesInCSV(archivo);
                if (dataSize == -1) {
                    cerr << "No se pudo cargar el data set de " << archivo << "\n";
                    return -1;
                }

                cout << "Videos.csv tiene: " << dataSize << " entradas\n";
                arraySeries = new(nothrow) Serie[dataSize];
                arrayPeliculas = new(nothrow) Pelicula[dataSize];

                if (arraySeries == nullptr || arrayPeliculas == nullptr) {
                    cerr << "No hubo memoria para el arreglo de " << archivo << "\n";
                    return 0;
                }

                if (!loadVideoFromCSV(archivo, arrayPeliculas, arraySeries, dataSize)) {
                    cerr << "Error al cargar el data set de " << archivo << "\n";
                    delete[] arraySeries;
                    delete[] arrayPeliculas;
                    return 0;
                }
                archivoCargado = true;

                break;
            }
            case 2: {
                if (!archivoCargado) {
                    cout << "Primero carga un archivo" << endl;
                    break;
                }
                bool menuPeliculas = true;
                while(menuPeliculas) {
                    cout << "1. Buscar por calificacion\n"
                            "2. Buscar por genero\n"
                            "3. Regresar\n";

                    int opcionPeliculas;
                    cin >> opcionPeliculas;

                    switch (opcionPeliculas) {
                        case 1: {
                            cout << "Insertar calificacion: " << endl;
                            float calificacion;
                            cin >> calificacion;
                            cout << "Peliculas con calificacion entre " << calificacion-0.5 << " y " << calificacion+0.5 << endl;
                            for (int i = 0; i < dataSize; i++) {
                                if (arrayPeliculas[i].get_nombre() != "NA" &&
                                        (arrayPeliculas[i].get_calificacion() > calificacion-0.5)
                                        && arrayPeliculas[i].get_calificacion() < calificacion+0.5){
                                    cout << "Pelicula: " << i << endl;
                                    arrayPeliculas[i].print();
                                        }
                            }
                            break;
                        }
                        case 2: {
                            cout << "Insertar genero: " << endl;
                            string genero;
                            cin >> genero;

                            for (int i = 0; i < dataSize; i++) {
                                if (arrayPeliculas[i].get_nombre() != "NA" &&
                                    arrayPeliculas[i].get_genero() == genero) {
                                    cout << "Pelicula: " << i << endl;
                                    arrayPeliculas[i].print();
                                    }
                            }
                            break;
                        }
                        case 3: {
                            menuPeliculas = false;
                            break;
                        }
                    }
                }

                break;
            }
            case 3: {
                if (!archivoCargado) {
                    cout << "Primero carga un archivo" << endl;
                    break;
                }
                bool menuSeries = true;
                while(menuSeries) {
                    cout << "1. Buscar por calificacion\n"
                                "2. Buscar por genero\n"
                                "3. Regresar\n";

                    int opcionSeries;
                    cin >> opcionSeries;

                    switch(opcionSeries) {
                        case 1: {
                            cout << "Insertar calificacion: " << endl;
                            float calificacion;
                            cin >> calificacion;
                            cout << "Series con calificacion entre " << calificacion-0.5 << " y " << calificacion+0.5 << endl;
                            for (int i = 0; i < dataSize; i++) {
                                if (arraySeries[i].get_nombre() != "NA" &&
                                    (arraySeries[i].get_calificacion() > calificacion-0.5)
                                    && arraySeries[i].get_calificacion() < calificacion+0.5){
                                    cout << "Serie: " << i << endl;
                                    arraySeries[i].print();
                                    }
                            }
                            break;
                        }
                        case 2: {
                            cout << "Insertar genero: " << endl;
                            string genero;
                            cin >> genero;
                            cout << "Series con genero: " << genero << endl;
                            for (int i = 0; i < dataSize; i++) {
                                if (arraySeries[i].get_nombre() != "NA" &&
                                    arraySeries[i].get_genero() == genero) {
                                    cout << "Serie: " << i << endl;
                                    arraySeries[i].print();
                                    }
                            }
                            break;
                        }
                        case 3: {
                            menuSeries = false;
                            break;
                        }
                    }

                    break;
                }
            }
                case 4: {
                    menu = false;
                    break;
                }
            }

        }


    delete [] arrayVideos;
    return 0;
}
