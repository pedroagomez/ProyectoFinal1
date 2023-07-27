#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char remitente[20];
    char destinatario[20];
    char asunto[50];
    char cuerpo[100];
    int leido;
} stMensaje;

void guardarMensajeenArchivo();
stMensaje escribeMensaje();
void bajarMensajedeArchivo();
void mostrarMenjase(stMensaje mensajes);
void centrarTexto(const char *texto);
void validarRemitente(stUsuario A);
void mostrarTodosLosMensajes();
//int validarRemitente(stUsuario A);
