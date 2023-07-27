#include "login.h"
#include "mensaje.h"

void centrarTexto(const char *texto) {
    int espacios = (80 - strlen(texto)) / 2;
    for (int i = 0; i < espacios; i++) {
        printf(" ");
    }
    printf("%s", texto);
}

void guardarMensajeenArchivo() {
    stMensaje mensaje;
    FILE *archiMensajes = fopen("mensajes.bin", "ab");
    if (archiMensajes != NULL) {
        mensaje = escribeMensaje();
        fwrite(&mensaje, sizeof(mensaje), 1, archiMensajes);
        printf("mensaje enviado\n");
        fclose(archiMensajes);
    } else {
        printf("error al enviar mensaje");
    }
}

void bajarMensajedeArchivo() {
    stMensaje mensaje;
    FILE *archiMensajes = fopen("mensajes.bin", "rb");
    if (archiMensajes != NULL) {
        fread(&mensaje, sizeof(mensaje), 1, archiMensajes);
        mostrarMenjase(mensaje);
        fclose(archiMensajes);
    }else
    {
     centrarTexto("no tiene ningun mensaje");
    }
}

void mostrarMenjase(stMensaje mensajes) {
   // system("cls"); // Limpiar la pantalla


    cuadro(47,13,67,15);
    gotoxy(49,14);
    printf("SU MENSAJE NUEVO");

    gotoxy(41,18);
    printf("De:");
    printf("%s", mensajes.remitente);
    gotoxy(39,19);
    printf("---------------------------------------\n");

    gotoxy(41,21);
    printf("Asunto:");
    printf("%s", mensajes.asunto);
    gotoxy(39,23);
    printf("---------------------------------------\n");

    gotoxy(41,24);
    printf(mensajes.cuerpo);
    printf("\n");
    gotoxy(39,26);
    printf("---------------------------------------\n");
    if(mensajes.leido == 0)
    {
        //printf("leido");
        mensajes.leido = 1;
    }

}

stMensaje escribeMensaje() {
    stMensaje nuevoMensaje;

    system("cls"); // Limpiar la pantalla

    cuadro(44,2,72,4);
    gotoxy(52,3);
    printf("NUEVO MENSAJE");
    printf("\n\n");

    printf("Para: ");
    fflush(stdin);
    gets(nuevoMensaje.destinatario);
    printf("\n");

    printf("Asunto: ");
    gets(nuevoMensaje.asunto);
    printf("\n");

    printf("Escriba el Mensaje:\n");
    gets(nuevoMensaje.cuerpo);
    printf("\n");

    printf("Firma: ");
    gets(nuevoMensaje.remitente);
    printf("\n");
    nuevoMensaje.leido=0;

    return nuevoMensaje;
}
void menumensajeria(stUsuario A)
{
    int eleccion=0;
    centrarTexto("ingrese lo que desea hacer");
    printf("\n");
    centrarTexto("1-Mandar mensaje");
    printf("\n");
    centrarTexto("2-ver casilla de mensajes");
    printf("\n");
    fflush(stdin);
    scanf("%d",&eleccion);
    switch(eleccion)
    {
    case 1:
        {
            guardarMensajeenArchivo();
        break;
        }
    case 2:
        {
            //bajarMensajedeArchivo();
             validarRemitente(A);
            break;
        }
    }
}
/*int validarRemitente(stUsuario A)///mostrarMensajesNoLeidos = nombre funcion
{

    FILE *archiMensajes = fopen("mensajes.bin", "rb");
    if (archiMensajes != NULL) {
        stMensaje mensajito;
        while (fread(&mensajito, sizeof(stMensaje), 1, archiMensajes) ==1) {
            if (strcmp(mensajito.destinatario, A.mail) == 0) {///&& mensajito.leido == 0
                mostrarMenjase(mensajito);
            }
        }
        fclose(archiMensajes);
    }
}
*/
void validarRemitente(stUsuario A)///MUESTRA MENSAJES CARGADOS -"CASE 2"-
{
    FILE * archiMensajes = fopen("mensajes.bin", "rb");
    if (archiMensajes != NULL)
    {

            ///muestra mensajes con un destinatario especifico
            stMensaje mensajito;
            while (fread(&mensajito, sizeof(stMensaje), 1, archiMensajes) ==1)
            {
                if (strcmp(mensajito.destinatario, A.mail) == 0)
                {
                    mostrarMenjase(mensajito);
                    printf("\n");
                }
            }
            fclose(archiMensajes);

    }
}
void mostrarTodosLosMensajes()///admin
{
    FILE * archiMensajes = fopen("mensajes.bin", "rb");
    if (archiMensajes != NULL)
    {
        stMensaje mensajito;
        while (fread(&mensajito, sizeof(stMensaje), 1, archiMensajes) ==1)
        {

            mostrarMenjase(mensajito);

        }
        fclose(archiMensajes);
    }
}
