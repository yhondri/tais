//
//  main_p4.cpp
//  PracticaLunes
//
//  Created by Yhondri on 13/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>

using namespace std;

struct Registro {
    int userId;
    int periocidad;
    int tiempoSiguienteEnvio;
    
    void siguienteEnvio() {
        tiempoSiguienteEnvio += periocidad;
    }
};

struct RegistroComparator {
    bool operator()(const Registro& a, const Registro& b) {
        return (a.tiempoSiguienteEnvio > b.tiempoSiguienteEnvio) ||
        (a.tiempoSiguienteEnvio == b.tiempoSiguienteEnvio && a.userId > b.userId);
    }
};

bool resuelveCaso() {
    int n;
    cin >> n;
    
    if (n == 0) {
        return false;
    }
    
    priority_queue<Registro, vector<Registro>, RegistroComparator> registros;
    
    for (int i = 0; i < n; i++) {
        int userId, periocidad;
        cin >> userId;
        cin >> periocidad;
        registros.push({userId, periocidad, periocidad});
    }
    
    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        Registro registro = registros.top();
        registros.pop();
        cout << registro.userId << '\n';
        registro.siguienteEnvio();
        registros.push(registro);
    }
    
    cout << "---" << '\n';

    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p4.txt");
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
