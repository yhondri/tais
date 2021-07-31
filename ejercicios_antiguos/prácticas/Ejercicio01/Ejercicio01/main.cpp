//
//  main.cpp
//  Ejercicio01
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


bool esEquilibrado(bintree<char> arbol);
int calcularAltura(bintree<char> arbol);

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
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio01/Ejercicio01/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        bintree<char> arbol = leerArbol('.');
        
        if (esEquilibrado(arbol)) {
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

bool esEquilibrado(bintree<char> arbol) {
    
    if (arbol.empty()) {
        return true;
    }
    
    int alturaHijoIzquierdo = calcularAltura(arbol.left());
    int alturaHijoDerecho = calcularAltura(arbol.right());

    int factorEquilibrio = (alturaHijoDerecho - alturaHijoIzquierdo);
    
    if (abs(factorEquilibrio) <= 1 && esEquilibrado(arbol.left()) && esEquilibrado(arbol.right())){
        return true;
    }
    
    return false;
}

int calcularAltura(bintree<char> arbol) {
    if (arbol.empty()) {
        return 0;
    }
<<<<<<< HEAD
    return 1 + max(calcularAltura(arbol.left()), calcularAltura(arbol.right()));
=======
    int acumulador = 1 + max(calcularAltura(arbol.left()), calcularAltura(arbol.right()));
    return acumulador;
>>>>>>> 0d894030d21b674de21a32f8b3ccf402f3c303bb
}
