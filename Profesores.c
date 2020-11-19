#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "Profesores.h"
#include "gotoxy.h"


void pauseAndClean() //Pausa y limpia la pantalla
{
    system("pause");
    system("cls");
}

void CargarContraseniaProfesor(char contrseniaProfe[]) //Carga la contrasenia del profesor
{
    char contrasenia[16];
    printf("\nIngrese una contrasenia, se distingue entre mayuscula y minuscula(maximo 16 caracteres): \n");
    fflush(stdin);
    gets(contrasenia);
    int flag = 0;
    while(flag == 0)
    {
        char confirm[16];
        printf("\nIngrese de nuevo su contrasenia para confirmar: \n");
        fflush(stdin);
        gets(confirm);
        if(strcmp(contrasenia,confirm)== 0)
        {
            Sleep(500);
            printf("\nContrasenia ingresada correctamente\n");
            strcpy(contrseniaProfe,confirm);
            flag++;
        }
        else
        {
            printf("\nConfirmacion de contrasenia incorrecta. Recuerde que se difencian minusculas de mayusculas\n\n");
            pauseAndClean();
            flag = 0;
        }
    }
}

int eleccionDeAnio() //Permite al profesor elegir un anio para dar clases
{
    int flag = 0;
    int anio;
    while(flag == 0)
    {
        printf("\nEn que anio le gustaria dar clases (1 al 7): \n");
        scanf("%d",&anio);
        if(anio >= 1 && anio <= 7)
        {
            Sleep(500);
            printf("\nAnio ingresado correctamente\n");
            flag++;
        }
        else
        {
            printf("\nEl anio ingresado no existe. Vuelva a intentarlo.\n\n");
            pauseAndClean();
            flag = 0;
        }
    }
    return anio;
}

int comprobacionMateriaOcupada(char materia[],int anio) //Comprueba si la materia donde se quiere inscribir el profesor ya esta ocupada
{
    int flag = 0;
    int corte = 0;
    stProfesor profe;
    FILE * archi = fopen("archivoProfesores","rb");
    if(archi != NULL)
    {
        while(fread(&profe,sizeof(stProfesor),1,archi) > 0 && corte == 0)
        {
            if(strcmp(profe.materia,materia)== 0 && profe.anio == anio)
            {
                flag = 1;
                corte++;
            }
            else
            {
                flag = 0;
            }
        }
    }
    return flag;
}

void eleccionDeMateria(char materia[], int *anio) // El profesor puede elegir en que materia dar clases
{
    if(*anio == 1)
    {
        menuMateriasPrimerAnio(materia);
    }
    else if(*anio == 2)
    {
        menuMateriasSegundoAnio(materia);
    }
    else
    {
        menuMateriasTercerAnioEnAdelante(materia);
    }
    char confirmacion;
    printf("Esta seguro de su eleccion? s/n: ");
    fflush(stdin);
    scanf("%c",&confirmacion);
    int flag = comprobacionMateriaOcupada(materia,*anio);
    if(confirmacion == 's' && flag == 0)
    {
        Sleep(500);
        printf("\nMateria ingresada correctamente\n");
    }
    else if(flag == 1)
    {
        printf("\nLa materia que ha elegido ya tiene un profesor. Intente elegir otro anio u otra materia:\n");
        *anio = eleccionDeAnio();
        eleccionDeMateria(materia,anio);
    }
    else
    {
        eleccionDeMateria(materia,anio);
    }

}

