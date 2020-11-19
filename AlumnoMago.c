#include "AlumnoMago.h"
#include "ArbolPreguntas.h"
#include "Profesores.h"
#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <pthread.h>
#include <windows.h>
#include <windowsx.h>

//CREAR ALUMNO

stAlumno Crear_Alumno() //Crea una estructura alumno que es
{
    pthread_attr_t atributo;
    pthread_t hilo;
    pthread_attr_init(&atributo);
    pthread_attr_setdetachstate(&atributo,PTHREAD_CREATE_DETACHED);
    pthread_create(&hilo,&atributo,reproducirmusica,NULL); //Creacion de un hilo que reproducirala el Tema principal de Harry Potter mientras dure
    pthread_detach(hilo);                                  //La creacion del alumno
    arbolDePreguntas *Arbol=inicArbol(); //Se crea e inicializa un arbol de preguntas
    Arbol=pasarDeArchivoToArbol(Arbol); //Se le cargan datos
    stAlumno aux; // Se crea un alumno auxiliar
    Cargar_Nombre(aux.nombre); //Asigna el nombre al alumno
    printf("Ingrese su nombre de usuario. El mismo no podra tener mas de 30 caracteres y distingue entre minuscula y mayusculas\n");
    fflush(stdin);
    gets(aux.usuario);//Asigna un nombre de usuario al alumno
    int control=Comprobacion_Usuario(aux.usuario); //Controla en los archivos de profesores y alumnos si el usuario ya esta en uso
    while(control==1) //Si devuelve 1 el usuario ya esta en uso y pedira que ingrese uno nuevo hasta que ingrese uno valido
    {
        printf("El nombre de usuario que quiere ingresar ya se encuentra en uso. Por favor ingrese uno nuevo\n");
        fflush(stdin);
        gets(aux.usuario);
        control=Comprobacion_Usuario(aux.usuario);
    }
    aux.genero=Cargar_Genero(); //Carga el genero
    aux.anio=Cargar_Anio(); //Carga el anio
    Cargar_Contrasenia(aux.contrasenia); //Carga la contrasenia
    printf("Usted ya posee una casa asignada?\n");
    char respuesta;
    fflush(stdin);
    scanf("%c",&respuesta);
    if(respuesta=='s') //Si el alumno tiene casa, podra elegir su casa
    {
        Cargar_Casa(aux.casa);
    }
    else //Si no tiene casa el sombrero seleccionador se encargara de asignarle una
    {
        int casaAsignada=sombreroSeleccionador(Arbol);
        lectorDeResultado(casaAsignada,aux.casa);
    }
    aux.estado=1; //Siempre que se crea un alumno se inicializa su estado en 1 mostrando que es un alumno activo
    aux.totalMaterias=0; //El total de materias es 0 porque todavia no se matriculo a ninguna
    pauseAndClean();
    PlaySound(NULL,NULL,SND_ASYNC);//Corta la reproduccion del nombre
    return aux;
}

//CARGAR NOMBRE

void Cargar_Nombre(char nombre[]) //Carga el nombre del alumno
{
    printf("Ingrese su nombre\n");
    fflush(stdin);
    gets(nombre);
    int control=Verificar_Cadena(nombre); //Verifica que la cadena solo este compuesta por letras o espacios en blanco
    while(control!=1)
    {
        printf("Los nombres solo pueden estar compuestos por letras, no se, fijate\n");
        fflush(stdin);
        gets(nombre);
        control=Verificar_Cadena(nombre);
    }

}

//VERIFICAR NOMBRE

int Verificar_Cadena(char Cadena[]) //Verifica si una cadena este compuesta solo por letras o espacios en blanco
{
    int flag=1,pos=0;
    int cantLetras=strlen(Cadena); //Cuenta la cantidad de letras de la cadena
    while((isalpha(Cadena[pos])!=0 || isspace(Cadena[pos])!=0 )&& pos<cantLetras) //Recorre el nombre verificandolo
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

char Cargar_Genero() //Carga el genero del alumno
{
    char genero;
    printf("Ingrese su genero M/F: \n");
    fflush(stdin);
    scanf("%c",&genero);

    while( genero!='m' && genero!='f')  //Si el genero del alumno es distinto a f o m pide ingresar uno nuevo
    {
        printf("En este colegio no nos deconstruimos, no hay nada de magues o brujes.Solo magos o brujas. Tal vez en Beauxbatons opten por esta politica\n");
        printf("Ingrese otra vez su genere: \n");
        fflush(stdin);
        scanf("%c",&genero);
    }
    return genero;
}

//CARGAR CASA

void Cargar_Casa(char casa[]) //Carga una casa al alumno
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

}

//CARGAR CONTRASENIA

