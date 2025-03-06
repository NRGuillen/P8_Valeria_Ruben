#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 1000
#define MAX_DRAGONES 3
#define MAXNOMBRE 50
#define MAXARMA 20
#define MAXATAQUE 20
#define MAXVIDA 100
#define MAXORO 600
#define MAXDESCRIPCION 200
#define MAXDESC 256  

#define NEGRO     "\033[30m"
#define ROJO      "\033[31m"
#define VERDE     "\033[32m"
#define AMARILLO  "\033[33m"
#define AZUL      "\033[34m"
#define MAGENTA   "\033[35m"
#define CIAN      "\033[36m"
#define BLANCO    "\033[37m"

#define NARANJA   "\033[38;2;255;128;0m"
#define ROSA      "\033[38;2;255;151;203m"
#define AZUL_C    "\033[38;2;53;149;240m"
#define VERDE_C   "\033[38;2;17;245;120m"
#define GRIS      "\033[38;2;176;174;174m"
#define VIOLETA   "\033[38;2;148;0;211m"
#define MARRON    "\033[38;2;139;69;19m"
#define TURQUESA  "\033[38;2;64;224;208m"
#define DORADO    "\033[38;2;255;215;0m"
#define LIMA      "\033[38;2;50;205;50m"
#define CELESTE   "\033[38;2;135;206;250m"
#define LAVANDA   "\033[38;2;230;230;250m"
#define SALMON    "\033[38;2;250;128;114m"
#define CHOCOLATE "\033[38;2;210;105;30m"
#define CURSIVA   "\033[3m"

#define SC        "\033[0m"

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    int vida;
    int ataque;
    int resistencia;
    char pasiva[MAX_DESCRIPCION];
    char descripcion[MAX_DESCRIPCION];
    int oro;
} Dragon;

typedef struct {
    int ID;
    char nombre[MAXNOMBRE + 1];
    char arma[MAXARMA + 1];
    int ataque;
    int vida;
    int oro;
    int defensa;
    char descripcion[MAXDESCRIPCION + 1];
} Cazador;

void comenzarBatalla(Cazador *cazador, Dragon *dragones, int totalDragones);
void inicializarCazador(Cazador *datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion);
void cazadorIMPRIMIR(const Cazador *cazador_a_imprimir);
void inicializarCazadores(Cazador **cazadores, int *totalCazadores);
void cazadorSELEC(Cazador *cazadores, int totalCazadores, Cazador **seleccionado);
void añadirCazador(Cazador **cazadores, int *totalCazadores);
void inicializarDragon(Dragon *dragon, int id, char *nombre, int vida, int ataque, int resistencia, char *pasiva, char *descripcion, int oro);
void mostrarDragon(Dragon *dragon);
void seleccionarDragon(Dragon *dragones, int totalDragones, Dragon **seleccionado);
void visualizarDragones(Dragon **dragones, int *totalDragones);
void añadir_dragon(Dragon **dragones, int *totalDragones);
void MENU(Cazador **cazadores, int *totalCazadores, Cazador **seleccionado);

