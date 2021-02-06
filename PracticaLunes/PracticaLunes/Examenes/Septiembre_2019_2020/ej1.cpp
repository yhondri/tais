
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;
#include "PriorityQueue.h"

/*@ <answer>
  
 Para empezar si sólo hay 1 equipo no podemos jugar un partido ya que son necesario 2 equipos, por ello el número de gorras necesarias para el caso con 1 sólo equipo es 0.
 Si hay 2 o más equipos la implementación se basa en acumular el número de gorras necesarias por cada partido y añadir la suma de ambos equipos de nuevo a la cola, ya que el equipo ganador pasará de tener sus seguidos A + B el número de seguidores = C, de tal forma que en el siguiente partido el equipo ganador tendrá C seguidores.
 
 Coste:
 El coste de resolver el problema en el caso peor es O(N). Ya que vamos a tener que acceder a todos los elementos de la cola para poder calcular el número total de gorras necesarias. 
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

long long calcularNumGorrasNecesarias(PriorityQueue<long long>& equiposQue) {
    long long acumulador = 0, temporal;
    while (equiposQue.size() >= 2) {
        long long equipo1 = equiposQue.top();
        equiposQue.pop();
        long long equipo2 = equiposQue.top();
        equiposQue.pop();
        temporal = equipo1 + equipo2;
        acumulador += temporal;
        equiposQue.push(temporal);
    }
    
    return acumulador;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int numEquipos;
    cin >> numEquipos;
   if (numEquipos == 0)
      return false;
    
    PriorityQueue<long long> equiposQue;
    int value;
    for (int i = 0; i < numEquipos; i++) {
        cin >> value;
        equiposQue.push(value);
    }
    
   // resolver el caso posiblemente llamando a otras funciones
    long long minGorrasNecesarias = calcularNumGorrasNecesarias(equiposQue);
   
   // escribir la solución
    cout << minGorrasNecesarias << '\n';

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Septiembre_2019_2020/ej1.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
//   system("PAUSE");
#endif
   return 0;
}



