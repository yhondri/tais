//
//  main_p11.cpp
//  PracticaLunes
//
//  Created by Yhondri on 27/10/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Grafo.h"
 
using namespace std;

class MayorGrupoAmigos {
private:
    //Igual a mayor componente conexta.
    int numeroAmigosMasGrandes;
    vector<int> visitado;
    
    int dfs(Grafo const& grafo, int vertice) {
        visitado[vertice] = true;
        int conexionesAmigos = 1;
        for(auto w : grafo.ady(vertice)) {
            if (!visitado[w]) {
                conexionesAmigos += dfs(grafo, w);
            }
        }
        
        return conexionesAmigos;
    }
    
public:
    MayorGrupoAmigos(Grafo const& grafo) : visitado(grafo.V(), false), numeroAmigosMasGrandes(0) {
        for(int i = 0; i < grafo.V(); i ++) {
            if (!visitado[i]) {
                int componenteConexa = dfs(grafo, i);
                numeroAmigosMasGrandes = max(componenteConexa, numeroAmigosMasGrandes);
            }
        }
    }
    
    int getNumeroAmigosMasGrandes() {
        return numeroAmigosMasGrandes;
    }
};

bool resuelveCaso() {
    int numVertices, numAristas;
    
    cin >> numVertices >> numAristas;
    
    int v, w;
    Grafo grafo(numVertices);
    for (int i = 0; i < numAristas; i++) {
        cin >> v >> w;
        grafo.ponArista(v-1, w-1);
    }
    
    MayorGrupoAmigos mayorGrupoAmigos(grafo);
    
    cout << mayorGrupoAmigos.getNumeroAmigosMasGrandes() << '\n';
    
    return true;
}



int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p11.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos = 0;
    cin >> numCasos;
    
    for (int i = 0; i < numCasos; i++) {
        resuelveCaso();
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
