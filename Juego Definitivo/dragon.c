#include "utilidades.h"
#include "dragon.h"

void añadir_dragon(Dragon **dragones, int *totalDragones) {
    Dragon nuevoDragon;

    printf(AMARILLO"\nIntroduzca los datos del nuevo dragon: \n"SC);

    nuevoDragon.id = (*totalDragones) + 1;
    printf(AZUL_C"\tID: %d\n"SC, nuevoDragon.id);

    while (getchar() != '\n' && getchar() != EOF);
    printf(AZUL_C"\tNOMBRE: "SC);
    fgets(nuevoDragon.nombre, MAX_NOMBRE, stdin);
    nuevoDragon.nombre[strcspn(nuevoDragon.nombre, "\n")] = 0;

    do {
        printf(AZUL_C"\tVIDA: "SC);
        if (scanf("%d", &nuevoDragon.vida) != 1) {
            printf(ROJO"\tPor favor, introduce solo números.\n"SC);
            while (getchar() != '\n');
        } else if (nuevoDragon.vida < 300 || nuevoDragon.vida > 400) {
            printf(ROJO"\tEl rango de vida tiene que estar entre 300-400\n"SC);
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    do {
        printf(AZUL_C"\tATAQUE: "SC);
        if (scanf("%d", &nuevoDragon.ataque) != 1) {
            printf(ROJO"\tPor favor, introduce solo números.\n"SC);
            while (getchar() != '\n');
        } else if (nuevoDragon.ataque < 0 || nuevoDragon.ataque > 50) {
            printf(ROJO"\tEl rango de ataque tiene que estar entre 0-50\n"SC);
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    do {
        printf(AZUL_C"\tRESISTENCIA: "SC);
        if (scanf("%d", &nuevoDragon.resistencia) != 1) {
            printf(ROJO"\tPor favor, introduce solo números.\n"SC);
            while (getchar() != '\n');
        } else if (nuevoDragon.resistencia < 0 || nuevoDragon.resistencia > 20) {
            printf(ROJO"\tEl rango de resistencia tiene que estar entre 0-20\n"SC);
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    int seleccion;
    printf(AZUL_C"\tPASIVA:\n"SC);
    printf(ROJO"\t  1) +25%% resistencia a ataques\n"SC);
    printf(ROJO"\t  2) +25%% ataque\n"SC);
    printf(ROJO"\t  3) Se curará un 5%% de su vida después de cada ataque\n"SC);
    printf(ROJO"\t  4) Sin pasiva\n"SC);
    printf(MAGENTA"\tSelección: "SC);
    scanf("%d", &seleccion);
    while (getchar() != '\n');

    switch (seleccion) {
        case 1: strcpy(nuevoDragon.pasiva, "+25% resistencia a ataques"); break;
        case 2: strcpy(nuevoDragon.pasiva, "+25% ataque"); break;
        case 3: strcpy(nuevoDragon.pasiva, "Se curará un 5% de su vida después de cada ataque"); break;
        default: strcpy(nuevoDragon.pasiva, "Sin pasiva"); break;
    }

    printf(AZUL_C"\tDESCRIPCIÓN: "SC);
    scanf(" %[^\n]", nuevoDragon.descripcion);
    while (getchar() != '\n');

    nuevoDragon.oro = 100;

    Dragon *temp = realloc(*dragones, (*totalDragones + 1) * sizeof(Dragon));
    if (temp == NULL) {
        printf(ROJO"\tError al asignar memoria\n"SC);
        free(*dragones);
        return;
    }
    *dragones = temp;

    (*dragones)[*totalDragones] = nuevoDragon;
    (*totalDragones)++;

    printf(NARANJA"\n\tDragón agregado:\n"SC);
    mostrarDragon(&(*dragones)[*totalDragones - 1]);
}

void inicializarDragon(Dragon *dragon, int id, char *nombre, int vida, int ataque, int resistencia, char *pasiva, char *descripcion, int oro) {
    dragon->id = id;
    strcpy(dragon->nombre, nombre);
    dragon->vida = vida;
    dragon->ataque = ataque;
    dragon->resistencia = resistencia;
    strcpy(dragon->pasiva, pasiva);
    strcpy(dragon->descripcion, descripcion);
    dragon->oro = oro;
}

void mostrarDragon(Dragon *dragon) {
    printf(ROJO"\tID:"SC" %d\n", dragon->id);
    printf(ROJO"\tNombre:"SC" %s\n", dragon->nombre);
    printf(ROJO"\tVida:"SC" %d\n", dragon->vida);
    printf(ROJO"\tataque:"SC" %d\n", dragon->ataque);
    printf(ROJO"\tResistencia:"SC" %d%%\n", dragon->resistencia);
    printf(ROJO"\tPasiva:"SC" %s\n", dragon->pasiva);
    printf(ROJO"\tDescripción:"SC" %s\n", dragon->descripcion);
    printf(ROJO"\tRecompensa:"SC" %d de oro\n\n", dragon->oro);
}

void visualizarDragones(Dragon **dragones, int *totalDragones) {
    *totalDragones = 3;
    *dragones = (Dragon*)malloc(3 * sizeof(Dragon));
    if (*dragones == NULL) {
        printf("Error al reservar memoria\n");
        exit(EXIT_FAILURE);
    }

    inicializarDragon(&(*dragones)[0], 1, "Nightmare", 400, 10, 15, "+25% resistencia a ataques", "Nightmare es un dragón...", 50);
    inicializarDragon(&(*dragones)[1], 2, "Cryonyx", 400, 15, 15, "+25% ataque", "Cryonyx es un dragón temido...", 125);
    inicializarDragon(&(*dragones)[2], 3, "Velkhanos", 400, 10, 15, "Se curará un 5%...", "Velkhanos es un dragón histórico...", 200);
}

void seleccionarDragon(Dragon *dragones, int totalDragones, Dragon **seleccionado) {
    int seleccion;
    int valido = 0;

    do {
        printf(NARANJA"Introduzca el ID del dragón con el que va a jugar: "SC);
        scanf("%d", &seleccion);
        while (getchar() != '\n');

        if (seleccion >= 1 && seleccion <= totalDragones) {
            switch (seleccion) {
                case 1:
                    printf("\n\nDragón seleccionado: %d\n", seleccion);
                    system("chafa -f symbols -s 50x30 Nightmare.jpg");
                    break;
                case 2:
                    printf("\n\nDragón seleccionado: %d\n", seleccion);
                    system("chafa -f symbols -s 50x30 Cryonyx.jpg");
                    break;
                case 3:
                    printf("\n\nDragón seleccionado: %d\n", seleccion);
                    system("chafa -f symbols -s 50x30 Velkhanos.jpg");
                    break;
            }
            mostrarDragon(&dragones[seleccion - 1]);
            valido = 1;
            *seleccionado = &dragones[seleccion - 1];
        } else {
            printf(ROJO"Has introducido un dragón que no existe.\n\n"SC);
        }
    } while (!valido);
}