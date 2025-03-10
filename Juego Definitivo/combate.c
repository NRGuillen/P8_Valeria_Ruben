#include "utilidades.h"
#include "cazador.h"
#include "dragon.h"
#include "combate.h"

void comenzarBatalla(Cazador *cazadores, int totalCazadores, Cazador **cazadorActivo, Dragon *dragones, int totalDragones) {
    srand(time(NULL));

    int vidaCazador = (*cazadorActivo)->vida;
    int dragonesDerrotados = 0;
    int *derrotados = (int*)calloc(totalDragones, sizeof(int));
    if (derrotados == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    int dañoTotalCazador = 0;
    int dañoTotalDragon = 0;
    int turnos = 0;
    int cazadoresUsados = 1;

    if (totalDragones == 1) {
        Dragon *dragon = &dragones[0];
        int vidaDragon = dragon->vida;
        printf(NARANJA "\n¡La batalla comienza entre %s (Cazador) y %s (Dragón)!\n" SC, (*cazadorActivo)->nombre, dragon->nombre);

        while (vidaCazador > 0 && vidaDragon > 0) {
            turnos++;
            printf("\n" AZUL_C "Estado actual:\n" SC);
            printf("  %s (Cazador): Vida = %d, Oro = %d, Frascos Pequeños = %d, Frascos Grandes = %d\n", 
                   (*cazadorActivo)->nombre, vidaCazador, (*cazadorActivo)->oro, (*cazadorActivo)->frascosPequenos, (*cazadorActivo)->frascosGrandes);
            printf("  %s (Dragón): Vida = %d\n", dragon->nombre, vidaDragon);

            int opcion;
            printf(NARANJA "\nTurno de %s: ¿Qué deseas hacer?\n" SC, (*cazadorActivo)->nombre);
            printf("  1) Atacar\n");
            printf("  2) Usar objeto\n");
            printf(MAGENTA "  Selección: " SC);
            scanf("%d", &opcion);
            while (getchar() != '\n');

            if (opcion == 1) {
                int dañoCazador = (*cazadorActivo)->ataque;
                int resistenciaDragon = dragon->resistencia;
                if (strcmp(dragon->pasiva, "+25% resistencia a ataques") == 0) {
                    resistenciaDragon = (int)(resistenciaDragon * 1.25);
                }
                int dañoReal = dañoCazador - (dañoCazador * resistenciaDragon / 100);
                if (dañoReal < 0) dañoReal = 0;
                vidaDragon -= dañoReal;
                dañoTotalCazador += dañoReal;
                printf(VERDE "%s ataca a %s y causa %d de daño!\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dañoReal);
            } else if (opcion == 2) {
                if ((*cazadorActivo)->frascosPequenos == 0 && (*cazadorActivo)->frascosGrandes == 0) {
                    printf(ROJO"No tienes objetos en el inventario.\n"SC);
                } else {
                    printf("Inventario:\n");
                    if ((*cazadorActivo)->frascosPequenos > 0) printf("  1) Frasco pequeño de Estus (%d) - +25 vida\n", (*cazadorActivo)->frascosPequenos);
                    if ((*cazadorActivo)->frascosGrandes > 0) printf("  2) Frasco grande de Estus (%d) - +50 vida\n", (*cazadorActivo)->frascosGrandes);
                    printf(MAGENTA"Selecciona un objeto: "SC);
                    int objOpcion;
                    scanf("%d", &objOpcion);
                    while (getchar() != '\n');

                    if (objOpcion == 1 && (*cazadorActivo)->frascosPequenos > 0) {
                        vidaCazador += 25;
                        if (vidaCazador > (*cazadorActivo)->vida) vidaCazador = (*cazadorActivo)->vida;
                        (*cazadorActivo)->frascosPequenos--;
                        printf(VERDE"%s usa un frasco pequeño de Estus y recupera 25 de vida.\n"SC, (*cazadorActivo)->nombre);
                    } else if (objOpcion == 2 && (*cazadorActivo)->frascosGrandes > 0) {
                        vidaCazador += 50;
                        if (vidaCazador > (*cazadorActivo)->vida) vidaCazador = (*cazadorActivo)->vida;
                        (*cazadorActivo)->frascosGrandes--;
                        printf(VERDE"%s usa un frasco grande de Estus y recupera 50 de vida.\n"SC, (*cazadorActivo)->nombre);
                    } else {
                        printf(ROJO"Opción inválida o no tienes ese objeto.\n"SC);
                    }
                }
            } else {
                printf(ROJO "Opción inválida. Pierdes el turno.\n" SC);
            }

            if (vidaDragon <= 0) {
                printf(DORADO "\n¡%s ha derrotado a %s! Ganaste %d de oro.\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dragon->oro);
                (*cazadorActivo)->oro += dragon->oro;
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
                dañoTotalDragon += dañoDragon;
                printf(ROJO "%s ataca a %s y causa %d de daño! (25%% extra por acierto)\n" SC, dragon->nombre, (*cazadorActivo)->nombre, dañoDragon);

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
                printf(ROJO "\n¡%s ha derrotado a %s! Has perdido.\n" SC, dragon->nombre, (*cazadorActivo)->nombre);
                (*cazadorActivo)->vida = vidaCazador;
                break;
            }
        }
    } else {
        while (dragonesDerrotados < totalDragones) {
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
                printf(DORADO "\n¡%s ha derrotado a todos los dragones! ¡Victoria total!\n" SC, (*cazadorActivo)->nombre);
                break;
            }

            int seleccion;
            int valido = 0;
            Dragon *dragon = NULL;
            int vidaDragon = 0;

            if (vidaCazador > 0 && dragon == NULL) {
                do {
                    printf(NARANJA "Introduzca el ID del dragón contra el que desea luchar: " SC);
                    scanf("%d", &seleccion);
                    while (getchar() != '\n');

                    if (seleccion >= 1 && seleccion <= totalDragones && !derrotados[seleccion - 1]) {
                        valido = 1;
                        dragon = &dragones[seleccion - 1];
                        vidaDragon = dragon->vida;
                        printf(NARANJA "\n¡La batalla comienza entre %s (Cazador) y %s (Dragón)!\n" SC, (*cazadorActivo)->nombre, dragon->nombre);
                    } else {
                        printf(ROJO "ID inválido o dragón ya derrotado. Elige otro.\n" SC);
                    }
                } while (!valido);
            }

            while (vidaCazador > 0 && vidaDragon > 0) {
                turnos++;
                printf("\n" AZUL_C "Estado actual:\n" SC);
                printf("  %s (Cazador): Vida = %d, Oro = %d, Frascos Pequeños = %d, Frascos Grandes = %d\n", 
                       (*cazadorActivo)->nombre, vidaCazador, (*cazadorActivo)->oro, (*cazadorActivo)->frascosPequenos, (*cazadorActivo)->frascosGrandes);
                printf("  %s (Dragón): Vida = %d\n", dragon->nombre, vidaDragon);

                int opcion;
                printf(NARANJA "\nTurno de %s: ¿Qué deseas hacer?\n" SC, (*cazadorActivo)->nombre);
                printf("  1) Atacar\n");
                printf("  2) Usar objeto\n");
                printf(MAGENTA "  Selección: " SC);
                scanf("%d", &opcion);
                while (getchar() != '\n');

                if (opcion == 1) {
                    int dañoCazador = (*cazadorActivo)->ataque;
                    int resistenciaDragon = dragon->resistencia;
                    if (strcmp(dragon->pasiva, "+25% resistencia a ataques") == 0) {
                        resistenciaDragon = (int)(resistenciaDragon * 1.25);
                    }
                    int dañoReal = dañoCazador - (dañoCazador * resistenciaDragon / 100);
                    if (dañoReal < 0) dañoReal = 0;
                    vidaDragon -= dañoReal;
                    dañoTotalCazador += dañoReal;
                    printf(VERDE "%s ataca a %s y causa %d de daño!\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dañoReal);
                } else if (opcion == 2) {
                    if ((*cazadorActivo)->frascosPequenos == 0 && (*cazadorActivo)->frascosGrandes == 0) {
                        printf(ROJO"No tienes objetos en el inventario.\n"SC);
                    } else {
                        printf("Inventario:\n");
                        if ((*cazadorActivo)->frascosPequenos > 0) printf("  1) Frasco pequeño de Estus (%d) - +25 vida\n", (*cazadorActivo)->frascosPequenos);
                        if ((*cazadorActivo)->frascosGrandes > 0) printf("  2) Frasco grande de Estus (%d) - +50 vida\n", (*cazadorActivo)->frascosGrandes);
                        printf(MAGENTA"Selecciona un objeto: "SC);
                        int objOpcion;
                        scanf("%d", &objOpcion);
                        while (getchar() != '\n');

                        if (objOpcion == 1 && (*cazadorActivo)->frascosPequenos > 0) {
                            vidaCazador += 25;
                            if (vidaCazador > (*cazadorActivo)->vida) vidaCazador = (*cazadorActivo)->vida;
                            (*cazadorActivo)->frascosPequenos--;
                            printf(VERDE"%s usa un frasco pequeño de Estus y recupera 25 de vida.\n"SC, (*cazadorActivo)->nombre);
                        } else if (objOpcion == 2 && (*cazadorActivo)->frascosGrandes > 0) {
                            vidaCazador += 50;
                            if (vidaCazador > (*cazadorActivo)->vida) vidaCazador = (*cazadorActivo)->vida;
                            (*cazadorActivo)->frascosGrandes--;
                            printf(VERDE"%s usa un frasco grande de Estus y recupera 50 de vida.\n"SC, (*cazadorActivo)->nombre);
                        } else {
                            printf(ROJO"Opción inválida o no tienes ese objeto.\n"SC);
                        }
                    }
                } else {
                    printf(ROJO "Opción inválida. Pierdes el turno.\n" SC);
                }

                if (vidaDragon <= 0) {
                    printf(DORADO "\n¡%s ha derrotado a %s! Ganaste %d de oro.\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dragon->oro);
                    (*cazadorActivo)->oro += dragon->oro;
                    derrotados[seleccion - 1] = 1;
                    dragonesDerrotados++;
                    dragon = NULL;

                    if (dragonesDerrotados < totalDragones) {
                        printf(MAGENTA"\n¿Qué deseas hacer ahora?\n"SC);
                        printf(AZUL_C"  1) Entrar a la tienda\n"SC);
                        printf(AZUL_C"  2) Continuar batalla\n"SC);
                        printf(MAGENTA"  Selección: "SC);
                        int postBatallaOpcion;
                        scanf("%d", &postBatallaOpcion);
                        while (getchar() != '\n');

                        switch (postBatallaOpcion) {
                            case 1:
                                TIENDA(*cazadorActivo);
                                break;
                            case 2:
                                printf(NARANJA"Continuando con la batalla...\n"SC);
                                break;
                            default:
                                printf(ROJO"Opción inválida. Continuando con la batalla...\n"SC);
                                break;
                        }
                    }
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
                    dañoTotalDragon += dañoDragon;
                    printf(ROJO "%s ataca a %s y causa %d de daño! (25%% extra por acierto)\n" SC, dragon->nombre, (*cazadorActivo)->nombre, dañoDragon);

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
                    printf(ROJO "\n¡%s ha derrotado a %s! Has perdido con este cazador.\n" SC, dragon->nombre, (*cazadorActivo)->nombre);
                    (*cazadorActivo)->vida = vidaCazador;

                    printf(MAGENTA"\n¿Qué deseas hacer ahora?\n"SC);
                    printf(AZUL_C"  1) Seleccionar otro cazador\n"SC);
                    printf(AZUL_C"  2) Rendirse\n"SC);
                    printf(MAGENTA"  Selección: "SC);
                    int opcionDerrota;
                    scanf("%d", &opcionDerrota);
                    while (getchar() != '\n');

                    switch (opcionDerrota) {
                        case 1:
                            cazadorSELEC(cazadores, totalCazadores, cazadorActivo);
                            if (*cazadorActivo == NULL) {
                                printf(ROJO"No hay más cazadores disponibles o selección fallida.\n"SC);
                                printf(MAGENTA"\nESTADÍSTICAS DE LA BATALLA:\n"SC);
                                printf(AZUL_C"  Cazadores usados: %d\n"SC, cazadoresUsados);
                                printf(AZUL_C"  Daño infligido por cazadores: %d\n"SC, dañoTotalCazador);
                                printf(AZUL_C"  Daño recibido de dragones: %d\n"SC, dañoTotalDragon);
                                printf(AZUL_C"  Turnos jugados: %d\n"SC, turnos);
                                printf(ROJO"Resultado: Derrota (Sin cazadores vivos)\n"SC);
                                free(derrotados);
                                return;
                            }
                            vidaCazador = (*cazadorActivo)->vida;
                            cazadoresUsados++;
                            printf(NARANJA"Continuando la batalla con %s contra %s...\n"SC, (*cazadorActivo)->nombre, dragon->nombre);
                            continue;
                        case 2:
                            printf(NARANJA"Saliendo del juego...\n"SC);
                            printf(MAGENTA"\nESTADÍSTICAS DE LA BATALLA:\n"SC);
                            printf(AZUL_C"  Cazadores usados: %d\n"SC, cazadoresUsados);
                            printf(AZUL_C"  Daño infligido por cazadores: %d\n"SC, dañoTotalCazador);
                            printf(AZUL_C"  Daño recibido de dragones: %d\n"SC, dañoTotalDragon);
                            printf(AZUL_C"  Turnos jugados: %d\n"SC, turnos);
                            printf(ROJO"Resultado: Derrota (Abandonaste)\n"SC);
                            free(derrotados);
                            return;
                        default:
                            printf(ROJO"Opción inválida. Saliendo del juego...\n"SC);
                            printf(MAGENTA"\nESTADÍSTICAS DE LA BATALLA:\n"SC);
                            printf(AZUL_C"  Cazadores usados: %d\n"SC, cazadoresUsados);
                            printf(AZUL_C"  Daño infligido por cazadores: %d\n"SC, dañoTotalCazador);
                            printf(AZUL_C"  Daño recibido de dragones: %d\n"SC, dañoTotalDragon);
                            printf(AZUL_C"  Turnos jugados: %d\n"SC, turnos);
                            printf(ROJO"Resultado: Derrota (Opción inválida)\n"SC);
                            free(derrotados);
                            return;
                    }
                }
            }
        }
    }

    (*cazadorActivo)->vida = vidaCazador;
    if (vidaCazador > 0 && dragonesDerrotados == totalDragones) {
        printf(DORADO "\n¡%s ha derrotado a todos los dragones! ¡Victoria total!\n" SC, (*cazadorActivo)->nombre);
    }

    printf(MAGENTA"\nESTADÍSTICAS DE LA BATALLA:\n"SC);
    printf(AZUL_C"  Cazadores usados: %d\n"SC, cazadoresUsados);
    printf(AZUL_C"  Daño infligido por cazadores: %d\n"SC, dañoTotalCazador);
    printf(AZUL_C"  Daño recibido de dragones: %d\n"SC, dañoTotalDragon);
    printf(AZUL_C"  Turnos jugados: %d\n"SC, turnos);
    if (vidaCazador > 0) {
        printf(VERDE"Resultado: Victoria\n"SC);
    } else {
        printf(ROJO"Resultado: Derrota\n"SC);
    }

    free(derrotados);
}
int totalCazadores;

void MENU(Cazador **cazadores, int *totalCazadores, Dragon **dragones, int *totalDragones, int *opcionElegida) {
    int opcion;

    printf(MAGENTA"\t MENÚ PRINCIPAL: \n"
           AZUL_C"\t 1) Combate con dragones y cazadores predefinidos\n"
                 "\t 2) Crear combate 1v1 con cazador y dragón personalizado\n"
                 "\t 3) Leer instrucciones y preguntas comunes\n"
                 "\t 4) Salir\n"SC
           MAGENTA"\t OPCIÓN: "SC);
    scanf("%d", &opcion);
    while (getchar() != '\n');

    *opcionElegida = opcion;
}