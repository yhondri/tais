//
//  main.cpp
//  Ejercicio20
//
//  Created by Yhondri on 22/11/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//

/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 El coste es linear, O(n), siendo n el número de agujeros a rellenar,
 esto es debido a que sólo recorremos un array que contiene las posiciones de los agujeros parchear, 1 sóla vez.
 
 */


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printAgujeros(vector<int> agujeros);
void calcularParchesNecesarios(vector<int> agujeros, size_t longitudParches);

int main(int argc, const char * argv[]) {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio20/Ejercicio20/casos.txt"); //MacBook Pro
    //ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio20/Ejercicio20/casos.txt"); //Mac Mini
    
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    size_t numAgujeros, longitudParche;
    bool seguir = true;
    while (seguir) {
        cin >> numAgujeros >> longitudParche;
        if (cin) {
            vector<int> agujeros(numAgujeros);
            for (int i = 0; i < numAgujeros; i++) {
                cin >> agujeros[i];
            }
            calcularParchesNecesarios(agujeros, longitudParche);
            //printAgujeros(agujeros);
        }
        else {
            seguir = false;
        }
        
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

void printAgujeros(vector<int> agujeros) {
    for (int value : agujeros) {
        cout << value << " ";
    }
    cout << endl;
}

void calcularParchesNecesarios(vector<int> agujeros, size_t longitudParches) {
    
    size_t numParchesUtilizados = 0;
    size_t posicionesParcheadas = 0;
    
    for (int posicionAgujero : agujeros) {
        if (posicionAgujero > posicionesParcheadas) {
            numParchesUtilizados++;
            posicionesParcheadas = (posicionAgujero + longitudParches);
        }
    }
    
    cout << numParchesUtilizados << endl;
}
