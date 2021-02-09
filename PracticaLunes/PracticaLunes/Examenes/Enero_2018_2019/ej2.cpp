
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
 Para resolver el problema utilizamos programación dinámica para evitar resolver múltiples veces un mismo problema.
 Para ello primero definimos el problema recursivamente.
 
 f(i,j) = Número máximo de veces que pueden comer las hermanas trozos iguales del pastel[i...j];
 f(i, j):
- f(i+1, j-1)+1 -> Si pastel[i] == pastel[j]
- max(f(i+2, j), f(i, j-2), f(i-1, j-1)) si pastel[i] != pastel[j]
 
 El coste en tiempo es O(N^2) siendo N el número de trozos, ya que tenemos que recorrer toda la matriz para encontrar la mejor solución.
 En cuanto a espacio el coste es O(N^2) siendo N el número de trozos, ya que utilizammos una matriz N*N.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int trozos_recursivo(vector<int> const& trozos, int i, int j, Matriz<int> & trozosMatriz) {
    if (i > j) {
        return 0;
    }
    
    int & res = trozosMatriz[i][j];

    if (res == -1) {
        if (i > j) {
            res = 0;
        } else if (i == j) {
            res = 1;
        } else if (trozos[i] == trozos[j]) {
            res = trozos_recursivo(trozos, i+1, j-1, trozosMatriz);
            if (trozos[i] != 0) { //El valor 0 indica que no tiene fruta, por lo tanto no tendríamos que añadir +1;
                res += 1;
            }
        } else {
            res = max(trozos_recursivo(trozos, i+2, j, trozosMatriz),
                      trozos_recursivo(trozos, i, j-2, trozosMatriz)); //Cogemos dos trozos del lado izquierdo, o cogemos 2 trozos del lado derecho.
            res = max(res, trozos_recursivo(trozos, i+1, j-1, trozosMatriz)); //O cogemos un trozo de cada lado y con suerte más adelante coincidirán los trozos.
        }
    }
    return res;
}

bool resuelveCaso() {
    
    // leer los datos de la entrada
    int numTrozos;
    cin >> numTrozos;
    
    if (!std::cin)  // fin de la entrada
        return false;
    
    vector<int> trozos;
    int value;
    for (int i = 0; i < numTrozos; i++) {
        cin >> value;
        trozos.push_back(value);
    }
    
    Matriz<int> trozosMatriz(numTrozos, numTrozos, -1);
    
    // resolver el caso posiblemente llamando a otras funciones
    int result = trozos_recursivo(trozos, 0, numTrozos-1, trozosMatriz);
    // escribir la solución
    cout << result << '\n';
    
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Enero_2018_2019/casos_p2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
