/*
	Grupo TAIS26 Silvia y Stefano

	soluci�n al problema 04 donde indicamos 
	 el ndo que ocupa la posicion que pasamos
	 si no la encuetnra mostrar� ??
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include "TreeMap_AVL.h"

using namespace std;

// lee un �rbol binario de la entrada est�ndar
map<int, int>insertaEnArbol(int* v, int n){

	map<int, int> arbol;
	int pos = 1;

	for (int i = 0; i < n; i++){
		arbol.insert(v[i]);
		pos++;
	}

	return arbol;
}


void resuelveCaso(int nodos) {
	
	int* v = new int[nodos];

	for (int i = 0; i <nodos; i++){
		std::cin >> v[i];
	}

	//insertamso de manera que se equilibre
	auto arbol = insertaEnArbol(v,nodos);
	
	int numPosiciones;
	std::cin >> numPosiciones;

	int* VectorPosicionesABuscar = new int[numPosiciones];
	for (int i = 0; i <numPosiciones; i++){
		std::cin >> VectorPosicionesABuscar[i];
	}

	arbol.KesimioElemento(arbol,numPosiciones,VectorPosicionesABuscar);

}

int main(int argc, const char * argv[]) {

// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
//    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/pr�cticas/Ejercicio04/Ejercicio04/casos.txt");
//    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	int tam;
	std::cin >> tam;

	while (tam != 0){
		resuelveCaso(tam);
		std::cin >> tam;
	}

	// para dejar todo como estaba al principio
	#ifndef DOMJUDGE
//        std::cin.rdbuf(cinbuf);
//        system("PAUSE");
	#endif

	return 0;
}
