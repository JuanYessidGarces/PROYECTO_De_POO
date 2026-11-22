cmake_minimum_required(VERSION 3.16)
project(solo_leveling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solo_leveling main.cpp
        Entidad.h
        Entidad.cpp
        Objeto.h
        Objeto.cpp
        Enemigo.h
        Enemigo.h
        Enemigo.cpp
        Habitacion.h
        Habitacion.cpp
        Jugador.h
        Jugador.cpp
        Goblin.h
        Goblin.cpp)