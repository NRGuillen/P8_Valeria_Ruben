#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOMBRE 50
#define MAXARMA 20
#define MAXATAQUE 20
#define MAXVIDA 200
#define MAXORO 200
#define MAXDESCRPCION 200

//STRUCT DATOS CAZADOR;   
    typedef struct{
        int ID;
        char nombre[MAXNOMBRE];
        char arma[MAXARMA];
        int ataque;
        int vida;
        int oro;
        char descripcion[MAXDESCRPCION];
    } Cazador;


//INICIALIZAR CAZADOR  
    void inizializarCazador (Cazador * datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion){
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
               "\033[31m\t Descripción:\033[0m %s.\n",
               cazador_a_imprimir->nombre,
               cazador_a_imprimir->arma,
               cazador_a_imprimir->ataque,
               cazador_a_imprimir->vida,
               cazador_a_imprimir->oro,
               cazador_a_imprimir->descripcion);
    }

int main() {
    Cazador * cazadores = (Cazador*) malloc (3*sizeof(Cazador));
     if (cazadores == NULL){
        printf("ERROR CATASTRÓFICO: No se pudo asignar memoria.\n");
        return 0;}

    inizializarCazador(&cazadores[0], 1, "Mushashi", "Iaido", 20, 120, 100, "Un caballero audaz y letal, cuya fuerza arrolladora destruye cualquier defensa. Ataca con velocidad y precisión, sin dar tregua a sus enemigos.");
    inizializarCazador(&cazadores[1], 2, "Conan", "Atlantean", 15, 150, 100, "Un caballero imponente y resistente, cuya armadura absorbe cualquier golpe. Avanza sin miedo, protegiendo a sus aliados con su inquebrantable defensa.");
    inizializarCazador(&cazadores[2], 3, "Sauron", "Narsil", 10, 90, 100, "Un sabio y compasivo curandero, cuyo poder restaura heridas y protege a sus aliados. Su magia divina es un faro de esperanza en la batalla.");

    printf("\033[35mCAZADORES DISPONIBLES:\033[0m\n");
    system("chafa -f symbols -s 50x30 Mushashi.jpg"); //PARA USAR CHAFA, EL USUARIO HA DE DESCARGARSE "sudo apt install chafa"
    cazadorSELECT(&cazadores[0]);
    system("chafa -f symbols -s 50x30 Conan.jpg");
    cazadorSELECT(&cazadores[1]);
    system("chafa -f symbols -s 50x30 Sauron.jpg");
    cazadorSELECT(&cazadores[2]);

    

    
free(cazadores);
return 0;
}