int menuMateriasPrimerAnio(char materia[]) // Menu para seleccionar una materia del primer anio
{
    int corte = 0;
    int opc;
    while(corte == 0)
    {
        printf("Elije entre una de las siguientes materias: \n\n\n[1]-Astronomia\n[2]-Encantamientos\n[3]-Transformaciones\n[4]-Defenza Contra Las Artes Oscuras\n[5]-Pociones\n[6]-Herbologia\n[7]-Historia de la magia\n[8]-Vuelo\n\nIngrese el numero de la materia elegida: ");
        scanf("%d",&opc);
        switch(opc)
        {
        case 1:
            strcpy(materia,"Astronomia");
            corte++;
            break;
        case 2:
            strcpy(materia,"Encantamientos");
            corte++;
            break;
        case 3:
            strcpy(materia,"Transformaciones");
            corte++;
            break;
        case 4:
            strcpy(materia,"Defensa Contra Las Artes Oscuras");
            corte++;
            break;
        case 5:
            strcpy(materia,"Pociones");
            corte++;
            break;
        case 6:
            strcpy(materia,"Herbologia");
            corte++;
            break;
        case 7:
            strcpy(materia,"Historia de la magia");
            corte++;
            break;
        case 8:
            strcpy(materia,"Vuelo");
            corte++;
            break;
        default:
            printf("Opcion ingresada incorrecta. vuelva a intentarlo.\n\n");
            pauseAndClean();
            break;
        }
    }
    return opc;
}
int menuMateriasSegundoAnio(char materia[])// Menu para seleccionar una materia del segundo anio
{
    int corte = 0;
    int opc;
    while(corte == 0)
    {
        printf("Elije entre una de las siguientes materias: \n[1]-Astronomia\n[2]-Encantamientos\n[3]-Transformaciones\n[4]-Defenza Contra Las Artes Oscuras\n[5]-Pociones\n[6]-Herbologia\n[7]-Historia de la magia\n");
        scanf("%d",&opc);
        switch(opc)
        {
        case 1:
            strcpy(materia,"Astronomia");
            corte++;
            break;
        case 2:
            strcpy(materia,"Encantamientos");
            corte++;
            break;
        case 3:
            strcpy(materia,"Transformaciones");
            corte++;
            break;
        case 4:
            strcpy(materia,"Defensa Contra Las Artes Oscuras");
            corte++;
            break;
        case 5:
            strcpy(materia,"Pociones");
            corte++;
            break;
        case 6:
            strcpy(materia,"Herbologia");
            corte++;
            break;
        case 7:
            strcpy(materia,"Historia de la magia");
            corte++;
            break;
        default:
            printf("Opcion ingresada incorrecta. vuelva a intentarlo.\n\n");
            pauseAndClean();
            break;
        }
    }
    return opc;
}
int menuMateriasTercerAnioEnAdelante(char materia[])// Menu para seleccionar una materia del tercer anio en adelanto
{
    int corte = 0;
    int opc;
    while(corte == 0)
    {
        printf("Elije entre una de las siguientes materias: \n[1]-Astronomia\n[2]-Encantamientos\n[3]-Transformaciones\n[4]-Defenza Contra Las Artes Oscuras\n[5]-Pociones\n[6]-Herbologia\n[7]-Historia de la magia\n");
        printf("[8]-Estudio de Runas Antiguas\n[9]-Aritmancia \n[10]-Estudios Muggles \n[11]-Cuidado de Criaturas Magicas \n[12]-Adivinacion \n[13]-Alquimia\n\nIngrese el numero de la materia elegida: ");
        scanf("%d",&opc);
        switch(opc)
        {
        case 1:
            strcpy(materia,"Astronomia");
            corte++;
            break;
        case 2:
            strcpy(materia,"Encantamientos");
            corte++;
            break;
        case 3:
            strcpy(materia,"Transformaciones");
            corte++;
            break;
        case 4:
            strcpy(materia,"Defensa Contra Las Artes Oscuras");
            corte++;
            break;
        case 5:
            strcpy(materia,"Pociones");
            corte++;
            break;
        case 6:
            strcpy(materia,"Herbologia");
            corte++;
            break;
        case 7:
            strcpy(materia,"Historia de la magia");
            corte++;
            break;
        case 8:
            strcpy(materia,"Estudio de Runas Antiguas");
            corte++;
            break;
        case 9:
            strcpy(materia,"Aritmancia ");
            corte++;
            break;
        case 10:
            strcpy(materia,"Estudios Muggles");
            corte++;
            break;
        case 11:
            strcpy(materia,"Cuidado de Criaturas Magicas");
            corte++;
            break;
        case 12:
            strcpy(materia,"Adivinacion");
            corte++;
            break;
        case 13:
            strcpy(materia,"Alquimia");
            corte++;
            break;
        default:
            printf("Opcion ingresada incorrecta. vuelva a intentarlo.\n\n");
            pauseAndClean();
            break;
        }
    }
    return opc;
}

