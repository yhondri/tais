//
//  main_p21.cpp
//  PracticaLunes
//
//  Created by Yhondri on 08/11/2020.
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

class ConsultorDeCaminos {
private:
    vector<int> visitado;
    GrafoValorado<int> grafo;
    vector<int> componente;
    
    void dfs(int verticeOrigen, int umbral, int numComponenteConexa) {
        visitado[verticeOrigen] = true;
        componente[verticeOrigen] = numComponenteConexa;
        
        for (auto a : grafo.ady(verticeOrigen)) {
            if (umbral <= a.valor()) {
                int w = a.otro(verticeOrigen);
                if (!visitado[w]) {
                    dfs(w, umbral, numComponenteConexa);
                }
            }
        }
    }
    
public:
    
    ConsultorDeCaminos(GrafoValorado<int> const& mGrafo) : visitado((int)mGrafo.V(), false), componente((int)mGrafo.V(), -1), grafo(mGrafo) {
        
    }
    
    bool puedeRecorrerseElCamino(int verticeOrigen, int verticeDestino, int anchuraDelCamion) {
        int numComponenteConexa = 0;
        for (int i = 0; i < grafo.V(); i++) {
            visitado[i] = false;
            componente[i] = -1;
        }
        
        for (auto v = 0; v < grafo.V(); ++v) {
            if (!visitado[v]) {
                dfs(v, anchuraDelCamion, numComponenteConexa);
                numComponenteConexa++;
            }
        }
        
        return componente[verticeOrigen] == componente[verticeDestino] && visitado[verticeDestino];
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
        vertice1--;
        vertice2--;
        grafo.ponArista({vertice1, vertice2, valor});
    }
    
    int consultas;
    cin >> consultas;
    ConsultorDeCaminos consultorDeCaminos(grafo);
    for (int i = 0; i < consultas; i++) {
        cin >> vertice1 >> vertice2 >> valor;
        vertice1--;
        vertice2--;
        bool result = consultorDeCaminos.puedeRecorrerseElCamino(vertice1, vertice2, valor);
        if (result) {
            cout << "SI";
        } else {
            cout << "NO";
        }
        cout << '\n';
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p21.txt");
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
