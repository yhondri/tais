//
//  main_27.cpp
//  PracticaLunes
//
//  Created by Yhondri on 20/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int numAguejeros, logintudParches;
    cin >> numAguejeros >> logintudParches;

    if (!cin) {
        return false;
    }

    int posicionAgujero, ultimaPosicionParcheada = -1, numParches = 0;
    for (int i = 0; i < numAguejeros; i++) {
        cin >> posicionAgujero;
        
        if (posicionAgujero > ultimaPosicionParcheada) {
            numParches += 1;
            ultimaPosicionParcheada = posicionAgujero + logintudParches;
        }
    }
    
    cout << numParches << '\n';
 
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p27.txt");
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

