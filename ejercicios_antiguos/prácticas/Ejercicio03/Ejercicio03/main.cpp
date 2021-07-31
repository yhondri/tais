//
//  main.cpp
//  Ejercicio03
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
 
 Lineal, dependerá de la altura a la que se encuentren las claves, valor mínimo y valor máximo.
 
 */

map<int, int> leerDictionario(int numDatos) {
    map<int, int> map;
    for (int i = 0; i < numDatos; i++) {
        int key;
        cin >> key;
        map[key] = 0;
        
    }
    return map;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/prácticas/Ejercicio03/Ejercicio03/casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numDatos;
    while ((cin >> numDatos) && numDatos != 0) {
        map<int, int> dictionary = leerDictionario(numDatos);
        int minValue, maxValue;
        cin >> minValue;
        cin >> maxValue;
        dictionary.mostrarClaves(minValue, maxValue);
        cout << endl;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

