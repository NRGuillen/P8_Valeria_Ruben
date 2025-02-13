#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 1000
#define MAX_DRAGONES 3

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    int vida;
    int daño;
    int resistencia;
    char pasiva[MAX_DESCRIPCION];
    char descripcion[MAX_DESCRIPCION];
    int oro;
} Dragon;

//AÑADIR VOIDS
void inicializarDragon(Dragon *dragon, int id,  char *nombre, int vida, int daño, int resistencia,  char *pasiva,  char *descripcion, int oro);
void mostrarDragon(Dragon *dragon);
void visualizarDragones(void);
