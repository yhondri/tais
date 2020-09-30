//
//  main.cpp
//  PracticaLunes
//
//  Created by Yhondri on 30/09/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include "bintree.h"

using namespace std;


/**
 Un árbol es AVL si:
 - Cumple que es un árbol binario de búsqueda y está equilibrado, es decir, si cumple que:
 - La diferencia de altura de sus hijos es >= 0 y <= 1.
 - La clave almacenada en la raíz de cualquier subárbol es estrictamente mayor que todas las claves en su hijo izquierdo y estrictamente menor que todas las claves en su hijo derecho.
 */
int esAVL(bintree<int> arbol, int minValue, int maxValue);

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos1.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        bintree<int> arbol = leerArbol(-1);
        
        if (esAVL(arbol, INT_MIN, INT_MAX) >= 0) {
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

/**
 De forma recursiva comprobamos si el árbol es AVL.
 Primero comprobamos si el árbol es vacío, en caso de serlo es AVL.
 - Si el árbol no es vacío, comprobamos que la clave es mayor que el valor mínimo y que la clave es menor que el valor máximo, de esta forma nos aseguramos que la raíz del subárbol, es mayor que todos los valores del árbol izquierdo y menor que todos los valores del árbol derecho.
 A continuación obtenemos las alturas de los hijos izquierdo y derecho.
 
 Por último comprobamos si está balanceado, es decir, si la diferencia de altura entre sus dos hijos es como máximo 1. 
 */
int esAVL(bintree<int> arbol, int minValue, int maxValue) {
    if (arbol.empty()) {
        return 0;
    }
    
    if (arbol.root() <= minValue || arbol.root() >= maxValue) {
        return -1;
    }
    
    int leftTreeHeight = esAVL(arbol.left(), minValue, arbol.root());
    if (leftTreeHeight == -1) {
        return -1;
    }
    
    int rightTreeHeight = esAVL(arbol.right(), arbol.root(), maxValue);
    if (rightTreeHeight == -1) {
        return -1;
    }
    
    int isBalanced = (leftTreeHeight - rightTreeHeight);
    if (abs(isBalanced) <= 1) {
        return 1 + max(leftTreeHeight, rightTreeHeight);
    }
    
    return -1;
}
