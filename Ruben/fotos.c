#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 1000

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    int vida;
    int dano;
    int resistencia;
    char pasiva[MAX_DESCRIPCION];
    char descripcion[MAX_DESCRIPCION];
    int oro;
} Dragon;

void añadir_dragon(char nombre, int vida, int daño, int resistencia, int pasiva, char descripcion, int oro){

    printf("Introduce el nombre de tu dragon:");
    scanf("%s", &nombre);

    printf("Introduce la vida de tu dragon:");
    scanf("%d", &vida);

    printf("Introduce el daño de tu dragon:");
    scanf("%d", &daño);

    printf("Introduce la resistencia de tu dragon:");
    scanf("%d", &resistencia);

    int seleccion;

    printf("Selecciona una pasiva para tu dragon:\n");
    printf("1) PASIVA: +25%% resistencia a ataques\n");
    printf("2) PASVIA: +25%% daño\n");
    printf("3) PASIVA: Se curara un 5%% de su vida despues de cada ataque\n");
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

    printf("Introduce la recompensa de oro de tu dragon: ");
    scanf("%d", &oro);

}

void inicializarDragon(Dragon *dragon, int id, const char *nombre, int vida, int dano, int resistencia, const char *pasiva, const char *descripcion, int oro) {
    dragon->id = id;
    strcpy(dragon->nombre, nombre);
    dragon->vida = vida;
    dragon->dano = dano;
    dragon->resistencia = resistencia;
    strcpy(dragon->pasiva, pasiva);
    strcpy(dragon->descripcion, descripcion);
    dragon->oro = oro;
}

void mostrarDragon(const Dragon *dragon) {
    printf("\n\t\033[31mDragon %d\033[0m\n", dragon->id);
    printf("\033[31m\t Nombre:\033[0m %s\n", dragon->nombre);
    printf("\033[31m\t Vida:\033[0m %d\n", dragon->vida);
    printf("\033[31m\t Daño:\033[0m %d\n", dragon->dano);
    printf("\033[31m\t Resistencia:\033[0m %d%%\n", dragon->resistencia);
    printf("\033[31m\t Pasiva:\033[0m %s\n", dragon->pasiva);
    printf("\033[31m\t Descripción:\033[0m %s\n", dragon->descripcion);
    printf("\033[31m\t Recompensa:\033[0m %d de oro\n", dragon->oro);
}

void visualizarDragones() {
    Dragon dragones[3];
    inicializarDragon(&dragones[0], 1, "Nightmare", 100, 10, 15, "+25% resistencia a ataques", "Nightmare es un dragón proveniente de las pesadillas más oscuras, ningún caballero quiere desafiarle.", 50);
    inicializarDragon(&dragones[1], 2, "Cryonyx", 100, 15, 15, "+25% daño", "Cryonyx es un dragón temido debido a su alto poder, vive en las montañas en solitario desarrollando aún más su fuerza.", 100);
    inicializarDragon(&dragones[2], 3, "Velkhanos", 100, 10, 15, "Se curará un 5% de su vida después de cada ataque", "Velkhanos es un dragón histórico, proveniente de Asia, ningún otro dragón ha podido derrotarle.", 200);

    printf("\033[35mDRAGONES DISPONIBLES:\033[0m\n");
    system("chafa -f symbols -s 50x30 blood.jpg"); //PARA USAR CHAFA, EL USUARIO HA DE DESCARGARSE "sudo apt install chafa"
    mostrarDragon(&dragones[0]);
    system("chafa -f symbols -s 50x30 drake3.jpg");
    mostrarDragon(&dragones[1]);
    system("chafa -f symbols -s 50x30 drake4.jpg");
    mostrarDragon(&dragones[2]);

}

int main() {
    int opcion;
    printf("1) Seleccionar un dragón predefinido\n");
    printf("2) Salir\n");
    printf("Seleccion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            visualizarDragones();
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
