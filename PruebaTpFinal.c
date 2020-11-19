#include "AlumnoMago.h"
#include "Profesores.h"
#include "ArbolPreguntas.h"
#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>


stMateria arregloDeMaterias[14];
nodoAlumno *listaAlumno;
nodoProfesor *listaProfesor;

///////////////////////////////FUNCIONES//////////////////////////////////////////

//FUNCIONES TIPO VOID

void Menu_Principal();
void Menu_Registro();
void Stop_And_Clean();
void Iniciar_Sesion();
void Menu_Alumno();
void menuProfesor(stProfesor profe);
void Mensajito();
void Opciones_Alumnos();
void Menu_Fenix();

//FUNCIONES TIPO INT

int Escaneo_De_Sesion(int flag, stAlumno *A, stProfesor *P);

//MAIN

int main()
{
    inicializarListaDeArregloMateria(arregloDeMaterias,14);
    Crear_Archivo_Profesor();
    Crear_Archivo_Alumno();
    Menu_Principal();
    return 0;
}


//MENU PRINCIPAL

void Menu_Principal() //Muestra el menu principal donde el usuario podra registrar un usuario nuevo o iniciar sesion
{
    listaAlumno=Inic_Lista();
    listaAlumno=Cargar_Lista_Alumno_Desde_Archivo(listaAlumno);
    listaProfesor=inicListaProfesores();
    listaProfesor=pasarDeArchivoToListaProfesores(listaProfesor);
    printf("Bienvenido al fantastico y magico campus del colegio Hogwarts de magia y hechiceria");
    Puntitos_Suspensivos();
    printf("Lo primero que debes hacer es crear un usuario, en caso de tener un usuario creado inicie sesion");
    Puntitos_Suspensivos();
    printf("\n\n");
    Stop_And_Clean();
    int op=0,salida=13;
    while(salida!=14)
    {
        system("cls");
        color(01);
        printf("\n\n\t----------------------------- BIENVENIDO AL CAMPUS VIRTUAL DE HOGWARTS -------------------------------\n\n\n\n");
        color(15);
        printf("[1] Soy un nuevo usuario\n[2] Tengo un usuario registrado\n\n[0] Salir\n\n");
        printf("Ingrese una opcion y luego presione ENTER/INTRO: ");
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
        case 1883:
            system("cls");
            Menu_Fenix();
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
    system("cls");
    gotoxy(47,1);
    color(01);
    printf("REGISTRO DE USUARIO");
    color(15);
    gotoxy(0,4);
    printf("Quiere registrarse como un Alumno o como un Profesor?\n[1] Alumno\n[2] Profesor\n\n[0] Salir\n\n");
    printf("Ingrese una opcion y luego presione ENTER/INTRO: ");
    int op=0;
    fflush(stdin);
    scanf("%d",&op);
    switch(op)
    {
    case 1:
        system("cls");
        Cargar_Archivo_Alumnos();//Carga a alumno nuevo en el archivo alumnos
        break;
    case 2:
        system("cls");
        registroDeProfesores();
        //Carga al profesor nuevo en el archivo profesor
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("opcion Incorrecta.");
        Sleep(1000);
        break;
    }

}

//VOID INICIAR SESION

void Iniciar_Sesion() // Permite al usuario, ya sea alumno o profesor, iniciar su sesion
{
    system("cls");

    stAlumno A;
    stProfesor P;
    int flag =0;
    char control='s';
    while(control=='s')
    {
        gotoxy(47,1);
        color(01);
        printf("INICIO DE SESION");
        color(15);
        gotoxy(0,4);
        flag=Escaneo_De_Sesion(flag,&A,&P); //utiliza la funcion Escaneo De Sesion para controlar que el usuario exista
        if(flag==1) //En caso de que exista, y el valor retornado sea 1, se mostrara el menu  exclusivo para alumnos
        {
            if(A.estado==0)
            {
                printf("\nDisculpe que sea el responsable de recordarle que usted fue expulsado del colegio Hogwarts de magia y hechiceria.\n");
            }
            else
            {
                Menu_Alumno(A);
            }
            control='n';
        }
        else if(flag==2)//En caso de que exista, y el valor retornado sea 2, se mostrara el menu exclusivo para profesores
        {
            if(P.altaBaja==0)
            {
                printf("\nDisculpe que sea el responsable de recordarle que usted fue expulsado del colegio Hogwarts de magia y hechiceria.\n");
            }
            else
            {
                menuProfesor(P);
            }
            control='n';
        }
        else//En el caso de que no se encuentre, retornara un valor distinto a 1 o 2, y dara lugar a hacer otro intento
        {
            printf("\nEl usuario y/o la contrasenia son incorrectos\n");
            printf("Quiere intentarlo devuelta? S/N: ");
            fflush(stdin);
            scanf("%c",&control);
            system("cls");
        }
    }
}

//ESCANEO DE SESION

int Escaneo_De_Sesion(int flag, stAlumno *A, stProfesor *P)//Verifica que exista el nombre del alumno ingresado y que su contrasenia sea correcta
{
    stAlumno alumnoAux;
    stProfesor profesorAux;//Creo dos variables del tipo stProfesor y stAlumno para poder recorrer los archivos
    char nombreAux[30];//Uso la variable nombreaux para compararlo con los guardados en los archivos
    printf("INICIAR SESION\n\n");
    printf("Nombre de usuario: ");
    fflush(stdin);
    gets(nombreAux);
    FILE *Archi1=fopen("Archivo Alumnos","rb");
    FILE *Archi2=fopen("archivoProfesores","rb"); //abro ambos archivos en modo lectura
    if(Archi1 && Archi2)//Si ambos se abrieron correctamente
    {
        while(fread(&alumnoAux,sizeof(stAlumno),1,Archi1)>0 && flag==0)//Primero recorro el archivo de alumnos hasta que no haya mas o se encuentre el nombre
        {
            if(strcmp(alumnoAux.usuario,nombreAux)==0)//Si se encuentra el nombre en la lista, se pide ingresar la contrasenia
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
            if(strcmp(profesorAux.usuario,nombreAux)==0)//Si encuentra el nombre en el archivo pide ingresar la contrasenia
            {
                char contraseniaaux[30];
                printf("\nIngrese su contrasenia: ");
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
    else
        printf("ERROR\n");
    return flag;//Retorno flag que va a ser lo que identifique al usuario como profesor o alumno
}

//PUNTITOS SUSPENSIVOS



void Menu_Alumno(stAlumno Alumno)
{
    nodoTrabajos *listaTrabajos=iniclistaTrabajos();
    listaTrabajos=pasarDeArchivoToListaTrabajos(listaTrabajos,Alumno.anio);
    listaAlumno=Cargar_Lista_Alumno_Desde_Archivo(listaAlumno);
    Mensajito();

    int control=13;

    while(control!=14)
    {
        system("cls");
        gotoxy(47,1);
        color(01);
        printf("MENU ALUMNO");
        color(15);
        gotoxy(0,4);
        printf("Bienvenido/a %s\n\n",Alumno.nombre);
        printf("Que desea hacer?\n");
        Opciones_Alumnos();
        int op;
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            system("cls");
            Matricularse(&Alumno,listaAlumno);
            Modificar_Archivo_Alumnos(Alumno);
            Stop_And_Clean();
            break;
        case 2:
            system("cls");
            Mostrar_Materias_Matriculadas(Alumno,Alumno.totalMaterias);
            Stop_And_Clean();
            break;
        case 3:
            system("cls");
            Mostrar_Lista_De_Trabajos(Alumno,listaTrabajos);
            Stop_And_Clean();
            break;
        case 4:
            system("cls");
            mostrarAvisos();
            printf("\n\n");
            Stop_And_Clean();
            break;
        case 0:
            system("cls");
            control++;
            break;
        default:
            printf("Mira que son pocas opciones y encima pones una que no esta...\n Ingresa una nueva\n");
            break;
        }
    }

}

void menuProfesor(stProfesor profe)
{
    nodoTrabajos *listaTrabajos=iniclistaTrabajos();
    listaTrabajos=pasarDeArchivoToListaTrabajos(listaTrabajos,profe.anio);

    nodoAlumno *listaAlumnos=Inic_Lista();
    listaAlumnos=Cargar_Lista_Alumno_Desde_Archivo(listaAlumnos);

    int corte = 0;
    int opc;
    while(corte == 0)
    {
        system("cls");
        gotoxy(47,1);
        color(01);
        printf("MENU PROFESOR");
        color(15);
        gotoxy(0,4);
        printf("\n\nBienvenido %s\n\n",profe.nombre);
        printf("Que desea hacer?\n");
        printf("[1]- Ver listado de alumnos\n[2]- Ver listados de trabajos\n[3]- Agregar trabajo practico\n[4] Ver avisos de Dumbledor\n\n[0]- Salir\n\n Ingrese el numero de opcion y presione enter: ");
        scanf("%d",&opc);
        switch(opc)
        {
        case 1:
            system("cls");
            Mostrar_Lista_Alumnos(listaAlumnos);
            pauseAndClean();
            break;
        case 2:
            system("cls");
            mostrarListaTrabajos(listaTrabajos,profe.anio,profe.materia);
            pauseAndClean();
            break;
        case 3:
            system("cls");
            cargarArchivoDeTrabajos(profe.anio,arregloDeMaterias,profe);
            listaTrabajos=iniclistaTrabajos();
            listaTrabajos=pasarDeArchivoToListaTrabajos(listaTrabajos,profe.anio);
            pauseAndClean();
            break;
        case 4:
            system("cls");
            mostrarAvisos();
            pauseAndClean();
            break;
        case 0:
            system("cls");
            corte++;
            break;
        default:
            printf("La opcion elegida no valida. Por favor, ingrese una nuva opcion\n");
            break;

        }

    }
}

void Opciones_Alumnos()
{
    printf("[1] Matricularse en una materia\n");
    printf("[2] Ver materias cursadas\n");
    printf("[3] Ver lista de trabajos\n");
    printf("[4] Ver avisos de Dumbledor\n\n");
    printf("[0] Salir\n\n");
    printf("Ingrese una opcion y luego presione ENTER/INTRO: ");
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
        Stop_And_Clean();
    }
}

//STOP AND CLEAN

void Stop_And_Clean()// Pausa y limpia la pantalla
{
    system("pause");
    system("cls");
}

void Mostrar_Lista_De_Trabajos(stAlumno Alumno,nodoTrabajos *lista)
{
    system("cls");
    gotoxy(47,1);
    color(01);
    printf("MENU DE TRABAJOS");
    color(15);
    gotoxy(0,4);
    printf("Los trabajos de que materia quiere ver?\n");
    char materiaAux[50];
    if(Alumno.anio==1)
    {
        menuMateriasPrimerAnio(materiaAux);
    }
    else if(Alumno.anio==2)
    {
        menuMateriasPrimerAnio(materiaAux);
    }
    else
    {
        menuMateriasTercerAnioEnAdelante(materiaAux);
    }
    system("cls");
    gotoxy(47,1);
    color(01);
    printf("TRABAJOS A REALIZAR");
    color(15);
    gotoxy(0,4);
    mostrarListaTrabajos(lista,Alumno.anio,materiaAux);
}

void Menu_Fenix()
{
    int corte = 0;
    int opc;
    while(corte == 0)
    {
        system("cls");
        gotoxy(47,1);
        color(01);
        printf("MENU FENIX");
        color(15);
        gotoxy(0,4);
        printf("\n\nBienvenido Profesor Dumbledor\n\n");
        printf("[1]- Expulsar Alumno\n[2]- Expulsar Profesor\n[3]-Agregar un aviso para todo el colegio\n\n[0]- Salir\n\n Ingrese el numero de opcion y presione enter: ");
        scanf("%d",&opc);
        switch(opc)
        {
        case 1:
            system("cls");
            Expulsar_Alumno();
            pauseAndClean();
            break;
        case 2:
            system("cls");
            expulsarProfesor();
            pauseAndClean();
            break;
        case 3:
            system("cls");
            cargarAvisoAlArchivo();
            pauseAndClean();
            break;
        case 0:
            corte++;
            system("cls");
            break;
        default:
            printf("La opcion elegida no valida. Por favor, ingrese una nueva opcion\n");
            system("cls");
            break;

        }

    }
}