stProfesor crearEstructuraProfesor(stProfesor nuevoProfesor) // Funcion que crea una estructura profesor
{
    int flag = 0;
    printf("Por favor, le pedimos que a continuacion ingrese una serie de datos personales");
    printf("\nIngrese su nombre: \n");
    fflush(stdin);
    gets(nuevoProfesor.nombre);
    printf("Ingrese su nombre de usuario. El mismo no podra tener mas de 30 caracteres y distingue entre minuscula y mayusculas\n");
    fflush(stdin);
    gets(nuevoProfesor.usuario);
    int control=Comprobacion_Usuario(nuevoProfesor.usuario);
    while(control==1)
    {
        printf("El nombre de usuario que quiere ingresar ya se encuentra en uso. Por favor ingrese uno nuevo\n");
        fflush(stdin);
        gets(nuevoProfesor.usuario);
        control=Comprobacion_Usuario(nuevoProfesor.usuario);
    }
    CargarContraseniaProfesor(nuevoProfesor.contrasenia);
    nuevoProfesor.anio = eleccionDeAnio();
    eleccionDeMateria(nuevoProfesor.materia, &nuevoProfesor.anio);
    nuevoProfesor.altaBaja = 1;
    while(flag != 1)
    {
        flag = eleccionDeCasas(nuevoProfesor.casa);
    }
    return nuevoProfesor;
}

nodoProfesor * buscarUltimo(nodoProfesor*lista) //Busca al nodo en la lista de profesores
{
    nodoProfesor * ultimo = lista;
    if(lista!=NULL)
    {
        while(ultimo->siguiente!=NULL)
        {
            ultimo = ultimo->siguiente;
        }
    }
    return ultimo;
}


nodoProfesor * agregarAlFinal(nodoProfesor * lista,nodoProfesor * nuevoNodo) //Agrega un profesor al final de la lista
{
    nodoProfesor * ultimo;
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }
    return lista;
}

int eleccionDeCasas(char casa[]) //Permite al profesor escoger una casa
{
    int eleccion;
    int flag;
    printf("\nIngrese a que casa pertece: ");
    printf("\n\n1. Gryffindor\n2. Hufflepuff\n3. Revenclaw\n4. Slytherin\nElige una opcion: ");
    scanf("%d",&eleccion);
    if(eleccion == 1)
    {
        strcpy(casa,"Gryffindor");
        flag = 1;
    }
    else if(eleccion == 2)
    {
        strcpy(casa,"Hufflepuff");
        flag = 1;
    }
    else if(eleccion == 3)
    {
        strcpy(casa,"Revenclaw");
        flag = 1;
    }
    else if(eleccion == 4)
    {
        strcpy(casa,"Slytherin");
        flag = 1;
    }
    else
    {
        printf("No has ingresado la opcion correcta. Vuelve a intentarlo.\n\n");
        fflush(stdin);
        pauseAndClean();
        flag = 0;
    }
    return flag;
}


void registroDeProfesores() //Agrega a un profesor al archivo de profesores
{
    stProfesor aux;
    FILE * archi = fopen("archivoProfesores","ab");
    if(archi != NULL)
    {
        aux = crearEstructuraProfesor(aux);
        fwrite(&aux,sizeof(stProfesor),1,archi);
        fclose(archi);
    }
}

nodoProfesor * inicListaProfesores() //Inicializa una lista de profesores
{
    return NULL;
}

nodoProfesor * crearNodoProfesor(stProfesor nuevoProfesor) //Crea un nodo profesor
{
    nodoProfesor * aux = (nodoProfesor*)malloc(sizeof(nodoProfesor));
    aux->profesor = nuevoProfesor;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}

nodoProfesor * pasarDeArchivoToListaProfesores(nodoProfesor * lista) //Carga una lista de profesores con un archivo de profesores
{
    stProfesor aux;
    nodoProfesor * nuevoNodo = inicListaProfesores();
    FILE * archivo = fopen("archivoProfesores","rb");
    if(archivo != NULL)
    {
        while(fread(&aux,sizeof(stProfesor),1,archivo)>0)
        {
            nuevoNodo = crearNodoProfesor(aux);
            lista = agregarAlFinal(lista,nuevoNodo);
        }
    }
    else
    {
        printf("\nERROR\n");
    }
    return lista;
}

