//Compilar con: g++ -o heap_sort heap_sort.cpp lector.cpp

#include "lector.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

void heapify(vector<int32_t>& arr, int n, int i){

    int mayor = i; //Asumimos que la raiz es el mayor
    int left = 2 * i + 1; // Hijo izquierdo
    int right = 2 * i + 2; //Hijo derecho

    // Si el hijo izquierdo es mayor que la raiz
    if(left < n && arr[left] > arr[mayor]){
        mayor = left; // Actualizamos el mayor
    }
    // Si el hijo derecho es mayor que el mayor actual
    if(right < n && arr[right] > arr[mayor]){
        mayor = right; // Actualizamos el mayor
    }
    // Si el mayor no es la raiz
    if(mayor != i){
        swap(arr[i], arr[mayor]); // Intercambiamos la raiz con el mayor
        heapify(arr, n, mayor); // Llamamos recursivamente a heapify
    }
}

void heap_sort(vector<int32_t>& arr, int n){
    // Construimos el heap
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    // Extraemos los elementos del heap
    for(int i = n - 1; i >= 0; i--){
        swap(arr[0], arr[i]); // Intercambiamos la raiz con el último elemento
        heapify(arr, i, 0); // Llamamos a heapify en el nuevo subárbol
    }
}

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

    // Llenamos el arreglo a ordenar con valores aleatorios 
    /*int *valores = new int[n];
    srand(time(0));
    for(int i=0; i < n; i++){
        valores[i] = rand() % 1000;
    }*/

    //Tomamos el tiempo de inicio
    auto start = chrono::high_resolution_clock::now();

    //Comenzamos la ejecucion del algoritmo
    heap_sort(valores, n);

    //Tomamos el tiempo de fin
    auto end = chrono::high_resolution_clock::now();

    //Imprimimos el arreglo ordenado
    for(int i = 0; i < 100000; i++){
        cout << valores[i] << " ";
    }
    cout << endl;

    //Calculamos el tiempo transcurrido
    double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    running_time *= 1e-9; //Conversion a segundos

    //Imprimimos el resultado
    cout << argv[0] << ";" << n << ";" << running_time << endl;

    return 0;
}