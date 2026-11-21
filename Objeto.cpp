#include "Objeto.h"

Objeto::Objeto()
    : nombre("Ninguno"), descripcion("Sin objeto"), tipo(TipoObjeto::POCION), bonificador(0) {
}

Objeto::Objeto(const std::string& nombre, const std::string& descripcion, TipoObjeto tipo, int bonificador)
    : nombre(nombre), descripcion(descripcion), tipo(tipo), bonificador(0) {
    setBonificador(bonificador);
}

std::string Objeto::getNombre() const {
    return nombre;
}

std::string Objeto::getDescripcion() const {
    return descripcion;
}

TipoObjeto Objeto::getTipo() const {
    return tipo;
}

std::string Objeto::getTipoTexto() const {
    if (tipo == TipoObjeto::POCION) {
        return "Poción";
    } else if (tipo == TipoObjeto::ARMA) {
        return "Arma";
    } else {
        return "Armadura";
    }
}

int Objeto::getBonificador() const {
    return bonificador;
}

void Objeto::setNombre(const std::string& nuevoNombre) {
    if (!nuevoNombre.empty()) {
        nombre = nuevoNombre;
    }
}

void Objeto::setDescripcion(const std::string& nuevaDescripcion) {
    if (!nuevaDescripcion.empty()) {
        descripcion = nuevaDescripcion;
    }
}

void Objeto::setTipo(TipoObjeto nuevoTipo) {
    tipo = nuevoTipo;
}

void Objeto::setBonificador(int nuevoBonificador) {
    // Validacion: el bonificador no puede ser negativo
    if (nuevoBonificador < 0) {
        bonificador = 0;
    } else {
        bonificador = nuevoBonificador;
    }
}