void mostrarUnProfesor(nodoProfesor * profesor) //Muestra un nodo profesor
{
    puts("\n-------------------------------\n");
    printf("\nNombre del Profesor: %s",profesor->profesor.nombre);
    printf("\nMateria que ejerce: %s",profesor->profesor.materia);
    printf("\nAnio en el que da clases: %d",profesor->profesor.anio);
    printf("\nCasa a la que pertenece: %s\n\n",profesor->profesor.casa);
    printf("\nAlta baja: %d",profesor->profesor.altaBaja);

}

void mostrarListaDeProfesores(nodoProfesor * lista) //Muestra la lista de profesores
{
    nodoProfesor * aux = lista;
    while(aux != NULL)
    {
        if(aux->profesor.altaBaja==1)
        {
            mostrarUnProfesor(aux);
        }

        aux = aux->siguiente;
    }
}


nodoTrabajos * iniclistaTrabajos() //Inicializa una lista de trabajos
{
    return NULL;
}

stTrabajo crearEstructuraTrabajo(int anio,char materia[]) //Crea una estructura trabajo
{
    stTrabajo nuevoTrabajo;
    strcpy(nuevoTrabajo.materia,materia);
    printf("\nIngrese el titulo del Nuevo Trabajo: \n");
    fflush(stdin);
    gets(nuevoTrabajo.titulo);
    printf("\nIngrese la consigna: \n");
    fflush(stdin);
    gets(nuevoTrabajo.consigna);
    printf("\nIngrese la demostracion de como se hace. En caso de que la consigna sea realizar una pocion, ingrese los ingredientes neceasios: \n");
    fflush(stdin);
    gets(nuevoTrabajo.demostracion);
    nuevoTrabajo.anio = anio;

    return nuevoTrabajo;
}

void cargarArchivoDeTrabajos(int anio, stMateria materias[], stProfesor profe) //Carga un archivo de trabajos
{
    stTrabajo nuevoTrabajo;
    char control = 's';
    FILE * archivo = fopen("archivoTrabajos","ab");
    if(archivo != NULL)
    {
        while(control == 's')
        {
            int pos=0;
            nuevoTrabajo = crearEstructuraTrabajo(anio,profe.materia);
            pos=buscarPosPorNombre(materias,14,profe.materia);
            materias[pos].trabajo=agregarTrabajoAlFinal(materias[pos].trabajo,crearNodoTrabajo(nuevoTrabajo));
            fwrite(&nuevoTrabajo,sizeof(stTrabajo),1,archivo);
            printf("\nQuiere agregar otro trabajo? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
            system("cls");

        }
        fclose(archivo);
    }
}

nodoTrabajos * buscarUltimoTrabajo(nodoTrabajos * lista) //Busca el ultimo trabajo en la lista
{
    nodoTrabajos * ultimo = lista;
    if(lista!=NULL)
    {
        while(ultimo->sig!=NULL)
        {
            ultimo = ultimo->sig;
        }
    }
    return ultimo;
}

nodoTrabajos * crearNodoTrabajo(stTrabajo nuevoTrabajo) //Crea un nodo trabajo
{
    nodoTrabajos * aux = (nodoTrabajos*)malloc(sizeof(nodoTrabajos));
    aux->trabajo = nuevoTrabajo;
    aux->sig = NULL;
    return aux;
}

nodoTrabajos * agregarTrabajoAlFinal(nodoTrabajos * lista, nodoTrabajos * nuevoNodo) //Agrega un nodo trabajo al final de la lista
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoTrabajos * ultimo = buscarUltimoTrabajo(lista);
        ultimo->sig = nuevoNodo;
    }
    return lista;
}

nodoTrabajos * pasarDeArchivoToListaTrabajos(nodoTrabajos * lista, int anio) //Pasa de un archivo a una lista
{
    stTrabajo aux;
    nodoTrabajos * nuevoNodo;
    FILE * archivo = fopen("archivoTrabajos","rb");
    if(archivo != NULL)
    {
        while(fread(&aux,sizeof(stTrabajo),1,archivo)>0)
        {
            if(aux.anio==anio)
            {
                nuevoNodo = crearNodoTrabajo(aux);
                lista = agregarTrabajoAlFinal(lista,nuevoNodo);
            }
        }
    }
    return lista;
}

