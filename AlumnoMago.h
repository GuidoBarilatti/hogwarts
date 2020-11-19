#ifndef ALUMNOMAGO_H_INCLUDED
#define ALUMNOMAGO_H_INCLUDED
#include "Profesores.h"

//////////////////////////////////////////ESTRUCTURAS//////////////////////////////////////////

//ESTRUCTURA NODO TRABAJOS


//ESTRUCTURA MATERIA


// ESTRUCTURA ALUMNO

typedef struct stAlumno

{
    char nombre[30];
    char usuario[30];
    char contrasenia[16];
    char casa[30];
    char genero; // m o f
    int anio;
    stMateria materias[14];
    int totalMaterias;
    int estado;
} stAlumno;

//ESTRUCTURA NODO ALUMNO
typedef struct nodoAlumno
{
    stAlumno alumno; // Estructura alumno
    struct nodoAlumno *sig;
} nodoAlumno;


//////////////////////////////////////////FUNCIONES//////////////////////////////////////////

//FUNCIONES VOID

void Cargar_Nombre(char nombre[]);
void Cargar_Casa(char casa[]);
void Mostrar_Alumno(stAlumno aux);
void Cargar_Archivo_Alumnos();
void Mostrar_Archivo_Alumno();
void Mostrar_Lista_Alumnos(nodoAlumno *lista);
void Cargar_Contrasenia(char contrasenia[]);
void Lista_Materias(stAlumno *alumno);
void Cargar_Archivo_Materias();
void Mostrar_Materias_Matriculadas(stAlumno alumno,int materiasValidas);
void musicadefondo();
void *reproducirmusica();
void Crear_Archivo_Alumno();
void Pasar_lista_To_Archivo(nodoAlumno * lista);
void Modificar_Alumno_Lista(nodoAlumno *listaAlumno, char nombreUsuario[],char materia[],int pos);
void Mostrar_Lista_De_Trabajos(stAlumno Alumno,nodoTrabajos *lista);
void Expulsar_Alumno();
void Matricularse(stAlumno *Alumno, nodoAlumno *lista);
void Modificar_Archivo_Alumnos(stAlumno alumno);

//FUNCIONES INT

int Verificar_Cadena(char Cadena[]);
int Cargar_Anio();
int Comprobar_Matriculacion(stAlumno *alumno, char nombreMateria[]);
int Buscar_Alumno_En_Archivo(char usuario[]);


//FUNCIONES CHAR

char Cargar_Genero();

//FUNCIONES CON OTRO TIPO DE RETORNO

stAlumno Crear_Alumno();
nodoAlumno *Inic_Lista();
nodoAlumno *Crear_Nodo_Alumno(stAlumno alumn);
nodoAlumno *Cargar_Lista_Alumno_Desde_Archivo(nodoAlumno *lista);
nodoAlumno *Agregar_Al_Ppio(nodoAlumno *lista,nodoAlumno *nuevoNodo);
stMateria Buscar_Materia_Por_Id(int numero);


#endif // ALUMNOMAGO_H_INCLUDED
