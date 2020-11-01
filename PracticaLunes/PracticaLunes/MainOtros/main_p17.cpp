//
//  main_p17.cpp
//  PracticaLunes
//
//  Created by Yhondri on 01/11/2020.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <deque>
#include "Digrafo.h"

using namespace std;

class OrdenadorDeTareas {
private:
    std::vector<bool> visitado; // visitado[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> anterior; // anterior[v] = vértice anterior en el camino a v
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool hayCiclo;
    deque<int> tareasOrdenadas;
    
    void dfs(Digrafo const& digrafo, int v) {
        apilado[v] = true;
        visitado[v] = true;

        for (int w : digrafo.ady(v)) {
            if (hayCiclo) {
                return;
            }
            
            if (!visitado[w]) {
                anterior[w] = v;
                dfs(digrafo, w);
            } else if(apilado[w]) {
                hayCiclo = true;
            }
            
        }
        apilado[v] = false;
        tareasOrdenadas.push_front(v); //Orden topológico ya que las tareas se tienen que ordenar según una restricciones de procedencia, en este caso, algunas tareas no se pueden realizar si no se han realizdo otras antes. 
    }
    
public:
    OrdenadorDeTareas(Digrafo const& digrafo) : visitado(digrafo.V(), false), anterior(digrafo.V()), apilado(digrafo.V(), false), hayCiclo(false) {
        
        for (int v = 0; v < digrafo.V(); ++v) {
            if (!visitado[v]) {
                dfs(digrafo, v);
            }
        }
    }
    
    bool esPosibleOrdenarTareas() {
        return !hayCiclo;
    }
    
    deque<int> const& getTareasOrdenadas() {
        return tareasOrdenadas;
    }
};

bool resuelveCaso() {
    Digrafo tareas(cin, 1);

    if (!std::cin) {
        return false;
    }
    
    OrdenadorDeTareas ordenadorDeTareas(tareas);
    
    if (ordenadorDeTareas.esPosibleOrdenarTareas()) {
        deque<int> tareas = ordenadorDeTareas.getTareasOrdenadas();
        while(!tareas.empty()) {
            cout << tareas.front() + 1 << " ";
            tareas.pop_front();
        }
    } else {
        cout << "Imposible";
    }
    
    cout << '\n';
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p17.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
//    system("PAUSE");
#endif
    return 0;
}
