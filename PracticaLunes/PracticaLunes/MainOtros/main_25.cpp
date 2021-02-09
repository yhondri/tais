//
//  main_25.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 21/11/20.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

using namespace std;

class MejorCamino {
private:
    const int INF = 1000000000;

    // Dijkstra
    std::vector<std::pair<int,int>> distDijkstra;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<pair<int, int>> pq;
    int aristas;
    //BFS
    std::vector<int> distBFS;
    std::vector<bool> marcados;
    int destino;

    void bfs(DigrafoValorado<int> const& dg, int origen) {
        std::queue<int> cola;
        distBFS[origen] = 0;
        marcados[origen] = true;
        cola.push(origen);
        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (AristaDirigida<int> a : dg.ady(v)) {
                int w = a.hasta();
                if (!marcados[w]) {
                    distBFS[w] = distBFS[v] + 1;
                    marcados[w] = true;
                    cola.push(w);
                }
            }
        }
    }

    void aristaDijkstra() {
        aristas = distDijkstra[destino].second;
    }

    void relajarArista(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();
        if (distDijkstra[w].first > distDijkstra[v].first + a.valor()) {
            distDijkstra[w].first = distDijkstra[v].first + a.valor();
            distDijkstra[w].second = distDijkstra[v].second + 1;
            ulti[w] = a;
            pq.update(w, distDijkstra[w]);
        }
        else if (distDijkstra[w].first == distDijkstra[v].first + a.valor() &&
            distDijkstra[w].second > distDijkstra[v].second + 1) {
            distDijkstra[w].second = distDijkstra[v].second + 1;
            ulti[w] = a;
            pq.update(w, distDijkstra[w]);
        }
    }

    void dijkstra(DigrafoValorado<int> const& dg, int origen) {
        distDijkstra[origen] = {0,0};
        pq.push(origen, { 0,0 });
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (AristaDirigida<int> a : dg.ady(v)) {
                relajarArista(a);
            }
        }
    }
public:
    MejorCamino(DigrafoValorado<int> dg, int origen, int dest) : marcados(dg.V(), false), distBFS(dg.V(), INF), distDijkstra(dg.V(), { INF, 0 }), ulti(dg.V()), pq(dg.V()) {
        destino = dest;
        bfs(dg, origen);
        dijkstra(dg, origen);
        if (marcados[destino]) aristaDijkstra();
    }

    bool hayCamino() const {
        return marcados[destino];
    }

    int distancia() const {
        return distDijkstra[destino].first;
    }
    bool iguales() const {
        return distBFS[destino] == aristas;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    int n, c;
    cin >> n >> c;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> dg(n);
    int o, d, v;
    for (int i = 0; i < c; i++) {
        cin >> o >> d >> v;
        dg.ponArista({ o - 1,d - 1,v });
        dg.ponArista({ d - 1,o - 1,v });
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> o >> d;
        MejorCamino mc(dg, o - 1, d - 1);
        if (mc.hayCamino()) {
            if (mc.iguales()) cout << mc.distancia() << " SI" << '\n';
            else cout << mc.distancia() << " NO" << '\n';
        }
        else cout << "SIN CAMINO" << '\n';
    }
    cout << "---" << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p25.txt");
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

