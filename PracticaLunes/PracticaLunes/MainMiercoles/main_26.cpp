//
//  main_26.cpp
//  PracticaLunes
//
//  Created by Yhondri on 18/11/2020.
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

class CalcularEsfuerzoMinimo {
private:
    /**
     Pista Profesor. Hay que calcular el coste del camino inverso, es decir grafo inverso.
     Utilizamos 2 vectores para almacenar las distancias de los 2 grafos.
     */
    std::vector<int> distanciaGrafoOriginal;
    std::vector<int> distanciaGrafoInverso;
    IndexPQ<int, int> pq;
    int paquetes;
    
    void dijkstra(int origen, DigrafoValorado<int> const& grafo, vector<int> &distanciaGrafo) {
        distanciaGrafo[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : grafo.ady(v)) {
                relajar(distanciaGrafo, a);
            }
        }
    }
    
    void relajar(vector<int> &distanciaGrafo, AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (distanciaGrafo[w] > (distanciaGrafo[v] + a.valor())) {
            distanciaGrafo[w] = distanciaGrafo[v] + a.valor();
            pq.update(w, distanciaGrafo[w]);
        }
    }
    
public:
    CalcularEsfuerzoMinimo(int origen, DigrafoValorado<int> const& grafoOriginal, DigrafoValorado<int> const& grafoInvertido, int packages): paquetes(packages), distanciaGrafoOriginal(grafoOriginal.V(), INF), distanciaGrafoInverso(grafoOriginal.V(), INF) {
        dijkstra(origen, grafoOriginal, distanciaGrafoOriginal);
        dijkstra(origen, grafoInvertido, distanciaGrafoInverso);
    }
    
    /**
     Calculamos el esfuerzo mínimo a partir del coste de ir a las diferentes casas tanto en el grafo original como en el grafo invertido.
     */
    void mostrarEsfuerzoMinimo(vector<int> casas) {
        int costeMinimo = 0, costeIda = 0, costeVuelta = 0;
        bool esImposible = false;
        
        for (int i = 0; i < paquetes && !esImposible; i++) {
            int numCasa = casas[i];
            costeIda = distanciaGrafoOriginal[numCasa];
            costeVuelta = distanciaGrafoInverso[numCasa];

            if (costeIda != INF && costeVuelta != INF) {
                costeMinimo += costeIda + costeVuelta;
            } else {
                esImposible = true;
            }
        }
        
        if (esImposible) {
            cout << "Imposible";
        } else {
            cout << costeMinimo;
        }
        
        cout << '\n';
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
    }
    
    int origenOficina, numPaquetes, numCasa;
    cin >> origenOficina >> numPaquetes;
    vector<int> casas(numPaquetes);
    for (int i = 0; i < numPaquetes; i++) {
        cin >> numCasa;
        numCasa--;
        casas[i] = numCasa;
    }
    
    //Pista Profesor. Hay que calcular el coste del camino inverso, es decir grafo inverso.
    DigrafoValorado<int> grafoInverso = grafo.inverso();
    
    //Hay que restar 1 unidad al origen ya que la entrada va desdes 1 -> N, pero el grafo lo construimos desde 0 -> N-1
    origenOficina--;
    CalcularEsfuerzoMinimo calcularCaminoMino(origenOficina, grafo, grafoInverso, numPaquetes);
    calcularCaminoMino.mostrarEsfuerzoMinimo(casas);
 
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p26.txt");
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
