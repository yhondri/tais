//
//  main.cpp
//  Ejercicio28
//
//  Created by Yhondri  on 6/1/18.
//  Copyright © 2018 Yhondri . All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 Complejidad O(N^2) + n en cuanto al tiempo, debido a que necesitamos recorrer rellenar una matriz de 2 dimensiones, y además necesitamos recorrer 1 vez un vector para encontrar la solución.
 Complejidad O(N^2) + 2n, debido a que tenemos una matriz de 2 dimensiones donde introducimos los datos para resolver el problema, y además tenemos 2 vectores para guardar los datos del problema, que se refieren a las profundidade y el oro de cada cofre. 
 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"

using namespace std;

struct cofre {
    
public:
    cofre() : profundidad(0), oro(0) {}
    
    cofre(int profundidad, int oro) : profundidad(profundidad), oro(oro) {}
    
    int getOro() const {
        return oro;
    }
    
    int getProfundidad() const {
        return profundidad;
    }
    
private:
    int profundidad;
    int oro;
    
};

void cofresDeOro(vector<int> const& profundidades,vector<int> const& valorCofres, int capacidadTanque);
void printMatriz(Matriz<int> matriz);
void printVector(vector<cofre> cofres);
void printCofreSeleccionado(vector<int> profundidades, vector<int> valorCofres, vector<bool> cofresSeleccionados, int seleccionados, int valor);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio25/Ejercicio25/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio28/Ejercicio28/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int capacidadBotellaDeAire;
    
    while (cin >> capacidadBotellaDeAire) {
        int numCofres;
        cin >> numCofres;
        vector<int> profundidades;
        vector<int> valorCofres;
        profundidades.push_back(0);
        valorCofres.push_back(0);
        for (int i = 0; i < numCofres; i++) {
            int profundidad, oro;
            cin >> profundidad >> oro;
            profundidades.push_back(profundidad);
            valorCofres.push_back(oro);
        }
        cofresDeOro(profundidades, valorCofres, capacidadBotellaDeAire);
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void cofresDeOro(vector<int> const& profundidades,vector<int> const& valorCofres, int capacidadTanque) {
    size_t n = profundidades.size() - 1;
    capacidadTanque /= 3;
    Matriz<int> mochila(n+1, capacidadTanque+1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= capacidadTanque; ++j) {
            if (profundidades[i] > j) {
                mochila[i][j] = mochila[i-1][j];
            }
            else {
                mochila[i][j] = max(mochila[i-1][j], mochila[i-1][j-profundidades[i]] + valorCofres[i]);
            }
        }
    }
    
    int valor = mochila[n][capacidadTanque];
    
    int resto = capacidadTanque;
    int seleccionados = 0;
    vector<bool> cofresSeleccionados(n+1);
    for (size_t i = n; i >= 1; --i) {
        if (mochila[i][resto] == mochila[i-1][resto]) {
            cofresSeleccionados[i] = false;
        }
        else {
            cofresSeleccionados[i] = true;
            seleccionados++;
            resto = resto - profundidades[i];
        }
    }
    printCofreSeleccionado(profundidades, valorCofres, cofresSeleccionados, seleccionados, valor);

}

void printCofreSeleccionado(vector<int> profundidades, vector<int> valorCofres, vector<bool> cofresSeleccionados, int seleccionados, int valor) {
    cout << valor << endl << seleccionados << endl;
    for (int i = 1; i < profundidades.size(); i++) {
        if (cofresSeleccionados.at(i)) {
            cout << profundidades[i] << " " << valorCofres[i] << endl;
        }
    }
    cout << "----" << endl;
}







