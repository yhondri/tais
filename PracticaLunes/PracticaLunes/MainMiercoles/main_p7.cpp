//
//  main_p7.cpp
//  PracticaLunes
//
//  Created by Yhondri on 14/10/2020.
//
#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>

using namespace std;

struct Tarea {
    int tInicioActual;
    int tFinActual;
    int periodo;
    
    Tarea(int tiempoInicio, int tiempoFin, int tiempoPeriodo) {
        inicio = tiempoInicio;
        fin = tiempoFin;
        tInicioActual = inicio;
        tFinActual = fin;
        periodo = tiempoPeriodo;
    }
    
    void siguienteRepeticion() {
        inicio += periodo;
        fin += periodo;
        tInicioActual = inicio;
        tFinActual = fin;
    }
    
private:
    int inicio;
    int fin;
};

struct ClienteComparator {
    bool operator()(const Tarea& a, const Tarea& b) {
        return (a.tInicioActual > b.tInicioActual);
    }
};

bool resuelveCaso() {
    int nTareasUnicas, mTareasPeriodicas, tMinutoConsulta;
    
    if (!(cin >> nTareasUnicas)) {
        return false;
    }
    
    cin >> mTareasPeriodicas >> tMinutoConsulta;
    
    priority_queue<Tarea, vector<Tarea>, ClienteComparator> tareaQueue;
    int tiempoInicio, tiempoduracion;

    for (int i = 0; i < nTareasUnicas; i++) {
        cin >> tiempoInicio >> tiempoduracion;
        tareaQueue.push({tiempoInicio, tiempoduracion, 0});
    }
    
    int periodo;
    for (int i = 0; i < mTareasPeriodicas; i++) {
        cin >> tiempoInicio >> tiempoduracion >> periodo;
        tareaQueue.push({tiempoInicio, tiempoduracion, periodo});
    }
    
    bool seguir = true;
    int finTareaAnterior = 0;
    int inicioSiguienteTarea = 0;
    
    while (seguir && !tareaQueue.empty() && inicioSiguienteTarea < tMinutoConsulta) {
        Tarea tarea = tareaQueue.top();
        tareaQueue.pop();
        
        Tarea tarea2 = tareaQueue.top();
        if (tarea.tInicioActual < tMinutoConsulta && ((tarea.tInicioActual < finTareaAnterior) || (!tareaQueue.empty() && tarea.tInicioActual == tarea2.tInicioActual))) {
            seguir = false;
        } else {
            inicioSiguienteTarea = tarea.tInicioActual;
            finTareaAnterior = tarea.tFinActual;
            if (tarea.periodo > 0) {
                tarea.siguienteRepeticion();
                tareaQueue.push(tarea);
            }
        }
    }
    
    if (seguir) {
        cout << "NO" << '\n';
    } else {
        cout << "SI" << '\n';
    }

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p7.txt");
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
