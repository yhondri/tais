//
//  main_36.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 26/1/21.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

const int MAX_VALUE = 2000000000;

struct Solucion {
    int minCoste = 2000000000;
};

void calcularMinCoste(int const& objetivo, vector<int> const& sectores) {
    int filas = (int)sectores.size();
    Matriz<Solucion> matrizSolucion(filas+1, objetivo+1);
    matrizSolucion[0][0].minCoste = 0;

    for (int i = 1; i <= (int)sectores.size(); i++) {
        matrizSolucion[i][0].minCoste = 0;
        for (int j = 1; j <= objetivo; j++) {
            if (sectores[i-1] <= j) {
                //Caso recursivo, mínimo de alcanzar el valor, utilizando el sector i-1 o utilizando el sector actual.
                matrizSolucion[i][j].minCoste = min(matrizSolucion[i - 1][j].minCoste, matrizSolucion[i][j-sectores[i-1]].minCoste+1);
            } else {
                matrizSolucion[i][j] = matrizSolucion[i - 1][j]; //Si con j no podemos llegar al valor de sectores[i-1], copiamos la solución alcanzada hasta ese momento.
            }
        }
    }
    
    if (matrizSolucion[filas][objetivo].minCoste == MAX_VALUE) {
        cout << "Imposible" << '\n';
    } else {
        cout << matrizSolucion[filas][objetivo].minCoste << ":";
        int i = filas, j = objetivo;
        while (j > 0) { //No hemos alcanzado la puntuación objetivo.
            //El enunciado exige que si hay varias soluciones tomemos aquella con mayor puntuación. Debido a que los sectores están ordenados de menor a mayor, al recorrer la solución, si podemos, siempre cogeremos la de la fila i, ya que esta será siempre mayor que el valor de i-1.
            if ((sectores[i-1] <= j) && ((matrizSolucion[i][j].minCoste != matrizSolucion[i-1][j].minCoste) || (matrizSolucion[i][j].minCoste == matrizSolucion[i][j-sectores[i-1]].minCoste+1))) {
                //Tomamos el sector de tipo i.
                cout << " " << sectores[i-1];
                j = j - sectores[i-1];
            } else {
                --i; //No tomamos el sector de tipo i.
            }
        }
        
        cout << '\n';
    }
}

bool resuelveCaso() {
    int objetivo, numSectores;
    cin >> objetivo >> numSectores;
    if (!cin) {
        return false;
    }
    
    vector<int> sectores;
    int value;
    
    for (int i = 0; i < numSectores; i++) {
        cin >> value;
        sectores.push_back(value);
    }
    
    calcularMinCoste(objetivo, sectores);
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p36.txt");
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
