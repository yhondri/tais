//
//  main_set_avl_minimum.cpp
//  PracticaLunes
//
//  Created by Yhondri on 04/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include "TreeSet_AVL.h"

using namespace std;

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Otros Casos/type1.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    
    while (numCasos > 0) {
        int numValues = 0;
        cin >> numValues;
        
        Set<int> treeSet;
        
        for (int i = 0; i < numValues; i++) {
            int newValue;
            cin >> newValue;
            treeSet.insert(newValue);
        }
        
        cout << "Mínimo: " << treeSet.minimum() << endl;
        numCasos--;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
