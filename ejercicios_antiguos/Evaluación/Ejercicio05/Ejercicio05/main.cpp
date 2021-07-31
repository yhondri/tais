//
//  main.cpp
//  Ejercicio05
//
//  Created by Yhondri  on 12/10/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
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

void calcularNumeroGorras(PriorityQueue<long long> queue);

int main(int argc, const char * argv[]) {
    
#ifndef DOMJUDGE
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio05/Ejercicio05/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numElementos;
    while ((cin >> numElementos) && numElementos != 0) {
        PriorityQueue<long long> queue;
        for (int i = 0; i < numElementos; i++) {
            int nuevoElemento;
            cin >> nuevoElemento;
            queue.push(nuevoElemento);
        }
        calcularNumeroGorras(queue);
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
//    system("PAUSE");
#endif

    return 0;
}

void calcularNumeroGorras(PriorityQueue<long long> queue) {
    long long gorrasTorneo = 0;
    while (queue.size() > 1) {
        long long gorrasPartido = queue.top();
        queue.pop();
        gorrasPartido += queue.top();
        queue.pop();
        
        gorrasTorneo += gorrasPartido;
        queue.push(gorrasPartido);
    }
    
    cout << gorrasTorneo << endl;
}

