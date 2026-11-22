#include "EstatuaAltar.h"
#include <iostream>

EstatuaAltar::EstatuaAltar(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
                           int experienciaOtorgada)
    : Enemigo(nombre, vidaMaxima, ataque, defensa, experienciaOtorgada),
      invulnerable(true),
      turnoAtaque(0) {
}

EstatuaAltar::~EstatuaAltar() {
    // Destructor virtual de EstatuaAltar
}

int EstatuaAltar::recibirDanio(int danioBruto) {
    if (invulnerable) {
        std::cout << "  -> ¡Tu ataque rebota contra la piel de piedra colosal sin hacerle ni un rasguño! Eres demasiado débil.\n";
        return 0;
    }
    return Entidad::recibirDanio(danioBruto);
}

void EstatuaAltar::atacar(Entidad& objetivo) {
    turnoAtaque++;

    // Calcula un golpe pesado entre 14 y 18 puntos de daño segun el turno
    int danioEstatua = 14 + ((turnoAtaque * 2) % 5); // Oscila entre 14 y 18

    int vidaActualObjetivo = objetivo.getVida();

    // Validacion estricta para no matar a Jin-Woo antes de la decision del Sistema:
    // Si el golpe dejaria al jugador con menos de 1 HP, se ajusta para dejarlo en exactamente 1 HP.
    if (vidaActualObjetivo - danioEstatua < 1) {
        danioEstatua = vidaActualObjetivo - 1;
    }

    objetivo.setVida(vidaActualObjetivo - danioEstatua);

    std::cout << "\n[COMBATE] ¡" << nombre
              << " descarga su colosal lanza de piedra haciendo temblar todo el altar sobre "
              << objetivo.getNombre() << "!\n";
    std::cout << "  -> El impacto te quita " << danioEstatua << " puntos de vida. ("
              << objetivo.getNombre() << " HP: " << objetivo.getVida()
              << "/" << objetivo.getVidaMaxima() << ")\n";
}

std::string EstatuaAltar::getTipo() const {
    return "EstatuaAltar";
}

bool EstatuaAltar::isInvulnerable() const {
    return invulnerable;
}

void EstatuaAltar::setInvulnerable(bool estado) {
    invulnerable = estado;
}

int EstatuaAltar::getTurnoAtaque() const {
    return turnoAtaque;
}

void EstatuaAltar::setTurnoAtaque(int turno) {
    if (turno < 0) {
        turnoAtaque = 0;
    } else {
        turnoAtaque = turno;
    }
}
