//
//  main.cpp
//  Ejercicio02
//
//  Created by Yhondri  on 3/10/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
#include <limits.h>

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 DNI: 51554391-Y
 
 <--------------------------------->
 Coste;

 Coste lineal en el caso peor que tengamos que recorrer todo el árbol.
 
 */

using namespace std;

int esAVL(bintree<int> arbol, int minValue, int maxValue);
    
// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un árbol vacío
        return {};
    } else { // leer recursivamente los hijos
        auto iz = leerArbol(vacio);
        auto dr = leerArbol(vacio);
        return {iz, raiz, dr};
    }
}

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio02/Ejercicio02/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        bintree<int> arbol = leerArbol(-1);
        
        if (esAVL(arbol, -1, INT_MAX) >= 0) {
            cout << "SI" << endl;
        } else {
            cout << "NO" << endl;
        }
        numCasos--;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

int esAVL(bintree<int> arbol, int minValue, int maxValue) {

    if (arbol.empty()) {
        return 0;
    }

    if (arbol.root() <= minValue || arbol.root() >= maxValue) {
        return -1;
    }
    
    int alturaIzquierda = esAVL(arbol.left(), minValue, arbol.root());
    
    if (alturaIzquierda == -1) {
        return  -1;
    }
    
    int alturaDerecha = esAVL(arbol.right(), arbol.root(), maxValue);
    
    if (alturaDerecha == -1) {
        return  -1;
    }
    
    int factorEquilibrio = (alturaDerecha - alturaIzquierda);
    if (abs(factorEquilibrio) <= 1) {
      return 1 + max(alturaIzquierda, alturaDerecha);
    }
    
    return -1;
}

