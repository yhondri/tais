
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class ArbolLibre {
private:
    vector<bool> visitado;
    vector<int> anterior;
    int numVerticesVisitados;
    bool existeCiclo;
    int numVerticesGrafo;
    
    void dfs(Grafo const& grafo, int vertice) {
        visitado[vertice] = true;
        numVerticesVisitados++;
        for (int w : grafo.ady(vertice)) {
            if (!visitado[w]) {
                anterior[w] = vertice;
                dfs(grafo, w);
            } else if (anterior[vertice] != w) {
                existeCiclo = true;
            }
        }
    }
    
public:
    ArbolLibre(Grafo const& g, int source): visitado(g.V(), false), anterior(g.V()), numVerticesVisitados(0), existeCiclo(false), numVerticesGrafo(g.V()) {
        dfs(g, source);
    }
    
    bool esUnArbolLibre() {
        return !existeCiclo && (numVerticesVisitados == numVerticesGrafo);
    }
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int numVertices, numAristas;
    cin >> numVertices >> numAristas;
    
   if (!std::cin)  // fin de la entrada
      return false;
    
    Grafo mGrafo(numVertices);
    int v, w;
    for (int i = 0; i < numAristas; i++) {
        cin >> v >> w;
        mGrafo.ponArista(v, w);
    }
   
   // resolver el caso posiblemente llamando a otras funciones
    ArbolLibre arbolLibre(mGrafo, 0);
   
   // escribir la solución
    if (arbolLibre.esUnArbolLibre()) {
        cout << "SI" << '\n';
    } else {
        cout << "NO" << '\n';
    }

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/ej2.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
