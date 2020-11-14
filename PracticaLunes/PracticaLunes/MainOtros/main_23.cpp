//
//  main_23.cpp
//  PracticaLunes
//
//  Created by Yhondri on 14/11/2020.
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
    std::vector<AristaDirigida<int>> ult;
    IndexPQ<int, int> pq;
    std::vector<int> costeCargaPaginas;
public:
    CalcularCaminoMinimo(DigrafoValorado<int> const& grafo, vector<int> const& cargaPaginas) : dist(grafo.V(), INF), costeCargaPaginas(cargaPaginas), ult(grafo.V()), pq(grafo.V()) {
        
        int origen = 0;
        
        dist[origen] = 0;
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
        if (dist[w] > (dist[v] + a.valor() + costeCargaPaginas[v])) {
            dist[w] = dist[v] + a.valor() + costeCargaPaginas[v];
            ult[w] = a;
            pq.update(w, dist[w]);
        }
    }
    
    int costeCaminoAPagina(int pagina) {
        int value = dist[pagina];
        if (value == INF) {
            return value;
        }
        return dist[pagina] + costeCargaPaginas[pagina];
    }
};

bool resuelveCaso() {
    int numPaginas, aristas;
    cin >> numPaginas;

    if (numPaginas == 0) {
        return false;
    }
    
    vector<int> costeCargaPaginas;
    int value;
    for (int i = 0; i < numPaginas; i++) {
        cin >> value;
        costeCargaPaginas.push_back(value);
    }
    
    cin >> aristas;
    DigrafoValorado<int> grafo(numPaginas);
    int vertice1, vertice2;
    for (int i = 0; i < aristas; i++) {
        cin >> vertice1 >> vertice2 >> value;
        vertice1--;
        vertice2--;
        grafo.ponArista({vertice1, vertice2, value});
    }
    
    CalcularCaminoMinimo calculadorCaminoMinimo(grafo, costeCargaPaginas) ;
    int coste = calculadorCaminoMinimo.costeCaminoAPagina(numPaginas-1);

    if (coste == INF) {
        cout << "IMPOSIBLE";
    } else {
        cout << coste;
    }
    
    cout << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p23.txt");
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
