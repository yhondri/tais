//
//  main_p20.cpp
//  PracticaLunes
//
//  Created by Yhondri on 06/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;
using Mapa = vector<vector<char>>;

using namespace std;

class DetectorDeMancha {
private:
    int F, C;
    ConjuntosDisjuntos conjuntoManchas;
    
    bool esPosicionValida(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }
public:
    DetectorDeMancha(int filas, int columnas) :  F(filas), C(columnas), conjuntoManchas(F*C) {}
    
    int getMayorConjunto() {
        return conjuntoManchas.getMayorConjunto();
    }
    
    void anhadirMancha(Mapa const& mapa, int fila, int columna) {
        //Diagonal izquierda fila anterior
        if (esPosicionValida(fila-1, columna-1) && mapa[fila-1][columna-1] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila-1)*C+columna-1);
        }
        
        //Fila anterior, misma columna (recorrido vertical)
        if (esPosicionValida(fila-1, columna) && mapa[fila-1][columna] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila-1)*C+columna);
        }
        
        //Diagonal derecha fila anterior
        if (esPosicionValida(fila-1, columna+1) && mapa[fila-1][columna+1] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila-1)*C+columna+1);
        }
        
        //Misma fila, columna anterior (recorrido horizontal)
        if (esPosicionValida(fila, columna-1) && mapa[fila][columna-1] == '#') {
            conjuntoManchas.unir(fila*C+columna, fila*C+columna-1);
        }
        
        //Misma fila, columna siguiente (recorrido horizontal)
        if (esPosicionValida(fila, columna+1) && mapa[fila][columna+1] == '#') {
            conjuntoManchas.unir(fila*C+columna, fila*C+columna+1);
        }
        
        //Diagonal izquierda fila siguiente
        if (esPosicionValida(fila+1, columna-1) && mapa[fila+1][columna-1] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila+1)*C+columna-1);
        }
        
        //Misma columna debajo
        if (esPosicionValida(fila+1, columna) && mapa[fila+1][columna] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila+1)*C+columna);
        }
        
        //Diagonal derecha fila siguiente
        if (esPosicionValida(fila+1, columna+1) && mapa[fila+1][columna+1] == '#') {
            conjuntoManchas.unir(fila*C+columna, (fila+1)*C+columna+1);
        }
    }
};

bool resuelveCaso() {
    int numFilas, numColumnas;
    cin >> numFilas >> numColumnas;

    if (!cin) {
        return false;
    }
    
    cin.ignore(1);
    
    DetectorDeMancha detectorDeMancha(numFilas, numColumnas);
    Mapa map(numFilas, vector<char>(numColumnas));
    string linea;
    bool existeMancha = false;
    
    for (int i = 0; i < numFilas; i++) {
        getline(cin, linea);
        for (int j = 0; j < numColumnas; j++) {
            map[i][j] = linea[j];
            if (linea[j] == '#') {
                detectorDeMancha.anhadirMancha(map, i, j);
                existeMancha = true;
            }
        }
    }
    
    if (existeMancha) {
        cout << detectorDeMancha.getMayorConjunto();
    } else {
        cout << "0";
    }
    
    int numNuevasImagenes, row, column;
    cin >> numNuevasImagenes;
    
    if (numNuevasImagenes > 0) {
        cout << ' ';
    }
    
    for (int i = 0; i < numNuevasImagenes; i++) {
        cin >> row >> column;
        row--;
        column--;
        map[row][column] = '#';
        detectorDeMancha.anhadirMancha(map, row, column);
        cout << detectorDeMancha.getMayorConjunto();

        if (i < numNuevasImagenes-1) {
            cout << ' ';
        }
    }
    
    cout << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p20.txt");
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

//Solución correcta, pero da TimeLimit. Hay que utilizar Conjuntos Disjuntos
//class DetectorDeMancha {
//private:
//    int F, C;
//    vector<vector<bool>> visitado;
//    const vector<pair<int, int>> direcciones = {{1,0},{0,1},{-1,0},{0,-1},{-1,-1},{-1,1},{1,1},{1,-1}};
//    Mapa const& mapa;
//
//    int dfs(Mapa const& mapa, int fila, int columna) {
//        visitado[fila][columna] = true;
//        int tamanhoComponenteConexa = 1;
//
//        for(auto direccion : direcciones) {
//            int positionI = fila + direccion.first, positionJ = columna + direccion.second;
//            if (esPosicionValida(positionI, positionJ) && mapa[positionI][positionJ] == '#' && !visitado[positionI][positionJ]) {
//                tamanhoComponenteConexa += dfs(mapa, positionI, positionJ);
//            }
//        }
//
//        return tamanhoComponenteConexa;
//    }
//
//    bool esPosicionValida(int i, int j) const {
//        return 0 <= i && i < F && 0 <= j && j < C;
//    }
//
//public:
//    DetectorDeMancha(Mapa const& map) : mapa(map), F((int)map.size()), C((int)map[0].size()), visitado(F, vector<bool>(C, false)) {
//    }
//
//    int getTamanhoManchaMayor() {
//        int maximaComponenteConexa = 0;
//        for (int i = 0; i < F; i++) {
//            for (int j = 0; j < C; j++) {
//                visitado[i][j] = false;
//            }
//        }
//
//        for(int i = 0; i < F; ++i) {
//            for (int j = 0; j < C; ++j) {
//                if (!visitado[i][j] && mapa[i][j] == '#') {
//                    int componenteConexa = dfs(mapa, i, j);
//                    maximaComponenteConexa = max(componenteConexa, maximaComponenteConexa);
//                }
//            }
//        }
//
//        return maximaComponenteConexa;
//    }
//
////    int getTamanhoManchaMayor() {
////        return maximaComponenteConexa;
////    }
////
////    int getNumeroDeManchas() {
////        return numManchas;
////    }
//};
