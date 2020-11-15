#ifndef PROFESOR_H_INCLUDED
#define PROFESOR_H_INCLUDED

//////////////////////////////////////////ESTRUCTURAS//////////////////////////////////////////

//ESTRUCTURA PROFESOR

typedef struct stProfesor
{
    char nombre[30];
    char contrasenia[30];
    char casa[30];
    int anio;
    char materia[30];
} stProfesor;

//////////////////////////////////////////FUNCIONES//////////////////////////////////////////

//FUNCIONES TIPO VOID

void Cargar_Archivo_Profesor();
void Cargar_Materia();
void Mostrar_Archivo_Profesor();

//FUNCIONES CON OTRO TIPO DE RETORNO

stProfesor Crear_Profesor();


#endif // PROFESOR_H_INCLUDED
