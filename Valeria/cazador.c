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
        printf(ROJO"\t Nombre:" SC " %s.\n"
               ROJO"\t Arma:" SC " %s.\n"
               ROJO"\t Daño:" SC " %d.\n"
               ROJO"\t Vida:" SC " %d.\n"
               ROJO"\t Oro:" SC " %d monedas.\n"
               ROJO"\t Descripción:" SC " %s\n",
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

    printf(NARANJA"CAZADORES DISPONIBLES: \n" SC);

        system("chafa -f symbols -s 50x30 Mushashi.jpg"); //PARA USAR CHAFA, EL USUARIO HA DE DESCARGARSE "sudo apt install chafa"
        cazadorSELECT(&cazadores[0]);
        system("chafa -f symbols -s 50x30 Conan.jpg");
        cazadorSELECT(&cazadores[1]);
        system("chafa -f symbols -s 50x30 Sauron.jpg");
        cazadorSELECT(&cazadores[2]);

free(cazadores);
}
