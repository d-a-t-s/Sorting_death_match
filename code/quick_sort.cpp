//Compilar con : g++ quick_sort.cpp lector.cpp -o quick_sort

#include "lector.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int partition(vector<int32_t>& arr, int left, int right){
    int ind = left + rand() % (right - left + 1); // Elegimos un pivote aleatorio
    int pivot = arr[ind]; // Guardamos el pivote

    int i = left;
    int j = right;
    while(i <= j){
        while(arr[i] < pivot){
            i++;
        }
        while(arr[j] > pivot){
            j--;
        }
        if(i <= j){
            swap(arr[i], arr[j]); // Intercambiamos los elementos
            i++;
            j--;
        }
    }
    return j; // Devolvemos el índice de la partición
}

void quick_sort(vector<int32_t>& arr, int left, int right){
    if(left < right){
        int ind = partition(arr, left, right); // Obtenemos el índice del pivote
        quick_sort(arr, left, ind); // Ordenamos la parte izquierda
        quick_sort(arr, ind + 1, right); // Ordenamos la parte derecha
    }
}


int main(int argc, char** argv){

    //Inicializamos la semilla para números aleatorios
    srand(time(0));
    
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
    quick_sort(valores, 0, n-1);

    //Tomamos el tiempo de fin
    auto end = chrono::high_resolution_clock::now();

    //Calculamos el tiempo transcurrido
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    running_time *= 1e-9; //Conversion a segundos

    //Imprimimos el resultado
    cout << argv[0] << ";" << n << ";" << running_time << endl;

    return 0;
}