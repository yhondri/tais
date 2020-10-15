//
//  main_p5.cpp
//  PracticaLunes
//
//  Created by Yhondri on 15/10/2020.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits.h>
#include <queue>

using namespace std;

struct Ingreso {
    string nombre;
    long gravedad;
    long ordenLlegada;
};

struct IngresoComparator {
    bool operator()(const Ingreso& a, const Ingreso& b) {
        return (a.gravedad < b.gravedad) || ((a.gravedad == b.gravedad) && (a.ordenLlegada > b.ordenLlegada));
    }
};

bool resuelveCaso() {
    int nEventos;
    cin >> nEventos;
    
    if (nEventos == 0) {
        return false;
    }
    
    priority_queue<Ingreso, vector<Ingreso>, IngresoComparator> ingresoQueue;
    
    string input;
    string command;
    string name;
    long gravedad;
    
    for (int i = 0; i < nEventos; i++) {
        cin >> command;
        
        if (command == "I") {
            cin >> name;
            cin >> gravedad;
            ingresoQueue.push({name, gravedad, i});
        } else {
            Ingreso ingreso = ingresoQueue.top();
            ingresoQueue.pop();
            cout << ingreso.nombre << '\n';
        }
    }

    cout << "---"<< '\n';

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p5.txt");
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
