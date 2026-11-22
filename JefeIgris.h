
#ifndef SOLO_LEVELING_JEFEIGRIS_H
#define SOLO_LEVELING_JEFEIGRIS_H

#include "Enemigo.h"
#include <string>

/**
 * @class JefeIgris
 * @brief Subclase concreta de Enemigo que representa al jefe final de la mision
 * de cambio de clase: Igris, el Comandante Sangriento.
 * Cada 3 turnos ejecuta su habilidad especial "Corte Carmesi".
 */
class JefeIgris : public Enemigo {
private:
    int contadorTurnos;
    int bonoCorteCarmesi;

public:
    // Constructor
    JefeIgris(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
              int experienciaOtorgada, int bonoCorteCarmesi);

    // Destructor virtual
    virtual ~JefeIgris();

    // Sobrescritura de metodos polimorficos
    virtual void atacar(Entidad& objetivo) override;
    virtual std::string getTipo() const override;

    // Getters y Setters con validacion
    int getContadorTurnos() const;
    void setContadorTurnos(int turnos);
    int getBonoCorteCarmesi() const;
    void setBonoCorteCarmesi(int bono);
};
#endif //SOLO_LEVELING_JEFEIGRIS_H
