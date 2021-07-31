//
//  main.cpp
//  Ejercicio04
//
//  Created by Yhondri  on 8/10/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

#include <iostream>
#include <fstream>
#include "TreeMap_AVL.h"

using namespace std;


/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 DNI: 51554391-Y
 
 <--------------------------------->
 Coste:
 Logarítmico :D
 */

map<int, int> leerDictionario(int numDatos) {
    map<int, int> map;
    for (int i = 0; i < numDatos; i++) {
        int key;
        cin >> key;
        map.insert(key);
    }
    return map;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/prácticas/Ejercicio04/Ejercicio04/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numDatos;
    while ((cin >> numDatos) && numDatos != 0) {
        map<int, int> dictionary = leerDictionario(numDatos);
//        dictionary.calcularTamI();
//        dictionary.mostrarArbol();
        int clavesAConsultar, clave;
        cin >> clavesAConsultar;
        for (int i = 0; i < clavesAConsultar; i++) {
            cin >> clave;
            int result = dictionary.buscarClave(clave);
            if (result != -1) {
                cout << result << "\n";
            }
            else {
                cout << "?? \n";
            }
        }
        
        cout << "---- \n";
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
