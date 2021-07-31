//
//  main.cpp
//  Ejercicio31
//
//  Created by Yhondri on 10/1/18.
//  Copyright © 2018 Yhondri. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Matriz.h"

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 Tiene complejidad cuadrática O(n*m) ya que necesitamos recorrer una matriz de 2 dimensiones.
 Tiene complejidad cuadrática O(n*m) en cuanto a espacio, debido a que necesitamos una matriz de 2 dimensiones, donde n = al número de carácteres de la primera palabra
 y m = al número de carácteres de la segunda palabra.
 
 */

using namespace std;

#define MAX 1000

vector<string> readWords(string textToRead, char delim);
void encontrarSecuenciaMayor(const char *word1Array, const char *word2Array, size_t n, size_t m);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio31/Ejercicio31/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio31/Ejercicio31/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    string text, word1, word2;
    bool seguir = true;
    while (seguir) {
        
        getline(cin, text);
        if (cin) {
            vector<string> words = readWords(text, ' ');
            word1 = words.at(0);
            word2 = words.at(1);
//            word1 = "AGGTAB";
//            word2 = "GXTXAYB";
            const char *word1Array = word1.c_str();
            const char *word2Array = word2.c_str();

            encontrarSecuenciaMayor(word1Array, word2Array, word1.length(), word2.length());
            //cout << word1 << " --- " << word2 << endl;
        }
        else {
            seguir = false;
        }
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> readWords(string textToRead, char delim) {
    vector<string> elems;
    split(textToRead, delim, back_inserter(elems));
    return elems;
}

void printMochila(Matriz<int> mochilaDeSecuencia, int n, int m, const char *word1Array, const char *word2Array) {
    
    for (size_t i = 0; i <= n; i++) {
        for (size_t j = 0; j <= m; j++) {
            cout << mochilaDeSecuencia[i][j] << " ";
        }
        cout << endl;
    }
}

void encontrarSecuenciaMayor(const char *word1Array, const char *word2Array, size_t n, size_t m) {
    
    Matriz<int> mochilaDeSecuencia(n+1, m+1, 0);
    
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (word1Array[i-1] == word2Array[j-1]) {
                mochilaDeSecuencia[i][j] = mochilaDeSecuencia[i-1][j-1] + 1;
            } else {
                mochilaDeSecuencia[i][j] = max(mochilaDeSecuencia[i-1][j], mochilaDeSecuencia[i][j-1]) ;
            }
        }
    }
    
//    printMochila(mochilaDeSecuencia, n, m, word1Array, word2Array);
    cout << mochilaDeSecuencia[n][m] << endl;
}
