typedef struct dragones{

    int id;
    char nombre[20];
    int vida;
    int daño;
    int resistencia;
    int pasiva;
    char descripcion[1000];
    int oro;

}dragones;

#include <stdio.h>
#include <stdlib.h>

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
    printf("1) PASIVA: +25%% resistencia a ataques\n")
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
    fgets(resistencia,1000,  stdin);

    printf("Introduce la recompensa de oro de tu dragon: ");
    scanf("%d", &oro);

}

void dragon1(){

    printf("\n\n\t\t\tDragon 1\n");
    system("chafa -f symbols -s 60x60 blood.jpg"); 
    printf("\n\n<----CARACTERISTICAS---->\n");
    printf("NOMBRE: Nigthmare.\n");
    printf("VIDA: 100\n");
    printf("DAÑO BASE: 10\n");
    printf("RESISTENCIA BASE: 15%%");
    printf("PASIVA: +25%% resistencia a ataques\n");
    printf("DESCRIPCION: Nigthmare es un dragon proveniente de las pesadillas mas oscuras, nigun caballero quiere desafiarle\n");
    printf("RECOMPENSA: 50 de oro\n");

}

void dragon2(){

    printf("\n\n\t\t\tDragon 2\n");
    system("chafa -f symbols -s 60x60 drake3.jpg");
    printf("\n\n<----CARACTERISTICAS---->\n");
    printf("NOMBRE: Cryonyx\n");
    printf("VIDA: 100\n");
    printf("DAÑO BASE: 15\n");
    printf("RESISTENCIA BASE: 15\n");
    printf("PASIVA: +25%% daño\n");
    printf("DESCRIPCION: Cryonyx es un dragon temido debido a tu alto poder, vive en las montañas solitario y desarrollando aun mas su fuerza\n");
    printf("RECOMPENSA: 100 de oro\n");
 
}

void dragon3(){

    printf("\n\n\t\t\tDragon 3\n");
    system("chafa -f symbols -s 60x60 drake4.jpg");
    printf("\n<----CARACTERISTICAS---->\n");
    printf("NOMBRE: Velkhanos\n");
    printf("VIDA: 100\n");
    printf("DAÑO BASE: 10\n");
    printf("RESISTENCIA BASE: 15%%\n");
    printf("PASIVA: Se curara un 5%% de su vida despues de cada ataque\n");
    printf("DESCRIPCION: Velkhanos es un dragon historico, proveniente de asia, ningun otro dragon a podido derrotarle\n");
    printf("RECOMPENSA: 200 de oro\n");

}


void visualizar_dragones(){

    dragon1();
    dragon2();
    dragon3();

    int seleccion;
    printf("\n\nIntroduce contra que dragon te quieres enfrentar primero:");
    scanf("%d", &seleccion);
    printf("\n\n");

    if(seleccion == 1){
        printf("<-----------------Has seleccionado el dragon %d------------->", seleccion);
        dragon1();
    }else if(seleccion == 2){
        dragon2();
    }else if(seleccion == 3){
        dragon3();
    }else{
        printf("No existe ningun dragon con el numero %d", seleccion);
    }



}

int main() {

    int opciones;

    printf("1) Seleccionar un dragon predefinido\n");
    printf("2) Crear un dragon personalizado\n");
    printf("3) Salir\n");
    printf("Seleccion:");
    scanf("%d", &opciones);

    switch(opciones){

        case 1:

            visualizar_dragones();
       
            break;

        case 2:

            break;

        case 3:
            break;

        default:
            break;

    }

    
    return 0;
}