//
//  main_39.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 27/1/21.
//
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

struct Solucion {
    int beneficio = -1;
};

struct Cofre {
    int profundidad = 0;
    int cantidadDeOro = 0;
};

double calcularBeneficioMaximoRecursivo(vector<Cofre> const& cofres, int i, int j, Matriz<Solucion> &matrizSolucion) {
    if (matrizSolucion[i][j].beneficio != -1) {
        return matrizSolucion[i][j].beneficio;
    }
    
    if (i == 0 || j == 0) {
        matrizSolucion[i][j].beneficio = 0;
    } else if((cofres[i-1].profundidad + 2*cofres[i-1].profundidad) > j) { //Si no queda oxígeno suficiente, intentamos recuperar otro cofre.
        matrizSolucion[i][j].beneficio = calcularBeneficioMaximoRecursivo(cofres, i-1, j, matrizSolucion);
    } else { //Si podemos coger el cofre, probamos a cogerlo y a no cogerlo.
        int costeCogerElCofre = j-(cofres[i-1].profundidad + 2*cofres[i-1].profundidad);
        matrizSolucion[i][j].beneficio = max(calcularBeneficioMaximoRecursivo(cofres, i-1, j, matrizSolucion),
                                             calcularBeneficioMaximoRecursivo(cofres, i-1, costeCogerElCofre, matrizSolucion) + cofres[i-1].cantidadDeOro);
    }
    
    return matrizSolucion[i][j].beneficio;
}

bool resuelveCaso() {
    int tSegundosBotella;
    cin >> tSegundosBotella;
    if (!cin) {
        return false;
    }
    
    int numCofres;
    cin >> numCofres;
    
    vector<Cofre> cofres;
    int profundidad, cantidadDeOro;
    
    for (int i = 0; i < numCofres; i++) {
        cin >> profundidad >> cantidadDeOro;
        cofres.push_back({profundidad, cantidadDeOro});
    }
    
    int filas = (int)cofres.size();
    Matriz<Solucion> matrizSolucion(filas+1, tSegundosBotella+1);
    
    //Solución
    double beneficioMaximoRecuperado = calcularBeneficioMaximoRecursivo(cofres, filas, tSegundosBotella, matrizSolucion);
    vector<Cofre> cofreRescatado;
    int i = filas, j = tSegundosBotella;
    while (i > 0 && j > 0) {
        if (matrizSolucion[i][j].beneficio != matrizSolucion[i-1][j].beneficio ) { //Hemos cogido el cofre i-1
            cofreRescatado.push_back(cofres[i-1]);
            j = j-(cofres[i-1].profundidad + 2*cofres[i-1].profundidad);
        }
        --i; //Sólo podemos coger el cofre una vez.
    }
    
    cout << beneficioMaximoRecuperado << endl;
    cout << cofreRescatado.size() << endl;
    for (int i = (int)cofreRescatado.size()-1; i >= 0; --i) { //Para poder representar los cofres tal y como aparecen en la entrada recorremos el vector en orden inverso ya que al recrear la solución, recorremos la matriz en orden de final al inicio.
        cout << cofreRescatado[i].profundidad << " " << cofreRescatado[i].cantidadDeOro << '\n';
    }
    cout << "---" << '\n';

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p39.txt");
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
