
#ifndef SOLO_LEVELING_GOBLIN_H
#define SOLO_LEVELING_GOBLIN_H

#include "Enemigo.h"
#include <string>

/**
 * @class Goblin
 * @brief Subclase concreta de Enemigo que representa a un Goblin de mazmorra
 * o a una variante de elite con armadura pesada (Caballero de Acero).
 */
class Goblin : public Enemigo {
private:
    bool esElite;

public:
    // Constructor (por defecto crea un Goblin comun, o de elite si esElite = true)
    Goblin(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
           int experienciaOtorgada, bool esElite = false);

    // Destructor virtual
    virtual ~Goblin();

    // Sobrescritura de metodos polimorficos
    virtual void atacar(Entidad& objetivo) override;
    virtual std::string getTipo() const override;

    // Getter y Setter
    bool getEsElite() const;
    void setEsElite(bool valor);
};



#endif //SOLO_LEVELING_GOBLIN_H