void mostrarUnNodoTrabajo(nodoTrabajos * lista) //Muesta un nodo trabajo
{
    puts("\n-------------------------------\n");
    printf("\nNTitulo del trabajo: %s\n",lista->trabajo.titulo);
    printf("\nConsigna: %s",lista->trabajo.consigna);
    printf("\nExplicacion: %s",lista->trabajo.demostracion);

}

void mostrarListaTrabajos(nodoTrabajos * listas, int anio,char materia[]) //Muestra la lista de trabajos segun el anio y la materia
{
    nodoTrabajos * aux = listas;
    while(aux != NULL)
    {

        if(aux->trabajo.anio == anio)
        {
            if(strcmp(aux->trabajo.materia,materia)==0)
            {
                mostrarUnTrabajo(aux->trabajo);
            }

        }
        aux = aux->sig;
    }
}


void mostrarUnTrabajo(stTrabajo trabajo) //Muestra un trabajo
{
    puts("\n-------------------------------\n");
    printf("Anio del trabajo: %d",trabajo.anio);
    printf("\nNTitulo del trabajo: \n%s\n\n",trabajo.titulo);
    printf("\nConsigna: \n%s\n",trabajo.consigna);
    printf("\nExplicacion: \n%s\n",trabajo.demostracion);

}

void mostrarArchivoRegistro() // Muestra 'archivoTrabajos'
{
    stTrabajo tp;
    FILE * archivo = fopen("archivoTrabajos", "rb");
    if(archivo != NULL)
    {
        while(fread(&tp, sizeof(stTrabajo), 1, archivo) > 0)
        {
            mostrarUnTrabajo(tp);
        }
        fclose(archivo);
    }
}

void inicializarListaDeArregloMateria(stMateria arreglo[],int dimension)
{
    int indice = 0;
    stMateria aux;
    FILE *Archi=fopen("Lista de materias","rb");
    if(Archi)
    {
        while(fread(&aux,sizeof(stMateria),1,Archi)>0 && indice<=dimension)
        {
            strcpy(arreglo[indice].nombre,aux.nombre);
            arreglo[indice].trabajo=iniclistaTrabajos();
            indice++;
        }
    }


}

int buscarPosPorNombre(stMateria arreglo[],int validos, char materia[])
{
    int indice=0,rta;
    while (indice<validos)
    {

        if(strcmpi(materia,arreglo[indice].nombre) == 0)
        {
            rta=indice;
        }
        indice++;
    }
    return rta;
}

void mostrarProfesor(stProfesor profesor) //Muestra una estructura profesor
{
    puts("\n-------------------------------\n");
    printf("\nNombre del Profesor: %s",profesor.nombre);
    printf("\nMateria que ejerce: %s",profesor.materia);
    printf("\nAnio en el que da clases: %d",profesor.anio);
    printf("\nCasa a la que pertenece: %s\n\n",profesor.casa);
    printf("\nActivo = 1, inactivo = 0: %d\n\n",profesor.altaBaja);

}

void mostrarArchivoProfesor() //Muestra el archivo de profesores
{
    FILE *Archi=fopen("archivoProfesores","rb");
    if(Archi)
    {
        stProfesor aux;

        while(fread(&aux,sizeof(stProfesor),1,Archi)>0)
        {
            if(aux.altaBaja==1)
            {
                mostrarProfesor(aux);
            }
        }
        fclose(Archi);
    }
}

void Crear_Archivo_Profesor() //Si el archivo de profesores no esta creado, lo crea
{
    FILE *Archi=fopen("archivoProfesores","rb");
    if(Archi==NULL)
    {
        Archi=fopen("archivoProfesores","ab");
    }
}

void mostrarListaSegunMateria(stMateria arreglo[],int validos, char materia[],int anio) //Muestra una lista segun la materia y el anio
{
    int indice=0;
    printf("El nombre de la materia buscada es: %s\n",materia);
    indice=buscarPosPorNombre(arreglo,validos,materia);
    printf("El indice quedo en: %d\n",indice);
    printf("La materia del el indice %d es %s\n",indice,arreglo[indice].nombre);
    printf("Anio: %d\n", anio);
    system("pause");
    mostrarListaTrabajos(arreglo[indice].trabajo,anio,materia);
}

