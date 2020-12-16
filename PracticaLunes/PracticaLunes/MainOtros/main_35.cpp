//
//  main_35.cpp
//  PracticaLunes
//
//  Created by Yhondri Acosta Novas on 5/12/20.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
//#include "EntInf.h"
//#include "Matriz.h"

using namespace std;

template <typename Object>
class Matriz {
public:
    // crea una matriz con fils filas y cols columnas,
    // con todas sus celdas inicializadas al valor e
    Matriz(int fils = 0, int cols = 0, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}
    
    // operadores para poder utilizar notaciÃ³n M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }
    std::vector<Object> & operator[](int f) {
        return datos[f];
    }
    
    // mÃ©todos que lanzan una excepciÃ³n si la posiciÃ³n no existe
    Object const& at(int f, int c) const {
        return datos.at(f).at(c);
    }
    Object & at(int f, int c) {
        return datos.at(f).at(c);
    }
    
    int numfils() const { return datos.size(); }
    int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }
    
    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }
    
private:
    std::vector<std::vector<Object>> datos;
};

template <typename Object>
inline std::ostream & operator<<(std::ostream & out, Matriz<Object> const& m) {
    for (int i = 0; i < m.numfils(); ++i) {
        for (int j = 0; j < m.numcols(); ++j) {
            out << m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}


struct Solucion {
    long long manerasDeConseguirLaCuerda;
    int minNumCordeles = 2000000000;
    int minCoste = 2000000000;
};

struct Cordel {
    int longitud;
    int coste;
};

void getSolucionB(vector<Cordel> const& cordeles, int const& longitudCuerda) {
    vector<Solucion> solucionVector((int)longitudCuerda+1);
    solucionVector[0].manerasDeConseguirLaCuerda = 1;
    solucionVector[0].minCoste = 0;
    solucionVector[0].minNumCordeles = 0;
    
    if (cordeles[0].longitud <= longitudCuerda) {
        solucionVector[cordeles[0].longitud].manerasDeConseguirLaCuerda = 1;
        solucionVector[cordeles[0].longitud].minCoste = cordeles[0].coste;
        solucionVector[cordeles[0].longitud].minNumCordeles = 1;
    }
    
    for (int i = 1; i < (int)cordeles.size(); ++i) {
        for (int j = longitudCuerda; j > 0; --j) {
            if (cordeles[i].longitud <= j) {
                solucionVector[j].manerasDeConseguirLaCuerda = solucionVector[j].manerasDeConseguirLaCuerda + solucionVector[j - cordeles[i].longitud].manerasDeConseguirLaCuerda;
                solucionVector[j].minNumCordeles = min(solucionVector[j].minNumCordeles, solucionVector[j - cordeles[i].longitud].minNumCordeles+1);
                solucionVector[j].minCoste = min(solucionVector[j].minCoste, solucionVector[j - cordeles[i].longitud].minCoste + cordeles[i].coste);
            }
        }
    }
    
    Solucion solucion = solucionVector[longitudCuerda];
    
    if (solucion.manerasDeConseguirLaCuerda > 0) {
        cout << "SI " << solucion.manerasDeConseguirLaCuerda << " " << solucion.minNumCordeles << " " << solucion.minCoste << '\n';
    } else {
        cout << "NO" << '\n';
    }
}

void getSolucion(vector<Cordel> const& cordeles, int const& longitudCuerda) {
    Matriz<Solucion> matrizFormasCrearCuerda((int)cordeles.size(), longitudCuerda+1);
    
    // Si la suma es 0, la respuesta es que sí se puede alcanzar la suma.
    for (int i = 0; i < (int)cordeles.size(); i++) {
        matrizFormasCrearCuerda[i][0].manerasDeConseguirLaCuerda = 1;
        matrizFormasCrearCuerda[i][0].minCoste = 0;
        matrizFormasCrearCuerda[i][0].minNumCordeles = 0;
    }
    
    if (cordeles[0].longitud <= longitudCuerda) {
        matrizFormasCrearCuerda[0][cordeles[0].longitud].manerasDeConseguirLaCuerda = 1;
        matrizFormasCrearCuerda[0][cordeles[0].longitud].minCoste = cordeles[0].coste;
        matrizFormasCrearCuerda[0][cordeles[0].longitud].minNumCordeles = 1;
    }
    
    //Rellenamos la matriz bottom up
    for (int i = 1; i < (int)cordeles.size(); ++i) {
        for (int j = 0; j < longitudCuerda+1; ++j) {
            if (cordeles[i].longitud <= j) {
                matrizFormasCrearCuerda[i][j].manerasDeConseguirLaCuerda = matrizFormasCrearCuerda[i - 1][j].manerasDeConseguirLaCuerda + matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].manerasDeConseguirLaCuerda;
                
                matrizFormasCrearCuerda[i][j].minCoste = min(matrizFormasCrearCuerda[i - 1][j].minCoste, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minCoste + cordeles[i].coste);
                                    
                matrizFormasCrearCuerda[i][j].minNumCordeles = min(matrizFormasCrearCuerda[i - 1][j].minNumCordeles, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minNumCordeles+1);
            } else {
                matrizFormasCrearCuerda[i][j] = matrizFormasCrearCuerda[i - 1][j];
            }
        }
    }
    
    Solucion solucion = matrizFormasCrearCuerda[(int)cordeles.size()-1][longitudCuerda];
    
    if (solucion.manerasDeConseguirLaCuerda > 0) {
        cout << "SI " << solucion.manerasDeConseguirLaCuerda << " " << solucion.minNumCordeles << " " << solucion.minCoste << '\n';
    } else {
        cout << "NO" << '\n';
    }
}

bool resuelveCaso() {
    int numCordeles, longitudCuerda;
    cin >> numCordeles >> longitudCuerda;
    if (!cin) {
        return false;
    }
    
    vector<Cordel> cordeles;
    int longitud, coste;
    
    for (int i = 0; i < numCordeles; i++) {
        cin >> longitud >> coste;
        cordeles.push_back({longitud, coste});
    }
    
//    getSolucion(cordeles, longitudCuerda);
    getSolucionB  (cordeles, longitudCuerda);

//    CalculadorNumeroCombinaciones calculador(cordeles, longitudCuerda);
    
    return true;
}


int main(int argc, const char * argv[]) {
//#ifndef DOMJUDGE
//    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p35.txt");
//    auto cinbuf = cin.rdbuf(in.rdbuf());
//#endif
//
    while (resuelveCaso()) {}
    
    // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    cin.rdbuf(cinbuf);
//    //    system("PAUSE");
//#endif
    return 0;
}
