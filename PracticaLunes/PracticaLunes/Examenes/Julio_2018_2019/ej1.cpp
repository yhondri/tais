
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
 
 El caso peor sería número baterías de 9V = Número baterías de 1.5V y todas con la misma capacidad. En este caso tendríamos que recorrer toda los elementos de las colas (habría baterías siempre) lo que nos daría como resultado un coste  O(N log N), donde N es el número de baterías.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

vector<long long> resuelveCaso(PriorityQueue<long long, greater<long long>> &priorityQue9V, PriorityQueue<long long, greater<long long>> &priorityQue1_5V, int numDrones) {
    vector<long long> totalHorasPorDia;
    while (!priorityQue9V.empty() && !priorityQue1_5V.empty()) {
        long long totalDia = 0;
        
        //Pilas no utilizadas ese finde y no agotadas las guardamos para el siguiente finde
        vector<long long> pilas9Restantes;
        vector<long long> pilas1_5Restantes;
        
        for (int i = 0; i < numDrones && !priorityQue9V.empty() && !priorityQue1_5V.empty(); i++) {
            long long bateria9V, bateria1_5V;
            bateria9V = priorityQue9V.top();
            priorityQue9V.pop();
            bateria1_5V = priorityQue1_5V.top();
            priorityQue1_5V.pop();
            
            if (bateria9V == bateria1_5V) {
                totalDia += bateria9V; //Pilas al cubo de reciclaje
            } else if(bateria9V > bateria1_5V) {
                totalDia += bateria1_5V;
                pilas9Restantes.push_back(bateria9V - bateria1_5V);
            } else {
                totalDia += bateria9V;
                pilas1_5Restantes.push_back(bateria1_5V - bateria9V);
            }
        }
        
        totalHorasPorDia.push_back(totalDia);
        
        for (auto value : pilas9Restantes) {
            priorityQue9V.push(value);
        }
        
        for (auto value : pilas1_5Restantes) {
            priorityQue1_5V.push(value);
        }
    }
    return totalHorasPorDia;
}

void rellenarQueue(int n, PriorityQueue<long long, greater<long long>> &queue) {
    long long value;
    for (int i = 0; i < n; i++) {
        cin >> value;
        queue.push(value);
    }
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int numDrones, numBaterias9V, numBaterias1_5V;
    cin >> numDrones >> numBaterias9V >> numBaterias1_5V;
   
   if (!std::cin)  // fin de la entrada
      return false;
    
    PriorityQueue<long long, greater<long long>> priorityQue9V;
    rellenarQueue(numBaterias9V, priorityQue9V);
    PriorityQueue<long long, greater<long long>> priorityQue1_5V;
    rellenarQueue(numBaterias1_5V, priorityQue1_5V);

   // resolver el caso posiblemente llamando a otras funciones
    vector<long long> totalHorasPorDia = resuelveCaso(priorityQue9V, priorityQue1_5V, numDrones);
   // escribir la solución
    for (auto value : totalHorasPorDia) {
        cout << value << " ";
    }
    
    cout << '\n';

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Julio_2018_2019/casos_p1.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
