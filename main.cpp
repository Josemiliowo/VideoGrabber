#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
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

void appendValueToLineInCSV(const std::string& filename, int lineNumber, const std::string& value) {
    std::ifstream fileIn(filename);
    std::vector<std::string> lines;
    std::string line;

    // Leer todas las lineas y guardarlas en un vector
    while (std::getline(fileIn, line)) {
        lines.push_back(line);
    }
    fileIn.close();

    // Busca la linea en el vector y modifica el valor. Igualmente revisa que la linea exista
    if (lineNumber >= 0 && lineNumber+1 < lines.size()) {
        lines[lineNumber+1] += "," + value;
    }

    // Reescribe el archivo en su totalidad
    std::ofstream fileOut(filename);
    for (const auto& line : lines) {
        fileOut << line << "\n";
    }
    fileOut.close();
}

bool loadVideoGradesfromCSV(const string& filename,float* gradeArray , unsigned int arraySize){
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return false;
    }
    if (!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    int element = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        float calificacion = 0;
        int contador = 0;

        while (getline(ss, cell, ',')) {
            calificacion = calificacion + stof(cell);
            contador++;
        }

        gradeArray[element] = static_cast<float>(calificacion)/contador;
        element++;
    }
    return true;
}


bool loadVideoFromCSV(const string& fileName, Video** videoArray, unsigned int arraySize) {
    ifstream file(fileName);
    string line;

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

    int element = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string cell;
        int campo = 0, errores = 0;
        int sizeArray = 0;

        bool flagSerie = false;
        bool flagPelicula = false;

        string nombre = "NA";
        string genero = "NA";
        float duracion = 0;
        float calificacion = 0;
        int nominaciones = 0;
        int capitulos = 0;
        int temporadas = 0;

        while (getline(ss, cell, ',')) {
            if (!cell.length())
                errores++;

            switch (campo) {
                case 0:
                    if (cell == "serie") {
                        flagSerie = true;
                    } else if (cell == "pelicula") {
                        flagPelicula = true;
                    }
                    //cout << cell << endl;
                    //cout << flagPelicula << " " << flagSerie << endl;
                    break;
                case 1:
                    if (flagSerie) {
                        nombre = cell;
                    } else if (flagPelicula) {
                        nombre = cell;
                    }
                    //cout << cell << endl;
                    break;
                case 2:
                    if (flagSerie) {
                        duracion = stof(cell);
                    } else if (flagPelicula) {
                        duracion = stof(cell);
                    }
                    break;
                case 3:
                    if (flagSerie) {
                        calificacion = stof(cell);
                    } else if (flagPelicula) {
                        calificacion = stof(cell);
                    }
                    //cout << cell << endl;
                    break;
                case 4:
                    if (flagSerie) {
                        genero = cell;
                    } else if (flagPelicula) {
                        genero = cell;
                    }
                    //cout << cell << endl;
                    break;
                case 5:
                    if (flagSerie) {
                        nominaciones = (stoi(cell));
                    } else if (flagPelicula) {
                        capitulos = (stoi(cell));
                    }
                    //cout << cell << endl;
                    break;
                case 6:
                    if (flagSerie) {
                        temporadas = (stoi(cell));
                        //cout << cell << endl;
                    }
                    break;

                default:
                    errores++;
                    break;

            }
            campo++;
        }
            // Comparar si son 7 campos, aqui depende de cuantas
            // entradas tiene cada clase
            if (errores || campo != ATTRIBUTES) {
                cerr << "Error en la linea: " << endl << line << endl;
                file.close();
                return false;
            }

            if ((element < arraySize) && flagSerie) {
                videoArray[element] = new(nothrow) Serie(temporadas, capitulos, duracion, calificacion, genero, nombre);
                element++;
            } else if ((element < arraySize) && flagPelicula) {
                videoArray[element] = new(nothrow) Pelicula(nominaciones, duracion, calificacion, genero, nombre);
                element++;
            } else if ((element) >= arraySize) {
                cerr << "Error, el arreglo es muy pequeño" << endl;
                file.close();
                return false;
            }
        }
        file.close();
        return true;
    }

