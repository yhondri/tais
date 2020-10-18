//
//  main_indexpq_actualizar_prioridad.cpp
//  PracticaLunes
//
//  Created by Yhondri on 18/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include "IndexPQ.h"

using namespace std;

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/caso_otros_indexpq.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    IndexPQ<string, int> cola;
     cola.push("Pedro", 50);
     cola.push("Marta", 100);
     cola.push("Luis", 40);
     cola.update("Pedro", 30);
     cola.push("Eva", 60);
     cout << cola.top().elem << '\n';  // debe salir Pedro
     cola.pop();
     cola.update("Marta", 10);
     cout << cola.top().elem << '\n';  // debe salir Marta
     cola.update("Marta", 70);
     cout << cola.top().elem << '\n';  // debe salir Luis
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
