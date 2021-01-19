//
//  main_48.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 17/1/21.
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
    vector<int> tarea;
    int funcionarioIndex;
    int coste;
    int costeEstimado;
};

bool operator<(Nodo const& a, Nodo const& b) {
    return (a.costeEstimado > b.costeEstimado);
}

/**
 La estimación coge de cada funcionario la tarea con menor tiempo de las que faltan por escoger.
 */
int calculoEstimacion(vector<vector<int>> const& tareasFuncionarios, Nodo const& nodoX) {
    int estimacion = nodoX.coste;
    for (int i = nodoX.funcionarioIndex + 1; i < (int)tareasFuncionarios.size(); ++i) {
        int minTareaDisponible = INT_MAX; //De las tareas disponibles, intentaremos coger siempre la mínima del funiconario i.
        
        for (int j = 0; j < (int)tareasFuncionarios.size(); ++j) {
            if (nodoX.tarea[j] != -1) {
                continue;
            }
            int costeTarea = tareasFuncionarios[i][j];
            if (costeTarea < minTareaDisponible) {
                minTareaDisponible = costeTarea;
            }
        }
        estimacion += minTareaDisponible;
    }
    return estimacion;
}

void costeTrabajo(vector<vector<int>> const& tareasFuncionarios, vector<bool> & mejorSolucion, int& mejorCoste) {
    int numTareas = (int) tareasFuncionarios.size();
    
    //Obtenemos la estimación de cada nodo.
//    vector<int> estimacion = getEstimacion(tareasFuncionarios);

    Nodo nodoY;
    nodoY.tarea = vector<int>(numTareas, -1);
    nodoY.funcionarioIndex = -1;
    nodoY.coste = 0;
    nodoY.costeEstimado = calculoEstimacion(tareasFuncionarios, nodoY);
    priority_queue<Nodo> nodoQueue;
    nodoQueue.push(nodoY);
    mejorCoste = INT_MAX;

    //Iteramos sobre cada tarea. El algoritmo intentará escoger para cada tarea el funcionario que la pueda realizar.
    while (!nodoQueue.empty() && nodoQueue.top().costeEstimado < mejorCoste) {
        nodoY = nodoQueue.top();
        nodoQueue.pop();
        Nodo nodoX(nodoY);
        ++nodoX.funcionarioIndex; //Seleccionamos la tarea k.

        //Para la tarea k, intentamos ver que funcionario la puede realizar.
        //Esto viene a ser, para la tarea X0, ¿qué coste conllevaría que la realizara el funcionario 0, 1, .... n?
        //Conforme bajamos en el árbol, iremos aplicando la poda, como por ejemplo, un funcionario ya seleccionado en una rama, no se puede volver a seleccionar, o que el coste de esta nueva rama es superior que el mejor coste hasta ahora.
        for (int i = 0; i < numTareas; i++) {
            //Restricciones implícitas. Un mismo funcionario no puede realizar varias tareas, por ello necesitamos realizar marcaje de qué funcionario está ya seleccionado.
            if (nodoX.tarea[i] != -1) {
                continue;
            }
            
            nodoX.coste = nodoY.coste + tareasFuncionarios[nodoX.funcionarioIndex][i];
            if (nodoX.coste < mejorCoste) {
                nodoX.tarea = nodoY.tarea; //Nos aseguramos de restablecer el nodo.
                nodoX.tarea[i] = nodoX.funcionarioIndex;
                nodoX.costeEstimado = calculoEstimacion(tareasFuncionarios, nodoX);
                
                if (nodoX.funcionarioIndex == numTareas-1) {
                    mejorCoste = nodoX.coste;
                } else {
                    nodoQueue.push(nodoX);
                }
            }
        }
    }
        
    cout << mejorCoste << '\n';
}

bool resuelveCaso() {
    int numFuncionarios;
    cin >> numFuncionarios;
    if (numFuncionarios == 0) {
        return false;
    }
    
    vector<vector<int>> tareasFuncionarios(numFuncionarios, vector<int>());
    int value;
    for (int i = 0; i < numFuncionarios; i++) {
        for (int j = 0; j < numFuncionarios; j++) {
            cin >> value;
            tareasFuncionarios[i].push_back(value);
        }
    }
    
    vector<bool> mejorSolucion(numFuncionarios, false);
    int mejorCoste = 0;
    costeTrabajo(tareasFuncionarios, mejorSolucion, mejorCoste);
   
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p48.txt");
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

/**
 La estimación coge de cada funcionario la tarea con menor tiempo de las que faltan por escoger.
 */
//int calculoEstimacion(vector<vector<int>> const& tareasFuncionarios, Nodo const& nodoX) {
//    int estimacion = nodoX.coste;
//    vector<bool> seleccionado = nodoX.solucion;
//
//    for (int i = 0; i < (int)tareasFuncionarios.size(); ++i) {
//        if (i != nodoX.funcionarioIndex) {
//            int minTareaDisponible = INT_MAX; //De las tareas disponibles, intentaremos coger siempre la mínima del funiconario i.
//            int indexMinSeleccinado = 0;
//
//            for (int j = 0; j < (int)tareasFuncionarios.size(); ++j) {
//                if (!seleccionado[j]) {
//                    if (tareasFuncionarios[i][j] < minTareaDisponible) {
//                        indexMinSeleccinado = j;
//                        minTareaDisponible = tareasFuncionarios[i][j];
//                    }
//                }
//            }
//            seleccionado[indexMinSeleccinado] = true;
//            estimacion += minTareaDisponible;
//        }
//    }
//    return estimacion;
//}
