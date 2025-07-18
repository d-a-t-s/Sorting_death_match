//Compilar con: g++ -o insertion_sort insertion_sort.cpp lector.cpp

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>

#include "lector.h"

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

    for(int i = 1; i < n; i++){ //El iterador comienza en 1 porque el primer elemento "ya está ordenado"
        int act = valores[i]; //Guardamos el valor a insertar
        int in = i;
        int fin = i - 1;
        while(fin >= 0 && act < valores[fin]){ //Mientras el elemento a insertar sea menor que el elemento en la posicion fin
            valores[in] = valores[fin]; //Desplazamos el elemento hacia la derecha
            in--;
            fin--;
        }
        valores[in] = act; //Insercion del elemento en la posision correcta
    }

    //Tomamos el tiempo de fin
    auto end = chrono::high_resolution_clock::now();

    //Calculamos el tiempo transcurrido
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    running_time *= 1e-9; //Conversion a segundos

    //Imprimimos el resultado
    cout << argv[0] << ";" << n << ";" << running_time << endl;

    return 0;
}