int main(){
    string archivoCalif;
    Video** arrayVideos = nullptr;
    float* arrayGrades;
    int dataSize = 0;
    bool menu = true;
    bool archivoCargado = false;

    while(menu) {
        cout << "1. Cargar archivo\n"
                "2. Menu peliculas\n"
                "3. Menu series\n"
                "4. Calificar\n"
                "5. Salir\n"
                "6. Debug\n";

        int opcion;
        cin >> opcion;

        switch(opcion){
            case 1: {
                cout << "Insertar nombre del archivo en la carpeta: " << endl;
                string archivo;
                cin >> archivo;
                archivoCalif = "C:/Users/coshe/OneDrive/Documents/GitHub/SPPOO2/C" + archivo;
                archivo = "C:/Users/coshe/OneDrive/Documents/GitHub/SPPOO2/" + archivo;

                dataSize = countDataLinesInCSV(archivo);
                if (dataSize == -1) {
                    cerr << "No se pudo cargar el data set de " << archivo << "\n";
                    return -1;
                }

                cout << "Videos.csv tiene: " << dataSize << " entradas\n";
                arrayVideos = new(nothrow) Video* [dataSize];
                if (arrayVideos == nullptr) {
                    cerr << "No hubo memoria para el arreglo de " << archivo << "\n";
                    return 0;
                }

                arrayGrades = new(nothrow) float[dataSize];
                if (!loadVideoFromCSV(archivo, arrayVideos, dataSize)) {
                    cerr << "Error al cargar el data set de " << archivo << "\n";
                    delete[] arrayVideos;
                    return 0;
                }
                if (!loadVideoGradesfromCSV(archivoCalif, arrayGrades, dataSize)) {
                    cerr << "Error al cargar el data set de " << archivoCalif << "\n";
                    delete[] arrayGrades;
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
                int opcionPeliculas;
                while(menuPeliculas) {
                    cout << "1. Buscar por calificacion\n"
                            "2. Buscar por genero\n"
                            "3. Regresar\n";

                    cin >> opcionPeliculas;

                    switch (opcionPeliculas) {
                        case 1: {
                            cout << "Insertar calificacion: " << endl;
                            float calificacion;
                            cin >> calificacion;
                            if (calificacion < 0 || calificacion > 5) {
                                cout << "Calificacion invalida" << endl;
                                break;
                            }
                            calificacion = floor(calificacion);
                            if(calificacion == 5.0){
                                cout << "Peliculas con calificacion 5:" << endl;
                                for (int i = 0; i < dataSize; i++) {
                                    if(typeid(*arrayVideos[i]) == typeid(Pelicula)){
                                        if (arrayVideos[i]->get_nombre() != "NA" && (arrayGrades[i] == 5.0)){
                                            cout << "Pelicula " << i << ":" << endl;
                                            arrayVideos[i]->print();
                                            cout << "Calificacion: " << arrayGrades[i] << endl;
                                        }
                                    }
                                }
                            } else{
                                cout << "Peliculas con calificacion entre " << calificacion << " y " << calificacion+0.9 << endl;
                                for (int i = 0; i < dataSize; i++) {
                                    if(typeid(*arrayVideos[i]) == typeid(Pelicula)){
                                        if (arrayVideos[i]->get_nombre() != "NA" &&
                                            (arrayGrades[i] > calificacion)
                                            && arrayGrades[i] < calificacion+0.99){
                                            cout << "Pelicula " << i << ":" << endl;
                                            arrayVideos[i]->print();
                                            cout << "Calificacion: " << arrayGrades[i] << endl;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                        case 2: {
                            cout << "Insertar genero: " << endl;
                            string genero;
                            cin >> genero;
                            cout << "Pelicula con genero: " << genero << endl;
                            for (int i = 0; i < dataSize; i++) {
                                if(typeid(*arrayVideos[i]) == typeid(Pelicula)){
                                    if (arrayVideos[i]->get_nombre() != "NA" &&
                                        arrayVideos[i]->get_genero() == genero) {
                                        cout << "Pelicula: " << i << endl;
                                        arrayVideos[i]->print();
                                    }
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
                int opcionSeries;
                bool menuSeries = true;
                while(menuSeries) {
                    cout << "1. Buscar por calificacion\n"
                                "2. Buscar por genero\n"
                                "3. Regresar\n";

                    cin >> opcionSeries;

                    switch(opcionSeries) {
                        case 1: {
                            cout << "Insertar calificacion: " << endl;
                            float calificacion;
                            cin >> calificacion;
                            if (calificacion < 0 || calificacion > 5) {
                                cout << "Calificacion invalida" << endl;
                                break;
                            }
                            calificacion = floor(calificacion);
                            if(calificacion == 5.0){
                                cout << "Series con calificacion 5:" << endl;
                                for (int i = 0; i < dataSize; i++) {
                                    if(typeid(*arrayVideos[i]) == typeid(Serie)){
                                        if (arrayVideos[i]->get_nombre() != "NA" && (arrayGrades[i] == 5.0)){
                                            cout << "Serie " << i << ":" << endl;
                                            arrayVideos[i]->print();
                                            cout << "Calificacion: " << arrayGrades[i] << endl;
                                        }
                                    }
                                }
                            } else{
                                cout << "Series con calificacion entre " << calificacion << " y " << calificacion+0.9 << endl;
                                for (int i = 0; i < dataSize; i++) {
                                    if(typeid(*arrayVideos[i]) == typeid(Serie)){
                                        if (arrayVideos[i]->get_nombre() != "NA" &&
                                            (arrayGrades[i] > calificacion)
                                            && arrayGrades[i] < calificacion+0.99) {
                                            cout << "Serie " << i << ":" << endl;
                                            arrayVideos[i]->print();
                                            cout << "Calificacion: " << arrayGrades[i] << endl;
                                        }
                                    }
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
                                if(typeid(*arrayVideos[i]) == typeid(Serie)){
                                    if (arrayVideos[i]->get_nombre() != "NA" &&
                                        arrayVideos[i]->get_genero() == genero) {
                                        cout << "Serie: " << i << endl;
                                        arrayVideos[i]->print();
                                    }
                                }
                            }
                            break;
                        }
                        case 3: {
                            menuSeries = false;
                            break;
                        }
                    }
                }

                break;
            }
                case 4: {
                    if (!archivoCargado) {
                        cout << "Primero carga un archivo" << endl;
                        break;
                    }
                    int opcionCalificaciones;
                    bool menuCalificaciones = true;
                    while(menuCalificaciones) {
                        cout << "1. Calificar por titulo\n"
                                "2. Regresar\n";

                        cin >> opcionCalificaciones;

                        switch(opcionCalificaciones) {
                            case 1:{
                                cout << "Insertar el titulo de la serie o pelicula: " << endl;
                                string titulo;
                                int errors = 0;
                                cin.ignore();
                                getline(std::cin, titulo);
                                for (int i = 0; i < dataSize; i++) {
                                    if (arrayVideos[i]->get_nombre() == titulo) {
                                        cout << "Insertar la calificacion: " << endl;
                                        float calificacion;
                                        cin >> calificacion;
                                        arrayGrades[i] = calificacion;
                                        appendValueToLineInCSV(archivoCalif, i, to_string(calificacion));
                                        if (!loadVideoGradesfromCSV(archivoCalif, arrayGrades, dataSize)) {
                                            cerr << "Error al cargar el data set de " << archivoCalif << "\n";
                                            delete[] arrayGrades;
                                            return 0;
                                        }
                                    } else {
                                        errors++;
                                    }
                                    if (errors == dataSize) {
                                        cout << "No se encontro el titulo" << endl;
                                    }
                                }
                                break;

                            }
                            case 2:{
                                menuCalificaciones = false;
                                break;
                            }
                        }
                        }
                    break;
                }
                case 5: {
                    menu = false;
                    break;
                }
                case 6:{
                    for (int i = 0; i < dataSize; i++) {
                        arrayVideos[i]->print();
                        cout << "Calificacion: " << arrayGrades[i] << endl;
                    }
                    break;
                }
            }
        }
    delete [] arrayVideos;
    delete [] arrayGrades;
    return 0;
}
