#include "AlumnoMago.h"
#include "ArbolPreguntas.h"
#include "Profesor.h"
#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include "pila.h"
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <pthread.h>
#include <windows.h>
#include <windowsx.h>

//CREAR ALUMNO

stAlumno Crear_Alumno()
{
    pthread_attr_t atributo;
    pthread_t hilo;
    pthread_attr_init(&atributo);
    pthread_attr_setdetachstate(&atributo,PTHREAD_CREATE_DETACHED);
    pthread_create(&hilo,&atributo,reproducirmusica,NULL);
    pthread_detach(hilo);
    arbolDePreguntas *Arbol=inicArbol();
    Arbol=pasarDeArchivoToArbol(Arbol);
    stAlumno aux;
    Cargar_Nombre(aux.nombre);
    aux.genero=Cargar_Genero();
    aux.anio=Cargar_Anio();
    Cargar_Contrasenia(aux.contrasenia);
    printf("Usted ya posee una casa asignada?\n");
    char respuesta;
    fflush(stdin);
    scanf("%c",&respuesta);
    if(respuesta=='s')
    {
        Cargar_Casa(aux.casa);
    }
    else
    {
        int casaAsignada=sombreroSeleccionador(Arbol);
        lectorDeResultado(casaAsignada,aux.casa);
    }
    aux.estado=1;
    aux.totalMaterias=0;
    PlaySound(NULL,NULL,SND_ASYNC);
    return aux;
}

//CARGAR NOMBRE

void Cargar_Nombre(char nombre[])
{
    printf("Ingrese su nombre\n");
    fflush(stdin);
    gets(nombre);
    int control=Verificar_Cadena(nombre);
    while(control!=1)
    {
        printf("Los nombres solo pueden estar compuestos por letras, no se, fijate\n");
        fflush(stdin);
        gets(nombre);
        control=Verificar_Cadena(nombre);
    }

}

//VERIFICAR NOMBRE

int Verificar_Cadena(char Cadena[])
{
    int flag=1,pos=0;
    int cantLetras=strlen(Cadena);
    while((isalpha(Cadena[pos])!=0 || isspace(Cadena[pos])!=0 )&& pos<cantLetras)
    {
        pos++;
    }
    if(pos!=cantLetras)
    {
        flag=0;
    }

    return flag;
}

//CARGAR GENERO

char Cargar_Genero()
{
    char genero;
    printf("Ingrese su genero\n");
    fflush(stdin);
    scanf("%c",&genero);
    while(genero!='m' && genero!='f')
    {
        printf("En este colegio no nos deconstruimos, no hay nada de magues o brujes.Solo magos o brujas. Tal vez en Beauxbatons opten por esta politica\n");
        printf("Ingrese otra vez su genere\n");
        fflush(stdin);
        scanf("%c",&genero);
    }
    return genero;
}

//CARGAR CASA

void Cargar_Casa(char casa[])
{
    char casa1[]="Gryffindor";
    char casa2[]="Slytherin";
    char casa3[]="Hufflepuff";
    char casa4[]="Ravenclaw";
    int control=1;
    printf("A que casa pertenece?\n");
    while(control==1)
    {
        printf("[1] Gryffindor\n[2] Slytherin\n[3] Hufflepuff\n[4] Ravenclaw\n");
        int op;
        fflush(stdin);
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            strcpy(casa,casa1);
            printf("Un valiente Gryffindor se ha unido a nuestro campus\n");
            control--;
            break;
        case 2:
            strcpy(casa,casa2);
            printf("Mmm asi que eres un Slytherin... Que tu ambision no se convierta en una desventaja\n");
            control--;
            break;

        case 3:
            strcpy(casa,casa3);
            printf("Espero que se mantenga leal al colegio en todo momento\n");
            control--;
            break;
        case 4:
            strcpy(casa,casa4);
            printf("inteligente y sagaz como su pad... Rowena lo fue\n");
            control--;
            break;
        default:
            printf("En este colegio tenemos 4 casas nada mas. Si no te convencen podrias probar en el Instituto Durmstrang\n");
            printf("Ingrese una nueva casa\n");
            break;
        }
    }
    system("pause");
}

//CARGAR CONTRASENIA

