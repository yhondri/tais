//
//  main.cpp
//  Ejercicio12
//
//  Created by Yhondri on 15/11/17.
//  Copyright © 2017 Yhondri. All rights reserved.
//


/**
 
 GRUPO: 3ºE
 Nombre: Yhondri Josué
 Apellidos: Acosta Novas
 
 <--------------------------------->
 
 Coste:
 
 Para resolver el ejercicio realizamos una Búsqueda en anchura, por lo tanto en el caso peor tendremos que recorrer todo el laberinto
 , es decir todas las posiciones. Por lo tanto el orden será O(Filas*columnas).
 
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

//Creamos struct coordinate para determinar la posición de cada punto en el tablero.
struct Coordinate {
    int x;
    int y;
    
    Coordinate() : x(0), y(0) {};
    Coordinate(int x, int y) : x(x), y(y) {};
};

//Creamos struct SensorInfo para luego añadir los sensores en el tablero.
struct SensorInfo {
    int x;
    int y;
    int k;
    
    SensorInfo() : x(0), y(0), k(0) {};
    SensorInfo(int x, int y, int k) : x(x), y(y), k(k) {};
};

//Método que añade los sensores en el tablero.
void populateSensors(vector<vector<int>> &matrix, int const& rows, int const& cols, vector<SensorInfo> const& sensors) {
    for (auto sensor : sensors) {
        // Left
        for (int i = 1; i <= sensor.k; i += 1) {
            int pos = sensor.x-i;
            if (pos < 0 ||matrix[sensor.y][pos] == -2) {
                break;
            }
            matrix[sensor.y][pos] = -3;
        }
        
        // Right
        for (int i = 1; i <= sensor.k; i += 1) {
            int pos = sensor.x+i;
            if (pos >= cols ||matrix[sensor.y][pos] == -2) {
                break;
            }
            matrix[sensor.y][pos] = -3;
        }
        
        // Up
        for (int i = 1; i <= sensor.k; i += 1) {
            int pos = sensor.y-i;
            if (pos < 0 ||matrix[pos][sensor.x] == -2) {
                break;
            }
            matrix[pos][sensor.x] = -3;
        }
        
        // Down
        for (int i = 1; i <= sensor.k; i += 1) {
            int pos = sensor.y+i;
            if (pos >= rows ||matrix[pos][sensor.x] == -2) {
                break;
            }
            matrix[pos][sensor.x] = -3;
        }
    }
}

//Hacemos un recorrido en anchura desde el punto inicial. Si alcanzamos el punto final antes de terminar el recorrido, paramos.
void recorridoAnchura(vector<vector<int>> &matrix, int const& rows, int const& cols, Coordinate const& start, Coordinate const& finish) {
    queue<Coordinate> q;
    q.push(start);
    Coordinate sides[] = {Coordinate(-1,0),Coordinate(1,0),Coordinate(0,-1),Coordinate(0,1)};
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (auto side : sides) {
            int x = v.x+side.x;
            int y = v.y+side.y;
            if (x < 0 || x >= cols || y < 0 || y >= rows) {
                continue;
            }
            if (matrix[y][x] == -1) {
                matrix[y][x] = matrix[v.y][v.x] + 1;
                
                if (x == finish.x && y == finish.y) {
                    return;
                }
                
                q.push(Coordinate(x, y));
            }
        }
    }
}

// resuelve un caso de prueba
void resuelveCaso() {
    int cols, rows;
    cin >> cols >> rows;
    
    vector<vector<int>> matrix(rows, vector<int>(cols));
    Coordinate start;
    Coordinate finish;
    vector<SensorInfo> sensors;
    
    for (int y = 0; y < rows; y += 1) {
        for (int x = 0; x < cols; x += 1) {
            char positionXY;
            cin >> positionXY;
            
            switch (positionXY) {
                case '.':
                    matrix[y][x] = -1;
                    break;
                case '#':
                    matrix[y][x] = -2;
                    break;
                case 'E':
                    matrix[y][x] = 0;
                    start.x = x;
                    start.y = y;
                    break;
                case 'P':
                    matrix[y][x] = -1;
                    finish.x = x;
                    finish.y = y;
                    break;
                default:
                    matrix[y][x] = -3;
                    SensorInfo sensor(x, y, positionXY-'0');
                    sensors.push_back(sensor);
                    break;
            }
        }
    }
    
    populateSensors(matrix, rows, cols, sensors);
    if (matrix[start.y][start.x] >= -1  && matrix[finish.y][finish.x] >= -1) { //Miramos que no haya sensores en la salida y llegada
        recorridoAnchura(matrix, rows, cols, start, finish);
    }
    
    int dist = matrix[finish.y][finish.x];
    if (dist < 0) {
        cout << "NO\n";
    }
    else {
        cout << dist << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio12/Ejercicio12/casos.txt"); //MacBook Pro
    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio12/Ejercicio12/casos.txt"); //Mac Mini
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    
    int numCasos;
    cin >> numCasos;
    while (numCasos > 0) {
        resuelveCaso();
        numCasos -= 1;
    }
    
    // restablecimiento de cin
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    //    system("pause");
#endif
    
    return 0;
}

//int main(int argc, const char * argv[]) {
//    // ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//    //    ifstream in("/Users/yhondri/Documents/Developer/C++/tais/Evaluación/Ejercicio12/Ejercicio12/casos.txt"); //MacBook Pro
//    ifstream in("/Users/admin/Documents/Developer/Universidad/tais/Evaluación/Ejercicio12/Ejercicio12/casos.txt"); //Mac Mini
//
//    auto cinbuf = cin.rdbuf(in.rdbuf());
//#endif
//
//    int numCasos, columnas, filas;
//    cin >> numCasos;
//
//    while (numCasos > 0) {
//        cin >> columnas >> filas;
//
//        Maze maze(filas, columnas);
//        maze.resolverLaberinto();
////        maze.resolverLaberinto();;
////        maze.printMaze();
//        numCasos--;
//    }
//
//    // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    cin.rdbuf(cinbuf);
//    //    system("PAUSE");
//#endif
//    return 0;
//}

