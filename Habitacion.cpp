#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion(int id, const std::string& nombre, const std::string& descripcion)
    : id(0), nombre(nombre), descripcion(descripcion), visitada(false) {
    setId(id);
}

Habitacion::~Habitacion() {
    // Liberacion de memoria dinamica de todos los enemigos restantes en la habitacion
    limpiarEnemigos();
}

void Habitacion::conectarSalida(const std::string& direccion, Habitacion* destino) {
    if (!direccion.empty() && destino != nullptr) {
        salidas[direccion] = destino;
    }
}

Habitacion* Habitacion::getSalida(const std::string& direccion) const {
    std::map<std::string, Habitacion*>::const_iterator it = salidas.find(direccion);
    if (it != salidas.end()) {
        return it->second;
    }
    return nullptr;
}

const std::map<std::string, Habitacion*>& Habitacion::getSalidas() const {
    return salidas;
}

void Habitacion::agregarObjeto(const Objeto& objeto) {
    objetos.push_back(objeto);
}

bool Habitacion::hayObjetos() const {
    return !objetos.empty();
}

std::vector<Objeto> Habitacion::recogerObjetos() {
    std::vector<Objeto> recolectados = objetos;
    objetos.clear();
    return recolectados;
}

const std::vector<Objeto>& Habitacion::getObjetos() const {
    return objetos;
}

void Habitacion::limpiarObjetos() {
    objetos.clear();
}

void Habitacion::agregarEnemigo(Enemigo* enemigo) {
    if (enemigo != nullptr) {
        enemigos.push_back(enemigo);
    }
}

bool Habitacion::tieneEnemigosVivos() const {
    for (size_t i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
            return true;
        }
    }
    return false;
}

Enemigo* Habitacion::getPrimerEnemigoVivo() const {
    for (size_t i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] != nullptr && enemigos[i]->estaVivo()) {
            return enemigos[i];
        }
    }
    return nullptr;
}

void Habitacion::eliminarEnemigosDerrotados() {
    std::vector<Enemigo*> sobrevivientes;
    for (size_t i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] != nullptr) {
            if (enemigos[i]->estaVivo()) {
                sobrevivientes.push_back(enemigos[i]);
            } else {
                // Liberamos la memoria del enemigo derrotado
                delete enemigos[i];
            }
        }
    }
    enemigos = sobrevivientes;
}

void Habitacion::limpiarEnemigos() {
    for (size_t i = 0; i < enemigos.size(); i++) {
        if (enemigos[i] != nullptr) {
            delete enemigos[i];
            enemigos[i] = nullptr;
        }
    }
    enemigos.clear();
}

const std::vector<Enemigo*>& Habitacion::getEnemigos() const {
    return enemigos;
}

void Habitacion::mostrarInformacion() const {
    std::cout << "\n==================================================================\n";
    std::cout << " UBICACIÓN: " << nombre << "\n";
    std::cout << "==================================================================\n";
    std::cout << descripcion << "\n";

    std::cout << "\n[Objetos en el suelo]: ";
    if (objetos.empty()) {
        std::cout << "Ninguno.\n";
    } else {
        std::cout << "\n";
        for (size_t i = 0; i < objetos.size(); i++) {
            std::cout << "  - " << objetos[i].getNombre() << " ["
                      << objetos[i].getTipoTexto() << " +"
                      << objetos[i].getBonificador() << "] ("
                      << objetos[i].getDescripcion() << ")\n";
        }
    }

    std::cout << "[Salidas disponibles]: ";
    if (salidas.empty()) {
        std::cout << "Ninguna.\n";
    } else {
        for (std::map<std::string, Habitacion*>::const_iterator it = salidas.begin();
             it != salidas.end(); ++it) {
            std::cout << "[" << it->first << " -> " << it->second->getNombre() << "] ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}

int Habitacion::getId() const {
    return id;
}

void Habitacion::setId(int nuevoId) {
    if (nuevoId < 0) {
        id = 0;
    } else {
        id = nuevoId;
    }
}

std::string Habitacion::getNombre() const {
    return nombre;
}

void Habitacion::setNombre(const std::string& nuevoNombre) {
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }
}

std::string Habitacion::getDescripcion() const {
    return descripcion;
}

void Habitacion::setDescripcion(const std::string& nuevaDescripcion) {
    if (!nuevaDescripcion.empty()) {
        descripcion = nuevaDescripcion;
    }
}

bool Habitacion::isVisitada() const {
    return visitada;
}

void Habitacion::setVisitada(bool estado) {
    visitada = estado;
}

