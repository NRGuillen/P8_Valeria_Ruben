/*Separamos en .c y .h
el .h tiene las funciones DECLARDAS CON UNA LINEA, includes, defines, struct

el .c DEFINIMOS Y HACEMOS LAS FUNCIONES COMPLETAS. ADEMÁS DEL <cazadores.h>
include <cazadores.h> 

Dos monedas: cazador.h y cazador.c

luego en el main.c SOLO HAY UN  MAIN EN LOS OTROS .h y .C NO HAY MAIN 
#include <cazadores.h>
#include <dragon.h>
#include <combate.h>
#include <utilidades.h>


COMPILAR:  gcc main.c cazador.c -o programa
*/

#include "cazador.h"
#include "utilidades.h"

int main() {
    int totalCazadores = 3;
    int opcion;
    Cazador *cazadores = NULL;
    inicializarCazadores(&cazadores, &totalCazadores);

    printf("1) Seleccionar un cazador.\n"
           "2) Añadir cazador.\n"
           "3) Salir.\n"
           "Seleccion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            visualizarCazador(cazadores, totalCazadores);  // Llamada a la función definida en cazador.c
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
return 0;
}

