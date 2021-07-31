//
//  main.cpp
//  Ejercicio24
//
//  Created by Yhondri  on 24/11/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 Coste lineal dependiendo del número de películas que se proyectarán.
 Esto se debe a que utilizamos una cola de prioridad que se recorre 1 sola vez.
 
 */


#include <iostream>
#include <fstream>
#include "Pelicula.h"
#include <sstream>
#include <vector>
#include <iterator>
#include "PriorityQueue.h"

using namespace std;

void print(PriorityQueue<Film>films);
void calcularPeliculasQuePuedoVer(PriorityQueue<Film>films, int numPeliculas);

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio21/Ejercicio21/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio24/Ejercicio24/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numPeliculas;

    while ((cin >> numPeliculas) && numPeliculas!= 0) {
   
        PriorityQueue<Film>films(0);

        for (int i = 0; i < numPeliculas; i++) {
            string hourString;
            int duracion;
            cin >> hourString;
            cin >> duracion;
            
            vector<string> hourSplited = split(hourString, ':');
            
            int hour = stoi(hourSplited[0]);
            int minute = stoi(hourSplited[1]);
            Film film(hour, minute, duracion);
            films.push(film);
        }
        calcularPeliculasQuePuedoVer(films, numPeliculas);
//        print(films);
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void print(PriorityQueue<Film>films) {
    while (!films.empty()) {
        Film film = films.top();
        films.pop();
        cout << film.getHoraDeInicio().toString() << "--" << film.getHoraFinal().toString() << endl;
    }
    cout << "-------------" << endl;
}

void calcularPeliculasQuePuedoVer(PriorityQueue<Film>films, int numPeliculas) {
    int contadorPeliculas = 0;
    Film peliculaAnterior;
    for (int i = 0; i < numPeliculas; i++) {

        Film film = films.top();

        if (peliculaAnterior.getHoraFinal() < film.getHoraDeInicio()) {
            contadorPeliculas++;
            peliculaAnterior = film;
        }
        films.pop();

    }
    cout << contadorPeliculas << endl;
}
