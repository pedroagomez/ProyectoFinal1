#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int idCategorias;
    char categorias[30];

} stCategorias;

void cargarCategorias();
void mostrarTodasCategorias();
void mostrarCategoria();
void traerTodasCategorias();

int totalCategorias();

stCategorias traerCategorias(int idCategoria);
