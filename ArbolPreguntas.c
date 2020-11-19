#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArbolPreguntas.h"
#include "AlumnoMago.h"
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <windowsx.h>

const char nombreArchivo[] = "archivoArbol";

arbolDePreguntas * inicArbol() //Inicializa un arbol
{
    return NULL;
}

arbolDePreguntas * crearPregunta(stPregunta nuevaPregunta) //Crea las preguntas que iran a los nodos
{
    arbolDePreguntas * aux = malloc(sizeof(arbolDePreguntas));
    strcpy(aux->pregunta.pregunta,nuevaPregunta.pregunta);
    strcpy(aux->pregunta.respuesta1,nuevaPregunta.respuesta1);
    strcpy(aux->pregunta.respuesta2,nuevaPregunta.respuesta2);
    aux->pregunta.idPregunta = nuevaPregunta.idPregunta;
    aux->der = NULL;
    aux->izq = NULL;
    return aux;
}

void crearArchivoArbol() //Crea un arbol y lo guarda en un archivo
{
    stPregunta aux;
    FILE * archi = fopen(nombreArchivo,"ab");
    char control = 's';
    if(archi != NULL)
    {
        while(control == 's')
        {
            printf("\nIngrese la pregunta: ");
            fflush(stdin);
            gets(aux.pregunta);
            printf("\nIngrese la primer respuesta: ");
            fflush(stdin);
            gets(aux.respuesta1);
            printf("\nIngrese la segunda respuesta: ");
            fflush(stdin);
            gets(aux.respuesta2);
            printf("\nIngrese la ID de la pregunta: ");
            scanf("%d",&aux.idPregunta);
            fwrite(&aux,sizeof(stPregunta),1,archi);
            printf("\nContinuar: ");
            fflush(stdin);
            scanf("%c",&control);
        }
        fclose(archi);
    }
}

void mostrarNodoPregunta(arbolDePreguntas * arbol) //Muestra una pregunta
{
    printf("\n");
    puts(arbol->pregunta.pregunta);
    printf("\n");
    puts(arbol->pregunta.respuesta1);
    puts(arbol->pregunta.respuesta2);

}

int sombreroSeleccionador(arbolDePreguntas * arbol) //Asigna una casa a un alumno
{
    int rta = 0;
    int resultado = 0;
    if(arbol->der == NULL && arbol->izq == NULL)
    {

        resultado = arbol->pregunta.idPregunta; //Asigna a resultado el id de la hoja

    }
    else //Recorre el arbol mostrando las preguntas
    {
        resultado = arbol->pregunta.idPregunta;
        mostrarNodoPregunta(arbol);
        printf("\nEscoge el numero de respuesta que quiera elegir y presione enter: ");
        scanf("%d",&rta);

        if(rta == 1)
        {
            resultado = sombreroSeleccionador(arbol->izq);
        }
        else if(rta == 2)
        {
            resultado = sombreroSeleccionador(arbol->der);
        }
        else
        {

            printf("\nRespuesta Equivocada. Vuelva a Intentarlo.\n\n");
            system("pause");

            resultado = sombreroSeleccionador(arbol);
        }

    }
    return resultado; //Retorna el resultado
}


void lectorDeResultado(int resultado,char casa[]) //Anuncia la casa asignada al alumno
{
    if(resultado == 1 || resultado == 11 || resultado == 23 || resultado == 29)
    {
        strcpy(casa,"Gryffindor");
        PlaySound("Gryffindor.wav",NULL,SND_ASYNC);
        printf("!!!GRYFFINDOR!!!\n");
        Sleep(5200);
    }
    else if(resultado == 3 || resultado == 13 || resultado == 19 || resultado == 25)
    {
        strcpy(casa,"Hufflepuff");
        PlaySound("Hufflepuff.wav",NULL,SND_ASYNC);
        printf("!!!HUFFLEPUFF!!!\n");
        Sleep(2100);
    }
    else if(resultado == 5 || resultado == 9 || resultado == 17 || resultado == 31)
    {
        printf("Mmmm");
        Puntitos_Suspensivos();
        printf("Ya se que hare contigo");
        Puntitos_Suspensivos();
        printf("!!!SLYTHERIN!!!\n");
        strcpy(casa,"Slytherin");
        PlaySound("Slytherin.wav",NULL,SND_ASYNC);
        Sleep(1100);

    }
    else if(resultado == 7 || resultado == 15 || resultado == 21 || resultado == 27)
    {
        strcpy(casa,"Ravenclaw");
        printf("Mmmm");
        Puntitos_Suspensivos();
        printf("Ya se que hare contigo");
        Puntitos_Suspensivos();
        printf("!!!RAVENCLAW!!!\n");
        PlaySound("Ravenclaw.wav",NULL,SND_ASYNC);
        Sleep(1500);
    }


}


arbolDePreguntas * pasarDeArchivoToArbol(arbolDePreguntas * arbol) //Carga el arbol desde un archivo
{
    stPregunta pregunta;
    arbolDePreguntas * arbolito = inicArbol();
    FILE * archi = fopen("archivoArbol","rb");
    if(archi != NULL)
    {
        while(fread(&pregunta,sizeof(stPregunta),1,archi) > 0)
        {

            arbolito = crearPregunta(pregunta);
            arbol = insertar(arbol,arbolito);
        }
        fclose(archi);
    }
    else
    {
        printf("\nERROR!\n");
    }
    return arbol;
}

arbolDePreguntas * insertar(arbolDePreguntas * arbol, arbolDePreguntas * nuevoNodo) //Inserta un nodo en el arbol
{
    if(arbol==NULL)
    {
        arbol = nuevoNodo;
    }
    else
    {
        if(nuevoNodo->pregunta.idPregunta > arbol->pregunta.idPregunta)
        {
            arbol->der = insertar(arbol->der, nuevoNodo);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, nuevoNodo);
        }
    }
    return arbol;
}

void Puntitos_Suspensivos()// Genera un aura de misterio que mantendra al usuario espectante de cuales seran las siguientes palabras emitidas en pantalla
{
    printf(".");//Este puntito genera intriga
    Sleep(500);
    printf(".");//Este puntito genera incertidumbre
    Sleep(500);
    printf(".\n");//Este puntito genera una duda excistencial que hara que te replantees tu vida por completo
    Sleep(500);
}
