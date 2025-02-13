#include "dragones.h"

int main() {
    int opcion;
    char nombre[MAX_NOMBRE];
    int vida, daño, resistencia, oro;
    char pasiva[MAX_DESCRIPCION];
    char descripcion[MAX_DESCRIPCION];

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
            //añadir_dragon(nombre, vida, daño, resistencia, pasiva, descripcion, oro);
            break;

        case 3:
            printf("Saliendo...\n");
            break;

        default:
            printf("Opción inválida.\n");
            break;
    }

    return 0;
}