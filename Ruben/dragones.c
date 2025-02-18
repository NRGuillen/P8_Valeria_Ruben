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

void inicializarDragon(Dragon *dragon, int id,  char *nombre, int vida, int daño, int resistencia,  char *pasiva,  char *descripcion, int oro);
void mostrarDragon(Dragon *dragon);
void visualizarDragones(void);
void añadir_dragon(Dragon **dragones, int *totalDragones);
void seleccionarDragon(Dragon *dragones, int totalDragones);


void añadir_dragon(Dragon **dragones, int *totalDragones) {
    Dragon nuevoDragon;
    int seleccion;

    getchar(); 

    printf("Introduce el nombre de tu dragón: ");
    fgets(nuevoDragon.nombre, sizeof(nuevoDragon.nombre), stdin);
    nuevoDragon.nombre[strcspn(nuevoDragon.nombre, "\n")] = 0; 

    printf("Introduce la vida de tu dragón: ");
    scanf("%d", &nuevoDragon.vida);

    printf("Introduce el daño de tu dragón: ");
    scanf("%d", &nuevoDragon.daño);

    printf("Introduce la resistencia de tu dragón: ");
    scanf("%d", &nuevoDragon.resistencia);

    printf("Selecciona una pasiva para tu dragón:\n");
    printf("\t1) +25%% resistencia a ataques\n");
    printf("\t2) +25%% daño\n");
    printf("\t3) Se curará un 5%% de su vida después de cada ataque\n");
    printf("\t4) Sin pasiva\n");
    printf("Selección: ");
    scanf("%d", &seleccion);
    getchar(); 

    switch (seleccion) {
        case 1:
            strcpy(nuevoDragon.pasiva, "+25% resistencia a ataques");
            break;
        case 2:
            strcpy(nuevoDragon.pasiva, "+25% daño");
            break;
        case 3:
            strcpy(nuevoDragon.pasiva, "Se curará un 5% de su vida después de cada ataque");
            break;
        default:
            strcpy(nuevoDragon.pasiva, "Sin pasiva");
            break;
    }

    printf("Introduce una descripción para tu dragón: ");
    fgets(nuevoDragon.descripcion, sizeof(nuevoDragon.descripcion), stdin);

    printf("Introduce la recompensa de oro de tu dragón: ");
    scanf("%d", &nuevoDragon.oro);

    nuevoDragon.id = (*totalDragones) + 1;

    *dragones = (Dragon *)realloc(*dragones, (*totalDragones + 1) * sizeof(Dragon));
    if (*dragones == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }

    memcpy(&((*dragones)[*totalDragones]), &nuevoDragon, sizeof(Dragon));

    (*totalDragones)++; 
    printf("\nDragón personalizado:\n");
    mostrarDragon(&nuevoDragon);
}

void inicializarDragon(Dragon *dragon, int id,  char *nombre, int vida, int daño, int resistencia,  char *pasiva,  char *descripcion, int oro) {
    dragon->id = id;
    strcpy(dragon->nombre, nombre);
    dragon->vida = vida;
    dragon->daño = daño;
    dragon->resistencia = resistencia;
    strcpy(dragon->pasiva, pasiva);
    strcpy(dragon->descripcion, descripcion);
    dragon->oro = oro;
}

void mostrarDragon(Dragon *dragon) {
    printf("\033[36mDragon %d\033[0m\n", dragon->id);
    printf("\033[31mNombre:\033[0m %s\n", dragon->nombre);
    printf("\033[31mVida:\033[0m %d\n", dragon->vida);
    printf("\033[31mDaño:\033[0m %d\n", dragon->daño);
    printf("\033[31mResistencia:\033[0m %d%%\n", dragon->resistencia);
    printf("\033[31mPasiva:\033[0m %s\n", dragon->pasiva);
    printf("\033[31mDescripción:\033[0m %s\n", dragon->descripcion);
    printf("\033[31mRecompensa:\033[0m %d de oro\033[30B\n\n", dragon->oro);
}

void visualizarDragones() {
    Dragon *dragones = (Dragon*) malloc(3 * sizeof(Dragon));
    if(dragones == NULL){
        printf("Error al reservar memoria\n");
        exit(EXIT_SUCCESS);
    }

    inicializarDragon(&dragones[0], 1, "Nightmare", 100, 10, 15, "+25% resistencia a ataques", "Nightmare es un dragón proveniente de las pesadillas más oscuras, ningún caballero quiere desafiarle.", 50);
    inicializarDragon(&dragones[1], 2, "Cryonyx", 100, 15, 15, "+25% daño", "Cryonyx es un dragón temido debido a su alto poder, vive en las montañas en solitario desarrollando aún más su fuerza.", 100);
    inicializarDragon(&dragones[2], 3, "Velkhanos", 100, 10, 15, "Se curará un 5% de su vida después de cada ataque", "Velkhanos es un dragón histórico, proveniente de Asia, ningún otro dragón ha podido derrotarle.", 200);

    printf("\033[35mDRAGONES DISPONIBLES:\033[0m\n");
    system("chafa -f symbols -s 50x30 Nightmare.jpg"); 
    mostrarDragon(&dragones[0]);
    system("chafa -f symbols -s 50x30 Cryonyx.jpg");
    mostrarDragon(&dragones[1]);
    system("chafa -f symbols -s 50x30 Velkhanos.jpg");
    mostrarDragon(&dragones[2]);

    seleccionarDragon(dragones, 3);

    free(dragones);
}

void seleccionarDragon(Dragon *dragones, int totalDragones) {
    int seleccion;
    printf("Introduce el número del dragón que quieres seleccionar (1-3): ");
    scanf("%d", &seleccion);

    if (seleccion >= 1 && seleccion <= totalDragones) {
        if (seleccion == 1) {
            system("chafa -f symbols -s 50x30 Nightmare.jpg");  
        } else if (seleccion == 2) {
            system("chafa -f symbols -s 50x30 Cryonyx.jpg");  
        } else if (seleccion == 3) {
            system("chafa -f symbols -s 50x30 Velkhanos.jpg");  
        }

        mostrarDragon(&dragones[seleccion - 1]);  
    } else {
        printf("Has introducido un dragón que no existe.\n");
    }
}


int main() {
    int opcion;
    Dragon *dragones = NULL; 
    int totalDragones = 0;  

    printf("1) Seleccionar un dragón predefinido\n");
    printf("2) Crear un nuevo dragón\n");
    printf("3) Salir\n");
    printf("Seleccion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            visualizarDragones();
            break;

        case 2:
            añadir_dragon(&dragones, &totalDragones);
            break;

        case 3:
            printf("Saliendo...\n");
            break;

        default:
            printf("Opción inválida.\n");
            break;
    }

    free(dragones);
    return 0;
}






