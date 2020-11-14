//
//  main_prim.cpp
//  PracticaLunes
//
//  Created by Yhondri on 11/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <deque>
#include "GrafoValorado.h"

using namespace std;

class Prim {
private:
    GrafoValorado<int> grafo;
    const int MAX_VALUE = numeric_limits<int>::max();
    int vertices;
    
public:
    
    Prim(GrafoValorado<int> const& mGrafo) : grafo(mGrafo) {
        
        
        
    }
    
    int minKey(vector<int> key, vector<bool> visitado) {
        int min = MAX_VALUE, min_index = 0;
        for (int i = 0; i < grafo.V(); i++) {
            if (!visitado[i] && key[i] < min) {
                min = key[i];
                min_index = i;
            }
        }
        
        return min_index;
    }
    
    void encontrarCaminoMinimo() {
        //Almacena el camíno mínimo
        vector<int> parent(grafo.V());
        //Clave para almacenar
        vector<int> key(grafo.V(), MAX_VALUE);
        //Representa los vértices visitados en MST.
        vector<bool> visitado(grafo.V(), false);
        
        key[0] = 0; //Hace el vértice 0 para elegirlo el primero.
        parent[0] = -1; //El primer nodo es siempre la raíz del árbol.
        
        for (int i = 0; i < grafo.V() - 1; i++) {
            //Coge la clave mínima del vértice aún no visitados.
            int u = minKey(key, visitado);
            visitado[u] = true;
            
            for (int j = 0; j < grafo.V(); j++) {
                if (grafo.hayArista(u, j) && !visitado[j] && grafo.getValorDeArista(u, j) < key[j]) {
                    parent[j] = u;
                    key[j] = grafo.getValorDeArista(u, j);
                }
            }
        }
        
        for (int i = 1; i < grafo.V(); i++) {
            cout << parent[i] << " - " << i << "\t" << grafo.getValorDeArista(i, parent[i]) << "\n";
        }
    }
};

bool resuelveCaso() {
    int vertices, aristas;
    cin >> vertices >> aristas;

    if (!cin) {
        return false;
    }
    
    GrafoValorado<int> grafo(vertices);
    int vertice1, vertice2, valor;
    for (int i = 0; i < aristas; i++) {
        cin >> vertice1 >> vertice2 >> valor;
        grafo.ponArista({vertice1, vertice2, valor});
    }
    
    Prim consultorDeCaminos(grafo);
    consultorDeCaminos.encontrarCaminoMinimo();
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/caso_prim.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

