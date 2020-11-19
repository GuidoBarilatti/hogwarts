#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AlumnoMago.h"
#ifndef PROFESORES_H_INCLUDED
#define PROFESORES_H_INCLUDED

//ESTRUCTURAS
typedef struct stTrabajo
{
    char materia[50];
    char titulo[50];
    char consigna[500];
    char demostracion[500];
    int anio;
} stTrabajo;

typedef struct nodoTrabajos
{
    stTrabajo trabajo;
    struct nodoTrabajos * sig;
} nodoTrabajos;

typedef struct
{
    stTrabajo tp;
    char materia[50];
} RegistroTrabajo;

typedef struct Profesor
{
    char nombre[30];
    char usuario[30];
    char contrasenia [16];
    char materia[50];
    char casa[50];
    int anio;
    int altaBaja; // Alta: 1 / Baja: 0.
} stProfesor;

typedef struct nodoProfesor
{
    stProfesor profesor;
    struct nodoProfesor * siguiente;
    struct nodoProfesor * anterior;
} nodoProfesor;

typedef struct stMateria
{
    char nombre[50];
    nodoTrabajos * trabajo;
} stMateria;

typedef struct
{
    char titulo[50];
    char aviso[500];
} stAviso;


//Funciones tipo Void
void pauseAndClean(); //Funcion que pausa y limpia la consola
void registroDeProfesores(); // Funcion que registra un nuevo profesor guardandolo en un archivo
void mostrarUnProfesor(nodoProfesor * profesor); // Funcion para mostrar un nodo profesor
void mostrarListaDeProfesores(nodoProfesor * lista); // Funcion que muestra la lista entera de profesores
void CargarContraseniaProfesor(char contrseniaProfe[]); //  Funcion que carga la contrasenia
void eleccionDeMateria(char materia[], int *anio);
void mostrarUnNodoTrabajo(nodoTrabajos * lista);
void mostrarListaTrabajos(nodoTrabajos * listas,int anio,char materia[]);
void cargarArchivoDeTrabajos(int anio, stMateria materias[], stProfesor profe);
void cargarArchivoRegistro(stProfesor profe); // Carga 'archivoTrbajos'.
void mostrarUnTrabajo(stTrabajo trabajo);
void mostrarArchivoRegistro(); // Muestra 'archivoTrabajos'.
void inicializarListaDeArregloMateria(stMateria arreglo[],int dimension);
void mostrarArchivoProfesor();
void mostrarProfesor(stProfesor profesor);
void Crear_Archivo_Profesor();
void mostrarListaSegunMateria(stMateria arreglo[],int validos, char materia[],int anio);
void Mostrar_Archivo_Trabajos();
void expulsarProfesor();
int BuscarProfesorEnArchivo(char usuario[]);
void mostrarUnAviso(stAviso aviso);
void cargarAvisoAlArchivo();
void mostrarAvisos();


//Funciones que devuelven estructuras
stProfesor crearEstructuraProfesor();
stTrabajo crearEstructuraTrabajo();

//Funciones de tipo nodo
nodoProfesor * buscarUltimo(nodoProfesor*lista);
nodoProfesor * agregarAlFinal(nodoProfesor * lista,nodoProfesor * nuevoNodo);
nodoProfesor * inicListaProfesores();
nodoProfesor * crearNodoProfesor(stProfesor nuevoProfesor);
nodoProfesor * pasarDeArchivoToListaProfesores(nodoProfesor * lista);
nodoTrabajos * iniclistaTrabajos();
nodoTrabajos * buscarUltimoTrabajo(nodoTrabajos * lista);
nodoTrabajos * agregarTrabajoAlFinal(nodoTrabajos * lista,nodoTrabajos * nuevoNodo);
nodoTrabajos * crearNodoTrabajo(stTrabajo nuevoTrabajo);
nodoTrabajos * pasarDeArchivoToListaTrabajos(nodoTrabajos * lista, int anio);


//Funciones que devuelven enteros
int eleccionDeCasas(char casa[]);
int eleccionDeAnio();
int comprobacionMateriaOcupada(char materia[],int anio);
int escaneoSesion(stProfesor * profe);
int menuMateriasPrimerAnio(char materia[]);
int menuMateriasSegundoAnio(char materia[]);
int menuMateriasTercerAnioEnAdelante(char materia[]);
int buscarPosPorNombre(stMateria arreglo[],int validos, char materia[]);
int Comprobacion_Usuario(char nombre[]);

#endif // PROFESORES_H_INCLUDED
