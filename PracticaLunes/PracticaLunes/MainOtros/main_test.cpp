//
//  main_test.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 24/11/20.
//

#include <algorithm>
#include <assert.h>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int trabajos(vector<pair<int, int>> & v, int C, int F, bool & imposible) {

    sort(v.begin(), v.end());

    stack<pair<int, int>> pila;

    int i = 0;
    int conect = C;
    int cont = 0;
    bool conseguido = false;
    imposible = false;

    while (!conseguido && !imposible && i < v.size()) {

        if (v[i].first > conect && !pila.empty()) {

            if (pila.top().first <= conect && pila.top().second > conect) {
                cont++;
                conect = pila.top().second;
                pila.pop();
            }

            else {
                imposible = true;
            }
        }

        if (conect >= F) {
            conseguido = true;
        }

        if (v[i].first <= conect && !conseguido) {

            if(pila.empty() || v[i].second > pila.top().second)
                pila.push(v[i]);
        }

        i++;
    }

    if (!pila.empty() && !conseguido) {
        if (pila.top().first <= conect && pila.top().second > conect) {
            cont++;
            conect = pila.top().second;
            pila.pop();
        }

        else {
            imposible = true;
        }
    }

    if (conect < F) {
        imposible = true;
    }

    return cont;
}

bool resuelveCaso() {
    int C, F, N, c, f;
    bool imposible;
    vector<pair<int, int>> v;

    cin >> C >> F >> N;

    if (C == 0 && F == 0 && N == 0)
        return false;

    for (int i = 0; i < N; i++) {
        cin >> c >> f;
        v.push_back({ c, f });
    }

    int sol = trabajos(v, C, F, imposible);

    if (imposible)
        cout << "Imposible\n";

    else
        cout << sol << '\n';

    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p32.txt");
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
