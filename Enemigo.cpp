#include "Enemigo.h"

Enemigo::Enemigo(const std::string& nombre, int vidaMaxima, int ataque, int defensa, int experienciaOtorgada)
    : Entidad(nombre, vidaMaxima, ataque, defensa), experienciaOtorgada(10) {
    setExperienciaOtorgada(experienciaOtorgada);
}

Enemigo::~Enemigo() {
    // Destructor virtual de Enemigo
}

int Enemigo::getExperienciaOtorgada() const {
    return experienciaOtorgada;
}

void Enemigo::setExperienciaOtorgada(int nuevaExperiencia) {
    if (nuevaExperiencia < 0) {
        experienciaOtorgada = 0;
    } else {
        experienciaOtorgada = nuevaExperiencia;
    }
}

