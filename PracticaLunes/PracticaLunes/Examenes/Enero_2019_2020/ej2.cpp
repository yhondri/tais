
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class DetectorDeCiclos {
private:
    vector<bool> visitado;
    vector<int> anterior;
    vector<bool> apilado;
    bool hayCiclo;
    std::deque<int> _orden; // ordenación topológica
    
public:
    DetectorDeCiclos(Digrafo const& grafo): visitado(grafo.V(), false), anterior(grafo.V()), apilado(grafo.V(), false), hayCiclo(false) {
        for (int v = 0; v < grafo.V(); v++) {
            if (!visitado[v]) {
                dfs(grafo, v);
            }
        }
    }
    
    void dfs(Digrafo const& grafo, int vertice) {
        apilado[vertice] = true;
        visitado[vertice] = true;
        for (int w : grafo.ady(vertice)) {
            if (hayCiclo) {
                return;
            }
            
            if (!visitado[w]) {
                anterior[w] = vertice;
                dfs(grafo, w);
            } else if(apilado[w]) {
                hayCiclo = true;
            }
        }
        _orden.push_front(vertice);
        apilado[vertice] = false;
    }
    
    bool existeCiclo() const {
        return hayCiclo;
    }
    
    deque<int> const& getOrden() const {
        return _orden;
    }
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int nTareas;
    cin >> nTareas;
   
   if (!std::cin)  // fin de la entrada
      return false;
    
    Digrafo grafo(nTareas);
    int mRelaciones;
    cin >> mRelaciones;
    int v, w;
    for (int i = 0; i < mRelaciones; i++) {
        cin >> v >> w;
        grafo.ponArista(v-1, w-1);
    }
   
   // resolver el caso posiblemente llamando a otras funciones
    DetectorDeCiclos detectorDeCiclos(grafo);
   // escribir la solución
    if (detectorDeCiclos.existeCiclo()) {
        cout << "Imposible" << '\n';
    } else {
        for (int v : detectorDeCiclos.getOrden()) {
            cout << v + 1 << " ";
        }
        cout << '\n';
    }

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Enero_2019_2020/ej2.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