void añadir_dragon(Dragon **dragones, int *totalDragones) {
    Dragon nuevoDragon;

    printf(AMARILLO"\nIntroduzca los datos del nuevo dragon: \n"SC);

    nuevoDragon.id = (*totalDragones) + 1;
    printf(AZUL_C"\tID: %d\n"SC, nuevoDragon.id);

    printf(AZUL_C"\tNOMBRE: "SC);
    fgets(nuevoDragon.nombre, MAX_NOMBRE, stdin);
    nuevoDragon.nombre[strcspn(nuevoDragon.nombre, "\n")] = 0;

    do {
        printf(VERDE_C"\tVIDA: "SC);
        if (scanf("%d", &nuevoDragon.vida) != 1) {
            printf(ROJO"\tPor favor, introduce solo números.\n"SC);
            while (getchar() != '\n');
        } else if (nuevoDragon.vida < 0 || nuevoDragon.vida > 100) {
            printf(ROJO"\tEl rango de vida tiene que estar entre 0-100\n"SC);
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    do {
        printf(ROJO"\tATAQUE: "SC);
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
        printf(AZUL "\tRESISTENCIA: "SC);
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
    printf(AMARILLO"\tPASIVA:\n"SC);
    printf(AZUL "\t  1) +25%% resistencia a ataques\n"SC);
    printf(ROJO"\t  2) +25%% ataque\n"SC);
    printf(VERDE_C"\t  3) Se curará un 5%% de su vida después de cada ataque\n"SC);
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
    fgets(nuevoDragon.descripcion, MAX_DESCRIPCION, stdin);
    nuevoDragon.descripcion[strcspn(nuevoDragon.descripcion, "\n")] = 0;

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

void inicializarCazadores(Cazador **cazadores, int *totalCazadores) {
    *totalCazadores = 3;

    *cazadores = (Cazador *)malloc(*totalCazadores * sizeof(Cazador));
    if (*cazadores == NULL) {
        printf("ERROR CATASTRÓFICO: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    inicializarCazador(&(*cazadores)[0], 1, "Mushashi", "Iaido", 20, 120, 100, "Un caballero audaz y letal...");
    inicializarCazador(&(*cazadores)[1], 2, "Conan", "Atlantean", 15, 150, 100, "Un guerrero con fuerza colosal...");
    inicializarCazador(&(*cazadores)[2], 3, "Jeremias", "Yari", 10, 200, 100, "Un estratega con gran resistencia...");
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
    printf(LIMA"\tNombre:"SC" %s\n", dragon->nombre);
    printf(VERDE_C"\tVida:"SC" %d\n", dragon->vida);
    printf(ROJO"\tAtaque:"SC" %d\n", dragon->ataque);
    printf(AZUL "\tResistencia:"SC" %d%%\n", dragon->resistencia);
    printf(AMARILLO"\tPasiva:"SC" %s\n", dragon->pasiva);
    printf(AZUL_C"\tDescripción:"SC" %s\n", dragon->descripcion);
    printf(DORADO"\tRecompensa:"SC" %d de oro\n\n", dragon->oro);
}

void visualizarDragones(Dragon **dragones, int *totalDragones) {
    *totalDragones = 3;
    *dragones = (Dragon*)malloc(3 * sizeof(Dragon));
    if (*dragones == NULL) {
        printf("Error al reservar memoria\n");
        exit(EXIT_FAILURE);
    }

    inicializarDragon(&(*dragones)[0], 1, "Nightmare", 100, 10, 15, "+25% resistencia a ataques", "Nightmare es un dragón...", 50);
    inicializarDragon(&(*dragones)[1], 2, "Cryonyx", 100, 15, 15, "+25% ataque", "Cryonyx es un dragón temido...", 125);
    inicializarDragon(&(*dragones)[2], 3, "Velkhanos", 100, 10, 15, "Se curará un 5%...", "Velkhanos es un dragón histórico...", 200);

    printf(NARANJA"\nDRAGONES DISPONIBLES:\n"SC);
    system("chafa -f symbols -s 50x30 Nightmare.jpg");
    mostrarDragon(&(*dragones)[0]);
    system("chafa -f symbols -s 50x30 Cryonyx.jpg");
    mostrarDragon(&(*dragones)[1]);
    system("chafa -f symbols -s 50x30 Velkhanos.jpg");
    mostrarDragon(&(*dragones)[2]);
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

void inicializarCazador(Cazador *datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion) {
    datos->ID = ID;
    strncpy(datos->nombre, nombre, sizeof(datos->nombre) - 1);
    datos->nombre[sizeof(datos->nombre) - 1] = '\0';
    strncpy(datos->arma, arma, sizeof(datos->arma) - 1);
    datos->arma[sizeof(datos->arma) - 1] = '\0';
    strncpy(datos->descripcion, descripcion, sizeof(datos->descripcion) - 1);
    datos->descripcion[sizeof(datos->descripcion) - 1] = '\0';
    datos->ataque = ataque;
    datos->vida = vida;
    datos->oro = oro;
    datos->defensa = 0;
}

void cazadorIMPRIMIR(const Cazador *cazador_a_imprimir) {
    printf(ROJO"\tID:"SC" %d\n", cazador_a_imprimir->ID);
    printf(LIMA"\tNombre:"SC" %s\n", cazador_a_imprimir->nombre);
    printf(ROJO"\tArma:"SC" %s\n", cazador_a_imprimir->arma);
    printf(ROJO"\tAtaque:"SC" %d\n", cazador_a_imprimir->ataque);
    printf(VERDE_C "\tVida:"SC" %d\n", cazador_a_imprimir->vida);
    printf(DORADO"\tOro:"SC" %d\n", cazador_a_imprimir->oro);
    printf(AZUL_C"\tDescripción:"SC" %s\n", cazador_a_imprimir->descripcion);
}

void cazadorSELEC(Cazador *cazadores, int totalCazadores, Cazador **seleccionado) {
    int intentos = 3;
    int cazadorACTIVO;

    printf(NARANJA"\nCAZADORES DISPONIBLES: \n"SC);

    system("chafa -f symbols -s 50x30 Mushashi.jpg");
    cazadorIMPRIMIR(&cazadores[0]);
    system("chafa -f symbols -s 50x30 Conan.jpg");
    cazadorIMPRIMIR(&cazadores[1]);
    system("chafa -f symbols -s 50x30 Sauron.jpg");
    cazadorIMPRIMIR(&cazadores[2]);

    do {
        printf(NARANJA"\n\nIntroduzca el ID del cazador con el que va a jugar: "SC);
        if (scanf("%d", &cazadorACTIVO) != 1) {
            printf(ROJO"Entrada inválida. Debe ingresar un número.\n"SC);
            while (getchar() != '\n');
            intentos--;
        } else if (cazadorACTIVO < 1 || cazadorACTIVO > totalCazadores) {
            printf(ROJO"El ID del primer cazador es 1 y el último es %d.\n"SC, totalCazadores);
            intentos--;
        } else {
            if (cazadorACTIVO == 1) {
                system("chafa -f symbols -s 50x30 Mushashi.jpg");
            } else if (cazadorACTIVO == 2) {
                system("chafa -f symbols -s 50x30 Conan.jpg");
            } else if (cazadorACTIVO == 3) {
                system("chafa -f symbols -s 50x30 Sauron.jpg");
            }
            cazadorIMPRIMIR(&cazadores[cazadorACTIVO - 1]);
            *seleccionado = &cazadores[cazadorACTIVO - 1];
            return;
        }

        if (intentos == 0) {
            printf(ROJO"INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n"SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);
}

void añadirCazador(Cazador **cazadores, int *totalCazadores) {
    int intentos = 3;
    Cazador nuevoCazador;
    printf(AMARILLO "\nIntroduzca los datos del nuevo cazador: \n" SC);

    nuevoCazador.ID = *totalCazadores + 1;
    printf(AZUL_C "\t ID:" SC " %d.\n", nuevoCazador.ID);

    do {
        printf(AZUL_C "\t NOMBRE: " SC);
        scanf(" %[^\n]", nuevoCazador.nombre);

        int esValido = 1;
        for (int i = 0; i < strlen(nuevoCazador.nombre); i++) {
            if (isdigit(nuevoCazador.nombre[i])) {
                esValido = 0;
                break;
            }
        }

        if (strlen(nuevoCazador.nombre) < 1 || strlen(nuevoCazador.nombre) > MAXNOMBRE) {
            printf(ROJO "Valor inválido, el nombre no puede ser menor a 1 o mayor a %d.\n" SC, MAXNOMBRE);
            intentos--;
        } else {
            intentos = 3;
            break;
        }

        if (intentos == 0) {
            printf(ROJO "INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n" SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);

    do {
        printf(AZUL_C "\t ARMA: " SC);
        scanf(" %[^\n]", nuevoCazador.arma);

        if (strlen(nuevoCazador.arma) < 1 || strlen(nuevoCazador.arma) > MAXARMA) {
            printf(ROJO "Valor inválido, el nombre del arma no puede ser menor a 1 o mayor a %d.\n" SC, MAXARMA);
            intentos--;
        } else {
            intentos = 3;
            break;
        }

        if (intentos == 0) {
            printf(ROJO "INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n" SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);

    do {
        printf(AZUL_C "\t ataque: " SC);

        if (scanf("%d", &nuevoCazador.ataque) != 1) {
            printf(ROJO "Entrada inválida. Debe ingresar un número.\n" SC);
            while (getchar() != '\n');
            intentos--;
        } else if (nuevoCazador.ataque < 1 || nuevoCazador.ataque > MAXATAQUE) {
            printf(ROJO "Valor inválido, el ataque no puede ser menor a 1 o mayor a %d.\n" SC, MAXATAQUE);
            intentos--;
        } else {
            intentos = 3;
            break;
        }

        if (intentos == 0) {
            printf(ROJO "INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n" SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);

    do {
        printf(AZUL_C "\t VIDA: " SC);

        if (scanf("%d", &nuevoCazador.vida) != 1) {
            printf(ROJO "Entrada inválida. Debe ingresar un número.\n" SC);
            while (getchar() != '\n');
            intentos--;
        } else if (nuevoCazador.vida < 1 || nuevoCazador.vida > MAXVIDA) {
            printf(ROJO "Valor inválido, la vida no puede ser menor a 1 o mayor a %d.\n" SC, MAXVIDA);
            intentos--;
        } else {
            intentos = 3;
            break;
        }

        if (intentos == 0) {
            printf(ROJO "INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n" SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);

    nuevoCazador.oro = 100;
    printf(AZUL_C "\t ORO:" SC " %d monedas.\n", nuevoCazador.oro);

    do {
        printf(AZUL_C "\t DESCRIPCIÓN: " SC);
        scanf(" %[^\n]", nuevoCazador.descripcion);

        if (strlen(nuevoCazador.descripcion) < 1 || strlen(nuevoCazador.descripcion) > MAXDESCRIPCION) {
            printf(ROJO "Valor inválido, la descripción no puede ser menor a 1 o mayor a %d.\n" SC, MAXDESCRIPCION);
            intentos--;
        } else {
            intentos = 3;
            break;
        }

        if (intentos == 0) {
            printf(ROJO "INTENTOS AGOTADOS. MÁS SUERTE LA PRÓXIMA VEZ.\n" SC);
            exit(EXIT_FAILURE);
        }
    } while (intentos > 0);

    Cazador *REALLOC_TEMP = (Cazador*) realloc(*cazadores, (*totalCazadores + 1) * sizeof(Cazador));
    if (REALLOC_TEMP == NULL) {
        printf("ERROR: No se pudo asignar memoria para el nuevo cazador.\n");
        exit(EXIT_FAILURE);
    }
    *cazadores = REALLOC_TEMP;

    (*cazadores)[*totalCazadores] = nuevoCazador;
    (*totalCazadores)++;

    printf(NARANJA "\nCAZADOR AGREGADO:\n" SC);
    cazadorIMPRIMIR(&(*cazadores)[*totalCazadores - 1]);
}

void BIENVENIDA() {
    system("clear");
    system("chafa -f symbols -s 90x50 Erebor.jpg");
    printf(CURSIVA"Tras la caída del gran dragón codicioso, los cielos sobre la Montaña Solitaria permanecieron en silencio por generaciones. Sin embargo, los ecos de su avaricia no desaparecieron tras su muerte a manos de Bardo. Los hijos del monstruo, nacidos en las sombras de su padre, regresan ahora, decididos a reclamar lo que consideran suyo: el oro que una vez perteneció al rey enano Thráin II.\n"

        "\nEl tesoro, una vez custodiado por un solo ser, ahora se ve protegido por una legión de dragones con la misma insaciable hambre que su antecesor. La Montaña, que guardó el silencio por tanto tiempo, vuelve a rugir con la furia de aquellos que ansían lo que no les pertenece.\n"

        "\nLos cazadores, sabiendo que esta vez el desafío es aún mayor, se preparan para enfrentar a una fuerza más peligrosa que cualquier que hayan conocido. No luchan solo por el oro, sino por evitar que la sombra de la codicia del dragón se apodere nuevamente de la tierra.\n\n"SC);
}

void comenzarBatalla(Cazador *cazador, Dragon *dragones, int totalDragones) {
    srand(time(NULL));

    int vidaCazador = cazador->vida;
    int dragonesDerrotados = 0;
    int *derrotados = (int*)calloc(totalDragones, sizeof(int));
    if (derrotados == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    while (vidaCazador > 0 && dragonesDerrotados < totalDragones) {
        printf(NARANJA "\nDRAGONES DISPONIBLES:\n" SC);
        int hayDragonesVivos = 0;
        for (int i = 0; i < totalDragones; i++) {
            if (!derrotados[i]) {
                switch (dragones[i].id) {
                    case 1: system("chafa -f symbols -s 50x30 Nightmare.jpg"); break;
                    case 2: system("chafa -f symbols -s 50x30 Cryonyx.jpg"); break;
                    case 3: system("chafa -f symbols -s 50x30 Velkhanos.jpg"); break;
                }
                mostrarDragon(&dragones[i]);
                hayDragonesVivos = 1;
            }
        }

        if (!hayDragonesVivos) {
            printf(DORADO "\n¡%s ha derrotado a todos los dragones! ¡Victoria total!\n" SC, cazador->nombre);
            break;
        }

        int seleccion;
        int valido = 0;
        do {
            printf(NARANJA "Introduzca el ID del dragón contra el que desea luchar: " SC);
            scanf("%d", &seleccion);
            while (getchar() != '\n');

            if (seleccion >= 1 && seleccion <= totalDragones && !derrotados[seleccion - 1]) {
                valido = 1;
            } else {
                printf(ROJO "ID inválido o dragón ya derrotado. Elige otro.\n" SC);
            }
        } while (!valido);

        Dragon *dragon = &dragones[seleccion - 1];
        int vidaDragon = dragon->vida;

        printf(NARANJA "\n¡La batalla comienza entre %s (Cazador) y %s (Dragón)!\n" SC, cazador->nombre, dragon->nombre);

        while (vidaCazador > 0 && vidaDragon > 0) {
            printf("\n" AZUL_C "Estado actual:\n" SC);
            printf("  %s (Cazador): Vida = %d\n", cazador->nombre, vidaCazador);
            printf("  %s (Dragón): Vida = %d\n", dragon->nombre, vidaDragon);

            int opcion;
            printf(NARANJA "\nTurno de %s: ¿Qué deseas hacer?\n" SC, cazador->nombre);
            printf("  1) Atacar\n");
            printf(MAGENTA "  Selección: " SC);
            scanf("%d", &opcion);
            while (getchar() != '\n');

            if (opcion == 1) {
                int dañoCazador = cazador->ataque;
                int resistenciaDragon = dragon->resistencia;
                if (strcmp(dragon->pasiva, "+25% resistencia a ataques") == 0) {
                    resistenciaDragon = (int)(resistenciaDragon * 1.25);
                }
                int dañoReal = dañoCazador - (dañoCazador * resistenciaDragon / 100);
                if (dañoReal < 0) dañoReal = 0;
                vidaDragon -= dañoReal;
                printf(VERDE "%s ataca a %s y causa %d de daño!\n" SC, cazador->nombre, dragon->nombre, dañoReal);
            } else {
                printf(ROJO "Opción inválida. Pierdes el turno.\n" SC);
            }

            if (vidaDragon <= 0) {
                printf(DORADO "\n¡%s ha derrotado a %s! Ganaste %d de oro.\n" SC, cazador->nombre, dragon->nombre, dragon->oro);
                cazador->oro += dragon->oro;
                derrotados[seleccion - 1] = 1;
                dragonesDerrotados++;
                break;
            }

            int ataqueDragon = rand() % 2;
            if (ataqueDragon == 1) {
                int dañoDragon = dragon->ataque;
                dañoDragon = (int)(dañoDragon * 1.25);
                if (strcmp(dragon->pasiva, "+25% ataque") == 0) {
                    dañoDragon = (int)(dañoDragon * 1.25);
                }
                vidaCazador -= dañoDragon;
                printf(ROJO "%s ataca a %s y causa %d de daño! (25%% extra por acierto)\n" SC, dragon->nombre, cazador->nombre, dañoDragon);

                if (strcmp(dragon->pasiva, "Se curará un 5% de su vida después de cada ataque") == 0) {
                    int curacion = (int)(dragon->vida * 0.05);
                    vidaDragon += curacion;
                    if (vidaDragon > dragon->vida) vidaDragon = dragon->vida;
                    printf(VERDE_C "%s se cura %d de vida.\n" SC, dragon->nombre, curacion);
                }
            } else {
                printf(GRIS "%s no ataca este turno.\n" SC, dragon->nombre);
            }

            if (vidaCazador <= 0) {
                printf(ROJO "\n¡%s ha derrotado a %s! Has perdido.\n" SC, dragon->nombre, cazador->nombre);
                cazador->vida = vidaCazador;
                free(derrotados);
                return;
            }
        }
    }

    cazador->vida = vidaCazador;
    if (vidaCazador > 0) {
        printf(DORADO "\n¡%s ha derrotado a todos los dragones! ¡Victoria total!\n" SC, cazador->nombre);
    }
    free(derrotados);
}

int totalCazadores;

void MENU(Cazador **cazadores, int *totalCazadores, Cazador **seleccionado) {
    int opcion;

    printf(MAGENTA"\t MENÚ: \n"
           AZUL_C"\t 1) Seleccionar un cazador.\n"
                 "\t 2) Añadir cazador.\n"
                 "\t 3) Salir.\n"SC
           MAGENTA"\t OPCIÓN: "SC);
    scanf("%d", &opcion);
    while (getchar() != '\n');

    switch (opcion) {
        case 1:
            cazadorSELEC(*cazadores, *totalCazadores, seleccionado);
            break;
        case 2:
            añadirCazador(cazadores, totalCazadores);
            *seleccionado = &(*cazadores)[*totalCazadores - 1];
            break;
        case 3:
            printf("Saliendo...\n");
            *seleccionado = NULL;
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }
}

int main() {
    Dragon *dragones = NULL;
    Cazador *cazadores = NULL;
    int totalDragones = 0;
    int totalCazadores = 0;
    int opcion;
    Cazador *cazadorSeleccionado = NULL;

    BIENVENIDA();
    inicializarCazadores(&cazadores, &totalCazadores);
    visualizarDragones(&dragones, &totalDragones);

    MENU(&cazadores, &totalCazadores, &cazadorSeleccionado);
    if (cazadorSeleccionado == NULL) {
        printf(ROJO"No se seleccionó un cazador. Saliendo...\n"SC);
        free(dragones);
        free(cazadores);
        return 0;
    }

    while (getchar() != '\n');

    printf(MAGENTA"\tMENÚ DE DRAGONES:\n"SC);
    printf(AZUL_C"\t1) Combatir dragones predefinidos (elige en cada turno)\n"SC);
    printf(AZUL_C"\t2) Crear y combatir un nuevo dragón\n"SC);
    printf(AZUL_C"\t3) Salir\n"SC);
    printf(MAGENTA"\tSelección: "SC);
    scanf("%d", &opcion);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    switch (opcion) {
        case 1:
            comenzarBatalla(cazadorSeleccionado, dragones, totalDragones);
            break;
        case 2:
            añadir_dragon(&dragones, &totalDragones);
            comenzarBatalla(cazadorSeleccionado, &dragones[totalDragones - 1], 1);
            break;
        case 3:
            printf("Saliendo...\n");
            free(dragones);
            free(cazadores);
            return 0;
        default:
            printf("Opción inválida.\n");
            break;
    }

    free(dragones);
    free(cazadores);
    return 0;
}