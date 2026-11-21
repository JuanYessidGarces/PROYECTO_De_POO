
#ifndef SOLO_LEVELING_OBJECTO_H
#define SOLO_LEVELING_OBJECTO_H

#include <string>

// Enumeracion fuertemente tipada para clasificar los objetos del juego
enum class TipoObjeto {
    POCION,
    ARMA,
    ARMADURA
};

/**
 * @class Objeto
 * @brief Representa un item dentro del juego (pocion, arma o armadura).
 * Aplica encapsulamiento manteniendo sus atributos privados con getters y setters.
 */
class Objeto {
private:
    std::string nombre;
    std::string descripcion;
    TipoObjeto tipo;
    int bonificador; // Vida curada (POCION), bono de ataque (ARMA) o bono de defensa (ARMADURA)

public:
    // Constructores
    Objeto();
    Objeto(const std::string& nombre, const std::string& descripcion, TipoObjeto tipo, int bonificador);

    // Getters
    std::string getNombre() const;
    std::string getDescripcion() const;
    TipoObjeto getTipo() const;
    std::string getTipoTexto() const;
    int getBonificador() const;

    // Setters con validacion
    void setNombre(const std::string& nuevoNombre);
    void setDescripcion(const std::string& nuevaDescripcion);
    void setTipo(TipoObjeto nuevoTipo);
    void setBonificador(int nuevoBonificador);
};

#endif //SOLO_LEVELING_OBJECTO_H
