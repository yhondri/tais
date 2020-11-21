//
//  main_22.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 21/11/20.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

template <typename Valor>

class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    bool _hayCamino;
    
public:
    Valor costeARM() const {
        return coste;
    }
    
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    
    bool hayCamino() const {
      return _hayCamino;
    }
    
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v,w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) {
                    break;
                }
            }
        }
        
        _hayCamino = (cjtos.num_cjtos() == 1);
    }
};


bool resuelveCaso() {
    int numVertices, aristas;
    cin >> numVertices >> aristas;
    
    if (!cin) {
        return false;
    }
    
    GrafoValorado<int> grafo(numVertices);
    int vertice1, vertice2, value;
    for (int i = 0; i < aristas; i++) {
        cin >> vertice1 >> vertice2 >> value;
        vertice1--;
        vertice2--;
        grafo.ponArista({vertice1, vertice2, value});
    }
    
    ARM_Kruskal<int>calculadorCaminoMinimo(grafo);
    
    if (calculadorCaminoMinimo.hayCamino()) {
        int coste = calculadorCaminoMinimo.costeARM();
        cout << coste;
    } else {
        cout << "No hay puentes suficientes";
    }
    
    cout << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p22.txt");
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
