//
//  main_p15.cpp
//  PracticaLunes
//
//  Created by Yhondri on 31/10/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"

using namespace std;

class CalculadorDeNodosAlzanzables {
private:
    vector<bool> visitado;
    vector<int> anterior;
    vector<int> distancia;
    Grafo grafo;
    
    /**
     
     */
    void bfs(int source) {
        std::queue<int> q;
        distancia[source] = 0;
        visitado[source] = true;
        q.push(source);
                
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : grafo.ady(v)) {
                if (!visitado[w]) {
                    anterior[w] = v;
                    distancia[w] = distancia[v] + 1;
                    visitado[w] = true;
                    q.push(w);
                }
            }
        }
    }
    
public:
    CalculadorDeNodosAlzanzables(Grafo mGrafo): grafo(mGrafo), visitado(mGrafo.V(), false), anterior(mGrafo.V()), distancia(mGrafo.V()) {

    }
    
    int getNodosInalcanzablesDesdeElVertice(int verticeOrigen, int ttl) {
        std::fill(visitado.begin(), visitado.end(), false);
       bfs(verticeOrigen-1);
        int nodosAlcanzados = 1;
        for (int i = 0; i < visitado.size(); i++) {
            if (visitado[i] && distancia[i] >= 1 && distancia[i] <= ttl) {
                nodosAlcanzados++;
            }
        }
        return grafo.V() - nodosAlcanzados;
    }
};

bool resuelveCaso() {
    int nNumeroNodos, cConexionesEntreNodos;
    cin >> nNumeroNodos >> cConexionesEntreNodos;
    
    if (!cin) {
        return false;
    }
    
    Grafo nodosGrafo(nNumeroNodos);
    int vertice1, vertice2;
    
    for (int i = 0; i < cConexionesEntreNodos; i++) {
        cin >> vertice1 >> vertice2;
        nodosGrafo.ponArista(vertice1-1, vertice2-1);
    }
    
    CalculadorDeNodosAlzanzables calculadorDeNodosAlzanzables(nodosGrafo);
    int consultas, consultaVerticeInicial, consultaTTL;
    cin >> consultas;
    for (int i = 0; i < consultas; i++) {
        cin >> consultaVerticeInicial >> consultaTTL;
        cout << calculadorDeNodosAlzanzables.getNodosInalcanzablesDesdeElVertice(consultaVerticeInicial, consultaTTL) << '\n';
    }
    
    cout << "---\n";
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p15.txt");
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
