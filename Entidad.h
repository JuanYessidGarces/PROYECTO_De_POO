
#ifndef SOLO_LEVELING_ENTIDAD_H
#define SOLO_LEVELING_ENTIDAD_H
/**
 * @class Entidad
 * @brief Clase base abstracta que representa a cualquier ser vivo en la mazmorra.
 * Aplica el pilar de Abstraccion mediante metodos virtuales puros y sirve como
 * base para la Herencia y el Polimorfismo en Jugador y Enemigo.
 */
class Entidad {
protected:
    std::string nombre;
    int vida;
    int vidaMaxima;
    int ataque;
    int defensa;

public:
    // Constructor parametrizado
    Entidad(const std::string& nombre, int vidaMaxima, int ataque, int defensa);

    // Destructor virtual obligatorio en clases base polimorficas
    virtual ~Entidad();

    // Metodos virtuales puros (convierten a Entidad en una clase abstracta)
    virtual void atacar(Entidad& objetivo) = 0;
    virtual std::string getTipo() const = 0;

    // Metodos de logica comun de combate
    virtual int recibirDanio(int danioBruto);
    void curar(int cantidad);
    bool estaVivo() const;

    // Getters
    std::string getNombre() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getAtaque() const;
    int getDefensa() const;

    // Setters con validacion
    void setNombre(const std::string& nuevoNombre);
    void setVida(int nuevaVida);
    void setVidaMaxima(int nuevaVidaMaxima);
    void setAtaque(int nuevoAtaque);
    void setDefensa(int nuevaDefensa);
};
#endif //SOLO_LEVELING_ENTIDAD_H
