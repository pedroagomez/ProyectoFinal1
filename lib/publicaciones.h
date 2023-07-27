#include <stdio.h>
#include <stdlib.h>
#include "Login.h"
//#include "categorias.h"

typedef struct
{
    int idUser; //esto para tener algo cargado
    int idContenido; // auto incremental
    char titulo[30];
    char descripcion[300];///idCategoria 1---categoria 1 futbol id cate-- 2---- comida  user catego[2] ={1, 2}
    ///int validosCategoria;
    int categoria;
    //char categoria[10][30]; ///esto puede ser una matriz
    int likes;
    //int puntosPorCompartir;  //no le veo sentido
    int activo;                     // indica 1 o 0 si el contenido esta activo
} stContenido;

stContenido cargaUnContenido();
stContenido mostrarContenido(stContenido contenido, int rol,stUsuario usuarios[], int validosUsuarios);
void mostrarArchivoContenido(char nombre_archivo_contenido[], stUsuario usuario);
void cargaDeContenidoArchivo(char nombre_archivo_contenido[], stUsuario usuario);
void darBajaPostAdmin(int idPost, char nombreArchivo[]);
void misPosteos(stContenido contenidos[], int validosContenidos, stUsuario usuario);
void funcionDarLike(stContenido contenido, char nombreArchivo[]);
void funcionDarDislike(stContenido contenido, char nombreArchivo[]);
void saltoDeLineaCada60Caracteres(const char* texto);

int filtrarPostCategoria(stContenido contenidos[], int validosContenidos, int idCategoria,stUsuario usuarios[], int validosUsuarios);
int traerTodosPostArray(stContenido contenidos[], char nombreArchivo[]);
int modificarPosteo(stContenido contenidos,int idUsuario, char nombreArchivo[]);
int buscarContenidoPorPalabra(stContenido contenidos[],int validosContenido , char palabra[]);
int buscarContenidoPorId(stContenido contenidos[], int validosContenidos, int idContenido);
int traerTodosPostAdmin(stContenido contenidos[], char nombreArchivo[]);


