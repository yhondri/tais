// GRACIAS ALBERTO

#ifndef HORAS_H
#define HORAS_H

#include <iostream>
#include <iomanip>
#include <stdexcept>  // invalid_argument

class horas {
private:
    int HH; // las horas
    int MM; // los minutos
    bool check(int h, int m) const {
        return 0 <= h && h < 24 && 0 <= m && m < 60;
    }

public:
    // constructora
    horas(int h = 0, int m = 0) {
        if (check(h, m)) {
            HH = h;
            MM = m;
        }
        else {
            throw std::domain_error("Hora invalida");
        }
    }

    // observadoras
    int hora() const { return HH; }
    int minuto() const { return MM; }

    // operador de comparaci�n
    bool operator<(horas const& h) const {
        return (HH * 3600 + MM * 60) < (h.HH * 3600 + h.MM * 60);
    }

    bool operator<=(horas const& h) const {
        return (HH * 3600 + MM * 60) <= (h.HH * 3600 + h.MM * 60);
    }

    horas operator+(horas const& h) {
        MM += h.MM;
        if (MM >= 60) {
            MM = MM % 60;
            HH++;
        }
        HH += h.HH;
        if (HH >= 24)
            throw std::domain_error("La hora pasa al dia actual");
        return *this;
    }

    horas operator+(int duracion) {
        MM += duracion;
        while (MM >= 60) {
            MM -= 60;
            HH++;
        }
        if (HH >= 24)
            throw std::domain_error("La hora pasa al dia actual");
        return *this;
    }

    void read(std::istream& input = std::cin) {
        int h, m;
        char c;
        input >> h >> c >> m;
        //alternativa:  *this = horas(h,m,s);
        if (check(h, m)) {
            HH = h;
            MM = m;
        }
        else {
            throw std::domain_error("Hora invalida");
        }
    }

    void print(std::ostream& o = std::cout) const {
        o << std::setfill('0') << std::setw(2) << HH << ':'
            << std::setfill('0') << std::setw(2) << MM;
    }
};

inline std::ostream& operator<<(std::ostream& salida, horas const& h) {
    h.print(salida);
    return salida;
}

inline std::istream& operator>>(std::istream& entrada, horas& h) {
    h.read(entrada);
    return entrada;
}

#endif
