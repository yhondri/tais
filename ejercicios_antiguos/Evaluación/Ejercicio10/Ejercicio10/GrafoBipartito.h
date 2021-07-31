//
//  GrafoBipartito.h
//  Ejercicio10
//
//  Created by Yhondri  on 28/10/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//
#include <iostream>
#include "Grafo.h"

using namespace std;

class GrafoBipartito {
    
public:
    
    GrafoBipartito(Grafo const& grafo) : marcados(grafo.V(), false), colorArray(grafo.V(), -1), isBipartite(true) {
        colorArray[0] = 1; //Coloreamos nuestro primer vértice, de esta forma sus vértices adyacentes se colorearán de otro color y asís sucesivamente.
        for (size_t v = 0; v < grafo.V() && isBipartite; v++) {
            if (!marcados[v]) {
                dfs(grafo, v);
            }
        }
    }
    
    bool esBipartito() const {
        return isBipartite;
    }
    
private:
    
    //Booleano que nos dice si nuestro grafo es o no bipartito.
    bool isBipartite;
    
    //Array de booleanos que lleva marcados los vértices visitados.
    vector<bool> marcados;
    
    /**
     Crea un array de colores para guardar los colores asignado a todos los vértices. Los vértices serán los índices del array.
     El valor -1 de colorArray[i], índica que no se ha asignado ningún color al vértice.
     El valor 1 indica el primer color.
     El valor 0 índica el segundo color.
     */
    vector<int> colorArray;
    
    void dfs(Grafo const& grafo, size_t v) {
        marcados[v] = true;
        for (size_t w : grafo.adj(v)) {
            if (!marcados[w] && colorArray[w] == -1) {
                colorArray[w] = 1 - colorArray[v];
                dfs(grafo, w);
            }
            else if(colorArray[v] == colorArray[w]) {
                isBipartite = false;
                break;
            }
        }
    }
};

