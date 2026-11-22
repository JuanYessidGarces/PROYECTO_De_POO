#include "Goblin.h"
#include <iostream>

Goblin::Goblin(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
               int experienciaOtorgada, bool esElite)
    : Enemigo(nombre, vidaMaxima, ataque, defensa, experienciaOtorgada), esElite(esElite) {
}

Goblin::~Goblin() {
    // Destructor virtual de Goblin
}

void Goblin::atacar(Entidad& objetivo) {
    if (esElite) {
        std::cout << "\n[COMBATE] ¡" << nombre
                  << " alza su mandoble pesado y descarga un tajo demoledor contra "
                  << objetivo.getNombre() << "!\n";
    } else {
        std::cout << "\n[COMBATE] ¡" << nombre
                  << " suelta un chillido salvaje y arremete con su daga oxidada contra "
                  << objetivo.getNombre() << "!\n";
    }

    int danioCausado = objetivo.recibirDanio(ataque);
    std::cout << "  -> Causa " << danioCausado << " puntos de daño. ("
              << objetivo.getNombre() << " HP: " << objetivo.getVida()
              << "/" << objetivo.getVidaMaxima() << ")\n";
}

std::string Goblin::getTipo() const {
    if (esElite) {
        return "Goblin Elite (Caballero)";
    }
    return "Goblin";
}

bool Goblin::getEsElite() const {
    return esElite;
}

void Goblin::setEsElite(bool valor) {
    esElite = valor;
}