void Cargar_Contrasenia(char contrasenia[])
{
    char aux[30];
    printf("Ingrese su contrasenia. Se distingue entre minusculas y mayusculas\n");
    fflush(stdin);
    gets(aux);
    int control=0;
    while (control==0)
    {
        char confirmacion[30];
        printf("Confirme su contrasenia\n");
        fflush(stdin);
        gets(confirmacion);
        if(strcmp(aux,confirmacion)==0)
        {
            strcpy(contrasenia,aux);
            control++;
        }
        else
        {
            printf("La contrasenia no coincide, por favor, ingresela nuevamente\n");
        }
    }
}


//CARGAR ANIO

int Cargar_Anio()
{
    int control=1,anio=0;
    while(control==1)
    {
        printf("Ingrese el anio en el que esta\n");
        fflush(stdin);
        scanf("%d",&anio);
        if(anio<1 || anio>7)
        {
            printf("Hogwarts solamente tiene cursos que van de primero a septimo. No se a que clase de colegio iras tu\n");
        }
        else
        {
            control--;
        }
    }
    return anio;
}


//MOSTRAR ALUMNO

void Mostrar_Alumno(stAlumno aux)
{
    printf("--------------------------\n");
    printf("Nombre: ");
    puts(aux.nombre);
    if(aux.genero=='f')
    {
        printf("Genero: Femenino\n");
    }
    else
    {
        printf("Genero: Masculino\n");
    }
    printf("Casa: ");
    puts(aux.casa);
    printf("Anio: %d\n",aux.anio);
    if(aux.estado==1)
    {
        printf("Estado del alumno: Activo");
    }
    else
    {
        printf("Estado del alumno: Inactivo");

    }
}


//CARGAR ARCHIVO ALUMNOS

void Cargar_Archivo_Alumnos()
{
    nodoAlumno *listaAlumno=Inic_Lista();
    FILE *Archi=fopen("Archivo Alumnos","ab");
    if(Archi!=NULL)
    {
        stAlumno aux;
        printf("Cargue sus datos personales\n\n");
        aux=Crear_Alumno();
        nodoAlumno *nuevoNodo;
        nuevoNodo=Crear_Nodo_Alumno(aux);
        listaAlumno=Agregar_Al_Ppio(listaAlumno,nuevoNodo);
        fwrite(&aux,sizeof(stAlumno),1,Archi);
        fclose(Archi);
        //Mostrar_Lista(listaAlumno);
    }
    else
    {
        printf("Hubo un inconveniente para crear su archivo\n");
    }
}

//MOSTRAR ARCHIVO ALUMNOS

void Mostrar_Archivo_Alumno()
{
    FILE *Archi=fopen("Archivo Alumnos","rb");
    if(Archi)
    {
        stAlumno aux;

        while(fread(&aux,sizeof(stAlumno),1,Archi)>0)
        {
            Mostrar_Alumno(aux);
        }
        fclose(Archi);
    }
}

//INIC LISTA

nodoAlumno *Inic_Lista()
{
    return NULL;
}

//CREAR NODO ALUMNO

nodoAlumno *Crear_Nodo_Alumno(stAlumno alumno)
{
    nodoAlumno *nuevoNodo=(nodoAlumno*)malloc(sizeof(nodoAlumno));
    nuevoNodo->alumno=alumno;
    nuevoNodo->sig=NULL;
    return nuevoNodo;
}

//AGREGAR AL PPIO

nodoAlumno *Agregar_Al_Ppio(nodoAlumno *lista,nodoAlumno *nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->sig=lista;
        lista=nuevoNodo;
    }
    return lista;
}

//CARGAR LISTA DESDE ARCHIVO

nodoAlumno *Cargar_Lista_Alumno_Desde_Archivo(char nombreArchivo[],nodoAlumno *lista)
{
    FILE *Archi=fopen(nombreArchivo,"r+b");
    stAlumno aux;
    if(Archi)
    {
        rewind(Archi);
        while(fread(&aux,sizeof(stAlumno),1,Archi)>0)
        {
            nodoAlumno *nuevoNodo=Crear_Nodo_Alumno(aux);
            lista=Agregar_Al_Ppio(lista,nuevoNodo);
        }
        fclose(Archi);
    }
    return lista;
}

//MOSTRAR LISTA

void Mostrar_Lista(nodoAlumno *lista)
{
    nodoAlumno *seg=lista;
    if(seg)
    {
        Mostrar_Lista(lista->sig);
        Mostrar_Alumno(lista->alumno);
    }
}

