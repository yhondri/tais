//
//  main_33.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 1/12/20.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void resuelveCaso() {
    int n, v;
    cin >> n >> v;
    
    vector<int> pilas;
    int voltajePila;
    for (int i = 0; i < n; i++) {
        cin >> voltajePila;
        pilas.push_back(voltajePila);
    }
    
    sort(pilas.begin(), pilas.end(), greater<int>());
    
    int indexLeft = 0, indexRight = (int)pilas.size()-1, contadorCoches = 0;
    while (indexLeft < indexRight) {
        if (pilas[indexLeft] + pilas[indexRight] >= v) {
            contadorCoches++;
            indexLeft++;
            indexRight--;
        } else {
            indexRight--;
        }
    }
    
    cout << contadorCoches << '\n';
    
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p33.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        resuelveCaso();
        numCasos--;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
