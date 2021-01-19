
// Grupo 15

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase

using namespace std;

struct monedas {
    int valor;
    int cantidad;
};

const int INF = 10000000;

// Funci—n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int calculoMonedas(vector<monedas> monedas, const int precio) {
    int tam = (int)monedas.size();
    Matriz<int> matriz(tam + 1, precio + 1, INF);
    matriz[0][0] = 0;
    for (int i = 1; i <= tam; i++) {
        matriz[i][0] = 0;
        for (int j = 1; j <= precio; j++){
            matriz[i][j] = matriz[i - 1][j];
            if (j >= monedas[i - 1].valor) {
                int aux = INF;
                //j - k * monedas[i - 1].valor ===> Lo que nos queda por pagar.
                for (int k = 1; k <= monedas[i - 1].cantidad && j - k * monedas[i - 1].valor >= 0; k++) {
                    aux = matriz[i - 1][j - k * monedas[i - 1].valor] + k;
                    if (aux < matriz[i][j]) {
                        matriz[i][j] = aux;
                    }
                }
            }
        }
    }

    return matriz[tam][precio];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<monedas> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].valor;
    }
    for (int i = 0; i < N; i++) {
        cin >> v[i].cantidad;
    }

    int precio;
    cin >> precio;

    int sol = calculoMonedas(v, precio);

    // escribir sol
    if (sol == INF) cout << "NO" << '\n';
    else cout << "SI " << sol << '\n';
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p46.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
