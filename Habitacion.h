
#ifndef SOLO_LEVELING_HABITACION_H
#define SOLO_LEVELING_HABITACION_H

#include "Objeto.h"
#include "Enemigo.h"
#include <string>
#include <vector>
#include <map>

/**
 * @class Habitacion
 * @brief Representa una sala o zona dentro de la mazmorra.
 * Aplica Agregacion con Enemigo* (vector de punteros), contiene Objetos en el suelo,
 * controla si ya fue visitada para eventos narrativos y conecta con otras habitaciones
 * mediante un std::map de salidas.
 */
class Habitacion {
private:
    int id;
    std::string nombre;
    std::string descripcion;
    bool visitada;
    std::vector<Objeto> objetos;
    std::vector<Enemigo*> enemigos;
    std::map<std::string, Habitacion*> salidas;

public:
    // Constructor y Destructor
    Habitacion(int id, const std::string& nombre, const std::string& descripcion);
    ~Habitacion();

    // Gestion de salidas (mapa de direcciones: norte, sur, este, oeste)
    void conectarSalida(const std::string& direccion, Habitacion* destino);
    Habitacion* getSalida(const std::string& direccion) const;
    const std::map<std::string, Habitacion*>& getSalidas() const;

    // Gestion de objetos en la habitacion
    void agregarObjeto(const Objeto& objeto);
    bool hayObjetos() const;
    std::vector<Objeto> recogerObjetos();
    const std::vector<Objeto>& getObjetos() const;
    void limpiarObjetos();

    // Gestion de enemigos (memoria dinamica)
    void agregarEnemigo(Enemigo* enemigo);
    bool tieneEnemigosVivos() const;
    Enemigo* getPrimerEnemigoVivo() const;
    void eliminarEnemigosDerrotados();
    void limpiarEnemigos();
    const std::vector<Enemigo*>& getEnemigos() const;

    // Visualizacion en consola
    void mostrarInformacion() const;

    // Getters y Setters con validacion
    int getId() const;
    void setId(int nuevoId);
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);
    std::string getDescripcion() const;
    void setDescripcion(const std::string& nuevaDescripcion);
    bool isVisitada() const;
    void setVisitada(bool estado);
};


#endif //SOLO_LEVELING_HABITACION_H
