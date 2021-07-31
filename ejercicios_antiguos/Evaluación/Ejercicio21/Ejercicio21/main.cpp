//
//  main.cpp
//  Ejercicio21
//
//  Created by Yhondri on 22/11/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 Coste linear dependiendo del número de viajeros.
 
 */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

void calcularNumViajes(PriorityQueue<int, greater<int>> &usuarios, int pesoMaximo);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio21/Ejercicio21/casos.txt"); //MacBook Pro
//    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio21/Ejercicio21/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int pesoMaximo = 0, numUsuarios = 0, usuario = 0;
    bool seguir = true;
    while (seguir) {
        cin >> pesoMaximo >> numUsuarios;
        if (cin) {
            PriorityQueue<int, greater<int>>usuarios(numUsuarios);
            for (int i = 0; i < numUsuarios; i++) {
                cin >> usuario;
                usuarios.push(usuario);
            }
            
            calcularNumViajes(usuarios, pesoMaximo);
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

void calcularNumViajes(PriorityQueue<int, greater<int>> &usuarios, int pesoMaximo) {
    int pesoViajero = 0, cargaActual = 0, numAsientosCoupados = 0;
    int numViajes = 1;
    
    while (!usuarios.empty()) {
        pesoViajero = usuarios.top();
        if (((cargaActual+pesoViajero) <= pesoMaximo) && (numAsientosCoupados < 2)) {
            cargaActual += pesoViajero;
            usuarios.pop();
            numAsientosCoupados++;
        }
        else {
            numViajes++;
            cargaActual = 0;
            numAsientosCoupados = 0;
        }
    }
    cout << numViajes << endl;
}
