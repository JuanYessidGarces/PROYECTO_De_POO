#include "SerpienteKasaka.h"
#include <iostream>

SerpienteKasaka::SerpienteKasaka(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
                                 int experienciaOtorgada, int danioVeneno)
    : Enemigo(nombre, vidaMaxima, ataque, defensa, experienciaOtorgada), danioVeneno(5) {
    setDanioVeneno(danioVeneno);
}

SerpienteKasaka::~SerpienteKasaka() {
    // Destructor virtual de SerpienteKasaka
}

void SerpienteKasaka::atacar(Entidad& objetivo) {
    std::cout << "\n[COMBATE] ¡" << nombre
              << " se lanza velozmente desde las aguas oscuras y clava sus colmillos en "
              << objetivo.getNombre() << "!\n";

    int danioFisico = objetivo.recibirDanio(ataque);

    // Aplicacion de daño adicional por el veneno corrosivo de Kasaka
    objetivo.setVida(objetivo.getVida() - danioVeneno);

    std::cout << "  -> Mordida física: " << danioFisico << " de daño.\n";
    std::cout << "  -> ¡Veneno de Kasaka! Inflige +" << danioVeneno
              << " de daño corrosivo directo.\n";
    std::cout << "  -> (" << objetivo.getNombre() << " HP: " << objetivo.getVida()
              << "/" << objetivo.getVidaMaxima() << ")\n";
}

std::string SerpienteKasaka::getTipo() const {
    return "SerpienteKasaka";
}

int SerpienteKasaka::getDanioVeneno() const {
    return danioVeneno;
}

void SerpienteKasaka::setDanioVeneno(int nuevoDanioVeneno) {
    if (nuevoDanioVeneno < 0) {
        danioVeneno = 0;
    } else {
        danioVeneno = nuevoDanioVeneno;
    }
}