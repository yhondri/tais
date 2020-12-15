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
#include "EntInf.h"
//#include "Matriz.h"

using namespace std;

struct Solucion {
    long long manerasDeConseguirLaCuerda;
    long long minNumCordeles;
    long long minCoste;
    bool existeSolucion; //Indica si es posible conseguir este valor sumando los otros.
    
    Solucion() {
        this->manerasDeConseguirLaCuerda = 0;
        this->minNumCordeles = 0;
        this->minCoste = 1000;
        this->existeSolucion = false;
    }
};

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


struct Cordel {
    int longitud;
    int coste;
};

class CalculadorNumeroCombinaciones {
private:
    int longitudCuerda;
    vector<Cordel> cordeles;
    int numValues;
    Matriz<Solucion> matrizFormasCrearCuerda;
    int numManeras = 0;
public:
    CalculadorNumeroCombinaciones(vector<Cordel> values, int longitudC):
    longitudCuerda(longitudC),
    cordeles(values),
    numValues((int)values.size()),
    matrizFormasCrearCuerda(numValues, longitudCuerda+1) {
        Solucion result = isSubsetSumb();
        vector<int> p;
//        long long manerasDeConseguirLaCuerda = 0;
//        long long minNumCordeles = -1;
//        long long minCoste = -1;
//        long long minCordelesActual = 0;
//        long long minCosteActual = 0;
//        countNumberOfFormToReachSum(numValues-1, longitudCuerda, manerasDeConseguirLaCuerda, minNumCordeles, minCordelesActual, minCoste, minCosteActual);
//
        if (result.existeSolucion) {
            cout << "SI" << " " << result.manerasDeConseguirLaCuerda << " " << result.minNumCordeles << " " << result.minCoste << '\n';
        } else {
            cout << "NO" << '\n';
        }
        
//        printDP();
        
//        cout << result << endl;
    }
    
    void printDP() {
        for (int i = 0; i < numValues; ++i) {
            for (int j = 0; j < longitudCuerda+1; j++) {
                cout << matrizFormasCrearCuerda[i][j].minCoste << " ";
            }
            printf("\n");
        }

        printf("-----------\n");
    }
    
    Solucion isSubsetSumb() {
        // Si la suma es 0, la respuesta es que sí se puede alcanzar la suma.
        for (int i = 0; i < numValues; i++) {
            matrizFormasCrearCuerda[i][0].existeSolucion = true;
            matrizFormasCrearCuerda[i][0].manerasDeConseguirLaCuerda = 1;
            matrizFormasCrearCuerda[i][0].minCoste = cordeles[i].coste;
        }
                
        if (cordeles[0].longitud <= longitudCuerda) {
            matrizFormasCrearCuerda[0][cordeles[0].longitud].existeSolucion = true;
            matrizFormasCrearCuerda[0][cordeles[0].longitud].manerasDeConseguirLaCuerda = 1;
            matrizFormasCrearCuerda[0][cordeles[0].longitud].minCoste = cordeles[cordeles[0].longitud].coste;
        }
                
        //Rellenamos la matriz bottom up
        for (int i = 1; i < numValues; ++i) {
            for (int j = 0; j < longitudCuerda+1; ++j) {
                
                if (cordeles[i].longitud <= j) {
                    if (matrizFormasCrearCuerda[i - 1][j].existeSolucion) {
                        matrizFormasCrearCuerda[i][j].existeSolucion = matrizFormasCrearCuerda[i - 1][j].existeSolucion;
                    } else {
                        matrizFormasCrearCuerda[i][j].existeSolucion = matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].existeSolucion;
                    }
                } else {
                    matrizFormasCrearCuerda[i][j].existeSolucion = matrizFormasCrearCuerda[i - 1][j].existeSolucion;
                }
                
                matrizFormasCrearCuerda[i][j].manerasDeConseguirLaCuerda = matrizFormasCrearCuerda[i - 1][j].manerasDeConseguirLaCuerda + matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].manerasDeConseguirLaCuerda;
                
                matrizFormasCrearCuerda[i][j].minNumCordeles = min(matrizFormasCrearCuerda[i - 1][j].minNumCordeles+1, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minNumCordeles+1);
                
                
                matrizFormasCrearCuerda[i][j].minCoste = min(matrizFormasCrearCuerda[i - 1][j].minCoste, matrizFormasCrearCuerda[i - 1][j - cordeles[i].longitud].minCoste);
                
                matrizFormasCrearCuerda[i][j].minCoste += cordeles[i].coste;
                //matrizFormasCrearCuerda[i][j].minCoste += costeNuevo;
                
            }
        }

        return matrizFormasCrearCuerda[numValues-1][longitudCuerda];
    }
        
