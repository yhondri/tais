//
//  main_32.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 24/11/20.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

struct Trabajo {
    int inicio;
    int fin;
    
public:
    Trabajo(int init, int end): inicio(init), fin(end) {  }
};

bool compareTrabajos(const Trabajo& a, const Trabajo& b) {
    return (a.inicio < b.inicio);
}

bool resuelveCaso() {
    int comienzoIntervaloPlaneta, finIntervaloPlaneta, numeroTrabajos;
    cin >> comienzoIntervaloPlaneta >> finIntervaloPlaneta >> numeroTrabajos;
    
    if (comienzoIntervaloPlaneta == 0 && finIntervaloPlaneta == 0 && numeroTrabajos == 0) {
        return false;
    }
    
    vector<Trabajo> trabajos;
    int inicio, fin;
    for (int i = 0; i < numeroTrabajos; i++) {
        cin >> inicio >> fin;
        trabajos.push_back({inicio, fin});
    }
    
    sort(trabajos.begin(), trabajos.end(), compareTrabajos);
    int index = 0, comienzoIntervalo = comienzoIntervaloPlaneta, numTrabajosNecesarios = 0;
    bool objetivoConseguido = false, esImposible = false;
    stack<Trabajo> trabajosStack;
    
    while (!esImposible && !objetivoConseguido && index < numeroTrabajos) {
        if (!trabajosStack.empty() && trabajos[index].inicio > comienzoIntervalo) {
            if (trabajosStack.top().inicio <= comienzoIntervalo && trabajosStack.top().fin > comienzoIntervalo) {
                numTrabajosNecesarios++;
                comienzoIntervalo = trabajosStack.top().fin;
                trabajosStack.pop();
            } else {
                esImposible = true;
            }
        }
        
        if (comienzoIntervalo >= finIntervaloPlaneta) {
            objetivoConseguido = true; //Hemos cubierto el interalo necesario para salvar el planeta.
        }
        
        if (trabajos[index].inicio <= comienzoIntervalo && !objetivoConseguido) {
            if (trabajosStack.empty() || (trabajos[index].fin > trabajosStack.top().fin)) {
                trabajosStack.push(trabajos[index]);
            }
        }
        
        index++;
    }
    
    if (!trabajosStack.empty() && !objetivoConseguido) {
        if (trabajosStack.top().inicio <= comienzoIntervalo && trabajosStack.top().fin > comienzoIntervalo) {
            numTrabajosNecesarios++;
            comienzoIntervalo = trabajosStack.top().fin;
        } else {
            esImposible = true;
        }
    }
    
    if (comienzoIntervalo < finIntervaloPlaneta) {
        esImposible = true;
    }
    
    if (esImposible) {
        cout << "Imposible" << '\n';
    } else {
        cout << numTrabajosNecesarios << '\n';
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p32.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
//     para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}

