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

void inicializarCazador (Cazador * datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion);

void cazadorSELECT ( const Cazador * cazador_a_imprimir);

void visualizarCazador(void);

