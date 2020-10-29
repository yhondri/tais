//
//  main_14.cpp
//  PracticaLunes
//
//  Created by Yhondri on 29/10/2020.
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

class CalculadorDeAmigosConectados {
private:
    vector<int> visitado;
    //Contiene el número de vértices alcanzables a partir de cada vértice.
    vector<int> contadorDeAmigos;

    int dfs(Grafo const& grafo, int vertice, queue<int>& mQueue) {
        visitado[vertice] = true;
        int conexionesAmigos = 1;
        mQueue.push(vertice);

        for(auto w : grafo.ady(vertice)) {
            if (!visitado[w]) {
                conexionesAmigos += dfs(grafo, w, mQueue);
            }
        }
        return conexionesAmigos;
    }
    
public:
    CalculadorDeAmigosConectados(Grafo const& grafo) : visitado(grafo.V(), false), contadorDeAmigos(grafo.V(), 1) {
        queue<int> mQueue;
        
        for(int i = 0; i < grafo.V(); i ++) {
            if (!visitado[i]) {
                int componenteConexa = dfs(grafo, i, mQueue);
                
                while (!mQueue.empty()) {
                    contadorDeAmigos[mQueue.front()] = componenteConexa;
                    mQueue.pop();
                }
            }
        }
    }
    
    int getNumeroDeAMigosDelUsuario(int idUsuario) {
        return contadorDeAmigos[idUsuario];
    }
};


bool resuelveCaso() {
    int nUsuarios, mGrupos;
    cin >> nUsuarios >> mGrupos;

    if (!cin) {
        return false;
    }
    
    Grafo gruposGrafo(nUsuarios);
    int usuariosEnGrupo, usuarioActual, usuarioAnterior = 0;
    for (int i = 0; i < mGrupos; i++) {
        cin >> usuariosEnGrupo;
        for (int i = 0; i < usuariosEnGrupo; i++) {
            cin >> usuarioActual;
            
            if (usuarioAnterior != 0) {
                gruposGrafo.ponArista(usuarioAnterior-1, usuarioActual-1);
            }
            
            usuarioAnterior = usuarioActual;
        }
        
        usuarioAnterior = 0;
    }
    
    CalculadorDeAmigosConectados calculadorDeAmigosConectados(gruposGrafo);
    
    for (int i = 0; i < nUsuarios; i++) {
        cout << calculadorDeAmigosConectados.getNumeroDeAMigosDelUsuario(i) << " ";
    }
    
    cout << '\n';
        
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p14.txt");
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

