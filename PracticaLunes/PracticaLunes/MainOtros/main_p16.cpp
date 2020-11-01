//
//  main_p16.cpp
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

using namespace std;

class MaquinaCalculadora {
private:
    const int MAX = 10000;
    const int INF = 1000000000;
    int menorNumeroDePasos;
    
    int adyacente(int v, int i) {
        switch (i) {
            case 0:
                return (v+1)%MAX; //Operación + 1
            case 1:
                return (v*2)%MAX; //Operación * 2
            case 2:
                return (v/3); //Operación / 3
        }
        
        return 0; //Operación no controlada. 
    }
    
    int bfs (int origen, int destino) {
        if (origen == destino) {
            return 0;
        }
        
        vector<int> distancia(MAX, INF);
        distancia[origen] = 0;
        queue<int> cola;
        cola.push(origen);
        
        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (int i = 0; i < 3; ++i) {
                int w = adyacente(v, i);
                if (distancia[w] == INF) {
                    distancia[w] = distancia[v] + 1;
                    if (w == destino) {
                        return distancia[w];
                    } else {
                        cola.push(w);
                    }
                }
            }
        }
        
        //No se debería dar.
        return 0;
    }
    
public:
    MaquinaCalculadora(int origen, int destino): menorNumeroDePasos(0)  {
        menorNumeroDePasos = bfs(origen, destino);
    }
    
    int getMenorNumeroDePasos() {
        return menorNumeroDePasos;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int origen, destino;
    cin >> origen >> destino;
    if (!std::cin) { // fin de la entrada
        return false;
    }
    
    MaquinaCalculadora calculadora(origen, destino);
    cout << calculadora.getMenorNumeroDePasos() << '\n';
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p16.txt");
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
