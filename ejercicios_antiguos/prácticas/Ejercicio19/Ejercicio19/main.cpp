//
//  main.cpp
//  Ejercicio19
//
//  Created by Yhondri on 29/11/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 El coste es Lineal O(n) donde n corresponde al número de libros a comprar. 
 Esto es debido a que recorremos, en el caso peor,
 todos los libros del caso de uso, que guardamos en un vector.
 
 Antes además utilizamos para la resolución del problema la función sort, la cual tiene un coste
 O(n Log(n)).
 
 El coste total por tanto es: O(n) + O(n Log(n)).
 */

//******NOTA*********
//HAY QUE AÑADIR EN EL COSTE QUE TAMBIÉN SE LLAMA A LA FUNCIÓN ORDENAR

#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

void calcularDescuentoMaximo(vector<size_t> libros, int numLibros);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/prácticas/Ejercicio19/Ejercicio19/casos.txt"); //MacBook Pro
    //ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio19/Ejercicio19/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numLibros;
    bool seguir = true;
    while (seguir) {
        cin >> numLibros;
        if (cin) {
            vector<size_t> libros;
            for (int i = 0; i < numLibros; i++) {
                size_t precioLibro;
                cin >> precioLibro;
                libros.push_back(precioLibro);
            }
            
            sort(libros.begin(), libros.end());
            calcularDescuentoMaximo(libros, numLibros);
            //printAgujeros(agujeros);
        }
        else {
            seguir = false;
        }
        
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void calcularDescuentoMaximo(vector<size_t> libros, int numLibros) {
    size_t descuento = 0;
    while (numLibros >= 3) {
        libros.pop_back();
        libros.pop_back();
        descuento += libros.back();
        libros.pop_back();
        numLibros = numLibros - 3;
    }
    cout << descuento << endl;
}


