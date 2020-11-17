//
//  main_24.cpp
//  PracticaLunes
//
//  Created by Yhondri on 15/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;
const int INF = std::numeric_limits<int>::max();

class CalcularCaminoMinimo {
private:
    std::vector<int> dist;
    IndexPQ<int, int> pq;
    std::vector<long long> caminosMinimos;
public:
    CalcularCaminoMinimo(DigrafoValorado<int> const& grafo) : dist(grafo.V(), INF), pq(grafo.V()), caminosMinimos(grafo.V(), 0) {
        
        int origen = 1;
        
        dist[origen] = 0;
        caminosMinimos[0] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : grafo.ady(v)) {
                relajar(a);
                
            }
        }
    }
    
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > (dist[v] + a.valor())) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
            caminosMinimos[w] = caminosMinimos[v];
        } else if (dist[w] == (dist[v] + a.valor())) {
            caminosMinimos[w] += caminosMinimos[v];
        }
    }
    
    long long getCaminosDistintos(int vertice) {
        return caminosMinimos[vertice];
    }
};

bool resuelveCaso() {
    int vertices, aristas;
    cin >> vertices >> aristas;

    if (!cin) {
        return false;
    }
    
    DigrafoValorado<int> grafo(vertices);
    int vertice1, vertice2, value;
    for (int i = 0; i < aristas; i++) {
        cin >> vertice1 >> vertice2 >> value;
        vertice1--;
        vertice2--;
        grafo.ponArista({vertice1, vertice2, value});
        grafo.ponArista({vertice2, vertice1, value});
    }
    
    CalcularCaminoMinimo calculadorCaminoMinimo(grafo) ;
    cout << calculadorCaminoMinimo.getCaminosDistintos(grafo.V()-1) << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p24.txt");
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

