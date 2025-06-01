//Compilar con: g++ -o STL_sort STL_sort.cpp lector.cpp

#include "lector.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){

    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2){
        cerr << "Usage: " << argv[0] << " <archivo.bin>" << endl;
        exit(1);
    }

    // Nombre del archivo
    const string filename = argv[1];

    // Leemos el archivo
    vector<int32_t> valores = leer_archivo(filename);

    // Obtenemos el tamaño del vector
    int n = valores.size();

    //Tomamos el tiempo de inicio
    auto start = chrono::high_resolution_clock::now();

    //Comenzamos la ejecucion del algoritmo
    sort(valores.begin(), valores.end());

    //Tomamos el tiempo de fin
    auto end = chrono::high_resolution_clock::now();

    //Calculamos el tiempo transcurrido
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    running_time *= 1e-9; //Conversion a segundos

    //Imprimimos el resultado
    cout << argv[0] << ";" << n << ";" << running_time << endl;

    return 0;
}