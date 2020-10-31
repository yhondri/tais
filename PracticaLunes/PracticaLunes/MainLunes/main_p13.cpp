
// Comentario general sobre la soluci—n,
// explicando c—mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Grafo.h"

using namespace std;

class ColocarGuardias {
private:
    std::vector<bool> visitados;
    std::vector<bool> colores;
    std::vector<int> menores;
    bool bipartito;
    int blanco;
    int negro;

    bool dfs(Grafo const& g, int v) {
        visitados[v] = true;
        for (int w : g.ady(v)) {
            if (!visitados[w]) {
                colores[w] = !colores[v];
                if (colores[w] == true) {
                    blanco++;
                } else {
                    negro++;
                }
                if (!dfs(g, w)) {
                    return false;
                }
            } else if (colores[w] == colores[v]) {
                return false;
            }
        }

        return true;
    }

    bool colorear() {
        if (bipartito) {
            if (blanco > negro) {
                menores.push_back(negro);
            } else {
                menores.push_back(blanco);
            }
            return true;
        } else {
            return false;
        }
    }

public:
    ColocarGuardias(Grafo const& g) : visitados(g.V(), false), colores(g.V(), false), bipartito(true), blanco(0), negro(0) {
        for (int i = 0; i < g.V() && bipartito; i++) {
            if (!visitados[i]) {
                colores[i] = true;
                blanco++;
                bipartito = dfs(g, i);
                colorear();
                blanco = 0;
                negro = 0;
            }
        }
    }

    bool esPosible() {
        return bipartito;
    }

    int minimo() {
        int suma = 0;
        for (int i = 0; i < menores.size(); i++) {
            suma += menores[i];
        }
        return suma;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci—n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V);
    int auxV, auxW;
    for (int i = 0; i < A; i++) {
        cin >> auxV >> auxW;
        g.ponArista(auxV - 1, auxW - 1);
    }

    ColocarGuardias cg(g);

    // escribir sol
    if (!cg.esPosible()) {
        cout << "IMPOSIBLE" << '\n';
    } else {
        cout << cg.minimo() << '\n';
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p13.txt");
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
