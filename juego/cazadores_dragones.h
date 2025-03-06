#ifndef DRAGONES_Y_CAZADORES_H
#define DRAGONES_Y_CAZADORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilidades.h"

// Definiciones y estructuras para Dragones
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

// Funciones para Dragones
void visualizarDragones(void);
void añadir_dragon(Dragon **dragones, int *totalDragones);
void seleccionarDragon(Dragon *dragones, int totalDragones);

// Definiciones y estructuras para Cazadores
#define MAXNOMBRE 50
#define MAXARMA 20
#define MAXATAQUE 20
#define MAXVIDA 100
#define MAXORO 600
#define MAXDESCRPCION 200

typedef struct {
    int ID;
    char nombre[MAXNOMBRE + 1];
    char arma[MAXARMA + 1];
    int ataque;
    int vida;
    int oro;
    char descripcion[MAXDESCRPCION + 1];
} Cazador;

// Funciones para Cazadores
void añadirCazador(Cazador **cazadores, int *totalCazadores);
void inicializarCazador(Cazador *datos, int ID, const char *nombre, const char *arma, int ataque, int vida, int oro, const char *descripcion);
void inicializarCazadores(Cazador **cazadores, int *totalCazadores);
void cazadorSELEC(Cazador *cazadores, int totalCazadores);

#endif // DRAGONES_Y_CAZADORES_H

