#include "lector.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

void merge(vector<int32_t>& arr, int left, int mid, int right){

    // Tamaño de los subarreglos
    int n2 = right - mid;
    int n1 = mid - left + 1;

    //Declaracion de los subarreglos
    vector<int32_t> L(n1);
    vector<int32_t> R(n2);

    // Copiamos los datos a los subarreglos
    for(int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    // Merge de los subarreglos
    int i = 0, j = 0, k = left; 
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copiamos los elementos restantes de L[]
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copiamos los elementos restantes de R[]
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int32_t>& arr, int left, int right){
    if(left < right){
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
    merge_sort(valores, 0, n-1);

    //Tomamos el tiempo de fin
    auto end = chrono::high_resolution_clock::now();

    //Imprimimos el arreglo ordenado
    for(int i = 0; i < n; i++){
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