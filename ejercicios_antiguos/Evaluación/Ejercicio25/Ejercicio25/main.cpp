//
//  main.cpp
//  Ejercicio25
//
//  Created by Yhondri  on 26/11/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 Coste lineal dependiendo del número de películas que se proyectarán.
 Esto se debe a que utilizamos una cola de prioridad que se recorre 1 solo una vez.
 
 */

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct conferencia {
    
    conferencia() : horaInicio(0), horaFin(0) {
        isInitialized = false;
    }
    
    conferencia(int horaInicio, int horaFin) : horaInicio(horaInicio), horaFin(horaFin) {
        isInitialized = true;
    }
    
    bool operator<(const conferencia& h) const {
        return (horaInicio < h.horaInicio);
    }
    
    bool getIsInitialized() {
        return isInitialized;
    }
    
    int getHoraInicio() {
        return horaInicio;
    }
    
    int getHoraFin() {
        return horaFin;
    }
    
private:
    
    int horaInicio;
    int horaFin;
    bool isInitialized;
};

class ComparadorHoraFin {
    
public:
    
    bool operator() (conferencia &a, conferencia &b) {
        return (a.getHoraFin() < b.getHoraFin());
    }
};

void calcularSalasNecesarias(PriorityQueue<conferencia>conferencias, size_t numConferencias);


int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio25/Ejercicio25/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio25/Ejercicio25/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    size_t numConferencias;
    
    while ((cin >> numConferencias) && numConferencias!= 0) {
        
        PriorityQueue<conferencia>conferencias(0);
        
        for (int i = 0; i < numConferencias; i++) {
            int horaInicio, horaFin;
            cin >> horaInicio >> horaFin;
            conferencia nuevaConferencia(horaInicio, horaFin);
            conferencias.push(nuevaConferencia);
        }
        calcularSalasNecesarias(conferencias, numConferencias);
        //        print(films);
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void calcularSalasNecesarias(PriorityQueue<conferencia>conferencias, size_t numConferencias) {
    
    int salasNecesarias = 1;
    PriorityQueue<conferencia, ComparadorHoraFin>conferenciasSinFinalizar;
    conferenciasSinFinalizar.push(conferencias.top());
    conferencias.pop();
    
    while(!conferencias.empty()) {
        
        conferencia nuevaConferencia = conferencias.top();
        conferencia conferenciaSinFinalizar = conferenciasSinFinalizar.top();
        
        if (conferenciaSinFinalizar.getHoraFin() <= nuevaConferencia.getHoraInicio()) { //Si la primera conferencia de las que están en marcha ha acabado, utilizamos esa sala que ha quedado vacía.
            conferenciasSinFinalizar.pop();
        }
        else {
            salasNecesarias++;
        }
        conferenciasSinFinalizar.push(nuevaConferencia);
        conferencias.pop();
    }
    cout << salasNecesarias << endl;
}
