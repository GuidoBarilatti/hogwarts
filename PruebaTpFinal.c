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




///////////////////////////////FUNCIONES//////////////////////////////////////////

//FUNCIONES TIPO VOID

void Menu_Principal();
void Menu_Registro();
void Puntitos_Suspensivos();
void Stop_And_Clean();
void Iniciar_Sesion();
void Menu_Alumno(stAlumno alumno);
void Mensajito();
void Opciones_Alumnos();

//FUNCIONES TIPO INT

int Escaneo_De_Sesion(int flag, stAlumno *A, stProfesor *P);

//MAIN

int main()
{

  //  Cargar_Archivo_Alumnos();
    //Cargar_Archivo_Materias();
    Menu_Principal();
    Mostrar_Archivo_Alumno();
    Mostrar_Archivo_Profesor();
    return 0;
}


//MENU PRINCIPAL

void Menu_Principal() //Muestra el menu principal donde el usuario podra registrar un usuario nuevo o iniciar sesion
{
     nodoAlumno *listaAlumno=Inic_Lista();
    listaAlumno=Cargar_Lista_Alumno_Desde_Archivo("Archivo Alumnos",listaAlumno);
   // printf("Bienvenido al magico fantastico campus del colegio Hogwarts de magia y hechiceria");
    //Puntitos_Suspensivos();
    //printf("Lo primero que debes hacer es crear un usuario, en caso de tener un usuario creado inicie sesion");
    //Puntitos_Suspensivos();
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
            system("cls");
            Iniciar_Sesion();
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
        Cargar_Archivo_Profesor(); //Carga al profesor nuevo en el archivo profesor
        break;
    }

}

//VOID INICIAR SESION

