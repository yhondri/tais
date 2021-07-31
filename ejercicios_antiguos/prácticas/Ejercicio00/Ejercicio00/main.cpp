//
//  main.cpp
//  Ejercicio00
//
//  Created by Yhondri  on 1/10/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 DNI: 51554391-Y
 
 */

#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

template <typename T>
int alturaArbol(bintree<T> arbol);

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
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio00/Ejercicio00/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        bintree<char> arbol = leerArbol('.');
        int altura = alturaArbol(arbol);
        
        cout << altura << endl;
        
        numCasos--;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
//    system("PAUSE");
#endif
    
    return 0;
}

template <typename T>
int alturaArbol(bintree<T> arbol) {
    if (arbol.empty()) {
        return 0;
    }
    int acumulador = 1 + max(alturaArbol(arbol.left()), alturaArbol(arbol.right()));
    return acumulador;
}
