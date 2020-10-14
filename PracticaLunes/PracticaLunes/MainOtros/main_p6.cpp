//
//  main_p6.cpp
//  PracticaLunes
//
//  Created by Yhondri on 14/10/2020.
//
#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>

using namespace std;

struct Caja {
    int idCaja;
    int tiempo;
    
    void addTime(int tiempoCliente) {
        tiempo += tiempoCliente;
    }
};

struct ClienteComparator {
    bool operator()(const Caja& a, const Caja& b) {
        return (a.tiempo > b.tiempo) ||
        (a.tiempo == b.tiempo && a.idCaja > b.idCaja);
    }
};

bool resuelveCaso() {
    int nCajasAbiertas, cClientesEsperando;
    cin >> nCajasAbiertas >> cClientesEsperando;
    
    if (nCajasAbiertas == 0 && cClientesEsperando == 0) {
        return false;
    }
    
    priority_queue<Caja, vector<Caja>, ClienteComparator> cajaQueue;
    
    for (int i = 1; i <= nCajasAbiertas; i++) {
        cajaQueue.push({i, 0});
    }
    
    int tiempoCliente;
    for (int i = 0; i < cClientesEsperando; i++) {
        Caja caja = cajaQueue.top();
        cajaQueue.pop();
        
        cin >> tiempoCliente;
        caja.addTime(tiempoCliente);
        cajaQueue.push(caja);
    }
    
    Caja caja = cajaQueue.top();
    cajaQueue.pop();

    cout << caja.idCaja << '\n';

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p6.txt");
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
