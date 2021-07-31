//
//  Amigos.h
//  Ejercicio09
//
//  Created by Yhondri  on 24/10/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

#include <iostream>
#include "Grafo.h"

using namespace std;

class Amigos {
    
public:
    
    Amigos(Grafo const& grafo) : marcados(grafo.V(), false), maxi(0) {
        for (size_t v = 0; v < grafo.V(); v++) {
            if (!marcados[v]) {
                size_t tam = 0;
                dfs(grafo, v, tam);
                if (tam > maxi) { //Hacemos la pregunt aquí para que se puedan comparar los vértices sin adyacentes, en ese caso su componente conexa es 1. 
                    maxi = tam;
                }
            }
        }
    }
    
    //Devuelve la mayor componente conexa
    size_t maximo() const {
        return maxi;
    }
    
private:
    
    //Variable donde guardaremos aquellos "amigos/nodos" que ya hemos visitado.
    vector<bool> marcados;
    
    //Mayor componente conexa
    size_t maxi;
    
//    Calcula recursivamente la componente conexa del grafo y el nodo en la posición v.
//    Si la componente es mayor que la calculada hasta ahora, pasa a ser la nueva componenente conexa mayor.
    void dfs(Grafo const& grafo, size_t v, size_t& tam) {
        marcados[v] = true;
        ++tam;
        for (size_t w : grafo.adj(v)) {
            if (!marcados[w]) {
                dfs(grafo, w, tam);
            }
        }
    }
};
