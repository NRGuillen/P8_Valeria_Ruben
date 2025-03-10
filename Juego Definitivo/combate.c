#include "utilidades.h"
#include "cazador.h"
#include "dragon.h"
#include "combate.h"

// FUNCION BATALLA
void comenzarBatalla(Cazador *cazadores, int totalCazadores, Cazador **cazadorActivo, Dragon *dragones, int totalDragones) {
    // Inicializa la semilla para números aleatorios basada en el tiempo actual
    srand(time(NULL)); 

    // Almacena la vida inicial del cazador activo
    int vidaCazador = (*cazadorActivo)->vida; 
    // Contador de dragones derrotados
    int dragonesDerrotados = 0; 
    // Arreglo para marcar dragones derrotados (0 = vivo, 1 = muerto)
    int *derrotados = (int*)calloc(totalDragones, sizeof(int)); 
    // Verifica si la asignación de memoria falló
    if (derrotados == NULL) { 
        // Imprime mensaje de error si falla la memoria
        printf("Error al asignar memoria\n");
        // Termina el programa si falla
        exit(EXIT_FAILURE); 
    }

    // Acumula el daño total hecho por los cazadores
    int dañoTotalCazador = 0; 
    // Acumula el daño total recibido de los dragones
    int dañoTotalDragon = 0; 
    // Contador de turnos jugados
    int turnos = 0; 
    // Contador de cazadores utilizados en la batalla
    int cazadoresUsados = 1; 

    // Caso especial: solo hay un dragón
    if (totalDragones == 1) { 
        // Selecciona el primer (y único) dragón
        Dragon *dragon = &dragones[0]; 
        // Almacena la vida inicial del dragón
        int vidaDragon = dragon->vida; 
        // Anuncia el inicio de la batalla entre cazador y dragón
        printf(NARANJA "\n¡La batalla comienza entre %s (Cazador) y %s (Dragón)!\n" SC, (*cazadorActivo)->nombre, dragon->nombre);

        // Bucle principal del combate mientras ambos estén vivos
        while (vidaCazador > 0 && vidaDragon > 0) { 
            // Incrementa el número de turnos
            turnos++; 

            // Muestra el estado actual del cazador y el dragón
            printf("\n" AZUL_C "Estado actual:\n" SC);
            printf("  %s (Cazador): Vida = %d, Oro = %d, Frascos Pequeños = %d, Frascos Grandes = %d\n", 
                   (*cazadorActivo)->nombre, vidaCazador, (*cazadorActivo)->oro, (*cazadorActivo)->frascosPequenos, (*cazadorActivo)->frascosGrandes);
            printf("  %s (Dragón): Vida = %d\n", dragon->nombre, vidaDragon);

            // Variable para la elección del jugador
            int opcion; 
            // Pide al jugador que elija una acción
            printf(NARANJA "\nTurno de %s: ¿Qué deseas hacer?\n" SC, (*cazadorActivo)->nombre);
            printf("  1) Atacar\n");
            printf("  2) Usar objeto\n");
            printf(MAGENTA "  Selección: " SC);
            // Lee la opción del jugador
            scanf("%d", &opcion);
            // Limpia el buffer de entrada
            while (getchar() != '\n');

            // Si el jugador elige atacar
            if (opcion == 1) {
                // Calcula el daño base del cazador
                int dañoCazador = (*cazadorActivo)->ataque; 
                // Obtiene la resistencia base del dragón
                int resistenciaDragon = dragon->resistencia;
                // Aumenta la resistencia del dragón si tiene la pasiva adecuada
                if (strcmp(dragon->pasiva, "+25% resistencia a ataques") == 0) { 
                    resistenciaDragon = (int)(resistenciaDragon * 1.25);
                }
                // Calcula el daño real considerando la resistencia
                int dañoReal = dañoCazador - (dañoCazador * resistenciaDragon / 100);
                // Asegura que el daño no sea negativo
                if (dañoReal < 0) dañoReal = 0;
                // Resta el daño a la vida del dragón
                vidaDragon -= dañoReal;
                // Acumula el daño total infligido por el cazador
                dañoTotalCazador += dañoReal;
                // Muestra el resultado del ataque
                printf(VERDE "%s ataca a %s y causa %d de daño!\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dañoReal);
            } 
            // Si el jugador elige usar un objeto
            else if (opcion == 2) { 
                // Verifica si el cazador tiene objetos disponibles
                if ((*cazadorActivo)->frascosPequenos == 0 && (*cazadorActivo)->frascosGrandes == 0) {
                    printf(ROJO"No tienes objetos en el inventario.\n"SC);
                } else {
                    // Muestra el inventario del cazador
                    printf("Inventario:\n");
                    if ((*cazadorActivo)->frascosPequenos > 0) printf("  1) Frasco pequeño de Estus (%d) - +25 vida\n", (*cazadorActivo)->frascosPequenos); 
                    if ((*cazadorActivo)->frascosGrandes > 0) printf("  2) Frasco grande de Estus (%d) - +50 vida\n", (*cazadorActivo)->frascosGrandes); 
                    printf(MAGENTA"Selecciona un objeto: "SC);
                    // Variable para la selección del objeto
                    int objOpcion;
                    // Lee la opción del objeto
                    scanf("%d", &objOpcion);
                    // Limpia el buffer de entrada
                    while (getchar() != '\n');

                    // Usa un frasco pequeño si está disponible y fue seleccionado
                    if (objOpcion == 1 && (*cazadorActivo)->frascosPequenos > 0) {
                        // Aumenta la vida del cazador en 25
                        vidaCazador += 25;
                        // Limita la vida al máximo del cazador
                        if (vidaCazador > (*cazadorActivo)->vida) vidaCazador = (*cazadorActivo)->vida;
                        // Reduce el contador de frascos pequeños
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

            if (vidaDragon <= 0) { //se cumple cuando la vida del dragon sea 0 o menor a 0
                printf(DORADO "\n¡%s ha derrotado a %s! Ganaste %d de oro.\n" SC, (*cazadorActivo)->nombre, dragon->nombre, dragon->oro);
                (*cazadorActivo)->oro += dragon->oro;
                dragonesDerrotados++;
                break;
            }

            int ataqueDragon = rand() % 2;// rand aleatorio, si sale 1 se cumple el ataque si no, falla
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

    (*cazadorActivo)->vida = vidaCazador; //actualizamos la vida del cazador activo
    if (vidaCazador > 0 && dragonesDerrotados == totalDragones) { //si la vida del cazador es mayor a 0 y los dragonesDerrotados igual a los dragones existentes, gana el cazador, de lo contrario pierde
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