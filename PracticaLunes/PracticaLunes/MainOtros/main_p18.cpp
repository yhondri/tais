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
#include <deque>
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
    std::vector<Sumidero> posiblesSumideros; // anterior[v] = vértice anterior en el camino a v
    
    void dfs(Digrafo const& digrafo) {
        for (int v = 0; v < digrafo.V(); ++v) {
//            cout << "Value: " << v << " Adyacentes " << (int)digrafo.ady(v).size() << endl;
            posiblesSumideros[v].setAdyacentes((int)digrafo.ady(v).size());
            for(auto w : digrafo.ady(v)) {
                posiblesSumideros[w].annadirEntrada();
            }
        }
    }
    
    
public:
    BuscadorDeSumidero(Digrafo const& digrafo): posiblesSumideros(digrafo.V(), digrafo.V()) {
        dfs(digrafo);
    }
    
    int getSumidero() {
        for (int v = 0; v < posiblesSumideros.size(); ++v) {
            if (posiblesSumideros[v].esPosibleSumidero()) {
                return v;
            }
        }
        
        return -1;
    }
};

bool resuelveCaso() {
    Digrafo tareas(cin, 0);

    if (!std::cin) {
        return false;
    }
    
    BuscadorDeSumidero ordenadorDeTareas(tareas);
    
    int sumidero = ordenadorDeTareas.getSumidero();
    if (sumidero != -1) {
        cout << "SI " << sumidero;
    } else {
        cout << "NO";
    }
    
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
