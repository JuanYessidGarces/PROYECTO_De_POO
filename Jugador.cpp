#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre)
    : Entidad(nombre, 50, 5, 1), // Inicia debil como Cazador Rango E (HP: 50, ATK: 5, DEF: 1)
      nivel(1),
      experiencia(0),
      experienciaSiguienteNivel(50),
      despertado(false),
      armaEquipada("Daga Desgastada", "Sin arma del Sistema", TipoObjeto::ARMA, 0),
      armaduraEquipada("Ropa de Cazador Rango E", "Sin armadura del Sistema", TipoObjeto::ARMADURA, 0),
      tieneArmaEquipada(false),
      tieneArmaduraEquipada(false),
      ubicacionActual(nullptr) {
}

Jugador::~Jugador() {
    // El vector inventario se destruye automaticamente (Composicion)
    // ubicacionActual no se elimina aqui porque es una Asociacion (pertenece a Juego)
}

void Jugador::atacar(Entidad& objetivo) {
    std::cout << "\n[COMBATE] ¡" << nombre;
    if (tieneArmaEquipada) {
        std::cout << " empuña [" << armaEquipada.getNombre() << "] y lanza un corte veloz contra ";
    } else if (despertado) {
        std::cout << " concentra el maná del Sistema en sus puños y golpea directamente a ";
    } else {
        std::cout << " ataca desesperadamente con su daga desgastada de Rango E a ";
    }
    std::cout << objetivo.getNombre() << "!\n";

    int danioCausado = objetivo.recibirDanio(ataque);
    if (danioCausado > 0) {
        std::cout << "  -> Infliges " << danioCausado << " puntos de daño. ("
                  << objetivo.getNombre() << " HP: " << objetivo.getVida()
                  << "/" << objetivo.getVidaMaxima() << ")\n";
    }
}

std::string Jugador::getTipo() const {
    if (despertado) {
        return "Cazador Despertado (Jugador del Sistema)";
    }
    return "Cazador Rango E (El más débil de la humanidad)";
}

void Jugador::despertar() {
    despertado = true;
    setVidaMaxima(100);
    setVida(100);

    int bonoArma = tieneArmaEquipada ? armaEquipada.getBonificador() : 0;
    int bonoArmadura = tieneArmaduraEquipada ? armaduraEquipada.getBonificador() : 0;

    setAtaque(18 + bonoArma);
    setDefensa(6 + bonoArmadura);

    std::cout << "\n+==============================================================+\n";
    std::cout << "|               [ DESPERTAR DEL JUGADOR COMPLETADO ]           |\n";
    std::cout << "+--------------------------------------------------------------+\n";
    std::cout << "  * Estado        : ¡JUGADOR DEL SISTEMA ACTIVADO!\n";
    std::cout << "  * Vida Restaurada: " << vida << "/" << vidaMaxima << " HP\n";
    std::cout << "  * Nuevo Ataque  : " << ataque << " (Base 18)\n";
    std::cout << "  * Nueva Defensa : " << defensa << " (Base 6)\n";
    std::cout << "+==============================================================+\n";
}

bool Jugador::isDespertado() const {
    return despertado;
}

void Jugador::setDespertado(bool estado) {
    despertado = estado;
}

void Jugador::ganarExperiencia(int expGanada) {
    if (expGanada <= 0) {
        return;
    }

    if (!despertado) {
        std::cout << "\n[AVISO] Aún eres un Cazador de Rango E ordinario sin acceso al Sistema de Niveles.\n";
        return;
    }

    experiencia += expGanada;
    std::cout << "\n[EL SISTEMA] Has obtenido +" << expGanada << " puntos de experiencia.\n";

    // Subir de nivel automaticamente mientras alcance el umbral requerido
    while (experiencia >= experienciaSiguienteNivel) {
        subirNivel();
    }
}

