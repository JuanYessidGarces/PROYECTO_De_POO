#include "Juego.h"
#include "Goblin.h"
#include "EstatuaAltar.h"
#include "SerpienteKasaka.h"
#include "JefeIgris.h"
#include <iostream>
#include <limits>

Juego::Juego()
    : jugador("Sung Jin-Woo"), juegoEnCurso(false) {
}

Juego::~Juego() {
    // Composicion: Juego es dueño de todas las Habitaciones y libera su memoria
    limpiarMapa();
}

void Juego::limpiarMapa() {
    for (size_t i = 0; i < habitaciones.size(); i++) {
        if (habitaciones[i] != nullptr) {
            delete habitaciones[i];
            habitaciones[i] = nullptr;
        }
    }
    habitaciones.clear();
}

void Juego::inicializarMapa() {
    limpiarMapa();

    // 1. Entrada de la Mazmorra Rango D (ID: 0)
    Habitacion* habEntrada = new Habitacion(
        0,
        "Entrada de la Mazmorra Rango D",
        "El portal dimensional azul brilla a tus espaldas. El aire es húmedo y frío.\n"
        "Antorchas tenues iluminan un pasillo de piedra musgosa que se adentra en la oscuridad."
    );
    habEntrada->agregarObjeto(Objeto(
        "Poción de Curación Menor",
        "Frasco básico de la Asociación de Cazadores (+25 HP)",
        TipoObjeto::POCION,
        25
    ));

    // 2. Tunel de los Goblins (ID: 1)
    Habitacion* habTunel = new Habitacion(
        1,
        "Túnel de los Goblins",
        "Un corredor estrecho lleno de huesos y restos de antiguos equipos de incursión.\n"
        "Al fondo se distingue una misteriosa puerta doble de piedra tallada."
    );
    habTunel->agregarEnemigo(new Goblin(
        "Goblin Saqueador",
        16,  // Vida maxima (balanceado para que un Rango E sobreviva a duras penas)
        8,   // Ataque
        1,   // Defensa
        0,   // Antes de despertar en el Altar no se gana EXP del Sistema
        false
    ));

    // 3. Altar de la Doble Mazmorra - Templo de Cartenon (ID: 2)
    Habitacion* habAltar = new Habitacion(
        2,
        "Altar de la Doble Mazmorra (Templo de Cartenon)",
        "Una colosal cámara subterránea rodeada de estatuas de piedra gigantescas.\n"
        "En el centro se alza el altar sacrificial donde despertaste como 'Jugador' del Sistema.\n"
        "Hacia el oeste se abre el portal del pantano tóxico y hacia el este resuenan armaduras."
    );
    habAltar->agregarEnemigo(new EstatuaAltar(
        "Estatua del Altar de Cartenon",
        500, // Vida colosal
        16,  // Ataque base (14 a 18 por turno sin matar al jugador antes de 1 HP)
        50,  // Defensa impenetrable
        50   // Experiencia otorgada al superar la prueba secreta y despertar
    ));
    habAltar->agregarObjeto(Objeto(
        "Colmillo de Kasaka",
        "Daga forjada con el colmillo de la gran serpiente azul (+8 Ataque)",
        TipoObjeto::ARMA,
        8
    ));
    habAltar->agregarObjeto(Objeto(
        "Poción de Curación Media",
        "Infusión concentrada de maná regenerativo (+45 HP)",
        TipoObjeto::POCION,
        45
    ));

    // 4. Pantano Subterraneo (ID: 3)
    Habitacion* habPantano = new Habitacion(
        3,
        "Pantano Subterráneo",
        "Una caverna inundada por aguas turbias y vapores tóxicos. Las columnas de roca\n"
        "están marcadas por enormes escamas azules y ácido corrosivo."
    );
    habPantano->agregarEnemigo(new SerpienteKasaka(
        "Serpiente Venenosa Kasaka",
        85,  // Vida maxima
        16,  // Ataque fisico
        5,   // Defensa
        100, // Experiencia otorgada
        6    // Daño adicional por veneno
    ));
    habPantano->agregarObjeto(Objeto(
        "Armadura de Escamas",
        "Peto ligero reforzado con escamas resistentes al veneno (+5 Defensa)",
        TipoObjeto::ARMADURA,
        5
    ));

    // 5. Galeria de los Caballeros (ID: 4)
    Habitacion* habGaleria = new Habitacion(
        4,
        "Galería de los Caballeros",
        "Un majestuoso pasillo de mármol agrietado flanqueado por armaduras medievales.\n"
        "Al fondo hacia el norte, dos enormes puertas carmesí custodian el Salón del Trono."
    );
    habGaleria->agregarEnemigo(new Goblin(
        "Caballero de Acero",
        115, // Vida maxima
        24,  // Ataque
        12,  // Defensa elevada
        140, // Experiencia otorgada
        true // Variante de elite
    ));
    habGaleria->agregarObjeto(Objeto(
        "Elixir del Sistema",
        "Recompensa divina de la tienda del Sistema que restaura gran vitalidad (+80 HP)",
        TipoObjeto::POCION,
        80
    ));

    // 6. Salon del Trono Carmesi (ID: 5)
    Habitacion* habTrono = new Habitacion(
        5,
        "Salón del Trono Carmesí",
        "Columnas imperiales destruidas rodean un trono vacío cubierto por un manto rojo.\n"
        "Frente a las gradas aguarda en silencio el guardián más leal de la sala: Igris."
    );
    habTrono->agregarEnemigo(new JefeIgris(
        "Igris, el Comandante Sangriento",
        180, // Vida maxima
        28,  // Ataque base
        14,  // Defensa
        300, // Experiencia otorgada
        15   // Bono de daño critico de Corte Carmesi
    ));

    // Conexion de salidas usando std::map<std::string, Habitacion*>
    // Sala 0 <-> Sala 1
    habEntrada->conectarSalida("norte", habTunel);
    habTunel->conectarSalida("sur", habEntrada);

    // Sala 1 <-> Sala 2
    habTunel->conectarSalida("norte", habAltar);
    habAltar->conectarSalida("sur", habTunel);

    // Sala 2 <-> Sala 3 (oeste)
    habAltar->conectarSalida("oeste", habPantano);
    habPantano->conectarSalida("este", habAltar);

    // Sala 2 <-> Sala 4 (este)
    habAltar->conectarSalida("este", habGaleria);
    habGaleria->conectarSalida("oeste", habAltar);

    // Sala 4 <-> Sala 5 (norte)
    habGaleria->conectarSalida("norte", habTrono);
    habTrono->conectarSalida("sur", habGaleria);

    // Almacenar las 6 habitaciones en el vector de Juego
    habitaciones.push_back(habEntrada);
    habitaciones.push_back(habTunel);
    habitaciones.push_back(habAltar);
    habitaciones.push_back(habPantano);
    habitaciones.push_back(habGaleria);
    habitaciones.push_back(habTrono);
}

