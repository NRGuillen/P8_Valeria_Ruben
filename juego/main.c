#include "cazadores_dragones.h"
#include "utilidades.h"

int main() {
    int opcion;
    Dragon *dragones = NULL;
    int totalDragones = 0;  

    Cazador *cazadores = NULL;
    int totalCazadores = 0;

    while (1) {
        // Menú principal
        printf(MAGENTA"\tMENÚ PRINCIPAL:\n");
        printf(AZUL_C"\t1) Gestionar Dragones\n");
        printf(AZUL_C"\t2) Gestionar Cazadores\n");
        printf(AZUL_C"\t3) Salir\n");
        printf(MAGENTA"\tSeleccion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Menú de gestión de dragones
                printf(MAGENTA"\tMENÚ DE DRAGONES:\n");
                printf(AZUL_C"\t1) Seleccionar un dragón predefinido\n");
                printf(AZUL_C"\t2) Crear un nuevo dragón\n");
                printf(AZUL_C"\t3) Volver al menú principal\n");
                printf(MAGENTA"\tSeleccion: ");
                int opcionDragon;
                scanf("%d", &opcionDragon);

                switch (opcionDragon) {
                    case 1:
                        visualizarDragones();
                        break;

                    case 2:
                        añadir_dragon(&dragones, &totalDragones);
                        break;

                    case 3:
                        break;

                    default:
                        printf("Opción inválida.\n");
                        break;
                }
                break;

            case 2:
                // Menú de gestión de cazadores
                printf(MAGENTA"\tMENÚ DE CAZADORES:\n");
                printf(AZUL_C"\t1) Seleccionar un cazador\n");
                printf(AZUL_C"\t2) Crear un nuevo cazador\n");
                printf(AZUL_C"\t3) Volver al menú principal\n");
                printf(MAGENTA"\tSeleccion: ");
                int opcionCazador;
                scanf("%d", &opcionCazador);

                switch (opcionCazador) {
                    case 1:
                        cazadorSELEC(cazadores, totalCazadores);
                        break;

                    case 2:
                        añadirCazador(&cazadores, &totalCazadores);
                        break;

                    case 3:
                        break;

                    default:
                        printf("Opción inválida.\n");
                        break;
                }
                break;

            case 3:
                printf("Saliendo...\n");
                free(dragones);
                free(cazadores);
                return 0;

            default:
                printf("Opción inválida.\n");
                break;
        }
    }

    return 0;
}
