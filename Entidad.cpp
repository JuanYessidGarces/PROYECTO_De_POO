#include "Entidad.h"

Entidad::Entidad(const std::string& nombre, int vidaMaxima, int ataque, int defensa)
    : nombre(nombre), vida(1), vidaMaxima(1), ataque(1), defensa(0) {
    setVidaMaxima(vidaMaxima);
    setVida(this->vidaMaxima);
    setAtaque(ataque);
    setDefensa(defensa);
}

Entidad::~Entidad() {
    // Destructor virtual base
}

int Entidad::recibirDanio(int danioBruto) {
    // El danio recibido se reduce segun la defensa (minimo 1 punto de danio)
    int danioReal = danioBruto - defensa;
    if (danioReal < 1) {
        danioReal = 1;
    }

    setVida(vida - danioReal);
    return danioReal;
}

void Entidad::curar(int cantidad) {
    if (cantidad > 0) {
        setVida(vida + cantidad);
    }
}

bool Entidad::estaVivo() const {
    return vida > 0;
}

std::string Entidad::getNombre() const {
    return nombre;
}

int Entidad::getVida() const {
    return vida;
}

int Entidad::getVidaMaxima() const {
    return vidaMaxima;
}

int Entidad::getAtaque() const {
    return ataque;
}

int Entidad::getDefensa() const {
    return defensa;
}

void Entidad::setNombre(const std::string& nuevoNombre) {
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }
}

void Entidad::setVida(int nuevaVida) {
    if (nuevaVida < 0) {
        vida = 0;
    } else if (nuevaVida > vidaMaxima) {
        vida = vidaMaxima;
    } else {
        vida = nuevaVida;
    }
}

void Entidad::setVidaMaxima(int nuevaVidaMaxima) {
    if (nuevaVidaMaxima < 1) {
        vidaMaxima = 1;
    } else {
        vidaMaxima = nuevaVidaMaxima;
    }
    if (vida > vidaMaxima) {
        vida = vidaMaxima;
    }
}

void Entidad::setAtaque(int nuevoAtaque) {
    if (nuevoAtaque < 1) {
        ataque = 1;
    } else {
        ataque = nuevoAtaque;
    }
}

void Entidad::setDefensa(int nuevaDefensa) {
    if (nuevaDefensa < 0) {
        defensa = 0;
    } else {
        defensa = nuevaDefensa;
    }
}
