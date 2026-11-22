
#ifndef SOLO_LEVELING_JUGADOR_H
#define SOLO_LEVELING_JUGADOR_H

#include "Entidad.h"
#include "Objeto.h"
#include "Habitacion.h"
#include <vector>
#include <string>

/**
 * @class Jugador
 * @brief Representa al protagonista Sung Jin-Woo, quien inicia como un debil
 * Cazador de Rango E y despierta como "Jugador" elegido por El Sistema.
 * Hereda de Entidad, contiene su inventario por Composicion y mantiene una
 * Asociacion con su Habitacion actual mediante un puntero.
 */
class Jugador : public Entidad {
private:
    int nivel;
    int experiencia;
    int experienciaSiguienteNivel;
    bool despertado;
    Objeto armaEquipada;
    Objeto armaduraEquipada;
    bool tieneArmaEquipada;
    bool tieneArmaduraEquipada;
    std::vector<Objeto> inventario;
    Habitacion* ubicacionActual;

public:
    // Constructor y Destructor
    Jugador(const std::string& nombre = "Sung Jin-Woo");
    virtual ~Jugador();

    // Sobrescritura de metodos polimorficos de Entidad
    virtual void atacar(Entidad& objetivo) override;
    virtual std::string getTipo() const override;

    // Estado de Despertar y Sistema de niveles ("El Sistema")
    void despertar();
    bool isDespertado() const;
    void setDespertado(bool estado);
    void ganarExperiencia(int expGanada);
    void subirNivel();

    // Gestion de inventario y equipamiento
    void agregarObjeto(const Objeto& objeto);
    bool usarOEquiparObjeto(int indice);
    void limpiarInventario();
    void mostrarInventario() const;
    void mostrarEstado() const;

    // Getters
    int getNivel() const;
    int getExperiencia() const;
    int getExperienciaSiguienteNivel() const;
    Objeto getArmaEquipada() const;
    Objeto getArmaduraEquipada() const;
    bool getTieneArmaEquipada() const;
    bool getTieneArmaduraEquipada() const;
    const std::vector<Objeto>& getInventario() const;
    Habitacion* getUbicacionActual() const;

    // Setters con validacion
    void setNivel(int nuevoNivel);
    void setExperiencia(int nuevaExperiencia);
    void setExperienciaSiguienteNivel(int nuevaExpSiguiente);
    void setArmaEquipada(const Objeto& arma, bool equipada);
    void setArmaduraEquipada(const Objeto& armadura, bool equipada);
    void setUbicacionActual(Habitacion* nuevaUbicacion);
};

#endif //SOLO_LEVELING_JUGADOR_H
