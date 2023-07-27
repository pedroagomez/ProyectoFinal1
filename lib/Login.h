#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idUsuario;
    int amigos[30];
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int listadoIdsContenidosGuardados[50];
    ///int validosIdsContenidos;
    int listadoCategorias[10];
    int validosCategorias;///agregado ultimo
    ///int misContenidos[50]; ///agregado ultimo
    int validosContenidos;
    int puntaje;
    int nivel;
    int rol;
    int activo;
} stUsuario;

int verificarExistenciaUsuario(char registroUsuario[], char userName[]);
stUsuario cargarUsuario();
void mostrarUsuario(stUsuario aux, int rol);
void cargarArchivoUsuario(char registroUsuario[]);
void mostrarArchivo(char registroUsuario[]);
void menuSistema(stUsuario);
void modificarPerfilUsuario(stUsuario usuario, char nombreArchivo[]);
void darBajaUsuario(int idUsuario, char nombreArchivo[]);
void darmeBajaUsuario(stUsuario usuario, char nombreArchivo[]);
stUsuario agregarContenidoLike(stUsuario usuario,int idContenido, char nombreArchivo[]);

int encontrarUsuario(stUsuario usuarios[], int validosUsuarios, char nombreUsuario[20]);
int traerTodosUsuarioArray(stUsuario usuarios[], char nombreArchivo[]);
int logear(char nombreUsuario[], char password[]);
int yaDioLike(stUsuario usuario, int idContenido);
int menuIniciarSesion();
int encontrarUsuarioPorId(stUsuario usuarios[], int validosUsuarios, int idUsuario);

int pesoArchivo(char nombreArchivo[], char structura[]); ///sacarla despues

stUsuario buscarUnUsuario(int idUsuario, char nombreArchivo[]);

#endif // LOGIN_H_INCLUDED