void Jugador::subirNivel() {
    experiencia -= experienciaSiguienteNivel;
    nivel++;
    experienciaSiguienteNivel += 45;

    // Incremento de estadisticas al subir de nivel
    int aumentoVidaMax = 25;
    int aumentoAtaque = 5;
    int aumentoDefensa = 3;
    int curacionNivel = 45;

    setVidaMaxima(vidaMaxima + aumentoVidaMax);
    setAtaque(ataque + aumentoAtaque);
    setDefensa(defensa + aumentoDefensa);
    curar(curacionNivel);

    std::cout << "\n+==============================================================+\n";
    std::cout << "|                     [ NOTIFICACIÓN ]                         |\n";
    std::cout << "|                    ¡HAS SUBIDO DE NIVEL!                     |\n";
    std::cout << "+--------------------------------------------------------------+\n";
    std::cout << "  * Nuevo Nivel   : " << nivel << "\n";
    std::cout << "  * Vida Máxima   : " << vidaMaxima << " (+" << aumentoVidaMax << ")\n";
    std::cout << "  * Ataque Total  : " << ataque << " (+" << aumentoAtaque << ")\n";
    std::cout << "  * Defensa Total : " << defensa << " (+" << aumentoDefensa << ")\n";
    std::cout << "  * Fatiga reducida: Recuperas +" << curacionNivel << " HP (Actual: "
              << vida << "/" << vidaMaxima << ")\n";
    std::cout << "+==============================================================+\n";
}

void Jugador::agregarObjeto(const Objeto& objeto) {
    inventario.push_back(objeto);
}

bool Jugador::usarOEquiparObjeto(int indice) {
    if (indice < 0 || indice >= static_cast<int>(inventario.size())) {
        std::cout << "\n[EL SISTEMA] Índice de objeto inválido.\n";
        return false;
    }

    Objeto seleccionado = inventario[indice];
    TipoObjeto tipo = seleccionado.getTipo();

    if (tipo == TipoObjeto::POCION) {
        int vidaAntes = vida;
        curar(seleccionado.getBonificador());
        int vidaRecuperada = vida - vidaAntes;

        std::cout << "\n[EL SISTEMA] Has consumido [" << seleccionado.getNombre()
                  << "]. Recuperas +" << vidaRecuperada << " HP ("
                  << vida << "/" << vidaMaxima << ").\n";

        inventario.erase(inventario.begin() + indice);
        return true;
    } else if (tipo == TipoObjeto::ARMA) {
        if (!despertado) {
            std::cout << "\n[AVISO] Necesitas despertar como Jugador del Sistema para equipar este artefacto.\n";
            return false;
        }

        // Retirar del inventario el arma seleccionada
        inventario.erase(inventario.begin() + indice);

        // Si ya tenia un arma equipada, devolverla al inventario y restar su bono
        if (tieneArmaEquipada) {
            setAtaque(ataque - armaEquipada.getBonificador());
            inventario.push_back(armaEquipada);
            std::cout << "[EL SISTEMA] Se ha guardado [" << armaEquipada.getNombre()
                      << "] nuevamente en el inventario.\n";
        }

        armaEquipada = seleccionado;
        tieneArmaEquipada = true;
        setAtaque(ataque + armaEquipada.getBonificador());

        std::cout << "\n[EL SISTEMA] Has equipado el arma [" << armaEquipada.getNombre()
                  << "] (+" << armaEquipada.getBonificador()
                  << " Ataque). Ataque actual: " << ataque << ".\n";
        return true;
    } else if (tipo == TipoObjeto::ARMADURA) {
        if (!despertado) {
            std::cout << "\n[AVISO] Necesitas despertar como Jugador del Sistema para equipar esta armadura.\n";
            return false;
        }

        // Retirar del inventario la armadura seleccionada
        inventario.erase(inventario.begin() + indice);

        // Si ya tenia una armadura equipada, devolverla al inventario y restar su bono
        if (tieneArmaduraEquipada) {
            setDefensa(defensa - armaduraEquipada.getBonificador());
            inventario.push_back(armaduraEquipada);
            std::cout << "[EL SISTEMA] Se ha guardado [" << armaduraEquipada.getNombre()
                      << "] nuevamente en el inventario.\n";
        }

        armaduraEquipada = seleccionado;
        tieneArmaduraEquipada = true;
        setDefensa(defensa + armaduraEquipada.getBonificador());

        std::cout << "\n[EL SISTEMA] Has equipado la armadura [" << armaduraEquipada.getNombre()
                  << "] (+" << armaduraEquipada.getBonificador()
                  << " Defensa). Defensa actual: " << defensa << ".\n";
        return true;
    }

    return false;
}

void Jugador::limpiarInventario() {
    inventario.clear();
}

