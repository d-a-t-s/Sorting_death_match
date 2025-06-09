#include "lector.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

/* 
 *  Algoritmo que compara byte a byte desde el menos significativo
 *  al mas significativo utilizando Counting Sort
 */
void radix_sort(vector<int32_t>& arr){

    int base = 256; //base que representa los valores que puede tomar un byte (0-255)
    vector<int32_t> buffer(arr.size()); //buffer auxiliar
    vector<int32_t>* in = &arr;         //puntero al arreglo de entrada
    vector<int32_t>* out = &buffer;     //puntero al arreglo que contiene el arreglo parcial
    
    //recorremos los 4 bytes de cada entero, de menor a mayor significancia
    for (int shift = 0; shift < 32; shift+=8){

        vector<int> count(base, 0); // Arreglo que cuenta la frecuencia de cada valor de byte
        
        //Contador de los bytes actuales presentes en el arreglo
        for (int32_t num : *in){
            int byte = (num >> shift) & 255; //Extraer byte actual
            
            //Operacion que permite cambiar el rango de (0-255) a (-128,127) en el byte que contiene el signo
            if (shift == 24) byte ^= 128;   
            
            //
            count[byte]++;
        }
        
        // Se construyen las posiciones acumuladas para definir el orden final
        for (int i = 1; i < base; i++){
            count[i] += count[i - 1]; 
        }

        /*
        *  Se construye el arreglo ordenado para el byte, de derecha a izquierda para mantener
        *  el orden relativo en caso de que se repitan valores
        */
        for (int i = arr.size() - 1; i >= 0; --i) {
            int byte = ((*in)[i] >> shift) & 255;
            if (shift == 24) byte ^= 128; // Se corrige el byte de signo
            count[byte]--;
            (*out)[count[byte]] = (*in)[i];// Coloca el numero en la posicion ordenada
        }
        //se intercambian punteros para evitar copiar vectores enteros
        swap(in, out);
    }
    //en caso que el resultado final quede en el buffer auxiliar, se copia en el original
    if (in != &arr) {
        arr = *in;
    }
}  


int main(int argc, char** argv) {

        // Si no hay suficientes argumentos, terminamos la ejecución
        if(argc < 2){
            cerr << "Usage: " << argv[0] << " <archivo.bin>" << endl;
            exit(1);
        }
        
        // Nombre del archivo
        const string filename = argv[1];
    
        // Leemos el archivo
        vector<int32_t> valores = leer_archivo(filename);
        
        int n = valores.size();

        //Tomamos el tiempo de inicio
        auto start = chrono::high_resolution_clock::now();

        //Comenzamos la ejecucion del algoritmo
        radix_sort(valores);

        //Tomamos el tiempo de fin
        auto end = chrono::high_resolution_clock::now();

        //Calculamos el tiempo transcurrido
        double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        running_time *= 1e-9; //Conversion a segundos

        cout << argv[0] << ";" << n << ";" << running_time << endl;
    
    return 0;
}