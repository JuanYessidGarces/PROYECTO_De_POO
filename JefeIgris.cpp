#include "JefeIgris.h"
#include <iostream>

JefeIgris::JefeIgris(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
                     int experienciaOtorgada, int bonoCorteCarmesi)
    : Enemigo(nombre, vidaMaxima, ataque, defensa, experienciaOtorgada),
      contadorTurnos(0), bonoCorteCarmesi(15) {
    setBonoCorteCarmesi(bonoCorteCarmesi);
}

JefeIgris::~JefeIgris() {
    // Destructor virtual de JefeIgris
}

void JefeIgris::atacar(Entidad& objetivo) {
    contadorTurnos++;

    if (contadorTurnos % 3 == 0) {
        std::cout << "\n==================================================================\n";
        std::cout << " [HABILIDAD DE JEFE - TURNO " << contadorTurnos << "] ¡CORTE CARMESÍ!\n";
        std::cout << " ¡El penacho rojo del yelmo de " << nombre << " ondea entre relámpagos\n";
        std::cout << "  de maná! Con velocidad sobrehumana, su gran espada traza un arco\n";
        std::cout << "  escarlata que parte el suelo del Salón del Trono.\n";
        std::cout << "==================================================================\n";

        int danioCriticoBruto = ataque + bonoCorteCarmesi;
        int danioCausado = objetivo.recibirDanio(danioCriticoBruto);

        std::cout << "  -> ¡IMPACTO CRÍTICO! Causa " << danioCausado
                  << " puntos de daño devastador a " << objetivo.getNombre() << ".\n";
        std::cout << "  -> (" << objetivo.getNombre() << " HP: " << objetivo.getVida()
                  << "/" << objetivo.getVidaMaxima() << ")\n";
    } else {
        std::cout << "\n[COMBATE - Turno " << contadorTurnos << "] ¡" << nombre
                  << " avanza en silencio absoluto y ejecuta una estocada imperial contra "
                  << objetivo.getNombre() << "!\n";

        int danioCausado = objetivo.recibirDanio(ataque);
        std::cout << "  -> Causa " << danioCausado << " puntos de daño. ("
                  << objetivo.getNombre() << " HP: " << objetivo.getVida()
                  << "/" << objetivo.getVidaMaxima() << ")\n";
    }
}

std::string JefeIgris::getTipo() const {
    return "JefeIgris";
}

int JefeIgris::getContadorTurnos() const {
    return contadorTurnos;
}

void JefeIgris::setContadorTurnos(int turnos) {
    if (turnos < 0) {
        contadorTurnos = 0;
    } else {
        contadorTurnos = turnos;
    }
}

int JefeIgris::getBonoCorteCarmesi() const {
    return bonoCorteCarmesi;
}

void JefeIgris::setBonoCorteCarmesi(int bono) {
    if (bono < 1) {
        bonoCorteCarmesi = 1;
    } else {
        bonoCorteCarmesi = bono;
    }
}
