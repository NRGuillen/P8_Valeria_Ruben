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


COMPILAR:  gcc *.c -o programa
*/

#include "cazador.h"
#include "utilidades.h"

int totalCazadores = 3;

int main() {
    system("clear");

    BIENVENIDA();
    
    MENU();

return 0;
}

