
/*@ <answer>
 *
 * Nombre y Apellidos: Yhondri Josué Acosta Novas
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"

using namespace std;

/*@ <answer>
 
 En primer lugar he creado una struct llamada Battery para poder manjear los datos de la batería (id, momento en el que le toca cargarse y la carga máxima que puede obtener tras cada carga).
Como estructura de datos he utilizado una PriorityQue para poder obtener ordenadas las baterías según la carga restante y el identificador (requisitos del enunciado).
 
 La solución entonces conciste en iterar sobre cada elemento de la cola batteryQueue (que contiene las baterías que se están utilizando en ese momento) y obtener el tiempo de su siguiente carga. En este punto vemos si hemos llegado al T tiempo de verificación, en caso contrario comprobamos si podemos recargar esa batería o en caso contrario si podemos añadir una batería de repuesto.
 En el momento que hayamos alcanzado el tiempo T o no nos queden más baterías (ya sean iniciales o de repuesto), salimos del bucle y mostramos los resultados en base a las baterías que hayan quedado en la cola.
 
El caso peor sería Z = 1 en este caso tendríamos que recorrer toda los elementos de las colas (habría baterías siempre) lo que nos daría como resultado un coste  O(T log B).
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Battery {
    long long identificador;
    long long siguienteCarga;
    long long cargaTotal; //Vida últil de la batería tras cada carga.
};

bool operator<(Battery const& lhs, Battery const& rhs) {
    if (lhs.siguienteCarga == rhs.siguienteCarga) {
        return lhs.identificador < rhs.identificador;
    }
    return lhs.siguienteCarga < rhs.siguienteCarga;
}

void resolverProblema(PriorityQueue<Battery>& batteryQueue,
                      queue<Battery>& batteryRepuestoQueue,
                      int const& zPerdidaVidaUtil,
                      int const& tTiempoConsulta,
                      int const& numBateriasNecesariasFuncionamiento) {
    
    Battery battery = batteryQueue.top();
    long long siguienteTiempo = battery.siguienteCarga;
    while (siguienteTiempo <= tTiempoConsulta && !batteryQueue.empty()) {
        batteryQueue.pop();
        
        if ((battery.cargaTotal-zPerdidaVidaUtil) > 0) { //Volvemos a meter
            battery.cargaTotal -= zPerdidaVidaUtil;
            battery.siguienteCarga = siguienteTiempo + battery.cargaTotal;
            batteryQueue.push(battery);
        } else if (!batteryRepuestoQueue.empty()) {
            Battery batteryRepuesto = batteryRepuestoQueue.front();
            batteryRepuestoQueue.pop();
            batteryRepuesto.siguienteCarga = siguienteTiempo + batteryRepuesto.siguienteCarga;
            batteryQueue.push(batteryRepuesto);
        }
        
        if (!batteryQueue.empty()) {
            battery = batteryQueue.top();
            siguienteTiempo = batteryQueue.top().siguienteCarga;
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
    
    cout << "---" << '\n';
}

bool resuelveCaso() {
   // leer los datos de la entrada
    int numBateriasNecesariasFuncionamiento, duracionBateria;
    cin >> numBateriasNecesariasFuncionamiento;
    
    if (!std::cin)  // fin de la entrada
       return false;
    
    PriorityQueue<Battery> batteryQueue;
    for (int i = 1; i <= numBateriasNecesariasFuncionamiento; i++) {
        cin >> duracionBateria;
        batteryQueue.push({i, duracionBateria, duracionBateria});
    }
    
    int numBateriasRepuesto;
    cin >> numBateriasRepuesto;
    
    queue<Battery> batteryRepuestoQueue;
    int identificador = numBateriasNecesariasFuncionamiento + 1;
    for (int i = 1; i <= numBateriasRepuesto; i++) {
        cin >> duracionBateria;
        batteryRepuestoQueue.push({identificador, duracionBateria, duracionBateria});
        ++identificador;
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
