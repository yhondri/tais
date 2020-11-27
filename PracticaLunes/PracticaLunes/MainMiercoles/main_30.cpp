//
//  main_30.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 27/11/20.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

PriorityQueue<int, less<int>> getDatos(int numDatos) {
    PriorityQueue<int, less<int>> queue;
    int value;
    for (int i = 0; i < numDatos; i++) {
        cin >> value;
        queue.push(value);
    }
    return queue;
}

bool resuelveCaso() {
    int numParejas;
    cin >> numParejas;
    
    if (numParejas == 0) {
        return false;
    }
    
    PriorityQueue<int, less<int>> esquiadores = getDatos(numParejas);
    PriorityQueue<int, less<int>> esquies = getDatos(numParejas);
    int sumDiferencias = 0;
    
    while (!esquiadores.empty()) {
        sumDiferencias += abs(esquiadores.top() - esquies.top());
        esquiadores.pop();
        esquies.pop();
    }
    
    cout << sumDiferencias << '\n';

    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p30.txt");
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

