#include "utilidades.h"
#include "dragones.h"

void añadir_dragon(char *nombre, int vida, int daño, int resistencia, char *pasiva, char *descripcion, int oro) {

    printf("Introduce el nombre de tu dragon:");
    scanf("%s", nombre);

    printf("Introduce la vida de tu dragon:");
    scanf("%d", &vida);

    printf("Introduce el daño de tu dragon:");
    scanf("%d", &daño);

    printf("Introduce la resistencia de tu dragon:");
    scanf("%d", &resistencia);

    int seleccion;

    printf("Selecciona una pasiva para tu dragon:\n");
    printf("\t1) PASIVA: +25%% resistencia a ataques\n");
    printf("\t2) PASVIA: +25%% daño\n");
    printf("\t3) PASIVA: Se curara un 5%% de su vida despues de cada ataque\n");
    printf("Seleccion:");
    scanf("%d", &seleccion);

    if(seleccion == 1){
        printf("PASIVA: +25%% resistencia a ataques\n");
    }else if(seleccion == 2){
        printf("PASVIA: +25%% daño\n");
    }else{
        printf("PASVIA: Se curara un 5%% de su vida despues de cada ataque\n");
    }

    printf("Introduce una descripcion para tu dragon:");
    fgets(descripcion, 1000, stdin);

    printf("Introduce la recompensa de oro de tu dragon: ");
    scanf("%d", &oro);




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

#define COLOR_ROJO "\033[40C"

void mostrarDragon(Dragon *dragon) {
    printf("\033[30A\033[60C\033[31mDragon %d\033[0m\n", dragon->id);
    printf("\033[50C\033[31m Nombre:\033[0m %s\n", dragon->nombre);
    printf("\033[50C\033[31m Vida:\033[0m %d\n", dragon->vida);
    printf("\033[50C\033[31m Daño:\033[0m %d\n", dragon->daño);
    printf("\033[50C\033[31m Resistencia:\033[0m %d%%\n", dragon->resistencia);
    printf("\033[50C\033[31m Pasiva:\033[0m %s\n", dragon->pasiva);
    printf("\033[50C\033[31m Descripción:\033[0m %s\n", dragon->descripcion);
    printf("\033[50C\033[31m Recompensa:\033[0m %d de oro\033[30B\n\n", dragon->oro);
}


void visualizarDragones() {
    
    Dragon *dragones = (Dragon*) malloc(3*sizeof(Dragon));
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

    free(dragones);

}



