//
//  main.cpp
//  Ejercicio8
//
//  Created by Yhondri  on 15/10/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include "PriorityQueue.h"

using namespace std;

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 DNI: 51554391-Y
 
 <--------------------------------->
 
 Coste:
 
 Coste nlogn sujeto al númeor de partituras disponible para repartir. El coste logarímico se debe a las operaciones push y pop
 que utilizamos para insertar datos en la cola.

 */

struct GrupoInstrumento {
    
private:
    float instrumentos;
    float partituras;
    float grupoMayor;
    
public:
    
    GrupoInstrumento() : instrumentos(0), partituras(0), grupoMayor(0) {};
    GrupoInstrumento(size_t instrumentos) : instrumentos(instrumentos), partituras(1), grupoMayor(instrumentos) {};
    
    void addPartitura() {
        partituras += 1;
        grupoMayor = instrumentos / partituras;
    }
    
    int getGrupoMayor() const {
        return ceil(grupoMayor);
    }
    
    const bool operator >(const GrupoInstrumento& y) const {
        return grupoMayor > y.grupoMayor;
    }
};

long long numMusicosEnAtrilMasConcurrido(PriorityQueue<GrupoInstrumento, std::greater<GrupoInstrumento>>queue, size_t numInstrumentos);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio8/Ejercicio8/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numPartituras, numInstrumentos, nuevoElemento;
    while (cin >> numPartituras) {
        cin >> numInstrumentos;
        
        PriorityQueue<GrupoInstrumento, std::greater<GrupoInstrumento>>queue;
        
        for (int i = 0; i < numInstrumentos; i++) {
            cin >> nuevoElemento;
            GrupoInstrumento nuevoGrupo(nuevoElemento);
            queue.push(nuevoGrupo);
        }
        
        cout << numMusicosEnAtrilMasConcurrido(queue, numPartituras) << endl;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void showQueueValues(PriorityQueue<long long, std::greater<long long>>queue) {
    while (!queue.empty()) {
        cout << queue.top() << " ";
        queue.pop();
    }
    cout << "FIN" << endl;
}

long long numMusicosEnAtrilMasConcurrido(PriorityQueue<GrupoInstrumento, std::greater<GrupoInstrumento>>queue, size_t numPartituras) {
    if (queue.size() == numPartituras) {
        return queue.top().getGrupoMayor();
    }
    long long partiturasRestantes = numPartituras - queue.size();
    while (partiturasRestantes > 0) {
        GrupoInstrumento maxValue = queue.top();
        queue.pop();
        maxValue.addPartitura();
        queue.push(maxValue);
        partiturasRestantes--;
        ////showQueueValues(queue);
    }
    return queue.top().getGrupoMayor();
}
