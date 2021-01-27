//
//  main_51.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 20/1/21.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

struct Nodo {
    vector<int> productosCompradosEnSupermercado;
    vector<int> producto;
    int productoIndex;
    int coste;
    int costeEstimado;
};

bool operator<(Nodo const& a, Nodo const& b) {
    return (a.costeEstimado > b.costeEstimado);
}

/**
 La estimación coge de cada funcionario la tarea con menor tiempo de las que faltan por escoger.
 */
int calculoEstimacion(vector<vector<int>> const& tareasFuncionarios, Nodo const& nodoX, int const& numSupermercados, int const& numProductos) {
    int estimacion = nodoX.coste;
    for (int i = nodoX.productoIndex + 1; i < numSupermercados; ++i) {
        int minTareaDisponible = INT_MAX; //De los productos disponibles, intentaremos coger siempre el mínimo del supermercado i.
        for (int j = 0; j < numProductos; ++j) {
            if (nodoX.producto[j] != -1) { //El producto no está cogido
                continue;
            }
            
            int costeTarea = tareasFuncionarios[i][j];
            if (costeTarea < minTareaDisponible) {
                minTareaDisponible = costeTarea;
            }
        }
        if (minTareaDisponible != INT_MAX) {
            estimacion += minTareaDisponible;
        }
    }
    return estimacion;
}

void costeTrabajo(vector<vector<int>> const& productosSupermercados,
                  vector<bool> & mejorSolucion,
                  int& mejorCoste,
                  int const& numSupermercados,
                  int const& numProductos) {
    
    Nodo nodoY;
    nodoY.productosCompradosEnSupermercado = vector<int>(numSupermercados, -1);
    nodoY.producto = vector<int>(numProductos, -1);
    nodoY.productoIndex = -1;
    nodoY.coste = 0;
//    nodoY.costeEstimado = calculoEstimacion(productosSupermercados, nodoY, numSupermercados, numProductos);
    priority_queue<Nodo> nodoQueue;
    nodoQueue.push(nodoY);
    mejorCoste = INT_MAX;

    //Iteramos sobre cada tarea. El algoritmo intentará escoger para cada tarea el funcionario que la pueda realizar.
    // && nodoQueue.top().costeEstimado < mejorCoste
    while (!nodoQueue.empty()) {
        nodoY = nodoQueue.top();
        nodoQueue.pop();
        Nodo nodoX(nodoY);
        ++nodoX.productoIndex; //Seleccionamos el supermercado K.
        
        if (nodoX.productoIndex >= numProductos) {
            continue;
        }
        
        for (int i = 0; i < numSupermercados; i++) {
            //Restricciones implícitas. Ya se ha escogido el producto i o en un supermercado no puedes comprar más de 3 productos.
            if (nodoX.productosCompradosEnSupermercado[i] == 3) {
                continue;
            }
            
            nodoX.coste = nodoY.coste + productosSupermercados[i][nodoX.productoIndex];
            if (nodoX.coste < mejorCoste) {
                nodoX.productosCompradosEnSupermercado = nodoY.productosCompradosEnSupermercado; //Nos aseguramos de restablecer el nodo.
                nodoX.producto = nodoY.producto; //Nos aseguramos de restablecer el nodo.
                nodoX.productosCompradosEnSupermercado[i]++;
                nodoX.producto[nodoX.productoIndex] = i; //El producto i, lo hemos comprado en el supermercadoIndex.
                //nodoX.costeEstimado = calculoEstimacion(productosSupermercados, nodoX, numSupermercados, numProductos);

                if (nodoX.productoIndex == numSupermercados-1) {
                    mejorCoste = nodoX.coste;
                } else {
                    nodoQueue.push(nodoX);
                }
            }
        }
    }
        
    cout << mejorCoste << '\n';
}

void resuelveCaso() {
    int numCasos, numSupermercados, numProductos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++) {
        cin >> numSupermercados >> numProductos;
        vector<vector<int>> productosSupermercados(numSupermercados, vector<int>());
        int value;
        for (int i = 0; i < numSupermercados; i++) {
            for (int j = 0; j < numProductos; j++) {
                cin >> value;
                productosSupermercados[i].push_back(value);
            }
        }
        
        vector<bool> mejorSolucion(numProductos, false);
        int mejorCoste = 0;
        costeTrabajo(productosSupermercados, mejorSolucion, mejorCoste, numSupermercados, numProductos);
    }
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p51.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
//
    resuelveCaso();
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
