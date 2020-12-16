//
//  main_35.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 5/12/20.
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
    long long manerasDeConseguirLaCuerda;
    int minNumCordeles = 2000000000;
    int minCoste = 2000000000;
};

struct Cordel {
    int longitud;
    int coste;
};

/// Esta implementación soluciona el problema con mejora en el espacio utilizado (Antes de mirar esta solución, mira la solución utilizando matriz).
/// Recursividad:
/// caso base 1: manerasConseguirCuerda(cordeles, n, cuerda) = false, si sum > 0 && n == 0
/// caso base 2: manerasConseguirCuerda(cordeles, n, cuerda) = true, si sum  == 0
/// Por lo tanto para contar todas las posibles maneras de conseguir la cuerda deseada con los córdeles es, por cada cada cordel, contar las posibiliades de incluirlo o no en la construcción de la cuerda.
/// resultado = manerasConseguirCuerda(cordeles, n-1, cuerda) || manerasConseguirCuerda(cordeles, n-1, cuerda-cordeles[n-1])
///
/// Esta versión utiliza programación dinámica, en concreto es una versión mejorada que mejora el espacio en memoria utilizado ya que en vez de utilizar una matriz, utiliza un vector. Esto podemos hacerlo ya que para resolver el caso n, sólo necesitamos el caso n-1, en
/// términos de matriz, para resolver la fila actual, sólo necesitamos la fila anterior.
/// Recorremos el vector de derecha a izquierda, porque si lo recorremos de izq-der, estariamos borrando los valores de n-1.
///
/// @param cordeles Cordeles disponibles para construir la cuerda.
/// @param longitudCuerda Longitud de la cuerda que queremos construir.
void getSolucionB(vector<Cordel> const& cordeles, int const& longitudCuerda) {
    vector<Solucion> solucionVector((int)longitudCuerda+1);
    solucionVector[0].manerasDeConseguirLaCuerda = 1;
    solucionVector[0].minCoste = 0;
    solucionVector[0].minNumCordeles = 0;
    
    if (cordeles[0].longitud <= longitudCuerda) {
        solucionVector[cordeles[0].longitud].manerasDeConseguirLaCuerda = 1;
        solucionVector[cordeles[0].longitud].minCoste = cordeles[0].coste;
        solucionVector[cordeles[0].longitud].minNumCordeles = 1;
    }
    
    for (int i = 1; i < (int)cordeles.size(); ++i) {
        for (int j = longitudCuerda; j > 0; --j) {
            if (cordeles[i].longitud <= j) {
                solucionVector[j].manerasDeConseguirLaCuerda = solucionVector[j].manerasDeConseguirLaCuerda + solucionVector[j - cordeles[i].longitud].manerasDeConseguirLaCuerda;
                solucionVector[j].minNumCordeles = min(solucionVector[j].minNumCordeles, solucionVector[j - cordeles[i].longitud].minNumCordeles+1);
                solucionVector[j].minCoste = min(solucionVector[j].minCoste, solucionVector[j - cordeles[i].longitud].minCoste + cordeles[i].coste);
            }
        }
    }
    
    Solucion solucion = solucionVector[longitudCuerda];
    
    if (solucion.manerasDeConseguirLaCuerda > 0) {
        cout << "SI " << solucion.manerasDeConseguirLaCuerda << " " << solucion.minNumCordeles << " " << solucion.minCoste << '\n';
    } else {
        cout << "NO" << '\n';
    }
}

//void getSolucion(vector<Cordel> const& cordeles, int const& longitudCuerda) {
//    Matriz<Solucion> matrizFormasCrearCuerda((int)cordeles.size(), longitudCuerda+1);
//
//    // Si la suma es 0, la respuesta es que sí se puede alcanzar la suma.
//    for (int i = 0; i < (int)cordeles.size(); i++) {
//        matrizFormasCrearCuerda[i][0].manerasDeConseguirLaCuerda = 1;
//        matrizFormasCrearCuerda[i][0].minCoste = 0;
//        matrizFormasCrearCuerda[i][0].minNumCordeles = 0;
//    }
//
//    if (cordeles[0].longitud <= longitudCuerda) {
//        matrizFormasCrearCuerda[0][cordeles[0].longitud].manerasDeConseguirLaCuerda = 1;
//        matrizFormasCrearCuerda[0][cordeles[0].longitud].minCoste = cordeles[0].coste;
//        matrizFormasCrearCuerda[0][cordeles[0].longitud].minNumCordeles = 1;
//    }
//
//    //Rellenamos la matriz bottom up
//    for (int i = 1; i < (int)cordeles.size(); ++i) {
//        for (int j = 0; j < longitudCuerda+1; ++j) {
//            if (cordeles[i].longitud <= j) {
//                //Maneras que tengo ahora, más las maneras que tenía antes.
//                matrizFormasCrearCuerda[i][j].manerasDeConseguirLaCuerda = matrizFormasCrearCuerda[i - 1][j].manerasDeConseguirLaCuerda + matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].manerasDeConseguirLaCuerda;
//                //número de cordeles necesarios hasta ahora, o número de cordeles necesarios añadiendo esta cuerda + 1.
//                matrizFormasCrearCuerda[i][j].minNumCordeles = min(matrizFormasCrearCuerda[i - 1][j].minNumCordeles, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minNumCordeles+1);
//                //Coste mínimo necesario hasta ahora o coste mínimo necesario añadiendo este cordel + el coste del cordel.
//                matrizFormasCrearCuerda[i][j].minCoste = min(matrizFormasCrearCuerda[i - 1][j].minCoste, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minCoste + cordeles[i].coste);
//            } else {
//                matrizFormasCrearCuerda[i][j] = matrizFormasCrearCuerda[i - 1][j];
//            }
//        }
//    }
//
//    Solucion solucion = matrizFormasCrearCuerda[(int)cordeles.size()-1][longitudCuerda];
//
//    if (solucion.manerasDeConseguirLaCuerda > 0) {
//        cout << "SI " << solucion.manerasDeConseguirLaCuerda << " " << solucion.minNumCordeles << " " << solucion.minCoste << '\n';
//    } else {
//        cout << "NO" << '\n';
//    }
//}

bool resuelveCaso() {
    int numCordeles, longitudCuerda;
    cin >> numCordeles >> longitudCuerda;
    if (!cin) {
        return false;
    }
    
    vector<Cordel> cordeles;
    int longitud, coste;
    
    for (int i = 0; i < numCordeles; i++) {
        cin >> longitud >> coste;
        cordeles.push_back({longitud, coste});
    }
    
//    getSolucion(cordeles, longitudCuerda);
    getSolucionB(cordeles, longitudCuerda);

//    CalculadorNumeroCombinaciones calculador(cordeles, longitudCuerda);
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p35.txt");
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