void Cargar_Contrasenia(char contrasenia[]) //Carga una contrasenia
{
    char aux[30];
    printf("Ingrese su contrasenia. Se distingue entre minusculas y mayusculas (maximo 16 caracteres)\n");
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

int Cargar_Anio() //Carga el anio del alumno
{
    int control=1,anio=0;
    while(control==1)
    {
        printf("Ingrese el anio en el que esta\n");
        fflush(stdin);
        scanf("%d",&anio);
        if(anio<1 || anio>7) //Solo permite cargar anios entre 1 y 7
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

void Mostrar_Alumno(stAlumno aux) //Muestra al alumno
{
    printf("--------------------------\n");
    printf("Nombre: ");
    puts(aux.nombre);
    printf("Nombre de usuario: ");
    puts(aux.usuario);
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
        printf("Estado del alumno: Activo\n");
    }
    else
    {
        printf("Estado del alumno: Inactivo\n");

    }
    printf("Cantidad de materias cursadas: %d\n",aux.totalMaterias);
}


//CARGAR ARCHIVO ALUMNOS

void Cargar_Archivo_Alumnos() //Carga un archivo donde estaran todos los alumnos
{
    nodoAlumno *listaAlumno=Inic_Lista();
    FILE *Archi=fopen("Archivo Alumnos","ab");
    if(Archi!=NULL)
    {
        stAlumno aux;
        printf("Por favor, le pedimos que a continuacion ingrese una serie de datos personales\n\n");
        aux=Crear_Alumno();
        nodoAlumno *nuevoNodo;
        nuevoNodo=Crear_Nodo_Alumno(aux);
        listaAlumno=Agregar_Al_Ppio(listaAlumno,nuevoNodo);
        fwrite(&aux,sizeof(stAlumno),1,Archi);
        fclose(Archi);
    }
    else
    {
        printf("Hubo un inconveniente para crear su archivo\n");
    }
}

//MOSTRAR ARCHIVO ALUMNOS

void Mostrar_Archivo_Alumno() //Muestra el archivo alumnos
{
    FILE *Archi=fopen("Archivo Alumnos","rb");
    if(Archi)
    {
        stAlumno aux;

        while(fread(&aux,sizeof(stAlumno),1,Archi)>0)
        {
            if(aux.estado==1) //Solo muestra a los alumnos activos
            {
                Mostrar_Alumno(aux);
            }
        }
        fclose(Archi);
    }
}

//INIC LISTA

nodoAlumno *Inic_Lista() //Inicializa una lista
{
    return NULL;
}

//CREAR NODO ALUMNO

nodoAlumno *Crear_Nodo_Alumno(stAlumno alumno) //Crea un nodo alumno
{
    nodoAlumno *nuevoNodo=(nodoAlumno*)malloc(sizeof(nodoAlumno));
    nuevoNodo->alumno=alumno;
    nuevoNodo->sig=NULL;
    return nuevoNodo;
}

//AGREGAR AL PPIO

nodoAlumno *Agregar_Al_Ppio(nodoAlumno *lista,nodoAlumno *nuevoNodo)//Grega un nuevo nodo al principio de la lista
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

nodoAlumno *Cargar_Lista_Alumno_Desde_Archivo(nodoAlumno *lista)// Carga una lista de alumnos desde el "Archivo Alumnos"
{
    FILE *Archi=fopen("Archivo Alumnos","r+b");
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

void Mostrar_Lista_Alumnos(nodoAlumno *lista)// Muestra una lista de alumnos
{
    nodoAlumno *seg=lista;
    if(seg)
    {
        Mostrar_Lista_Alumnos(lista->sig);
        if(lista->alumno.estado==1)
        {
            Mostrar_Alumno(lista->alumno);
        }
    }
}

void Matricularse(stAlumno *Alumno, nodoAlumno *lista)  // Funcion para que los alumnos puedan matricularse a materias
{
    int i;
    char materiaAux[50];
    if(Alumno->anio==1)
    {
        menuMateriasPrimerAnio(materiaAux);
    }
    else if(Alumno->anio==2)
    {
        menuMateriasPrimerAnio(materiaAux);
    }
    else
    {
        menuMateriasTercerAnioEnAdelante(materiaAux);
    }
    int control=Comprobar_Matriculacion(Alumno,materiaAux);
    if(control==0)
    {
        printf("El alumno ya se encuentra matriculado a esta materia\n");
    }
    else
    {
        i=Alumno->totalMaterias;
        Modificar_Alumno_Lista(lista,Alumno->usuario,materiaAux,i);
        strcpy(Alumno->materias[i].nombre,materiaAux);
        i++;
        Alumno->totalMaterias=i;
        printf("El alumno ha sido matriculado exitosamente\n");
    }
}


void Modificar_Alumno_Lista(nodoAlumno *listaAlumno, char nombreUsuario[],char materia[],int pos) // Funcion que toma un nodo de la lista y lo modifica para agregarle materias
{
    if(listaAlumno)
    {
        if(strcmp(listaAlumno->alumno.usuario,nombreUsuario)==0)
        {
            strcpy(listaAlumno->alumno.materias[pos].nombre,materia);
            listaAlumno->alumno.totalMaterias++;
        }
        else
        {
            nodoAlumno *seg=listaAlumno;
            while(seg!=NULL && strcmp(seg->alumno.usuario,nombreUsuario)!=0 )
            {
                seg=seg->sig;
            }
            strcpy(seg->alumno.materias[pos].nombre,materia);
            seg->alumno.totalMaterias++;
        }
    }
}


void Cargar_Archivo_Materias()//CARGAR ARCHIVO MATERIAS
{
    stMateria materia;
    FILE *Archi=fopen("Lista de materias","ab");
    if(Archi)
    {
        int i=1;
        while(i<=14)
        {
            printf("Ingrese en nombre de la materia");
            fflush(stdin);
            gets(materia.nombre);
            fwrite(&materia,sizeof(stMateria),1,Archi);
            i++;
        }
        fclose(Archi);
    }
}


//MOSTRAR MATERIAS MATRICULADAS
void Mostrar_Materias_Matriculadas(stAlumno alumno,int materiasValidas)// Muestra solamente las materias al que el alumno se matriculo
{
     gotoxy(47,1);
        color(01);
        printf("Lista de Materias");
        color(15);
        gotoxy(0,4);
    int i=0;
    for(i=0; i<materiasValidas; i++)
    {
        puts(alumno.materias[i].nombre);
    }
}

//COMPROBAR MATRICULACION

int Comprobar_Matriculacion(stAlumno *alumno, char nombreMateria[])// Comprueba si un alumno ya esta matriculado en una materia para que no lo haga dos veces
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

int Buscar_Alumno_En_Archivo(char usuraio[]) // Busca un alumno dentro del archivo "Archivo Alumnos"
{
    FILE *Archi=fopen("Archivo Alumnos","rb");
    stAlumno aux;
    int i=0;
    if(Archi)
    {
        while(fread(&aux,sizeof(stAlumno),1,Archi)>0 && strcmp(aux.usuario,usuraio)!=0)
        {
            i++;
        }
        fclose(Archi);
    }
    return i;
}


void musicadefondo() // Funcion para la musica de fondo utilizando hilos
{
    pthread_t th1;
    pthread_create(&th1, NULL, reproducirmusica, NULL);
    pthread_join(th1,NULL);
}

void *reproducirmusica() // Funchion que va a dentro del hilo para reproducir la musica
{
    PlaySound("[ONTIVA.COM] Harry Potter Theme Song-320k.wav",NULL,SND_ASYNC);
    return 0;
}

void Crear_Archivo_Alumno()// Funcion que crea el archivo "Archivo Alumnos"
{
    FILE *Archi=fopen("Archivo Alumnos","rb");
    if(Archi==NULL)
    {
        Archi=fopen("Archivo Alumnos","ab");
    }
}


void Modificar_Archivo_Alumnos(stAlumno alumno) // Funcion para modificar un registro dentro de "Archivo Alumnos"
{
    FILE *Archi=fopen("Archivo Alumnos","r+b");
    if(Archi)
    {
        int pos=Buscar_Alumno_En_Archivo(alumno.usuario); //Busca la posicion del alumno
        fseek(Archi,pos*sizeof(stAlumno),SEEK_SET); //Voy hasta la posicion del alumno
        fwrite(&alumno,sizeof(stAlumno),1,Archi); //Lo sobreescribo
        fclose(Archi);
    }
}

void Expulsar_Alumno() //Cambia el estado de un alumno a 0
{
    stAlumno alumno;
    char usuarioExpulsado[20];
    Mostrar_Archivo_Alumno();
    FILE *Archi=fopen("Archivo Alumnos","r+b");
    if(Archi != NULL)
    {
        printf("Ingrese el nombre de usuario del alumno que merezca la expulsion: ");
        fflush(stdin);
        gets(usuarioExpulsado);
        int pos = Buscar_Alumno_En_Archivo(usuarioExpulsado);
        fseek(Archi,pos*sizeof(stAlumno),SEEK_SET);
        fread(&alumno,sizeof(stAlumno),1,Archi);
        alumno.estado = 0;
        fseek(Archi,pos*sizeof(stAlumno),SEEK_SET);
        fwrite(&alumno,sizeof(stAlumno),1,Archi);
        fclose(Archi);
    }
}