//    void countNumberOfFormToReachSum(int i, int sum,
//                                     long long& manerasDeConseguirLaCuerda,
//                                     long long& minNumCordeles,
//                                     long long& minCordelesActual,
//                                     long long& minCoste,
//                                     long long& minCosteActual) {
//
//        //Si llegamos al final y la zuma es diferente a 0. Sólo tomamos el resultado si cordeles[0] es igual a sum o si matriz[0][sum] == true
//        if (i == 0 && sum != 0 && matrizFormasCrearCuerda[0][sum]) {
//            minCordelesActual++;
//            minCosteActual += cordeles[i].coste;
//
//            if (minNumCordeles == -1) {
//                minNumCordeles = minCordelesActual;
//            } else {
//                minNumCordeles = min(minNumCordeles, minCordelesActual);
//            }
//
//            if (minCoste == -1) {
//                minCoste = minCosteActual;
//            } else {
//                minCoste = min(minCoste, minCosteActual);
//            }
//
//            manerasDeConseguirLaCuerda++;
//
//            return;
//        }
//
//        if (i == 0 && sum == 0) {
//            if (minNumCordeles == -1) {
//                minNumCordeles = minCordelesActual;
//            } else {
//                minNumCordeles = min(minNumCordeles, minCordelesActual);
//            }
//
//            if (minCoste == -1) {
//                minCoste = minCosteActual;
//            } else {
//                minCoste = min(minCoste, minCosteActual);
//            }
//
//            manerasDeConseguirLaCuerda++;
//            return;
//        }
//
//        // Si podemos llegar al valor objetivo ignorando el valor actual.
//        if (matrizFormasCrearCuerda[i-1][sum]) {
//            countNumberOfFormToReachSum(i-1, sum, manerasDeConseguirLaCuerda, minNumCordeles, minCordelesActual, minCoste, minCosteActual);
//        }
//
//        // Si podemos llegar al valor objetivo tomando el valor actual.
//        if (sum >= cordeles[i].longitud && matrizFormasCrearCuerda[i-1][sum-cordeles[i].longitud]) {
//            minCordelesActual++;
//            minCosteActual += cordeles[i].coste;
//            countNumberOfFormToReachSum(i-1, sum-cordeles[i].longitud, manerasDeConseguirLaCuerda, minNumCordeles, minCordelesActual, minCoste, minCosteActual);
//        }
//
//    }
};

//class BuscadorCosteMinimo {
//private:
//    int n;
//    Matriz<EntInf> cuerdas;
//    vector<Cordel> cordeles;
//    int longitudCuerda;
//    bool existeSolucion;
//
//    EntInf calcularCuerdaMinima() {
//        cuerdas[0][0] = 0;
//        for (int i = 1; i <= n; ++i) {
//            cuerdas[i][0] = 0;
//            for (int j = 1; j <= longitudCuerda; ++j) {
//                if (cordeles[i-1].longitud > j) {
//                    cuerdas[i][j] = cuerdas[i-1][j];
//                } else {
//                    cuerdas[i][j] = min(cuerdas[i-1][j], cuerdas[i][j - cordeles[i-1].longitud]+1);
//                }
//            }
//        }
//        return cuerdas[n][longitudCuerda];
//    }
//
//public:
//    BuscadorCosteMinimo(vector<Cordel> const& cordelesVector, int longitudC, map<int, int> const& cordelesDisponibles): n((int)cordelesVector.size()),
//    cuerdas(n+1, longitudC+1, Infinito),
//    cordeles(cordelesVector),
//    longitudCuerda(longitudC) {
//        if (calcularCuerdaMinima() != Infinito) {
//            existeSolucion = true;
//        } else {
//            existeSolucion = false;
//        }
//
//        vector<int> sol = obtenerSolucion(cordelesDisponibles);
//
////        cout << cuerdas;
//    }
//
//    bool haySolucion() const {
//        return existeSolucion;
//    }
//
//    vector<int> obtenerSolucion(map<int, int> cordelesDisponibles) {
//        vector<int> solucion;
//        if (cuerdas[n][longitudCuerda] != Infinito) {
//            int i = n, j = longitudCuerda;
//            while (j > 0 && existeSolucion) {
//                //Si hay cordeles disponibles
//                if (cordeles[i-1].longitud <= j && cuerdas[i][j] != cuerdas[i-1][j]) {
//                    if (cordelesDisponibles.at(cordeles[i-1].longitud) > 0) {
//                        solucion.push_back(cordeles[i-1].longitud);
//                        cordelesDisponibles[cordeles[i-1].longitud]--; //Ya hemos utilizado el corder de esta longitud
//                        j = j - cordeles[i-1].longitud;
//                    } else {
//                        existeSolucion = false;
//                    }
//                } else {
//                    --i;
//                }
//            }
//        }
//        return solucion;
//    }
//};


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
    
    CalculadorNumeroCombinaciones calculador(cordeles, longitudCuerda);
    
//    BuscadorCosteMinimo buscadorCosteMinimo(cordeles, longitudCuerda, cordelesDisponibles);
//
//    if (buscadorCosteMinimo.haySolucion()) {
//        cout << "SI" << '\n';
//    } else {
//        cout << "No" << '\n';
//    }
    
    return true;
}


int main(int argc, const char * argv[]) {
#ifndef DOMJUDGE
    ifstream in("/Users/yhondri/Developer/universidad/tais/PracticaLunes/PracticaLunes/Casos/casos_p35.txt");
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
