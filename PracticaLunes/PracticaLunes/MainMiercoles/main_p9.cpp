//
//  main_p9.cpp
//  PracticaMiércoles
//
//  Created by Yhondri on 21/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include <stdexcept>
#include <cmath>
#include "PriorityQueue.h"

using namespace std;

struct GrupoMusicos {
    
    float numMusicos;
    float partituras;
    //Nº de musico por parrtitura en el grupo.
    float grupoMayor;
    
    GrupoMusicos() : numMusicos(0), partituras(0), grupoMayor(0) {};
    GrupoMusicos(int musicos) : numMusicos(musicos), partituras(1), grupoMayor(musicos) {};
    
    void addPartitura() {
        partituras += 1;
        grupoMayor = numMusicos / partituras;
    }
    
    //Utilizamos ceil para redondear hacía arriba para cuando haya operaciones que no den números enteros.
    int getGrupoMayor() const {
        return ceil(grupoMayor);
    }
    
    const bool operator >(const GrupoMusicos& y) const {
        return grupoMayor > y.grupoMayor;
    }
};

/**
 El coste de calcular el atril más concurrido es log(N) debido a que es el coste mayor de las operaciones de mayor coste que realizamos en esta función que son push y pop, que en una cola de priroridad de montículo binario tiene coste log(N) en ambas operaciones.
 
 En el caso mejor el coste es 1 ya que es el coste de obtener el primer valor en una cola de prioridad cuya implementación es de montículo binario.
 */
long long calcularNumMusicosEnAtrilMasConcurrido(PriorityQueue<GrupoMusicos,
                                           greater<GrupoMusicos>>queue,
                                           int numPartituras) {
    if (queue.size() == numPartituras) {
        return queue.top().getGrupoMayor();
    }
    
    int partiturasRestantes = numPartituras - queue.size();

    while (partiturasRestantes > 0) {
        GrupoMusicos grupoMusicos = queue.top();
        queue.pop();
        grupoMusicos.addPartitura();
        queue.push(grupoMusicos);
        partiturasRestantes--;
    }
    
    return queue.top().getGrupoMayor();
}

/**
 Implementamos una estructura GrupoMusicos que va a tener los datos de cada grupo de músicos y además nos va a permitir saber cuántas partituras tenemos por cada grupo de instrumentos.
 En esta misma estructura implementamos el operador > (mayor) que nos permitirá ordenar dentro de una cola de prioridad los grupos de músicos.
 
 La operación de push tiene un coste log N en la implementación de colas de prioridad con montículo binario. 
 */
bool resuelveCaso() {
    int partituras, instrumentos;
    
    if (!(cin >> partituras)) {
        return false;
    }
    
    cin >> instrumentos;
    
    int musicos;
    PriorityQueue<GrupoMusicos, greater<GrupoMusicos>> grupoMusicosQueue;
    for (int i = 0; i < instrumentos; i++) {
        cin >> musicos;
        GrupoMusicos grupoMusicos(musicos);
        grupoMusicosQueue.push(grupoMusicos);
    }
    
    cout << calcularNumMusicosEnAtrilMasConcurrido(grupoMusicosQueue, partituras) << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p9.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
