#include "utilidades.h"




void TIENDA() {
    system("clear");
    
    char compV;
    printf("¿Desea comprar vida? (s/n)\n");
    scanf(" %c", &compV);

    if (compV == 's') {
        printf("OBJETOS DISPONIBLES:\n"
               "\nVIDA:\n");
        system("chafa -f symbols -s 30x30 Estus.png");
        printf("\t- Frasco pequeño de Estus: 25 monedas - +25 vida.\n"
               "\t- Frasco grande de Estus: 50 monedas - +50 vida.\n");
        
        int opcionVida;
        printf("¿Cuánta vida quiere adquirir? (1 o 2)\n");
        scanf("%d", &opcionVida);

        if (opcionVida == 1) {
            if (monedas >= 25) {
                printf("Has comprado un frasco pequeño de Estus. +25 vida.\n");
                monedas -= 25; // Restamos las monedas
                // Aquí se suma la vida
            } else {
                printf("No tienes suficientes monedas para esta compra.\n");
            }
        } 
        else if (opcionVida == 2) {
            if (monedas >= 50) {
                printf("Has comprado un frasco grande de Estus. +50 vida.\n");
                monedas -= 50; // Restamos las monedas
                // Aquí se suma la vida
            } else {
                printf("No tienes suficientes monedas para esta compra.\n");
            }
        } 
        else {
            printf("Opción inválida. El combate continúa...\n");
        }
    } 
    else if (compV == 'n') {
        char compA;
        printf("¿Desea adquirir un arma? (s/n)\n");
        scanf(" %c", &compA);

        if (compA == 's') {
            printf("OBJETOS DISPONIBLES:\n"
                   "\tARMAS:\n");
            system("chafa -f symbols -s 40x30 Anduril.jpg");
            printf("\t- Anduril: 150 monedas - 30 daño.\n");
            system("chafa -f symbols -s 30x30 gimli.jpg");
            printf("\t- Bearded Axe: 150 monedas - 35 daño.\n");

            int opcionArma;
            printf("¿Cuál arma desea adquirir? (1 o 2)\n");
            scanf("%d", &opcionArma);

            if (opcionArma == 1) {
                if (monedas >= 150) {
                    printf("Has comprado Anduril, una espada de alto alcance. +30 daño.\n");
                    monedas -= 150;  // Restamos las monedas
                    daño += 30;      // Aumentamos el daño
                } else {
                    printf("No tienes suficientes monedas para esta compra.\n");
                }
            } 
            else if (opcionArma == 2) {
                if (monedas >= 150) {
                    printf("Has comprado la Bearded Axe, un hacha de doble filo +35 daño.\n");
                    monedas -= 150;  // Restamos las monedas
                    daño += 35;      // Aumentamos el daño
                } else {
                    printf("No tienes suficientes monedas para esta compra.\n");
                }
            } 
            else {
                printf("Opción inválida. El combate continúa...\n");
            }
        } 
        else {
            printf("El combate continúa...\n");
        }
    } 
    else {
        printf("El combate continúa...\n");
    }
}
