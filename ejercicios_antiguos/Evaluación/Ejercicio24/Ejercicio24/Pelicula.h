//
//  Pelicula.h
//  Ejercicio24
//
//  Created by Yhondri  on 24/11/17.
//  Copyright © 2017 Yhondri . All rights reserved.
//

#ifndef Pelicula_h
#define Pelicula_h


#include <sstream>

using namespace std;

class Hora {
    
    int hora;
    int minuto;
    int duracion;
    
public:
    friend class FechaYHora;
    
    Hora() : hora(0), minuto(0), duracion(0) {}
    
    Hora(int hora, int minuto, int duracion) : hora(hora), minuto(minuto), duracion(duracion) {}
    
    bool operator<(const Hora& h) const{
        return (hora < h.hora) || (hora == h.hora && minuto < h.minuto);
    }
//
//    bool operator<=(const Hora& h) const{
//        return operator<(h) || operator==(h);
//    }
    
    bool operator==(const Hora& h) const{
        return hora == h.hora && minuto == h.minuto;
    }
    
    bool operator!=(const Hora& h) const{
        return !operator==(h);
    }
    
    // Devuelve una FechaYHora obtenida a partir del this incrementandolo minutos minutos
    Hora sumaMinutos(int minutos) const {
        //Pre: minutos < 1000
        Hora ret = *this;
        ret.hora = (hora + minutos/60)%24;
        ret.minuto = (minuto + minutos%60)%60;
        if (ret.minuto < minuto) {
            ret.hora = (ret.hora+1)%24;
        }
        return ret;
    }
    
    string toString() const{
        stringstream ss;
        ss << hora << ":" << minuto;
        return ss.str();
    }
    
    friend istream& operator>>(istream& sIn,Hora& h);
};


class Film {
    
public:
    
    Film() : horaDeInicio(0, 0, 0), horaFinal(0, 0, 0) , initialized(false) {}
    
    Film(int hora, int minuto, int duracion) {
        horaDeInicio = Hora(hora, minuto, duracion);
        horaFinal = horaDeInicio.sumaMinutos(duracion);
        initialized = true;
    }
    
    bool hasBeenInitialized() {
        return initialized;
    }
    
    Hora getHoraFinal() {
        return horaFinal;
    }
    
    Hora getHoraDeInicio() {
        return horaDeInicio;
    }
    
    bool operator<(const Film& h) const{
        return horaDeInicio < h.horaDeInicio;
    }
    
private:
    
    Hora horaDeInicio;
    Hora horaFinal;
    bool initialized;
};



#endif /* Pelicula_h */
