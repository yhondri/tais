//
//  main_p18.cpp
//  PracticaLunes
//
//  Created by Yhondri on 05/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include "Digrafo.h"

using namespace std;

struct Sumidero {
private:
    int gradoDeEntrada;
    int numAdyacentes;
    int verticesDeGrafo;
    int vertice;
public:
    Sumidero(int numVertices): verticesDeGrafo(numVertices), gradoDeEntrada(0) {}
    
    bool esPosibleSumidero() {
        return numAdyacentes == 0 && gradoDeEntrada == verticesDeGrafo-1;
    }
    
    void setAdyacentes(int adyacentes) {
        numAdyacentes = adyacentes;
    }
    
    void annadirEntrada() {
        gradoDeEntrada++;
    }
    
    int getSumidero() {
        return vertice;
    }
};

class BuscadorDeSumidero {
private:
    Digrafo digrafo;
    
public:
    BuscadorDeSumidero(Digrafo const& grafo): digrafo(grafo) {}
    
    void buscarSumidero() {
        int posibleSumidero = 0;
        bool encontrado = false;
        bool posibleSumideroEncontrado = false;
        
        for (int v = 0; v < digrafo.V() && !posibleSumideroEncontrado; ++v) {
            if ((int)digrafo.ady(v).size() == 0) {
                posibleSumidero = v;
                posibleSumideroEncontrado = true;
            }
        }
        
        int verticesDeEntrada = 0;
        for (int v = 0; v < digrafo.V() && !encontrado && posibleSumideroEncontrado; ++v) {
            if (digrafo.hayArista(v, posibleSumidero)) {
                verticesDeEntrada++;
                
                if (verticesDeEntrada == digrafo.V()-1) {
                    encontrado = true;
                }
            }
        }
        
        if (encontrado) {
            cout << "SI " << posibleSumidero;
        } else {
            cout << "NO";
        }
    }
};

bool resuelveCaso() {
    Digrafo tareas(cin, 0);

    if (!std::cin) {
        return false;
    }
    
    BuscadorDeSumidero buscadorDeSumidero(tareas);
    buscadorDeSumidero.buscarSumidero();
    
    cout << '\n';
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p18.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
#endif
    return 0;
}
