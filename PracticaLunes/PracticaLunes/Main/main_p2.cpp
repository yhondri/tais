//
//  main_p2.cpp
//  PracticaLunes
//
//  Created by Yhondri on 05/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include "TreeSet_AVL.h"
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos2.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numValues = 0;
    
    while (cin >> numValues && numValues > 0) {
        Set<int> treeSet;
        for (int i = 0; i < numValues; i++) {
            int newValue;
            cin >> newValue;
            treeSet.insert(newValue);
        }
        
//        cout << endl;
//        for (auto v : treeSet.preorder()) {
////            cout << v << " " << endl;
//        }
        
        int numConsultas = 0;
        cin >> numConsultas;
        while (numConsultas > 0) {
            int kValue;
            cin >> kValue;
            try {
                cout << treeSet.kesimo(kValue) << endl;
            } catch (out_of_range e) {
                cout << "??" << endl;
            }
            numConsultas--;
        }
        cout << "---" << endl;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
