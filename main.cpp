#include "Juego.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @file main.cpp
 * @brief Punto de entrada principal del juego RPG "Solo Leveling".
 * Configura la codificacion UTF-8 en Windows para mostrar correctamente
 * tildes y signos de puntuacion en espanol (¡, ¿, ñ, á, é, í, ó, ú).
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    Juego juego;
    juego.iniciar();
    return 0;
}