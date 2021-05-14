
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1000000000;

struct Bombilla {
    int potencia;
    int coste;
};

bool resuelveCaso() {
    
    // leer los datos de la entrada
    int numBombillas, potenciaMaxima, potenciaMinima;
    cin >> numBombillas >> potenciaMaxima >> potenciaMinima;
    
    if (!std::cin)  // fin de la entrada
        return false;
    
    vector<Bombilla> bombillas;
    int value;
    for (int i = 0; i < numBombillas; i++) {
        cin >> value;
        bombillas.push_back({value, 0});
    }
    
    for (int i = 0; i < numBombillas; i++) {
        cin >> value;
        bombillas[i].coste = value;
    }
    
    // resolver el caso posiblemente llamando a otras funciones
    
    Matriz<int> minBombillasMatriz(numBombillas, potenciaMaxima+1, INF);
    minBombillasMatriz[0][0] = 0;

    for (int i = 1; i <= numBombillas-1; ++i) {
        minBombillasMatriz[i][0] = 0;
        for (int j = 1; j <= potenciaMaxima; i++) {
            if (bombillas[i].potencia > j) {
                minBombillasMatriz[i][j] = minBombillasMatriz[i-1][j];
            } else {
                minBombillasMatriz[i][j] = min(minBombillasMatriz[i-1][j], minBombillasMatriz[i][j - bombillas[i].potencia] + bombillas[i].coste);
            }
        }
    }
    
    int costeMinimo = minBombillasMatriz[numBombillas-1][potenciaMinima];
    int potenciaIndex = 0;
    for (int i = potenciaMinima; i <= potenciaMaxima; ++i) {
        if (costeMinimo > minBombillasMatriz[numBombillas-1][i]) {
            costeMinimo = minBombillasMatriz[numBombillas-1][i];
            potenciaIndex = i;
        }
    }
    
    // escribir la solución
    
    if (costeMinimo == INF) {
        cout << "IMPOSIBLE" << '\n';
    } else {
        cout << costeMinimo << " " << potenciaIndex;
    }
    
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.


int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Julio_2018_2019/casos_p3.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
