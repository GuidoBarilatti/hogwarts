#include "AlumnoMago.h"
#include "Profesor.h"
#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <conio.h>

stProfesor Crear_Profesor()
{
    stProfesor aux;
    Cargar_Nombre(aux.nombre);
    Cargar_Casa(aux.casa);
    Cargar_Materia(aux.materia);
    aux.anio=Cargar_Anio();
    Cargar_Contrasenia(aux.contrasenia);
    return aux;
}

//CARGAR MATERIA

void Cargar_Materia(char materia[])
{
    printf("De que materia imparte clases este profesor?\n");
    fflush(stdin);
    gets(materia);
}

void Cargar_Archivo_Profesor()
{
    FILE *Archi=fopen("Archivo Profesor","ab");
    stProfesor aux;
    if(Archi!=NULL)
    {
        printf("Cargue sus datos personales\n\n");
        aux=Crear_Profesor();
        fwrite(&aux,sizeof(stProfesor),1,Archi);
        fclose(Archi);
    }
    else
    {
        printf("Hubo un inconveniente para crear su archivo\n");
    }
}

//MOSTRAR PROFESOR

void Mostra_Profesor(stProfesor aux)
{
    printf("--------------------------\n");
    printf("Nombre: ");
    puts(aux.nombre);
    printf("Casa: ");
    puts(aux.casa);
    printf("Materia: ");
    puts(aux.materia);
    printf("Anio en el que da clases: %d",aux.anio);
}

void Mostrar_Archivo_Profesor()
{
        FILE *Archi=fopen("Archivo Profesor","rb");
        stProfesor aux;
        if(Archi)
        {
            while(fread(&aux,sizeof(stProfesor),1,Archi)>0)
            {
                Mostra_Profesor(aux);
            }
            fclose(Archi);
        }

}