//MATRICULARSE EN MATERIA
int Matricularse_En_Materia(stAlumno *alumno)
{
    int i=alumno->totalMaterias;
    Lista_Materias(alumno);
    int salida=13;
    while(salida!=14)
    {
        printf("Seleccione una de las materias\n");
        int op=0;
        scanf("%d",&op);

        if(op<=0 || op>14)
        {
            printf("Elija una opcion valida\n");
        }
        else
        {
            stMateria aux=Buscar_Materia_Por_Id(op);
            if(Comprobar_Matriculacion(alumno,aux.nombre)!=0)
            {
                strcpy(alumno->materias[i].nombre,aux.nombre);
                alumno->materias[i].anio=aux.anio;
                i++;
            }
            else
            {
                printf("El alumno ya se encuentra matriculado a la materia\n");
            }
            salida++;
        }
        break;
    }




    return i;
}

//LISTA MATERIAS

void Lista_Materias(stAlumno *alumno)
{
    printf("Estas son las materias a las que se puede matricular:\n");
    if(alumno->anio==1)
    {
        printf("[1] Astronomia\n");
        printf("[2] Encantamientos\n");
        printf("[3] Defensa contra las artes oscuras\n");
        printf("[4] Vuelo\n");
        printf("[5] Herbologia\n");
        printf("[6] Historia de la magia\n");
        printf("[7] Pociones\n");
        printf("[8] Transformaciones\n");
    }
    else if(alumno->anio>1 && alumno->anio<3)
    {
        printf("[1] Astronomia\n");
        printf("[2] Encantamientos\n");
        printf("[3] Defensa contra las artes oscuras\n");
        printf("[4] Herbologia\n");
        printf("[5] Historia de la magia\n");
        printf("[6] Pociones\n");
        printf("[7] Transformaciones\n");
    }
    else
    {
        printf("[1] Astronomia\n");
        printf("[2] Encantamientos\n");
        printf("[3] Defensa contra las artes oscuras\n");
        printf("[4] Herbologia\n");
        printf("[5] Historia de la magia\n");
        printf("[6] Pociones\n");
        printf("[7] Transformaciones\n");
        printf("[8] Estudio de runas antiguas\n");
        printf("[9] Artimancia\n");
        printf("[10] Estudios muggles\n");
        printf("[11] Cuidado de criaturas magicas\n");
        printf("[12] Adivinacion\n");
        printf("[13] Alquimia\n");
    }
}

//CARGAR ARCHIVO MATERIAS
void Cargar_Archivo_Materias()
{
    stMateria materia;
    FILE *Archi=fopen("Lista de materias","wb");
    if(Archi)
    {
        int i=1;
        while(i<=14)
        {
            printf("Ingrese en nombre de la materia");
            fflush(stdin);
            gets(materia.nombre);
            materia.id=i;
            fwrite(&materia,sizeof(stMateria),1,Archi);
            i++;
        }
        fclose(Archi);
    }
}

//BUSCAR MATERIA POR ID

stMateria Buscar_Materia_Por_Id(int numero)
{
    FILE *Archi=fopen("Lista de materias","rb");
    stMateria aux;
    if(Archi)
    {
        fseek(Archi,(numero-1 )*sizeof(stMateria),SEEK_SET);
        fread(&aux,sizeof(stMateria),1,Archi);
    }
    puts(aux.nombre);
    return aux;
}

//MOSTRAR MATERIAS MATRICULADAS
void Mostrar_Materias_Matriculadas(stAlumno alumno,int materiasValidas)
{
    int i=0;
    for(i=0; i<materiasValidas; i++)
    {
        puts(alumno.materias[i].nombre);
    }
}

//COMPROBAR MATRICULACION

int Comprobar_Matriculacion(stAlumno *alumno, char nombreMateria[])
{
    int i=0,flag=0;
    while(i<14 && strcmp(alumno->materias[i].nombre,nombreMateria)!=0)
    {
        i++;
    }
    if(i==14)
    {
        flag=1;
    }
    return flag;
}

void musicadefondo()
{
    pthread_t th1;
    pthread_create(&th1, NULL, reproducirmusica, NULL);
    pthread_join(th1,NULL);
}

void *reproducirmusica()
{
    PlaySound("[ONTIVA.COM] Harry Potter Theme Song-320k.wav",NULL,SND_ASYNC);
    return 0;
}

