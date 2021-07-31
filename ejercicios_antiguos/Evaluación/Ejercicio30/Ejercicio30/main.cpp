//
//  main.cpp
//  Ejercicio30
//
//  Created by Yhondri  on 7/1/18.
//  Copyright © 2018 Yhondri . All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
Tiene complejidad cuadrática N^2 ya que necesitamos recorrer una matriz de 2 dimensiones.
Tiene complejidad cuadrática N^2 en cuanto a espacio, debido a que necesitamos una matriz de 2 dimensiones.
 
 */

#include <iostream>
#include <fstream>
#include "Matriz.h"

using namespace std;

void findMinInsertions(string str, size_t n);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio25/Ejercicio25/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio30/Ejercicio30/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    string word;
    bool seguir = true;
    while (seguir) {
        getline(cin, word);
        if (cin) {
            findMinInsertions(word, word.size());
        } else {
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

void findMinInsertions(string str, size_t n) {
    Matriz<int> mochila(n, n, 0);
    
    for (int gap = 1; gap < n; ++gap) {
        for (int l = 0, h = gap; h < n; ++l, ++h) {
            if (str[l] == str[h]) { //vamos comparando en subproblemas pares. Si 2 letras contiguas son iguales, ya son palíndromos
                mochila[l][h] = mochila[l+1][h-1];
            } else {
                mochila[l][h] = min(mochila[l][h-1], mochila[l+1][h]) + 1; //Caso contrarío, tenemos que encontrar el mínimo para crear un palíndromo.
            }
        }
    }
    
    cout << mochila[0][n-1] << endl;
}
