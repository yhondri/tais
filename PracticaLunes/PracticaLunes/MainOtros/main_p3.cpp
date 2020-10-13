//
//  main_p3.cpp
//  PracticaLunes
//
//  Created by Yhondri on 13/10/2020.
//

#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>

using namespace std;

bool resuelveCaso() {
    int n;
    cin >> n;
    
    if (n == 0) {
        return false;
    }
    
    priority_queue<long long, vector<long long>, greater<long long>> queue;
    
    for (int i = 0; i < n; i++) {
        long long value;
        cin >> value;
        queue.push(value);
    }
    
    long acumulador = 0;
    
    while (queue.size() > 1) {
        long long value1 = queue.top();
        queue.pop();
        long long value2 = queue.top();
        queue.pop();
        
        long long currentSum = value1 + value2;
        acumulador += currentSum;
        queue.push(currentSum);
    }
    
    cout << acumulador << endl;
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p3.txt");
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
