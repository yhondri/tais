
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
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

struct Battery {
    int identificador;
    int siguienteCarga;
    int cargaTotal; //Vida últil de la batería tras cada carga.
};

bool operator<(Battery const& lhs, Battery const& rhs) {
    if (lhs.siguienteCarga == rhs.siguienteCarga) {
        return lhs.identificador < rhs.identificador;
    }
    return lhs.siguienteCarga < rhs.siguienteCarga;
}

void resolverProblema(PriorityQueue<Battery> batteryQueue,
                      PriorityQueue<Battery> batteryRepuestoQueue,
                      int const& zPerdidaVidaUtil,
                      int const& tTiempoConsulta,
                      int const& numBateriasNecesariasFuncionamiento) {
    
    Battery battery = batteryQueue.top();
    
    for (int i = 0; i <= tTiempoConsulta && !batteryQueue.empty(); i++) {
        while (battery.siguienteCarga == i && !batteryQueue.empty()) { //Se nos puede quedar la cola vacía.
            batteryQueue.pop();
            
            if ((battery.cargaTotal-zPerdidaVidaUtil) > 0) { //Volvemos a meter
                battery.cargaTotal -= zPerdidaVidaUtil;
                battery.siguienteCarga = i+battery.cargaTotal;
                batteryQueue.push(battery);
            } else {
                //Sacamos batería de repuesto si es posible
                if (!batteryRepuestoQueue.empty()) {
                    Battery batteryRepuesto = batteryRepuestoQueue.top();
                    batteryRepuestoQueue.pop();
                    batteryRepuesto.siguienteCarga += i;
                    batteryQueue.push(batteryRepuesto);
                }
            }
            
            if (!batteryQueue.empty()) {
                battery = batteryQueue.top();
            }
        }
    }
    
    if (numBateriasNecesariasFuncionamiento == batteryQueue.size()) {
        cout << "CORRECTO" << '\n';
    } else if (!batteryQueue.empty()) {
        cout << "FALLO EN EL SISTEMA" << '\n';
    } else {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE" << '\n';
    }
    
    while (!batteryQueue.empty()) {
        battery = batteryQueue.top();
        batteryQueue.pop();
        cout << battery.identificador << " " << battery.siguienteCarga << '\n';
    }
    
    cout << "---\n";
}

bool resuelveCaso() {
   // leer los datos de la entrada
    int numBateriasNecesariasFuncionamiento, duracionBateria;
    cin >> numBateriasNecesariasFuncionamiento;
    
    if (!std::cin)  // fin de la entrada
       return false;
    
    PriorityQueue<Battery> batteryQueue;
    for (int i = 0; i < numBateriasNecesariasFuncionamiento; i++) {
        cin >> duracionBateria;
        batteryQueue.push({i+1, duracionBateria, duracionBateria});
    }
    
    int numBateriasRepuesto;
    cin >> numBateriasRepuesto;
    int identificadorBateriaRepuestoInicial = numBateriasRepuesto;
    
    PriorityQueue<Battery> batteryRepuestoQueue;
    int identificador;
    for (int i = 1; i <= numBateriasRepuesto; i++) {
        cin >> duracionBateria;
        identificador = i + identificadorBateriaRepuestoInicial + 1;
        batteryRepuestoQueue.push({identificador, duracionBateria, duracionBateria});
    }
    
    int zPerdidaVidaUtil, tTiempoConsulta;
    cin >> zPerdidaVidaUtil >> tTiempoConsulta;
   
   // resolver el caso posiblemente llamando a otras funciones
   // escribir la solución
    resolverProblema(batteryQueue, batteryRepuestoQueue, zPerdidaVidaUtil, tTiempoConsulta, numBateriasNecesariasFuncionamiento);

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/Examenes/Enero_2019_2020/ej1.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
#endif
   return 0;
}
