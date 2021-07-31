//
//  main.cpp
//  Ejercicio32
//
//  Created by Yhondri on 17/1/18.
//  Copyright © 2018 Yhondri. All rights reserved.
//

#include <iostream>
#include "GrafoDirigido.h"
#include "Matriz.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 */

#define MAX 10000

vector<string> readWords(string textToRead, char delim);
int getVerticePersona(string persona, map <string, int> &personas, int &acumuladorPersonas);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio32/Ejercicio32/casos.txt"); //MacBook Pro
    //ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio32/Ejercicio32/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    string text, nombrePersona1, nombrePersona2;
    int numPersonas, numRelaciones;
    bool seguir = true;
    while (seguir) {
        
        cin >> numPersonas >> numRelaciones;
           // empty map container

        if (cin) {
              map <string, int> personasMap;
            GrafoDirigido grafo(numPersonas);
            int acumuladorPersonas = 0;
            for(int i = 0; i < numRelaciones; i++) {
                cin >> nombrePersona1 >> nombrePersona2;
                int verticePersona1, verticePersona2;
                verticePersona1 = getVerticePersona(nombrePersona1, personasMap, acumuladorPersonas);
                verticePersona2 = getVerticePersona(nombrePersona2, personasMap, acumuladorPersonas);
                grafo.ponArista(verticePersona1, verticePersona2);
            }
            
            grafo.print();
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

//UTILIZAR GRAFO DIRIGIDO VALORADO
void calcularGradoDeSeparacion(GrafoDirigido grafoPersonas) {
    size_t numVertices = grafoPersonas.V();
    size_t numAristas = grafoPersonas.E();
    
    Matriz<int> grafo(numVertices+1, numVertices+1, MAX);
    for (size_t i = 1; i <= numVertices; ++i) {
        grafo[i][i] = 0;
    }
    size_t u, v; int coste;
    for (size_t i = 1; i <= numAristas; ++i) { // leer aristas
        cin >> u >> v >> coste;
        grafo[u][v] = coste;
    }

}

int getVerticePersona(string persona, map <string, int> &personas, int &acumuladorPersonas) {
    int vertice = 0;
    if (personas.count(persona) == 1) {
        vertice = personas.at(persona);
    } else {
        personas[persona] = acumuladorPersonas;
        vertice = acumuladorPersonas;
        acumuladorPersonas++;
    }
    return vertice;
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
