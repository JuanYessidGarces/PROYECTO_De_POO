
#ifndef SOLO_LEVELING_JUEGO_H
#define SOLO_LEVELING_JUEGO_H

#include "Jugador.h"
#include "Habitacion.h"
#include <vector>
#include <string>

/**
 * @class Juego
 * @brief Clase controladora principal del RPG "Solo Leveling".
 * Administra el ciclo de vida de las habitaciones (Composicion), el flujo de
 * exploracion, las cinematicas interactivas y el sistema de combate polimorfico
 * por turnos.
 */
class Juego {
private:
    Jugador jugador;
    std::vector<Habitacion*> habitaciones;
    bool juegoEnCurso;

    // Metodos privados auxiliares de inicializacion y limpieza
    void inicializarMapa();
    void limpiarMapa();

    // Metodos de flujo de juego
    void bucleExploracion();
    void iniciarCombate(Enemigo* enemigo);
    bool procesarDecisionAltar(Enemigo* estatua);
    void moverJugador();
    void recogerObjetosHabitacion();
    void gestionarInventario();

    // Metodos de narrativa y cinematicas interactivas
    void mostrarCinematica(const std::string& titulo, const std::vector<std::string>& parrafos);
    void mostrarCinematicaHabitacion(Habitacion* habitacion);
    void mostrarMensajeVictoriaFinal();

    // Validacion segura de entradas por consola
    int leerOpcionNumerica(int min, int max);
    std::string leerTextoMinusculas();

public:
    // Constructor y Destructor
    Juego();
    ~Juego();

    // Punto de entrada del menu principal
    void iniciar();

    // Inicializacion de una nueva partida
    void nuevaPartida();
};

#endif //SOLO_LEVELING_JUEGO_H
