//
//  main_29.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 27/11/20.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include "PriorityQueue.h"

using namespace std;

struct Hora {
    int hora;
    int minutos;
};

bool operator<(Hora const& lhs, Hora const& rhs) {
    if (lhs.hora == rhs.hora) {
        return lhs.minutos < rhs.minutos;
    }
    return lhs.hora < rhs.hora;
}

bool operator<=(Hora const& lhs, Hora const& rhs) {
    if (lhs.hora == rhs.hora) {
        if (lhs.minutos == rhs.minutos) {
            return true;
        }
        return lhs.minutos < rhs.minutos;
    }
    return lhs.hora < rhs.hora;
}

struct Pelicula {
    Hora horaInicio;
    Hora horaFin;
    
    Hora getHoraInicio() const {
        return horaInicio;
    }
    
    Hora getHoraFin() const {
        return horaFin;
    }
};

bool operator<(Pelicula const& lhs, Pelicula const& rhs) {
    return lhs.getHoraFin() < rhs.getHoraFin();
}

void addHours(Hora &hora, int minutos) {
    hora.minutos += minutos;
    while (hora.minutos >= 60) {
        hora.hora++;
        hora.minutos -= 60;
    }
}

bool resuelveCaso() {
    int numPeliculas;
    cin >> numPeliculas;
    
    if (numPeliculas == 0) {
        return false;
    }
    
    PriorityQueue<Pelicula> peliculas;
    int duracion;
    char basura;
    Pelicula nuevaPelicula;
    Hora hora;
    
    for (int i = 0; i < numPeliculas; i++) {
        cin >> hora.hora >> basura >> hora.minutos >> duracion;
        nuevaPelicula.horaInicio = hora;
        addHours(hora, duracion+10);
        nuevaPelicula.horaFin = hora;
        peliculas.push(nuevaPelicula);
    }
    
    int numPeliculasPuedoVer = 1;
    int result = peliculas.size()-1;
    Hora horaFin = peliculas.top().getHoraFin();
    peliculas.pop();
    for (int i = 0; i < result; i++) {
        if (horaFin <= peliculas.top().getHoraInicio()) {
            horaFin = peliculas.top().getHoraFin();
            numPeliculasPuedoVer++;
        }
        peliculas.pop();
    }
    
    cout << numPeliculasPuedoVer << '\n';
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p29.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
//     para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}


