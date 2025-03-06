#include "cazadores_dragones.h"
#include "utilidades.h"

// Función para visualizar los dragones (simulada)
void visualizarDragones(void) {
    printf(MAGENTA "\tLISTADO DE DRAGONES:\n" SC);
    printf(AZUL_C "\t1) Dragón de Fuego\n");
    printf(AZUL_C "\t2) Dragón del Viento\n");
    printf(AZUL_C "\t3) Dragón de la Tierra\n");
}

// Función para añadir un cazador
void añadirCazador(Cazador **cazadores, int *totalCazadores) {
    *totalCazadores += 1;
    *cazadores = realloc(*cazadores, (*totalCazadores) * sizeof(Cazador));
    Cazador nuevoCazador;

    printf(MAGENTA "\tIngrese el nombre del cazador: ");
    scanf("%s", nuevoCazador.nombre);

    printf(MAGENTA "\tIngrese el nombre del arma: ");
    scanf("%s", nuevoCazador.arma);

    printf(MAGENTA "\tIngrese el ataque del cazador: ");
    scanf("%d", &nuevoCazador.ataque);

    printf(MAGENTA "\tIngrese la vida del cazador: ");
    scanf("%d", &nuevoCazador.vida);

    printf(MAGENTA "\tIngrese el oro del cazador: ");
    scanf("%d", &nuevoCazador.oro);

    printf(MAGENTA "\tIngrese la descripción del cazador: ");
    getchar();  // Limpiar el buffer
    fgets(nuevoCazador.descripcion, MAXDESCRPCION, stdin);

    // Guardar al cazador en la lista
    (*cazadores)[*totalCazadores - 1] = nuevoCazador;

    printf(AZUL_C "\tCazador añadido correctamente.\n" SC);
}

// Función para inicializar un dragón
void inicializarDragon(Dragon *dragon, int id, char *nombre, int vida, int daño, int resistencia, char *pasiva, char *descripcion, int oro) {
    dragon->id = id;
    strcpy(dragon->nombre, nombre);
    dragon->vida = vida;
    dragon->daño = daño;
    dragon->resistencia = resistencia;
    strcpy(dragon->pasiva, pasiva);
    strcpy(dragon->descripcion, descripcion);
    dragon->oro = oro;
}

// Función para mostrar un dragón
void mostrarDragon(Dragon *dragon) {
    printf(AZUL_C "\tID: %d\n", dragon->id);
    printf(AZUL_C "\tNombre: %s\n", dragon->nombre);
    printf(AZUL_C "\tVida: %d\n", dragon->vida);
    printf(AZUL_C "\tDaño: %d\n", dragon->daño);
    printf(AZUL_C "\tResistencia: %d\n", dragon->resistencia);
    printf(AZUL_C "\tPasiva: %s\n", dragon->pasiva);
    printf(AZUL_C "\tDescripción: %s\n", dragon->descripcion);
    printf(AZUL_C "\tOro: %d\n", dragon->oro);
}

// Función para añadir un nuevo dragón
void añadir_dragon(Dragon **dragones, int *totalDragones) {
    *totalDragones += 1;
    *dragones = realloc(*dragones, (*totalDragones) * sizeof(Dragon));
    Dragon nuevoDragon;

    printf(MAGENTA "\tIngrese el nombre del dragón: ");
    scanf("%s", nuevoDragon.nombre);

    printf(MAGENTA "\tIngrese la vida del dragón: ");
    scanf("%d", &nuevoDragon.vida);

    printf(MAGENTA "\tIngrese el daño del dragón: ");
    scanf("%d", &nuevoDragon.daño);

    printf(MAGENTA "\tIngrese la resistencia del dragón: ");
    scanf("%d", &nuevoDragon.resistencia);

    printf(MAGENTA "\tIngrese la pasiva del dragón: ");
    getchar();  // Limpiar el buffer
    fgets(nuevoDragon.pasiva, MAX_DESCRIPCION, stdin);

    printf(MAGENTA "\tIngrese la descripción del dragón: ");
    fgets(nuevoDragon.descripcion, MAX_DESCRIPCION, stdin);

    printf(MAGENTA "\tIngrese la cantidad de oro que posee el dragón: ");
    scanf("%d", &nuevoDragon.oro);

    // Guardar al dragón en la lista
    (*dragones)[*totalDragones - 1] = nuevoDragon;

    printf(AZUL_C "\tDragón añadido correctamente.\n" SC);
}

// Función para seleccionar un dragón
void seleccionarDragon(Dragon *dragones, int totalDragones) {
    int id;
    printf(MAGENTA "\tSeleccione el ID del dragón: ");
    scanf("%d", &id);

    if (id < 1 || id > totalDragones) {
        printf(ROJO "\tID inválido.\n" SC);
    } else {
        mostrarDragon(&dragones[id - 1]);
    }
}



