//
//  main.cpp
//  Ejercicio22
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
 
 El coste es Lineal O(n) donde n corresponde al número de partidos a jugar.
 Esto es debido a que recorremos todos los partidos que guardamos en las colas.
 
 */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

void fillQueue(PriorityQueue<int> &cola, int numDatosEsperados);
void fillQueue(PriorityQueue<int, greater<int>> &cola, int numDatosEsperados);
void calcularExitoMaximo(PriorityQueue<int>puntosRivales, PriorityQueue<int, greater<int>>puntosBroncos);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/prácticas/Ejercicio22/Ejercicio22/casos.txt"); //MacBook Pro
    //ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio22/Ejercicio22/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numPartidos;
    while ((cin >> numPartidos) && numPartidos > 0) {

        PriorityQueue<int>puntosRivales;
        PriorityQueue<int, greater<int>>puntosBroncos;
        fillQueue(puntosRivales, numPartidos);
        fillQueue(puntosBroncos, numPartidos);
        calcularExitoMaximo(puntosRivales, puntosBroncos);
        
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void fillQueue(PriorityQueue<int> &cola, int numDatosEsperados) {
    while (numDatosEsperados > 0) {
        int dato;
        cin >> dato;
        cola.push(dato);
        numDatosEsperados--;
    }
}
void fillQueue(PriorityQueue<int, greater<int>> &cola, int numDatosEsperados) {
    while (numDatosEsperados > 0) {
        int dato;
        cin >> dato;
        cola.push(dato);
        numDatosEsperados--;
    }
}

void calcularExitoMaximo(PriorityQueue<int>puntosRivales, PriorityQueue<int, greater<int>>puntosBroncos) {
    int maxPuntos = 0;
    
    while (!puntosRivales.empty()) {
        int puntosConseguidosPorRivales = puntosRivales.top();
        int puntosconseguidosPorBroncos = puntosBroncos.top();
        puntosRivales.pop();
        puntosBroncos.pop();
        
        if (puntosconseguidosPorBroncos > puntosConseguidosPorRivales) {
            maxPuntos += (puntosconseguidosPorBroncos - puntosConseguidosPorRivales);
        }
    }
    
    cout << maxPuntos << endl;
}
