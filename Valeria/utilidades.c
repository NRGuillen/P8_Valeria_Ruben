//AÑADIDO VALERIA

#include "utilidades.h"
#include "cazador.h"

//MENSAJE DE BIENVENIDA
 void BIENVENIDA(){
 	system("clear");
	system("chafa -f symbols -s 90x50 Erebor.jpg");
	printf(CURSIVA"Tras la caída del gran dragón codicioso, los cielos sobre la Montaña Solitaria permanecieron en silencio por generaciones. Sin embargo, los ecos de su avaricia no desaparecieron tras su muerte a manos de Bardo. Los hijos del monstruo, nacidos en las sombras de su padre, regresan ahora, decididos a reclamar lo que consideran suyo: el oro que una vez perteneció al rey enano Thráin II.\n"

		"\nEl tesoro, una vez custodiado por un solo ser, ahora se ve protegido por una legión de dragones con la misma insaciable hambre que su antecesor. La Montaña, que guardó el silencio por tanto tiempo, vuelve a rugir con la furia de aquellos que ansían lo que no les pertenece.\n"

		"\nLos cazadores, sabiendo que esta vez el desafío es aún mayor, se preparan para enfrentar a una fuerza más peligrosa que cualquier que hayan conocido. No luchan solo por el oro, sino por evitar que la sombra de la codicia del dragón se apodere nuevamente de la tierra.\n\n"SC);
	}

extern Cazador CazadorActivo;

//TIENDA
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
            if (CazadorActivo.oro >= 25) {
                printf("Has comprado un frasco pequeño de Estus. +25 vida.\n");
                CazadorActivo.oro -= 25; // Restamos el oro
                CazadorActivo.vida += 25; // Aumentamos la vida del cazador
            } else {
                printf("No tienes suficientes monedas para esta compra.\n");
            }
        } 
        else if (opcionVida == 2) {
            if (CazadorActivo.oro >= 50) {
                printf("Has comprado un frasco grande de Estus. +50 vida.\n");
                CazadorActivo.oro -= 50; // Restamos el oro
                CazadorActivo.vida += 50; // Aumentamos la vida del cazador
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
                if (CazadorActivo.oro >= 150) {
                    printf("Has comprado Anduril, una espada de alto alcance. +30 daño.\n");
                    CazadorActivo.oro -= 150;  // Restamos el oro
                    CazadorActivo.daño += 30;  // Aumentamos el daño
                } else {
                    printf("No tienes suficientes monedas para esta compra.\n");
                }
            } 
            else if (opcionArma == 2) {
                if (CazadorActivo.oro >= 150) {
                    printf("Has comprado la Bearded Axe, un hacha de doble filo +35 daño.\n");
                    CazadorActivo.oro -= 150;  // Restamos el oro
                    CazadorActivo.daño += 35;  // Aumentamos el daño
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



//MENÚ
 extern int totalCazadores;

 void MENU(){
	Cazador *cazadores = NULL;//Tenemos que inicializar el puntero donde vamos a guradar a los cazadores en el main, como todavía no tiene 'nada', lo inicializamos en nulo.
    inicializarCazadores(&cazadores, &totalCazadores);


	int opcion;

    printf(MAGENTA"\t MENÚ: \n"
            AZUL_C"\t 1) Seleccionar un cazador.\n"
                  "\t 2) Añadir cazador.\n"
                  "\t 3) Salir.\n"SC
           MAGENTA"\t OPCIÓN: "SC);
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            cazadorSELEC(cazadores, totalCazadores);  // Llamada a la función definida en cazador.c
            break;
        case 2:
            añadirCazador(&cazadores, &totalCazadores);
            break;
        case 3:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }
 free (cazadores);
 }


