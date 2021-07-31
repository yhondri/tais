//
//  main.cpp
//  Ejercicio10
//
//  Created by Yhondri on 25/10/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

#include <iostream>
#include "Grafo.h"
#include "GrafoBipartito.h"

using namespace std;

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 DNI: 51554391-Y
 
 <--------------------------------->
 
 Coste:

 Debido a que aprovechamos una búscqueda en profundidad, DFS, y en base a ello implementamos las funciones necesarias para detectar si nuestro grafo es bipartito,
 la solución tiene por tanto un coste O(V+E), ya que en el peor de los casos tendremos que visitar todos los vértices. 
 
 */

Grafo fillGraph(int numVertices, int numAristas) {
    Grafo grafo(numVertices);
    while (numAristas > 0) {
        int edge1, edge2;
        cin >> edge1 >> edge2;
        grafo.ponArista(edge1, edge2);
        numAristas--;
    }
    return grafo;
}

/**
 
 Resultados esperados de los casos de prueba:
 
 YES
 NO
 NO
 NO
 YES
 
 */

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio10/Ejercicio10/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio10/Ejercicio10/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numVertices;
    while (cin >> numVertices) {
        
        int numAristas;
        cin >> numAristas;
        
        Grafo grafo = fillGraph(numVertices, numAristas);
        GrafoBipartito grafoBipartito(grafo);
        
        grafoBipartito.esBipartito() ? cout << "SI" : cout << "NO";
        cout << endl;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
