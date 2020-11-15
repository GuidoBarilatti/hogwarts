#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AlumnoMago.h"
#ifndef ARBOLPREGUNTAS_H_INCLUDED
#define ARBOLPREGUNTAS_H_INCLUDED

//Estructuras
typedef struct
{
    int idPregunta;
    char pregunta[500];
    char respuesta1[500];
    char respuesta2[500];
}stPregunta;
typedef struct nodoPregunta
{
    stPregunta pregunta;
    struct nodoPregunta * izq;
    struct nodoPregunta * der;
}arbolDePreguntas;

//Funciones tipo VOID
void crearArchivoArbol();
void mostrarNodoPregunta(arbolDePreguntas * arbol);

//Funciones que devuelven nodos
arbolDePreguntas * inicArbol();
arbolDePreguntas * crearPregunta(stPregunta nuevaPregunta);
arbolDePreguntas * pasarDeArchivoToArbol(arbolDePreguntas * arbol);
arbolDePreguntas * insertar(arbolDePreguntas * arbol, arbolDePreguntas * nuevoNodo);

//Funciones que devuelven enteros
int sombreroSeleccionador(arbolDePreguntas * arbol);

//Funciones que devuelven estructuras
void lectorDeResultado(int resultado,char casa[]);


#endif // ARBOLPREGUNTAS_H_INCLUDED
