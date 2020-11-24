//
//  main_31.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 24/11/20.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>
#include <vector>

using namespace std;

struct Edificio {
    int inicio;
    int fin;
    
public:
    Edificio(int init, int end): inicio(init), fin(end) {  }
    
    
};

struct EdificioComparator {
    bool operator()(const Edificio& a, const Edificio& b) {
        return (a.fin > b.fin);
    }
};

struct Tunel {
    int inicio;
    int fin;
    
public:
    Tunel(int init = 0, int end = 0): inicio(init), fin(end) {  }
};

bool pointIsOnLine(Edificio edificio, Tunel tunel) {
    if (edificio.inicio > tunel.fin || tunel.fin <= edificio.inicio) {
        return false;
    }
  
    return true;
}
  

bool resuelveCaso() {
    int n;
    cin >> n;
    
    if (n == 0) {
        return false;
    }
    
    priority_queue<Edificio, vector<Edificio>, EdificioComparator> edificios;
    int inicio, fin;
    for (int i = 0; i < n; i++) {
        cin >> inicio >> fin;
        edificios.push({inicio, fin});
    }
    
    Tunel ultimoTunel;
    bool existeTunel = false;
    int numeroTuneles = 0;
    
    while (!edificios.empty()) {
        Edificio edificio = edificios.top();
        edificios.pop();
        
        if (!existeTunel || !pointIsOnLine(edificio, ultimoTunel)) {
            ultimoTunel = Tunel({edificio.fin-1, edificio.fin});
            existeTunel = true;
            numeroTuneles++;
        }
    }
    
    cout << numeroTuneles << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p31.txt");
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
