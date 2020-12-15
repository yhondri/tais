//
//  main_36.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 2/12/20.
//

#include <stdio.h>

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

using namespace std;

struct Actividad {
    int horaInicio;
    int horaFin;
};

bool operator<(Actividad const& lhs, Actividad const& rhs) {
    return lhs.horaInicio < rhs.horaInicio;
}

//Número - 1
bool resuelveCaso() {
    int nActividades;
    cin >> nActividades;
    
    if (nActividades == 0) {
        return false;
    }
    
    PriorityQueue<Actividad> actividades;
    int hInicio, hFin;
    for (int i = 0; i < nActividades; i++) {
        cin >> hInicio >> hFin;
        actividades.push({hInicio, hFin});
    }
    
    //Pista profesor contamigos amigos. Si uno ya ha quedado libre, lo podemos reutilizar.
    PriorityQueue<int> amigosQueue;
    amigosQueue.push(actividades.top().horaFin);
    actividades.pop();
    int contador = 0;
    Actividad actual;
    
    for (int i = 1; i < nActividades; i++) {
        actual = actividades.top();
        actividades.pop();
        
        if (amigosQueue.top() > actual.horaInicio) {
            contador++;
            amigosQueue.push(actual.horaFin);
        } else {
            amigosQueue.pop();
            amigosQueue.push(actual.horaFin);
        }
    }
    
    cout << contador << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p34.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
