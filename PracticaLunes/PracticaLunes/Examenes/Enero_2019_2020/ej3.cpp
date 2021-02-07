
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
 
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 Para solucionar el problema de forma eficiente he utilizado de forma.
 En primer lugar planteamos el problmea de forma recursiva.
 
 - grupos(i, j) = Número máximo de grupos que podré ver, teniendo como límite presupuestario j y considerando el coste de los festivales i.
  
 - grupos(i, j)
    1-. grupos(i-1, j); Si Ci > J (si el coste de festival es mayor al del presupuesto actual, no podemos asistir a ese festival).
    2-. max (grupos(i-1, j), grupos(i-1, j-Ci) + grupos[i]); Si Ci < j, probamos a no ir al festival, o a ir al festival.
 
 casos base:
 grupos(0, j) = 0 --- 0 <= j <= Presupuesto
 grupos(i, 0) = 0 --- 0 <= i <= Festivales
 
 Esto nos lleva a utilizar programación dinámica ya que a partir de la implementación recursiva podríamos incurrir en resolver varias veces un mismo problema.
 Para ello creamos una matriz, cuyo numFilas = numFestivales y su numColumnas = Presupuesto.
 De esta forma aplicamos de forma recursiva el problema anteriormente planteado almacenando los resultados de los subproblemas en la matriz para no repetir su cálculo.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Festival {
    int grupos;
    int coste;
};

int calculadorCosteRecursivo(vector<Festival> const& festivales, int i, int j, Matriz<int> &costeMatriz) {
    if (costeMatriz[i][j] != -1) { //Ya hemos resuelto este subproblema.
        return costeMatriz[i][j];
    }
    
    if (i == 0 || j == 0) { //No hay presupuesto o festivales.
        costeMatriz[i][j] = 0;
    } else if(festivales[i-1].coste > j) { //No vamos a ese concierto
        costeMatriz[i][j] = calculadorCosteRecursivo(festivales, i-1, j, costeMatriz);
    } else { //Probamos a no ir a ese concierto y a sí ir para ver con qué camino obtendremos mayor beneficio.
        costeMatriz[i][j] = max(calculadorCosteRecursivo(festivales, i-1, j, costeMatriz),
                                calculadorCosteRecursivo(festivales, i-1, j-festivales[i-1].coste, costeMatriz) + festivales[i-1].grupos);
    }
    
    return costeMatriz[i][j];
}

bool resuelveCaso() {
    
    // leer los datos de la entrada
    int pPresupuesto, nNumeroFestivales;
    cin >> pPresupuesto >> nNumeroFestivales;
    
    if (!std::cin)  // fin de la entrada
        return false;
    
    vector<Festival> festivales;
    int grupo, coste;
    for (int i = 0; i < nNumeroFestivales; i++) {
        cin >> grupo >> coste;
        festivales.push_back({grupo, coste});
    }
    
    Matriz<int> costeMatriz(nNumeroFestivales+1, pPresupuesto+1, -1);
    
    // resolver el caso posiblemente llamando a otras funciones
    int resultado = calculadorCosteRecursivo(festivales, nNumeroFestivales, pPresupuesto, costeMatriz);
    // escribir la solución
    cout << resultado << '\n';
    
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Enero_2019_2020/ej3.txt");
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