void Iniciar_Sesion() // Permite al usuario, ya sea alumno o profesor, iniciar su sesion
{
    gotoxy(47,1);
    color(01);
    printf("INICIO DE SESION");
    color(15);
    gotoxy(0,4);
    stAlumno A;
    stProfesor P;
    int flag =0;
    char control='s';
    while(control=='s')
    {
        flag=Escaneo_De_Sesion(flag,&A,&P); //utiliza la funcion Escaneo De Sesion para controlar que el usuario exista
        if(flag==1) //En caso de que exista, y el valor retornado sea 1, se mostrara el menu  exclusivo para alumnos
        {
            Menu_Alumno(A);
            control='n';
        }
        else if(flag==2)//En caso de que exista, y el valor retornado sea 2, se mostrara el menu exclusivo para profesores
        {
            printf("Hola, soy un profesore\n");
            control='n';
        }
        else//En el caso de que no se encuentre, retornara un valor distinto a 1 o 2, y dara lugar a hacer otro intento
        {
            printf("Hola, soy un espacio vacio porque no existo\n");
            printf("Quiere intentarlo devuelta?\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
}

//ESCANEO DE SESION

int Escaneo_De_Sesion(int flag, stAlumno *A, stProfesor *P)//Verifica que exista el nombre del alumno ingresado y que su contrasenia sea correcta
{
    stAlumno alumnoAux;
    stProfesor profesorAux;//Creo dos variables del tipo stProfesor y stAlumno para poder recorrer los archivos
    char nombreAux[30];//Uso la variable nombreaux para compararlo con los guardados en los archivos
    printf("INICIAR SESION\n");
    printf("Nombre: ");
    fflush(stdin);
    gets(nombreAux);
    FILE *Archi1=fopen("Archivo Alumnos","rb");
    FILE *Archi2=fopen("Archivo Profesor","rb"); //abro ambos archivos en modo lectura
    if(Archi1 && Archi2)//Si ambos se abrieron correctamente
    {
        while(fread(&alumnoAux,sizeof(stAlumno),1,Archi1)>0 && flag==0)//Primero recorro el archivo de alumnos hasta que no haya mas o se encuentre el nombre
        {
            if(strcmpi(alumnoAux.nombre,nombreAux)==0)//Si se encuentra el nombre en la lista, se pide ingresar la contrasenia
            {
                char contraseniaaux[30];
                printf("Ingrese su contrasenia: ");
                fflush(stdin);
                gets(contraseniaaux);
                if(strcmp(contraseniaaux,alumnoAux.contrasenia)==0)//Si la contrasenia es la correcta
                {
                    flag=1;//Cambio el valor de la variable flag a 1 para reconocerlo como alumno y para que corte el ciclo while actual y no ingrese al siguiente
                    *A=alumnoAux;//Modifico la variable de tipo stAlumno pasado por referencia para tener los datos de la mismo
                }
            }
        }
        while(fread(&profesorAux,sizeof(stProfesor),1,Archi2)>0 && flag==0)//Si no se encuentra el nombre en la lista de alumnos pasa a la lista de profesores
        {
            if(strcmpi(profesorAux.nombre,nombreAux)==0)//Si encuentra el nombre en el archivo pide ingresar la contrasenia
            {
                char contraseniaaux[30];
                printf("Ingrese su contrasenia: ");
                fflush(stdin);
                gets(contraseniaaux);
                if(strcmp(contraseniaaux,profesorAux.contrasenia)==0)//Si la contrasenia es la correcta
                {
                    flag=2;//Cambio la variable flag a 2 para reconocerlo como profesor y para qe corte el ciclo while actual
                    *P=profesorAux;//Modifico la variable de tipo stProfesor pasada por referencia para tener los datos de la misma
                }
                else//En caso de no encontrarlo en ninguna de las dos listas
                {
                    flag=-1;//Cambio la variable flag a -1 para que corte el ciclo while actual
                }
            }
        }
        fclose(Archi1); //Cierro ambos archivos, no me acuerdo si era necesario cuando era solo lectura pero por las dudas lo hice
        fclose(Archi2);
    }
    return flag;//Retorno flag que va a ser lo que identifique al usuario como profesor o alumno
}

//PUNTITOS SUSPENSIVOS

void Puntitos_Suspensivos()// Genera un aura de misterio que mantendra al usuario espectante de cuales seran las siguientes palabras emitidas en pantalla
{
    printf(".");//Este puntito genera intriga
    Sleep(500);
    printf(".");//Este puntito genera incertidumbre
    Sleep(500);
    printf(".\n");//Este puntito genera una duda excistencial que hara que te replantees tu vida por completo
    Sleep(500);
}

void Menu_Alumno(stAlumno alumno)
{
    Mensajito();
    system("cls");
    gotoxy(47,1);
    color(01);
    printf("MENU ALUMNO");
    color(15);
    gotoxy(0,4);
    int control=13;
    while(control!=14)
    {
        printf("Que desea hacer?\n");
        Opciones_Alumnos();
        int op;
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            alumno.totalMaterias=Matricularse_En_Materia(&alumno);
            break;
        case 2:
            Mostrar_Materias_Matriculadas(alumno,alumno.totalMaterias);
            break;
        case 0:
            control++;
            break;
        default:
            printf("Mira que son pocas opciones y encima pones una que no esta...\n Ingresa una nueva\n");
            break;
        }
    }

}

void Opciones_Alumnos()
{
    printf("[1] Matricularse en una materia\n");
    printf("[2] Ver materias cursadas\n");
    printf("[2] Ver lista de trabajos\n");
    printf("[0] Salir\n");
}

void Mensajito()
{
    printf("Esta es tu primera vez utilizando este campus?\n");
    char resp;
    fflush(stdin);
    scanf("%c",&resp);
    if(resp=='s')
    {
        printf("Ok mi joven aprendiz de magia y hechiceria, este es el campus oficial del colegio Hogwarts de magia y hechiceria.\n");
        printf("Aqui podras hacer muchas cosas. Desde ver las materias en las que esta inscripto, ver los trabajos que debe hacer y muchas mas cosas\n");
        Stop_And_Clean();
    }
    else
    {
        printf("Como ya tienes experiencia te dejare solo");
        Puntitos_Suspensivos();
        printf("Solo por ahora\n");
    }
}

//STOP AND CLEAN

void Stop_And_Clean()// Pausa y limpia la pantalla
{
    system("pause");
    system("cls");
}
