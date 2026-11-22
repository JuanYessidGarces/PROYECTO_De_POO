

#ifndef SOLO_LEVELING_ESTATUAALTAR_H
#define SOLO_LEVELING_ESTATUAALTAR_H

#include "Enemigo.h"
#include <string>

/**
 * @class EstatuaAltar
 * @brief Subclase concreta de Enemigo que representa a la Estatua de Piedra del
 * Templo de Cartenon (Altar de la Doble Mazmorra).
 * Demuestra polimorfismo sobrescribiendo tanto atacar() como recibirDanio():
 * es invulnerable a los ataques de un Rango E sin despertar y reduce la vida
 * de Sung Jin-Woo hasta dejarlo exactamente a 1 HP para activar "El Sistema".
 */
class EstatuaAltar : public Enemigo {
private:
    bool invulnerable;
    int turnoAtaque;

public:
    // Constructor
    EstatuaAltar(const std::string& nombre, int vidaMaxima, int ataque, int defensa,
                 int experienciaOtorgada);

    // Destructor virtual
    virtual ~EstatuaAltar();

    // Sobrescritura de metodos polimorficos de Entidad / Enemigo
    virtual int recibirDanio(int danioBruto) override;
    virtual void atacar(Entidad& objetivo) override;
    virtual std::string getTipo() const override;

    // Getters y Setters con validacion
    bool isInvulnerable() const;
    void setInvulnerable(bool estado);
    int getTurnoAtaque() const;
    void setTurnoAtaque(int turno);
};

#endif //SOLO_LEVELING_ESTATUAALTAR_H