int Comprobacion_Usuario(char nombre[]) //Comprueba que el usuario no este en uso
{
    FILE *ArchivoProfesores=fopen("archivoProfesores","rb");
    FILE *ArchivoAlumnos=fopen("Archivo Alumnos","rb");
    stAlumno alumnoAux;
    stProfesor profesorAux;
    int control=0;
    if(ArchivoAlumnos && ArchivoProfesores)
    {
        while (fread(&alumnoAux,sizeof(stAlumno),1,ArchivoAlumnos)>0 && control==0)
        {
            if(strcmp(alumnoAux.usuario,nombre)==0)
            {
                control=1;
            }
        }
        while (fread(&profesorAux,sizeof(stProfesor),1,ArchivoProfesores)>0 && control==0)
        {
            if(strcmp(profesorAux.usuario,nombre)==0)
            {
                control=1;
            }
        }
        fclose(ArchivoAlumnos);
        fclose(ArchivoProfesores);
    }
    return control;
}

void Mostrar_Archivo_Trabajos() //Muestra el archhivo trabajo
{
    FILE *Archi=fopen("archivoTrabajos","rb");
    stTrabajo aux;
    if(Archi)
    {
        while(fread(&aux,sizeof(stTrabajo),1,Archi)>0)
        {
            mostrarUnTrabajo(aux);
        }
        fclose(Archi);
    }
}

int BuscarProfesorEnArchivo(char usuario[]) //Busca una posicion por nombre de usuario y la retorna
{
    FILE *Archi=fopen("archivoProfesores","rb");
    stProfesor aux;
    int i=0;
    if(Archi)
    {
        while(fread(&aux,sizeof(stProfesor),1,Archi)>0 && strcmp(aux.usuario,usuario)!=0)
        {
            i++;
        }
        fclose(Archi);
    }
    return i;
}

void expulsarProfesor() //Cambia el estado del profesor a 0
{
    stProfesor profesor;
    char usuarioExpulsado[20];
    mostrarArchivoProfesor();
    FILE *Archi=fopen("archivoProfesores","r+b");
    if(Archi != NULL)
    {
        printf("Ingrese el nombre de usuario del profesor que merezca la expulsion: ");
        fflush(stdin);
        gets(usuarioExpulsado);
        int pos = BuscarProfesorEnArchivo(usuarioExpulsado);
        fseek(Archi,pos*sizeof(stProfesor),SEEK_SET);
        fread(&profesor,sizeof(stProfesor),1,Archi);
        profesor.altaBaja = 0;
        fseek(Archi,pos*sizeof(stProfesor),SEEK_SET);
        fwrite(&profesor,sizeof(stProfesor),1,Archi);
        fclose(Archi);
    }
}


void cargarAvisoAlArchivo() //Carga un archivo avisos
{
    stAviso nuevoAviso;
    FILE *Archi=fopen("archivoAvisos","ab");
    if(Archi != NULL)
    {
        printf("Escriba un titulo: \n");
        fflush(stdin);
        gets(nuevoAviso.titulo);
        printf("Escriba un nuevo aviso: \n");
        fflush(stdin);
        gets(nuevoAviso.aviso);
        fwrite(&nuevoAviso,sizeof(stAviso),1,Archi);
        fclose(Archi);
    }
    fclose(Archi);
}



void mostrarUnAviso(stAviso aviso) //Muestra el archivo avisos
{
    printf("\n----------------------------------------\n");
    printf("Titulo: %s\n",aviso.titulo);
    printf("\n%s\n",aviso.aviso);
}

void mostrarAvisos() //Muestra todos los avisos
{
    gotoxy(47,1);
    color(01);
    printf("AVISOS DEL COLEGIO HOGWARTS");
    color(15);
    gotoxy(0,4);
    stAviso nuevoAviso;
    FILE *Archi=fopen("archivoAvisos","rb");
    if(Archi != NULL)
    {
        while(fread(&nuevoAviso,sizeof(stAviso),1,Archi)>0)
        {
            mostrarUnAviso(nuevoAviso);
        }
        fclose(Archi);
    }
    else
    {
        printf("\n\nEl honorable director Dumbledor no ha cargado ningun aviso. Mantengase al tanto por posibles publicaciones\n\n");
        system("pause");
    }
}

