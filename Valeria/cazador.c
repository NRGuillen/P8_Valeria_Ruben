#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cazador.h"
#include "utilidades.h"

//INICIALIZAR CAZADOR  
    void inicializarCazador (Cazador * datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion){
        datos -> ID = ID;
        strcpy(datos-> nombre, nombre);
        strcpy(datos-> arma, arma);
        datos -> ataque = ataque;
        datos -> vida = vida;
        datos -> oro = oro;
        strcpy(datos-> descripcion, descripcion);
    }

//VISUALIZAR CAZADOR
    void cazadorSELECT ( const Cazador * cazador_a_imprimir){
        printf("\033[31m\t Nombre:\033[0m %s.\n"
               "\033[31m\t Arma:\033[0m %s.\n"
               "\033[31m\t Daño:\033[0m %d.\n"
               "\033[31m\t Vida:\033[0m %d.\n"
               "\033[31m\t Oro:\033[0m %d monedas.\n"
               "\033[31m\t Descripción:\033[0m %s\n",
               cazador_a_imprimir->nombre,
               cazador_a_imprimir->arma,
               cazador_a_imprimir->ataque,
               cazador_a_imprimir->vida,
               cazador_a_imprimir->oro,
               cazador_a_imprimir->descripcion);
    }
//IMPRIMIR CAZADORES:
    void visualizarCazador(){
        Cazador * cazadores = (Cazador*) malloc (3*sizeof(Cazador));
    if (cazadores == NULL){
        printf("ERROR CATASTRÓFICO: No se pudo asignar memoria.\n");
        exit(EXIT_SUCCESS);} //Salimos con código de error.

    inicializarCazador(&cazadores[0], 1, "Mushashi", "Iaido", 20, 120, 100, "Un caballero audaz y letal, cuya fuerza arrolladora destruye cualquier defensa. Ataca con velocidad y precisión, sin dar tregua a sus enemigos.");
    inicializarCazador(&cazadores[1], 2, "Conan", "Atlantean", 15, 150, 100, "Un caballero imponente y resistente, cuya armadura absorbe cualquier golpe. Avanza sin miedo, protegiendo a sus aliados con su inquebrantable defensa.");
    inicializarCazador(&cazadores[2], 3, "Sauron", "Narsil", 10, 90, 100, "Un sabio y compasivo curandero, cuyo poder restaura heridas y protege a sus aliados. Su magia divina es un faro de esperanza en la batalla.");

    printf("\033[35mCAZADORES DISPONIBLES:\033[0m\n");

        system("chafa -f symbols -s 50x30 Mushashi.jpg"); //PARA USAR CHAFA, EL USUARIO HA DE DESCARGARSE "sudo apt install chafa"
        cazadorSELECT(&cazadores[0]);
        system("chafa -f symbols -s 50x30 Conan.jpg");
        cazadorSELECT(&cazadores[1]);
        system("chafa -f symbols -s 50x30 Sauron.jpg");
        cazadorSELECT(&cazadores[2]);

free(cazadores);

    }

int main() {
    
    int opcion;
    printf("1) Seleccionar un cazador.\n"
           "2) Salir\n"
           "Seleccion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            visualizarCazador();
            break;

        case 2:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }



return 0;
}
