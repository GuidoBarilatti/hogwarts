#include "Menues.h"
#include "AlumnoMago.h"
#include "Profesor.h"
#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

//MENU PRINCIPAL

void Menu_Principal() //Muestra el menu principal donde el usuario podra registrar un usuario nuevo o iniciar sesion
{

    printf("Bienvenido al magico fantastico campus del colegio Hogwarts de magia y hechiceria");
    Puntitos_Suspensivos();
    printf("Lo primero que debes hacer es crear un usuario, en caso de tener un usuario creado inicie sesion");
    Puntitos_Suspensivos();
    int op=0,salida=13;

    while(salida!=14)
    {
        Stop_And_Clean();
        gotoxy(47,1);
        color(01);
        printf("MENU PRINCIPAL");
        color(15);
        gotoxy(0,4);
        printf("[1] Soy usurario nuevo\n[2] Tengo un usuario creado\n[0] Salir\n");
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            system("cls");
            Menu_Registro();
            break;
        case 2:
            //Inicio_Sesion();
            printf("2\n");
            break;
        case 0:
            salida++;
            break;
        default:
            printf("Loco son 2 opciones nada mas, media pila\n");
            break;
        }
    }
}

//MENU REGISTRO

void Menu_Registro() //Menu donde el usuario podra registrarse como un usuario o como un profesor
{
    gotoxy(47,1);
    color(01);
    printf("REGISTRO DE USUARIO");
    color(15);
    gotoxy(0,4);
    printf("Quiere registrarse como un Estudiante o como un Profesor?\n[1] Estudiante\n[2] Profesor\n[0] Salir\n");
    int op=0;
    fflush(stdin);
    scanf("%d",&op);
    switch(op)
    {
    case 1:
        Cargar_Archivo_Alumnos(); //Carga a alumno nuevo en el archivo alumnos
        break;
    case 2:

        Cargar_Archivo_Profesor();
        break;
    }

}

void Iniciar_Sesion()
{
    stAlumno A;
    stProfesor P;
    int flag =0;
    char control='s';
    while(control=='s')
    {
        flag=Escaneo_De_Sesion(flag,&A,&P);
    }
}

int Escaneo_De_Sesion(int flag, stAlumno *A, stProfesor *P)
{
    stAlumno alumnoAux;
    stProfesor profesorAux;
    char nombreAux[30];
    printf("INICIAR SESION\n");
    printf("Nombre: ");
    fflush(stdin);
    gets(nombreAux);
    FILE *Archi1=fopen("Archivo Alumnos","rb");
    FILE *Archi2=fopen("Archivo Profesor","rb");
    if(Archi1 && Archi2)
    {
        while(fread(&alumnoAux,sizeof(stAlumno),1,Archi1)>0 && flag==0)
        {
            if(strcmpi(alumnoAux.nombre,nombreAux)==0)
            {
                char contraseniaaux[30];
                printf("Ingrese su contrasenia: ");
                fflush(stdin);
                gets(contraseniaaux);
                if(strcmp(contraseniaaux,alumnoAux.contrasenia)==0)
                {
                    flag=1;
                    &A=alumnoAux;
                }
            }
        }
        while(fread(&profesorAux,sizeof(stProfesor),1,Archi2)>0 && flag==0)
        {
            if(strcmpi(profesorAux.nombre,nombreAux)==0)
            {
                char contraseniaaux[30];
                printf("Ingrese su contrasenia: ");
                fflush(stdin);
                gets(contraseniaaux);
                if(strcmp(contraseniaaux,profesorAux.contrasenia)==0)
                {
                    flag=2;
                    *P=profesorAux;
                }
                else
                {
                    flag=-1;
                }
            }
        }
        fclose(Archi1);
        fclose(Archi2);
    }
    return flag;
}

//PUNTITOS SUSPENSIVOS

void Puntitos_Suspensivos()// Genera un aura de misterio que mantendra al usuario espectante de cuales seran las siguientes palabras emitidas en pantalla
{
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".\n");
    Sleep(1000);
}

//STOP AND CLEAN

void Stop_And_Clean()// Pausa y limpia la pantalla
{
    system("pause");
    system("cls");
}
