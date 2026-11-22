#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"
#include <string>

/**
 * @class Enemigo
 * @brief Clase abstracta intermedia que hereda de Entidad y representa a las criaturas
 * hostiles de la mazmorra. Anade la experiencia que otorga al ser derrotado.
 */
class Enemigo : public Entidad {
protected:
    int experienciaOtorgada;

public:
    // Constructor
    Enemigo(const std::string& nombre, int vidaMaxima, int ataque, int defensa, int experienciaOtorgada);

    // Destructor virtual
    virtual ~Enemigo();

    // Metodos polimorficos que seran implementados por las subclases concretas
    virtual void atacar(Entidad& objetivo) override = 0;
    virtual std::string getTipo() const override = 0;

    // Getter y Setter con validacion
    int getExperienciaOtorgada() const;
    void setExperienciaOtorgada(int nuevaExperiencia);
};

#endif // ENEMIGO_H

