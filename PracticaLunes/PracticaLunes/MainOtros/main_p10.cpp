//
//  main_p10.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 25/10/20.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Grafo.h"
 
using namespace std;

class CaminosDFS {
private:
    vector<bool> visitado;
    vector<int> anterior;
    int verticeOrigen;
    int numVerticesVisitados;
    bool existeCiclo;
    int numVertices;
    
    void dfs(Grafo const& grafo, int vertice) {
        visitado[vertice] = true;
        numVerticesVisitados++;
        for(int w : grafo.ady(vertice)) {
            if (!visitado[w]) {
                anterior[w] = vertice;
                dfs(grafo, w);
            } else if (anterior[vertice] != w) {
                existeCiclo = true; //Significa que hemos encontrado otro camino para llegar a w.
            }
        }
    }
    
public:
    CaminosDFS(Grafo const& grafo, int source) : visitado(grafo.V(), false), anterior(grafo.V()), verticeOrigen(source), numVertices(grafo.V()), numVerticesVisitados(0), existeCiclo(false) {
        dfs(grafo, source);
    }
    
    bool esUnArbolLibre() {
        return !existeCiclo && (numVerticesVisitados == numVertices);
    }
};


bool resuelveCaso() {
    int numVertices, numAristas;
    
    if (!(cin >> numVertices)) {
        return false;
    }
    
    cin >> numAristas;
    
    int v, w;
    Grafo grafo(numVertices);
    for (int i = 0; i < numAristas; i++) {
        cin >> v >> w;
        grafo.ponArista(v, w);
    }
    
    CaminosDFS camino(grafo, 0);
    
    if (camino.esUnArbolLibre()) {
        cout << "SI"<< '\n';
    } else {
        cout << "NO" << '\n';
    }
    
//    grafo.print();
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p10.txt");
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