void Jugador::mostrarInventario() const {
    std::cout << "\n+==============================================================+\n";
    std::cout << "|                 [ INVENTARIO DEL SISTEMA ]                   |\n";
    std::cout << "+==============================================================+\n";

    if (inventario.empty()) {
        std::cout << "  El inventario dimensional está vacío.\n";
    } else {
        for (size_t i = 0; i < inventario.size(); i++) {
            std::cout << "  " << (i + 1) << ". " << inventario[i].getNombre()
                      << " [" << inventario[i].getTipoTexto()
                      << " +" << inventario[i].getBonificador() << "] - "
                      << inventario[i].getDescripcion() << "\n";
        }
    }
    std::cout << "+==============================================================+\n";
}

void Jugador::mostrarEstado() const {
    std::cout << "\n+==============================================================+\n";
    std::cout << "|                    [ VENTANA DE ESTADO ]                     |\n";
    std::cout << "+==============================================================+\n";
    std::cout << "  Nombre    : " << nombre << "\n";
    std::cout << "  Clase     : " << getTipo() << "\n";
    std::cout << "  Despertado: " << (despertado ? "Sí (Jugador del Sistema)" : "No (Rango E)") << "\n";
    std::cout << "  Nivel     : " << nivel << " (EXP: " << experiencia << "/"
              << experienciaSiguienteNivel << ")\n";
    std::cout << "  HP        : " << vida << "/" << vidaMaxima << "\n";
    std::cout << "  Ataque    : " << ataque;
    if (tieneArmaEquipada) {
        std::cout << " (Incluye +" << armaEquipada.getBonificador()
                  << " de " << armaEquipada.getNombre() << ")";
    }
    std::cout << "\n";

    std::cout << "  Defensa   : " << defensa;
    if (tieneArmaduraEquipada) {
        std::cout << " (Incluye +" << armaduraEquipada.getBonificador()
                  << " de " << armaduraEquipada.getNombre() << ")";
    }
    std::cout << "\n";

    std::cout << "--------------------------------------------------------------\n";
    std::cout << "  Arma Equipada     : "
              << (tieneArmaEquipada ? armaEquipada.getNombre() : "Ninguna") << "\n";
    std::cout << "  Armadura Equipada : "
              << (tieneArmaduraEquipada ? armaduraEquipada.getNombre() : "Ninguna") << "\n";
    if (ubicacionActual != nullptr) {
        std::cout << "  Ubicación Actual  : " << ubicacionActual->getNombre() << "\n";
    }
    std::cout << "+==============================================================+\n";
}

int Jugador::getNivel() const {
    return nivel;
}

int Jugador::getExperiencia() const {
    return experiencia;
}

int Jugador::getExperienciaSiguienteNivel() const {
    return experienciaSiguienteNivel;
}

Objeto Jugador::getArmaEquipada() const {
    return armaEquipada;
}

Objeto Jugador::getArmaduraEquipada() const {
    return armaduraEquipada;
}

bool Jugador::getTieneArmaEquipada() const {
    return tieneArmaEquipada;
}

bool Jugador::getTieneArmaduraEquipada() const {
    return tieneArmaduraEquipada;
}

const std::vector<Objeto>& Jugador::getInventario() const {
    return inventario;
}

Habitacion* Jugador::getUbicacionActual() const {
    return ubicacionActual;
}

void Jugador::setNivel(int nuevoNivel) {
    if (nuevoNivel < 1) {
        nivel = 1;
    } else {
        nivel = nuevoNivel;
    }
}

void Jugador::setExperiencia(int nuevaExperiencia) {
    if (nuevaExperiencia < 0) {
        experiencia = 0;
    } else {
        experiencia = nuevaExperiencia;
    }
}

void Jugador::setExperienciaSiguienteNivel(int nuevaExpSiguiente) {
    if (nuevaExpSiguiente < 10) {
        experienciaSiguienteNivel = 10;
    } else {
        experienciaSiguienteNivel = nuevaExpSiguiente;
    }
}

void Jugador::setArmaEquipada(const Objeto& arma, bool equipada) {
    armaEquipada = arma;
    tieneArmaEquipada = equipada;
}

void Jugador::setArmaduraEquipada(const Objeto& armadura, bool equipada) {
    armaduraEquipada = armadura;
    tieneArmaduraEquipada = equipada;
}

void Jugador::setUbicacionActual(Habitacion* nuevaUbicacion) {
    ubicacionActual = nuevaUbicacion;
}

