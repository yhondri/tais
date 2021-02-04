//
//  main_40.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 28/1/21.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

int creadorPalindromo(string const& palabra, int i, int j, Matriz<int>& palindromoMatriz) {
    int &resultado = palindromoMatriz[i][j];
    if (resultado == -1) {
        if (i == j || i > j) {
            resultado = 0;
        } else if(palabra[i] == palabra[j]) {
            resultado = creadorPalindromo(palabra, i+1, j-1, palindromoMatriz);
        } else {
            resultado = min(creadorPalindromo(palabra, i+1, j, palindromoMatriz),
                            creadorPalindromo(palabra, i, j-1, palindromoMatriz)) + 1;
        }
    }
    
    return resultado;
}

//string reconstruirSolucion(string const& palabra, int i, int j, Matriz<int>& palindromoMatriz) {
//    if (palindromoMatriz[i][j] == 0) {
//        return {};
//    }
//
//    if (palindromoMatriz[i][j-1] == palindromoMatriz[i+1][j]) {
//        return palabra[i] + reconstruirSolucion(palabra, i+1, j-1, palindromoMatriz); //Diagonal
//    } else if (palindromoMatriz[i][j-1] > palindromoMatriz[i+1][j]) {
//        return palabra[i] + reconstruirSolucion(palabra, i+1, j, palindromoMatriz); //Hacía abajo
//    } else {
//        return palabra[i] + reconstruirSolucion(palabra, i, j-1, palindromoMatriz);
//    }
//}


//void reconstruirSolucionB(string const& patitos,
//                          Matriz<int> const& palindromoMatriz,
//                          int i,
//                          int j,
//                          string & sol) {
//    if (i > j) return;
//
//    if (i == j){
//        sol.push_back(patitos[i]);
//    } else if (patitos[i] == patitos[j]) {
//        sol.push_back(patitos[i]);
//        reconstruirSolucionB(patitos, palindromoMatriz, i+1, j-1, sol);
//        sol.push_back(patitos[j]);
//    } else if(palindromoMatriz[i+1][j] < palindromoMatriz[i][j-1]){
//        sol.push_back(patitos[i]);
//        reconstruirSolucionB(patitos, palindromoMatriz, i+1, j, sol);
//    } else {
//        sol.push_back(patitos[j]);
//        reconstruirSolucionB(patitos, palindromoMatriz, i, j-1, sol);
//    }
//}

bool resuelveCaso() {
    string palabra;
    cin >> palabra;
    if (!cin) {
        return false;
    }
    
    int longitudPalabra = (int)palabra.length();
    Matriz<int> palindromoMatriz(longitudPalabra, longitudPalabra, -1);
    cout << creadorPalindromo(palabra, 0, longitudPalabra-1, palindromoMatriz);
//    cout << " " << reconstruirSolucion(palabra, 0, longitudPalabra-1, palindromoMatriz) << '\n';
        cout << " " << palindromoMatriz << "\n";

//    string patitos;
//    reconstruirSolucion(palabra, 0, longitudPalabra-1, palindromoMatriz);


    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p40.txt");
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
