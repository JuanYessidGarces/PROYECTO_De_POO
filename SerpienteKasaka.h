
#ifndef SOLO_LEVELING_SERPIENTEKASAKA_H
#define SOLO_LEVELING_SERPIENTEKASAKA_H

#include "Enemigo.h"
#include <string>

/**
 * @class SerpienteKasaka
 * @brief Subclase concreta de Enemigo que representa al jefe del pantano:
 * la Serpiente Venenosa Kasaka, capaz de infligir danio adicional por veneno.
 */
class SerpienteKasaka : public Enemigo {
private:
    int danioVeneno;

public:
    // Constructor
    SerpienteKasaka(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
                    int experienciaOtorgada, int danioVeneno);

    // Destructor virtual
    virtual ~SerpienteKasaka();

    // Sobrescritura de metodos polimorficos
    virtual void atacar(Entidad& objetivo) override;
    virtual std::string getTipo() const override;

    // Getter y Setter con validacion
    int getDanioVeneno() const;
    void setDanioVeneno(int nuevoDanioVeneno);
};
#endif //SOLO_LEVELING_SERPIENTEKASAKA_H
