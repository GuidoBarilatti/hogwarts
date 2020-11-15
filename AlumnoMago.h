#ifndef ALUMNOMAGO_H_INCLUDED
#define ALUMNOMAGO_H_INCLUDED


//////////////////////////////////////////ESTRUCTURAS//////////////////////////////////////////

//ESTRUCTURA NODO TRABAJOS

typedef struct nodoTrabajos
{
    char consigna[300];
    struct nodoTrabajos *sig;
} nodoTrabajos;

//ESTRUCTURA MATERIA

typedef struct stMateria
{
    char nombre[30];
    int anio;
    int id;
    nodoTrabajos *listaTrabajos;
} stMateria;

// ESTRUCTURA ALUMNO

typedef struct stAlumno

{
    char nombre[30];
    char contrasenia[30];
    char casa[30];
    char genero; // m o f
    int anio;
    stMateria materias[16];
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
void Mostrar_Lista(nodoAlumno *lista);
void Cargar_Contrasenia(char contrasenia[]);
void Lista_Materias(stAlumno *alumno);
void Cargar_Archivo_Materias();
void Mostrar_Materias_Matriculadas(stAlumno alumno,int materiasValidas);
void musicadefondo();
void *reproducirmusica();

//FUNCIONES INT

int Verificar_Cadena(char Cadena[]);
int Cargar_Anio();
int Matricularse_En_Materia(stAlumno *alumno);
int Comprobar_Matriculacion(stAlumno *alumno, char nombreMateria[]);

//FUNCIONES CHAR

char Cargar_Genero();

//FUNCIONES CON OTRO TIPO DE RETORNO

stAlumno Crear_Alumno();
nodoAlumno *Inic_Lista();
nodoAlumno *Crear_Nodo_Alumno(stAlumno alumn);
nodoAlumno *Cargar_Lista_Alumno_Desde_Archivo(char nombreArchivo[],nodoAlumno *lista);
nodoAlumno *Agregar_Al_Ppio(nodoAlumno *lista,nodoAlumno *nuevoNodo);
stMateria Buscar_Materia_Por_Id(int numero);

#endif // ALUMNOMAGO_H_INCLUDED
