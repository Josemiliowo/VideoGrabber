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

bool loadVideoFromCSV(const string& fileName, Pelicula *peliculaArray, Serie *serieArray, unsigned int arraySize) {
    ifstream file(fileName);
    string line;
    unsigned int sizeSerie = 0;
    unsigned int sizePelicula = 0;

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
        Pelicula nPelicula;
        Serie nSerie;

        stringstream ss(line);
        string cell;
        int campo = 0, errores = 0;

        bool flagSerie = false;
        bool flagPelicula = false;

        while (getline(ss, cell, ',')) {
            if (!cell.length())
                errores++;

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
                    if(flagSerie){
                        nSerie.set_nombre(cell);
                    } else if(flagPelicula){
                        nPelicula.set_nombre(cell);
                    }
                    //cout << cell << endl;
                    break;
                case 2:
                    if(flagSerie){
                        nSerie.set_duracion(stof(cell));
                    } else if(flagPelicula){
                        nPelicula.set_duracion(stof(cell));
                    }
                    break;
                case 3:
                    if(flagSerie){
                        nSerie.set_calificacion(stof(cell));
                    } else if(flagPelicula){
                        nPelicula.set_calificacion(stof(cell));
                    }
                    //cout << cell << endl;
                    break;
                case 4:
                    if(flagSerie){
                        nSerie.set_genero(cell);
                    } else if(flagPelicula){
                        nPelicula.set_genero(cell);
                    }
                    //cout << cell << endl;
                    break;
                case 5:
                    if (flagPelicula) {
                        nPelicula.set_nominaciones(stoi(cell));
                    } else if(flagSerie){
                        nSerie.set_capitulos(stoi(cell));
                    }
                    //cout << cell << endl;
                    break;
                case 6:
                    if(flagSerie){
                        nSerie.set_temporas(stoi(cell));
                    } else if(flagPelicula){
                        // No hay campo 6 en Pelicula
                    }
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

        if((sizeSerie + sizePelicula) < arraySize && flagSerie) {
            serieArray[sizeSerie] = nSerie;
            sizeSerie ++;
        } else if((sizeSerie + sizePelicula) < arraySize && flagPelicula) {
            peliculaArray[sizePelicula] = nPelicula;
            sizePelicula ++;
        } else if((sizeSerie + sizePelicula) >= arraySize){
            cerr << "Error, el arreglo es muy pequeño" << endl;
            file.close();
            return false;
        }

    }
    file.close();

    return true;
}

int main() {
    Pelicula *arrayPeliculas = nullptr;
    Serie *arraySeries = nullptr;

    int dataSize = 0;

    dataSize = countDataLinesInCSV(VIDEOS);
    if(dataSize == -1) {
        cerr << "No se pudo cargar el data set de " << VIDEOS << "\n";
        return -1;
    }

    cout << "Videos.csv tiene: " << dataSize << " entradas\n";
    arraySeries = new(nothrow) Serie[dataSize];
    arrayPeliculas = new(nothrow) Pelicula[dataSize];

    if(arraySeries == nullptr || arrayPeliculas == nullptr) {
        cerr << "No hubo memoria para el arreglo de " << VIDEOS << "\n";
        return 0;
    }

    if(!loadVideoFromCSV(VIDEOS, arrayPeliculas, arraySeries, dataSize)) {
        cerr << "Error al cargar el data set de " << VIDEOS << "\n";
        delete [] arraySeries;
        delete [] arrayPeliculas;
        return 0;
    }

    for (int i = 0; i < dataSize; i++) {
        if(arrayPeliculas[i].get_nombre() != "NA"){
            cout << "Pelicula: " << i << endl;
            arrayPeliculas[i].print();
        }
    }
    for(int i = 0; i < dataSize; i++){
        if(arraySeries[i].get_nombre() != "NA"){
            cout << "Serie: " << i << endl;
            arraySeries[i].print();
        }
    }

    delete [] arraySeries;
    delete [] arrayPeliculas;
    return 0;
}
