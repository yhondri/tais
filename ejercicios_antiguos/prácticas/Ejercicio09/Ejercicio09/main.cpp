//
//  main.cpp
//  Ejercicio09
//
//  Created by Yhondri on 18/10/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "Amigos.h"

using namespace std;

size_t getGrupoDeAmigosMayor(Grafo graph, int numVertices);

Grafo fillGraph(int numCiudadanos, int numPares) {
    Grafo grafo(numCiudadanos);
    while (numPares > 0) {
        int edge1, edge2;
        cin >> edge1;
        cin >> edge2;
        grafo.ponArista(--edge1, --edge2);
        numPares--;
    }
    return grafo;
}

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/prácticas/Ejercicio09/Ejercicio09/casos.txt"); //MacBook Pro
//    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio09/Ejercicio09/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        
        int numCiudadanos, numPares;
        cin >> numCiudadanos >> numPares;
        
        Grafo grafo = fillGraph(numCiudadanos, numPares);
        Amigos amigos(grafo);
        cout << amigos.maximo() << endl;;
        
        numCasos--;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

size_t getGrupoDeAmigosMayor(Grafo graph, int numVertices) {
    size_t max = 0;
    
    if (numVertices > 0) {
        numVertices--;
        
        bool marked[numVertices];
        
        while (numVertices > 0) {
            if (!marked[numVertices]) {
                Adys ad = graph.adj(numVertices);
                for (int i = 0; i < ad.size(); i++) {
                    marked[ad[i]] = true;
                }
                
                DepthFirstSearch browser(graph, numVertices);
                size_t numVerticesAdyacentes = browser.count();
                if (numVerticesAdyacentes > max) {
                    max = numVerticesAdyacentes;
                }
            }
            numVertices--;
        }
    }
    return max;
}
