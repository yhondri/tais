//
//  main_28.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 21/11/20.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

PriorityQueue<int, less<int>> getEfectivosData(int n) {
    PriorityQueue<int, less<int>>efectivosQueue;
    int value;
    for (int i = 0; i < n; i++) {
        cin >> value;
        efectivosQueue.push(value);
    }
    return efectivosQueue;
}

bool resuelveCaso() {
    int numCiudades;
    cin >> numCiudades;
    
    if (!cin) {
        return false;
    }
    
    PriorityQueue<int, less<int>>efectivosEnemigosQueue = getEfectivosData(numCiudades);
    PriorityQueue<int, less<int>>efectivosDefensaQueue = getEfectivosData(numCiudades);
    int ciudadesDefendidas = 0;
    
    for (int i = 0; i < numCiudades && !efectivosEnemigosQueue.empty() && !efectivosDefensaQueue.empty(); i++) {
        int efectivosEnemigos = efectivosEnemigosQueue.top();
        efectivosEnemigosQueue.pop();
        
        bool puedeDefenderse = false;
        while (!puedeDefenderse && !efectivosDefensaQueue.empty()) {
            int efectivosDefensa = efectivosDefensaQueue.top();
            efectivosDefensaQueue.pop();
            
            if (efectivosDefensa >= efectivosEnemigos) {
                puedeDefenderse = true;
                ciudadesDefendidas++;
            }
        }
    }
    
    cout << ciudadesDefendidas << '\n';
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p28.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
//     para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

