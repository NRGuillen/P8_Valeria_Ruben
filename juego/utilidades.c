// AÑADIDO VALERIA

#include "utilidades.h"
#include "cazadores_dragones.h"

// MENSAJE DE BIENVENIDA
void BIENVENIDA() {
    system("clear");
    system("chafa -f symbols -s 90x50 Erebor.jpg");
    printf(CURSIVA "Tras la caída del gran dragón codicioso, los cielos sobre la Montaña Solitaria permanecieron en silencio por generaciones. Sin embargo, los ecos de su avaricia no desaparecieron tras su muerte a manos de Bardo. Los hijos del monstruo, nacidos en las sombras de su padre, regresan ahora, decididos a reclamar lo que consideran suyo: el oro que una vez perteneció al rey enano Thráin II.\n"

           "\nEl tesoro, una vez custodiado por un solo ser, ahora se ve protegido por una legión de dragones con la misma insaciable hambre que su antecesor. La Montaña, que guardó el silencio por tanto tiempo, vuelve a rugir con la furia de aquellos que ansían lo que no les pertenece.\n"

           "\nLos cazadores, sabiendo que esta vez el desafío es aún mayor, se preparan para enfrentar a una fuerza más peligrosa que cualquier que hayan conocido. No luchan solo por el oro, sino por evitar que la sombra de la codicia del dragón se apodere nuevamente de la tierra.\n\n" SC);
}

// MENÚ
extern int totalCazadores;

void MENU() {
    Cazador *cazadores = NULL;  // Tenemos que inicializar el puntero donde vamos a guardar a los cazadores en el main, como todavía no tiene 'nada', lo inicializamos en nulo.
    inicializarCazadores(&cazadores, &totalCazadores);

    int opcion;

    printf(MAGENTA "\t MENÚ: \n"
                   AZUL_C "\t 1) Seleccionar un cazador.\n"
                          "\t 2) Añadir cazador.\n"
                          "\t 3) Salir.\n" SC
           MAGENTA "\t OPCIÓN: " SC);
    scanf("%d", &opcion);

    switch (opcion) {
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
    free(cazadores);
}

