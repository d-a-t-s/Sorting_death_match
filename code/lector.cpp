#include "lector.h"

#include <iostream>
#include <fstream>

using namespace std;

vector<int32_t> leer_archivo(const string& filename){

    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "Error abriendo el archivo: " << filename << endl;
        exit(1);
    }

    // Leer el tamaño del archivo
    file.seekg(0, ios::end);
    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Calcular el número de enteros en el archivo
    size_t numIntegers = fileSize / sizeof(int32_t);

    // Crear un vector para almacenar los enteros
    vector<int32_t> integers(numIntegers);

    // Leer los enteros del archivo
    if (!file.read(reinterpret_cast<char*>(integers.data()), fileSize)) {
        cerr << "Error leyendo el archivo: " << filename << endl;
        exit(1);
    }

    return integers;
}