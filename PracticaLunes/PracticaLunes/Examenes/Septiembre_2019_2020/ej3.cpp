//
//  ej3.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 3/2/21.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

const int INF = 1000000000;

struct Poblado {
    vector<int> costeAlquiler;
};

void calcularCostesMinimos(Matriz<int> &costesMinimos, vector<Poblado> const& poblados, int const& numPoblados) {
    int n = (int)poblados.size();
    costesMinimos[n-1][n-1] = poblados[n-1].costeAlquiler[0];
    for (int i = n-2; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (j == i) {
                costesMinimos[i][j] = poblados[i].costeAlquiler[0];
            } else {
                int coste_A_B = poblados[i].costeAlquiler[j-2]; // Coste de A a B
                int coste_B_C = costesMinimos[i+1][j]; //Coste de B a C
                int costeDirecto = poblados[i].costeAlquiler[j-i];
                costesMinimos[i][j] = min(costeDirecto, (coste_A_B + coste_B_C));
            }
        }
    }
}

bool resuelveCaso() {
   // leer los datos de la entrada
    int numPoblados;
    cin >> numPoblados;
    
   if (!std::cin)  // fin rde la entrada
      return false;
    
    vector<Poblado> poblados;
    int value;
    for (int i = 0; i < numPoblados-1; i++) {
        vector<int> costeAlquiler;
        for (int j = 0; j < numPoblados-(i+1); j++) {
            cin >> value;
            costeAlquiler.push_back(value);
        }
        poblados.push_back({costeAlquiler});
    }
    
    Matriz<int> costesMinimos(numPoblados-1, numPoblados-1, INF);
    calcularCostesMinimos(costesMinimos, poblados, numPoblados);
    
    for (int i = 0; i < numPoblados-1; i++) {
        for (int j = 0; j < numPoblados-1; j++) {
            if (costesMinimos[i][j] == INF) {
                continue;
            }
            cout << costesMinimos[i][j] << " ";
        }
        cout << '\n';
    }
   
   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/ej3.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
