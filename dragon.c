#include <stdio.h>
#include <stdlib.h>

void cargarImagen(const char*);

int main(void) {
    cargarImagen("banner.txt");
    return 0;
}

void cargarImagen(const char* nombre) {
    FILE *f = fopen(nombre, "r");
    if (f) {
        char linea[1024];  // Buffer para almacenar una línea
        while (fgets(linea, sizeof(linea), f)) { // Lee línea por línea
            printf("%s", linea);  // Imprime la línea completa
        }
        fclose(f);
    } else {
        fprintf(stderr, "No existe el archivo %s\n", nombre);
    }
}


