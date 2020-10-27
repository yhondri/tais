//
//  main_p12.cpp
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
using Mapa = vector<string>;

class DetectorDeMancha {
private:
    int F, C;
    int maximaComponenteConexa;
    int numManchas;
    vector<vector<bool>> visitado;
    const vector<pair<int, int>> direcciones = {{1,0},{0,1},{-1,0},{0,-1}};
    
    int dfs(Mapa const& mapa, int fila, int columna) {
        visitado[fila][columna] = true;
        int tamanhoComponenteConexa = 1;
        
        for(auto direccion : direcciones) {
            int positionI = fila + direccion.first, positionJ = columna + direccion.second;
            if (esPosicionValida(positionI, positionJ) && mapa[positionI][positionJ] == '#' && !visitado[positionI][positionJ]) {
                tamanhoComponenteConexa += dfs(mapa, positionI, positionJ);
            }
        }
        
        return tamanhoComponenteConexa;
    }
    
    bool esPosicionValida(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }
    
public:
    DetectorDeMancha(Mapa const& map) : F(map.size()), C(map[0].size()), visitado(F, vector<bool>(C, false)), numManchas(0), maximaComponenteConexa(0) {
        for(int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                if (!visitado[i][j] && map[i][j] == '#') {
                    numManchas++;
                    int componenteConexa = dfs(map, i, j);
                    maximaComponenteConexa = max(componenteConexa, maximaComponenteConexa);
                }
            }
        }
    }
    
    int getTamanhoManchaMayor() {
        return maximaComponenteConexa;
    }
    
    int getNumeroDeManchas() {
        return numManchas;
    }
};

bool resuelveCaso() {
    int numFilas, numColumnas;
    cin >> numFilas >> numColumnas;

    if (!cin) {
        return false;
    }
    
    Mapa map(numFilas);
    for (string & linea : map)
          cin >> linea;
    
    DetectorDeMancha detectorDeMancha(map);
    cout << detectorDeMancha.getNumeroDeManchas() << ' ' << detectorDeMancha.getTamanhoManchaMayor() << '\n';

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p12.txt");
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
