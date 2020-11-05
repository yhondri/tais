//
//  main_19.cpp
//  PracticaLunes
//
//  Created by Yhondri on 04/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int resolver( int nDimensionTablero, int kCarasDado, int sSerpientes, int eEscaleras) {
    vector<int> saltosVector(nDimensionTablero*nDimensionTablero+1);

    int v, w;
    for (int i = 0; i < sSerpientes+eEscaleras; i++) {
        cin >> v >> w;
        saltosVector[v] = w; //En la posición v hay un salto a w.
    }
    
    //bfs
    queue<int> queue;
    vector<int> visitado(nDimensionTablero*nDimensionTablero+1, false);
    vector<int> distancia(nDimensionTablero*nDimensionTablero+1, false);

    visitado[1] = true;
    queue.push(1);
    distancia[1] = 0;
    
    while (!queue.empty()) {
        int position = queue.front();
        queue.pop();
        
        //Por cada cara del dado iteramos, es como si recorriesemos los adyacentes de un grafo
        for (int i = 1; i <= kCarasDado && position+1 <= nDimensionTablero*nDimensionTablero; i++) {
            int w = position+i;
            if (saltosVector[w] > 0) {
                w = saltosVector[w];
            }
            
            if (!visitado[w]) {
                distancia[w] = distancia[position] + 1;
                if (w == nDimensionTablero*nDimensionTablero) { //Hemos llegado al final del tablero
                    return distancia[nDimensionTablero*nDimensionTablero];
                }
                
                visitado[w] = true;
                queue.push(w);
            }
            
        }
    }
    return distancia[nDimensionTablero*nDimensionTablero];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int nDimensionTablero, kCarasDado, sSerpientes, eEscaleras;
    cin >> nDimensionTablero >> kCarasDado >> sSerpientes >> eEscaleras;
    if (nDimensionTablero == 0 && kCarasDado == 0 && sSerpientes == 0 && eEscaleras == 0) { // fin de la entrada
        return false;
    }
    
    int resultado = resolver(nDimensionTablero, kCarasDado, sSerpientes, eEscaleras);
    cout << resultado << '\n';
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p19.txt");
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


