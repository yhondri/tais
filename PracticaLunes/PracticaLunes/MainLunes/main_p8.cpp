//
//  main_p8.cpp
//  PracticaLunes
//
//  Created by Yhondri on 20/10/2020.
//
#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>
//#include "PriorityQueue.h"
#include <stdexcept>

using namespace std;

template <typename T = int, typename Comparator = std::less<T>>
 class ColaMedianas {
     priority_queue<int, vector<int>, greater<int>> minQueue; //n/2+1, N
     priority_queue<int, vector<int>, less<int>> maxQueue; //0, N/2
//     PriorityQueue<int, less<int>> minQueue; //n/2+1, N
//     PriorityQueue<int, greater<int>> maxQueue; //0, N/2
  public:
     void insertar(int x) {
         if (vacia()) {
             maxQueue.push(x);
         } else {
             if (x < maxQueue.top()) {
                 maxQueue.push(x);
                 if (minQueue.size() + 1 < maxQueue.size()) {
                     minQueue.push(maxQueue.top());
                     maxQueue.pop();
                 }
             } else {
                 minQueue.push(x);
                 if (minQueue.size() > maxQueue.size()) {
                     maxQueue.push(minQueue.top());
                     minQueue.pop();
                 }
             }
         }
     }
     
     bool vacia() const {
         return maxQueue.empty();
     }
     
     int mediana() const {
         if (vacia()) {
             throw std::out_of_range("ECSA");
         }
         return maxQueue.top();
     }
     
     void quitarMediana() {
         maxQueue.pop();
         
         if ((maxQueue.size() + 1 <= minQueue.size()) || (!minQueue.empty() && maxQueue.empty())) {
             maxQueue.push(minQueue.top());
             minQueue.pop();
         }
     }
 };

bool resuelveCaso() {
    int N;
    ColaMedianas<int> cola;
    cin >> N;
    
    if (!std::cin) {
        return false;
    }
    
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        try {
            if (x == 0) {
                cout << cola.mediana() << " ";
                cola.quitarMediana();
            } else {
                cola.insertar(x);
            }
        } catch (out_of_range e) {
            cout << e.what() << " ";
        }
    }
    
    cout << '\n';
    
    return true;
}

int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Documents/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p8.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso()) {}
    
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("PAUSE");
#endif
    return 0;
}
