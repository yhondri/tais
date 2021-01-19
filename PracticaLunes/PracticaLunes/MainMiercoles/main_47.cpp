//
//  main_47.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 13/1/21.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

int cubosRecursivo(vector<int> const& cubosVector, int i, int j, Matriz<int> & cubosMatriz) {
    if (cubosMatriz[i][j] != -1) { //Subproblema ya resuelto
        return cubosMatriz[i][j];
    }
    
    if (i == 0 || j == 0) {
        cubosMatriz[i][j] = 0;
    } else {
        int cuboLeft = max(cubosRecursivo(cubosVector, i-1, j, cubosMatriz), cubosRecursivo(cubosVector, i-1, j - cubosVector[i-1], cubosMatriz) + cubosVector[i-1]);
        int cuboRight = max(cubosRecursivo(cubosVector, i-1, j, cubosMatriz), cubosRecursivo(cubosVector, i-1, j - cubosVector[i-1], cubosMatriz) + cubosVector[i-1]);
        cubosMatriz[i][j] = max(cuboLeft, cuboRight);
        return cubosMatriz[i][j];
    }
    
    return cubosMatriz[i][j];
}



void getSolucion(vector<int> const& cubos, int const& cuboMayor) {
    Matriz<int> matrizFormasCrearCuerda((int)cubos.size()+1, cuboMayor+1, -1);
    int i = (int)cubos.size();
    int resultado = cubosRecursivo(cubos, i, cuboMayor, matrizFormasCrearCuerda);
    cout << resultado << endl;
}

bool resuelveCaso() {
    int numCubos;
    cin >> numCubos;
    if (numCubos == 0) {
        return false;
    }
    
    vector<int> cubos;
    int cubo;
    int maximo = 0; //Para saber la longitud a lo ancho de la matriz.
    
    for (int i = 0; i < numCubos; i++) {
        cin >> cubo;
        maximo = max(maximo, cubo);
        cubos.push_back(cubo);
    }
    
    getSolucion(cubos, maximo);
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p47.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
//
    while (resuelveCaso()) {}
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