void Juego::mostrarCinematica(const std::string& titulo, const std::vector<std::string>& parrafos) {
    std::cout << "\n+==================================================================+\n";
    std::cout << "  [ HISTORIA ] " << titulo << "\n";
    std::cout << "+==================================================================+\n";

    for (size_t i = 0; i < parrafos.size(); i++) {
        std::cout << "\n" << parrafos[i] << "\n";
        std::cout << "\n  [Presiona ENTER para continuar...]";
        if (std::cin.eof()) {
            std::cout << "\n";
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "+==================================================================+\n";
}

void Juego::mostrarCinematicaHabitacion(Habitacion* habitacion) {
    if (habitacion == nullptr || habitacion->isVisitada()) {
        return;
    }

    habitacion->setVisitada(true);
    int id = habitacion->getId();
    std::vector<std::string> parrafos;

    if (id == 0) {
        parrafos.push_back(
            "  Cruzas el portal dimensional hacia la Entrada de la Mazmorra Rango D.\n"
            "  A simple vista parece una cueva común y húmeda infestada de bestias\n"
            "  mágicas menores (Goblins), iluminada apenas por cristales de maná opacos."
        );
        parrafos.push_back(
            "  Siendo un Cazador Rango E con estadísticas mínimas (Vida: 50, Ataque: 5,\n"
            "  Defensa: 1), sabes que incluso la criatura más débil puede matarte.\n"
            "  Aferras tu daga desgastada, revisas el suelo en busca de suministros\n"
            "  y te preparas para avanzar hacia el norte."
        );
        mostrarCinematica("ACTO I: LA CUEVA DE LAS BESTIAS MENORES", parrafos);
    } else if (id == 1) {
        parrafos.push_back(
            "  Te adentras en el Túnel de los Goblins. El pasillo se estrecha entre\n"
            "  escombros y restos de antiguos cazadores que subestimaron el peligro\n"
            "  de las profundidades."
        );
        parrafos.push_back(
            "  De repente, un Goblin Saqueador salta desde las sombras con una daga\n"
            "  oxidada. Sin magia poderosa que te respalde, tendrás que usar todo tu\n"
            "  ingenio para sobrevivir antes de alcanzar el túnel oculto del fondo."
        );
        mostrarCinematica("ACTO I: SUPERVIVENCIA EN EL TÚNEL", parrafos);
    } else if (id == 2) {
        parrafos.push_back(
            "  Al cruzar las pesadas puertas al final del túnel oculto, el escuadrón\n"
            "  descubre el Templo de Cartenon: una cámara subterránea rodeada de\n"
            "  estatuas de piedra gigantescas. De repente, las puertas se sellan de\n"
            "  golpe y las estatuas cobran vida, aniquilando con rayos de energía a\n"
            "  quienes intentan huir."
        );
        parrafos.push_back(
            "  En medio de la masacre, logras descifrar las tablas de piedra con los\n"
            "  Tres Mandamientos del Templo: \"Primero: Adora a Dios. Segundo: Alaba\n"
            "  a Dios. Tercero: Demuestra tu fe\". Los cazadores sobreviven a duras\n"
            "  penas siguiendo tus indicaciones, pero pierden miembros y fuerzas."
        );
        parrafos.push_back(
            "  En la prueba final, el altar exige que alguien se quede atrás mientras\n"
            "  los demás escapan por la puerta. Herido y sin una pierna, decides\n"
            "  sacrificarte quedándote solo en el altar para salvar a los últimos\n"
            "  sobrevivientes."
        );
        parrafos.push_back(
            "  Las puertas se cierran. Una colosal Estatua del Altar desciende de su\n"
            "  pedestal empuñando una lanza de piedra gigante y se abalanza sobre ti..."
        );
        mostrarCinematica("ACTO II: EL TEMPLO DE CARTENON Y LOS TRES MANDAMIENTOS", parrafos);
    } else if (id == 3) {
        parrafos.push_back(
            "  Tras despertar con 'El Sistema' y completar entrenamientos diarios\n"
            "  extremos, recibes como recompensa una Llave de Mazmorra Instantánea\n"
            "  que abre un portal distorsionado hacia este Pantano Subterráneo tóxico."
        );
        parrafos.push_back(
            "  Las aguas oscuras se agitan violentamente: ante ti emerge la temible\n"
            "  Serpiente Venenosa Kasaka, una bestia gigante de escamas azules casi\n"
            "  impenetrables que pondrá a prueba tu nuevo poder como Jugador."
        );
        mostrarCinematica("ACTO III: LA PRUEBA DE LA SERPIENTE KASAKA", parrafos);
    } else if (id == 4) {
        parrafos.push_back(
            "  Tras superar varias mazmorras y alcanzar un nivel superior, 'El Sistema'\n"
            "  hace sonar una notificación urgente frente a tus ojos:\n"
            "  [ ¡SE HA ACTIVADO LA MISIÓN DE CAMBIO DE CLASE! ]"
        );
        parrafos.push_back(
            "  Un portal te transporta a la Galería de los Caballeros, una fortaleza\n"
            "  oscura custodiada por armaduras vivientes de acero que protegen sin\n"
            "  descanso el acceso al Salón del Trono."
        );
        mostrarCinematica("ACTO IV: LA MISIÓN DE CAMBIO DE CLASE", parrafos);
    } else if (id == 5) {
        parrafos.push_back(
            "  Empujas los enormes portones y entras al Salón del Trono Carmesí.\n"
            "  Frente a un trono vacío de piedra oscura aguarda Igris, el Comandante\n"
            "  Sangriento, un caballero de armadura carmesí y capa desgarrada."
        );
        parrafos.push_back(
            "  Igris desenfunda su espadón en silencio absoluto, reconociéndote como\n"
            "  un rival digno para probar si mereces obtener el verdadero poder del\n"
            "  Monarca. ¡El combate definitivo comienza!"
        );
        mostrarCinematica("ACTO FINAL: IGRIS, EL COMANDANTE SANGRIENTO", parrafos);
    }
}

void Juego::iniciar() {
    bool salirMenuPrincipal = false;

    while (!salirMenuPrincipal) {
        std::cout << "\n==================================================================\n";
        std::cout << "          SOLO LEVELING: EL DESPERTAR DEL MONARCA (RPG)           \n";
        std::cout << "==================================================================\n";
        std::cout << "  1. Nueva Partida\n";
        std::cout << "  2. Salir\n";
        std::cout << "==================================================================\n";

        int opcion = leerOpcionNumerica(1, 2);

        if (opcion == 1) {
            nuevaPartida();
            bucleExploracion();
        } else if (opcion == 2) {
            std::cout << "\n[EL SISTEMA] Cerrando la interfaz del Jugador. ¡Hasta pronto, Cazador!\n";
            salirMenuPrincipal = true;
        }
    }
}

void Juego::nuevaPartida() {
    inicializarMapa();
    jugador = Jugador("Sung Jin-Woo");
    jugador.setUbicacionActual(habitaciones[0]);
    juegoEnCurso = true;

    // Prologo interactivo por parrafos: Medicion de Rango E y entrada a la mazmorra
    std::vector<std::string> prologo;
    prologo.push_back(
        "  Sung Jin-Woo llega a la sala de evaluación de la Asociación de Cazadores,\n"
        "  donde los aspirantes y cazadores de élite (Rango A y S) miden su poder\n"
        "  mágico antes de entrar a una incursión. Sin habilidades destacables,\n"
        "  Jin-Woo arriesga su vida en mazmorras de bajo nivel para pagar las\n"
        "  facturas hospitalarias de su madre enferma."
    );
    prologo.push_back(
        "  Jin-Woo avanza nervioso y coloca su mano sobre la maquinaria especial\n"
        "  de medición de maná (el cristal detector de rango). La máquina apenas\n"
        "  parpadea con una lectura mínima y muestra en pantalla:\n\n"
        "                         >>> [ RANGO E ] <<<"
    );
    prologo.push_back(
        "  Al ver el resultado del rango más bajo existente, todos los cazadores de\n"
        "  élite presentes en la sala se burlan de él a carcajadas, humillándolo y\n"
        "  llamándolo \"el cazador más débil de toda la humanidad\". Decidido a\n"
        "  demostrar su valor y sobrevivir para pagar el tratamiento de su madre,\n"
        "  Jin-Woo aprieta los puños y entra a la mazmorra de Rango D."
    );
    prologo.push_back(
        "  Tras derrotar al primer grupo de bestias en la cueva inicial, el escuadrón\n"
        "  descubre un túnel oculto que no aparecía en los registros de la Asociación\n"
        "  y deciden explorarlo, llevándolos hacia las profundidades..."
    );

    mostrarCinematica("PRÓLOGO: EL CAZADOR MÁS DÉBIL DE LA HUMANIDAD", prologo);
}

void Juego::bucleExploracion() {
    while (juegoEnCurso && jugador.estaVivo()) {
        Habitacion* actual = jugador.getUbicacionActual();
        if (actual == nullptr) {
            break;
        }

        // Si es la primera vez que entra a esta habitacion, muestra su cinematica
        if (!actual->isVisitada()) {
            mostrarCinematicaHabitacion(actual);
        }

        // Si hay enemigos vivos en la habitacion, inicia combate por turnos automaticamente
        while (actual->tieneEnemigosVivos() && jugador.estaVivo() && juegoEnCurso) {
            Enemigo* enemigoActivo = actual->getPrimerEnemigoVivo();
            if (enemigoActivo != nullptr) {
                iniciarCombate(enemigoActivo);
            }
        }

        // Verificar si el juego termino tras el combate (victoria contra Igris o muerte)
        if (!juegoEnCurso || !jugador.estaVivo()) {
            break;
        }

        // Mostrar estado de la habitacion y menu de exploracion
        actual->mostrarInformacion();

        std::cout << "Opciones de Exploración:\n";
        std::cout << "  1. Moverse\n";
        std::cout << "  2. Recoger objetos\n";
        std::cout << "  3. Ver inventario / Usar o Equipar objeto\n";
        std::cout << "  4. Ver estado de Jugador (Ventana del Sistema)\n";
        std::cout << "  5. Salir al menú principal\n";

        int opcion = leerOpcionNumerica(1, 5);

        if (opcion == 1) {
            moverJugador();
        } else if (opcion == 2) {
            recogerObjetosHabitacion();
        } else if (opcion == 3) {
            gestionarInventario();
        } else if (opcion == 4) {
            jugador.mostrarEstado();
        } else if (opcion == 5) {
            std::cout << "\n[EL SISTEMA] Regresando al menú principal...\n";
            juegoEnCurso = false;
        }
    }
}

bool Juego::procesarDecisionAltar(Enemigo* estatua) {
    std::cout << "\n+==================================================================+\n";
    std::cout << "|                      [ ALERTA DEL SISTEMA ]                      |\n";
    std::cout << "+==================================================================+\n";
    std::cout << "  Cuando las estatuas te rodean y la lanza de piedra está a 0.02\n";
    std::cout << "  segundos de atravesar tu corazón, el tiempo se detiene por completo.\n\n";
    std::cout << "  [ALERTA DEL SISTEMA] Tu corazón está a punto de detenerse (HP: 1).\n";
    std::cout << "  Has demostrado el coraje de los débiles frente a la muerte.\n";
    std::cout << "  ¿Aceptas convertirte en JUGADOR?\n\n";
    std::cout << "  1. Aceptar\n";
    std::cout << "  2. Rechazar\n";
    std::cout << "+==================================================================+\n";

    int decision = leerOpcionNumerica(1, 2);

    if (decision == 2) {
        std::cout << "\n+==================================================================+\n";
        std::cout << "  Rechazas el llamado. La pantalla holográfica de El Sistema se\n";
        std::cout << "  desvanece en la oscuridad y el tiempo vuelve a correr...\n";
        std::cout << "  ¡La colosal lanza de piedra de la estatua atraviesa tu pecho!\n";
        std::cout << "+==================================================================+\n";
        jugador.setVida(0);
        return false;
    }

    // Si elige 1 (Aceptar): ejecuta despertar() y muestra la cinematica epica
    jugador.despertar();

    std::vector<std::string> parrafosDespertar;
    parrafosDespertar.push_back(
        "  ¡[Misión Secreta 'El Coraje de los Débiles' completada]! Una deslumbrante\n"
        "  luz azul envuelve todo tu cuerpo sobre el altar sacrificial mientras\n"
        "  tus heridas mortales se regeneran por completo."
    );
    parrafosDespertar.push_back(
        "  Las colosales estatuas de piedra del Templo de Cartenon se detienen al\n"
        "  instante, se resquebrajan y colapsan ante la autoridad de 'El Sistema'.\n"
        "  Ya no eres un simple Rango E: ¡ahora eres un JUGADOR capaz de subir de\n"
        "  nivel, equipar artefactos y volverte fuerte sin límites!"
    );
    mostrarCinematica("EL DESPERTAR DEL JUGADOR SUNG JIN-WOO", parrafosDespertar);

    if (estatua != nullptr) {
        estatua->setVida(0);
    }
    return true;
}

void Juego::iniciarCombate(Enemigo* enemigo) {
    if (enemigo == nullptr) {
        return;
    }

    std::cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    std::cout << " ¡ALERTA DE COMBATE! Un enemigo hostil bloquea tu camino:\n";
    std::cout << " -> " << enemigo->getNombre() << " [Tipo: " << enemigo->getTipo()
              << " | HP: " << enemigo->getVida() << "/" << enemigo->getVidaMaxima()
              << " | ATK: " << enemigo->getAtaque() << " | DEF: " << enemigo->getDefensa() << "]\n";
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

    while (enemigo->estaVivo() && jugador.estaVivo()) {
        std::cout << "\n--- TURNO DE COMBATE ---\n";
        std::cout << "  [" << jugador.getNombre() << " HP: " << jugador.getVida() << "/"
                  << jugador.getVidaMaxima() << "] vs ["
                  << enemigo->getNombre() << " HP: " << enemigo->getVida() << "/"
                  << enemigo->getVidaMaxima() << "]\n";
        std::cout << "  1. Atacar\n";
        std::cout << "  2. Usar objeto del inventario\n";
        std::cout << "  3. Ver estado\n";

        int opcion = leerOpcionNumerica(1, 3);
        bool turnoConsumido = false;

        if (opcion == 1) {
            // Ataque del jugador hacia el enemigo
            jugador.atacar(*enemigo);
            turnoConsumido = true;
        } else if (opcion == 2) {
            const std::vector<Objeto>& inv = jugador.getInventario();
            if (inv.empty()) {
                std::cout << "\n[EL SISTEMA] Tu inventario está vacío. No puedes usar objetos.\n";
            } else {
                jugador.mostrarInventario();
                std::cout << "  0. Cancelar\n";
                int idx = leerOpcionNumerica(0, static_cast<int>(inv.size()));
                if (idx > 0) {
                    turnoConsumido = jugador.usarOEquiparObjeto(idx - 1);
                }
            }
        } else if (opcion == 3) {
            jugador.mostrarEstado();
        }

        // Si el jugador realizo su accion y el enemigo sigue vivo, el enemigo contraataca
        if (turnoConsumido && enemigo->estaVivo()) {
            // Polimorfismo: invoca dinamicamente el metodo atacar() de la subclase correspondiente
            enemigo->atacar(jugador);

            // Evento especial: si se enfrenta a EstatuaAltar y Jin-Woo queda exactamente a 1 HP
            if (enemigo->getTipo() == "EstatuaAltar" && jugador.getVida() == 1 && !jugador.isDespertado()) {
                procesarDecisionAltar(enemigo);
                break;
            }
        }
    }

    if (!jugador.estaVivo()) {
        std::cout << "\n+==============================================================+\n";
        std::cout << "|                      [ GAME OVER ]                           |\n";
        std::cout << "|       Tu ritmo cardíaco se ha detenido. HAS MUERTO.          |\n";
        std::cout << "+==============================================================+\n";
        juegoEnCurso = false;
        return;
    }

    // El enemigo fue derrotado (o colapso tras el despertar en el Altar)
    std::string tipoDerrotado = enemigo->getTipo();
    std::string nombreDerrotado = enemigo->getNombre();
    int expRecompensa = enemigo->getExperienciaOtorgada();

    std::cout << "\n[VICTORIA] ¡Has superado a " << nombreDerrotado << "!\n";
    jugador.ganarExperiencia(expRecompensa);

    // Liberar memoria dinamica del enemigo derrotado en la habitacion actual
    if (jugador.getUbicacionActual() != nullptr) {
        jugador.getUbicacionActual()->eliminarEnemigosDerrotados();
    }

    // Si el enemigo derrotado era el Jefe Final Igris, mostrar final epico
    if (tipoDerrotado == "JefeIgris") {
        mostrarMensajeVictoriaFinal();
        juegoEnCurso = false;
    }
}

void Juego::moverJugador() {
    Habitacion* actual = jugador.getUbicacionActual();
    if (actual == nullptr) {
        return;
    }

    std::cout << "\nIngresa la dirección a la que deseas moverte (norte / sur / este / oeste): ";
    std::string direccion = leerTextoMinusculas();

    Habitacion* destino = actual->getSalida(direccion);
    if (destino == nullptr) {
        std::cout << "\n[EL SISTEMA] No hay ninguna salida en la dirección '" << direccion << "'.\n";
    } else {
        jugador.setUbicacionActual(destino);
        std::cout << "\n[EL SISTEMA] Te desplazas hacia el " << direccion
                  << " -> " << destino->getNombre() << ".\n";
    }
}

void Juego::recogerObjetosHabitacion() {
    Habitacion* actual = jugador.getUbicacionActual();
    if (actual == nullptr) {
        return;
    }

    if (!actual->hayObjetos()) {
        std::cout << "\n[EL SISTEMA] No hay objetos para recoger en esta habitación.\n";
        return;
    }

    std::vector<Objeto> objetosSala = actual->recogerObjetos();
    for (size_t i = 0; i < objetosSala.size(); i++) {
        jugador.agregarObjeto(objetosSala[i]);
        std::cout << "[EL SISTEMA] Has obtenido: [" << objetosSala[i].getNombre()
                  << "] (" << objetosSala[i].getTipoTexto()
                  << " +" << objetosSala[i].getBonificador() << ").\n";
    }
}

void Juego::gestionarInventario() {
    jugador.mostrarInventario();
    const std::vector<Objeto>& inv = jugador.getInventario();
    if (inv.empty()) {
        return;
    }

    std::cout << "Ingresa el número del objeto para Usar/Equipar (o 0 para volver): ";
    int opcion = leerOpcionNumerica(0, static_cast<int>(inv.size()));
    if (opcion > 0) {
        jugador.usarOEquiparObjeto(opcion - 1);
    }
}

void Juego::mostrarMensajeVictoriaFinal() {
    std::vector<std::string> epilogo;
    epilogo.push_back(
        "  Igris, el Comandante Sangriento, cae de rodillas ante ti en el Salón del\n"
        "  Trono Carmesí. Una densa niebla púrpura y negra emerge de su armadura\n"
        "  mientras una nueva ventana holográfica ilumina la cámara imperial."
    );
    epilogo.push_back(
        "  [EL SISTEMA] ¡Has superado la Misión de Cambio de Clase!\n"
        "  Por tu desempeño extraordinario, la clase oculta 'Nigromante' evoluciona\n"
        "  al título supremo que cambiará tu destino para siempre:\n\n"
        "                >>> ¡MONARCA DE LAS SOMBRAS! <<<\n"
        "                * Habilidad única: Extracción de Sombras."
    );
    epilogo.push_back(
        "  Te acercas al caballero caído, extiendes tu mano hacia la oscuridad\n"
        "  y pronuncias el comando absoluto de tu nuevo ejército:\n\n"
        "                       \"... ¡SURGE! (ARISE)\"\n\n"
        "  La sombra carmesí de Igris se levanta de entre los muertos y se arrodilla\n"
        "  lealmente ante su nuevo rey. ¡FELICIDADES! Has completado el juego."
    );

    mostrarCinematica("EPÍLOGO: EL NACIMIENTO DEL MONARCA DE LAS SOMBRAS", epilogo);
}

int Juego::leerOpcionNumerica(int min, int max) {
    int opcion = 0;
    while (true) {
        std::cout << "\nSeleccione una opción (" << min << "-" << max << "): ";
        std::cin >> opcion;

        if (std::cin.eof()) {
            // Manejo seguro de fin de entrada (EOF)
            return max;
        }

        if (std::cin.fail() || opcion < min || opcion > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ENTRADA INVÁLIDA] Por favor, ingrese un número entero entre "
                      << min << " y " << max << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        }
    }
}

std::string Juego::leerTextoMinusculas() {
    std::string entrada;
    std::getline(std::cin, entrada);

    // Eliminar espacios al inicio y al final
    size_t inicio = 0;
    while (inicio < entrada.size() && (entrada[inicio] == ' ' || entrada[inicio] == '\t' || entrada[inicio] == '\r')) {
        inicio++;
    }
    size_t fin = entrada.size();
    while (fin > inicio && (entrada[fin - 1] == ' ' || entrada[fin - 1] == '\t' || entrada[fin - 1] == '\r')) {
        fin--;
    }
    entrada = entrada.substr(inicio, fin - inicio);

    // Convertir mayusculas ASCII a minusculas manualmente
    for (size_t i = 0; i < entrada.size(); i++) {
        if (entrada[i] >= 'A' && entrada[i] <= 'Z') {
            entrada[i] = entrada[i] + ('a' - 'A');
        }
    }
    return entrada;
}

