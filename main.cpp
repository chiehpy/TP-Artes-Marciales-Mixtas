#include <iostream>
using namespace std;

struct Luchador
{
    int id;
    char nombre[10+1];
    char apodo[10+1]; 
    float peso; 
    int victorias;
    int derrotas;
};

struct NodoLuchadorSE
{
    Luchador info;
    NodoLuchadorSE *sgte;
};

void menu(Luchador [],NodoLuchadorSE *&);
Luchador busqueda_id_secuencial(NodoLuchadorSE *&, int);
void liberar_memoria(NodoLuchadorSE *&, int);
void cargar_ordenado(NodoLuchadorSE *&, Luchador&);
void actualizar_ranking(Luchador [],NodoLuchadorSE *&);

// Función sugerida
Luchador ingresar_luchador();

int main()
{
    Luchador ranking[10];
    NodoLuchadorSE *lista=NULL;

    // Libero la memoria
    while (lista)
    {
        liberar_memoria(lista,lista->info.id);
    }
    
    return 0;
}

void menu(Luchador vec[], NodoLuchadorSE *&lista)
{
    int num; // Número que elija el usuario (opción seleccionada)
    bool salida=false; // Condición de salida del bucle
    // El usuario quiere salir del bucle cuando esta variable sea TRUE

    int id;
    // Variable sugerida
    Luchador luchador;
    
    do
    {
        cout <<
        "1- Inscripción de Atleta\n"<<
        "2- Generar Main Card:\n"<<
        "3- Actualizar Récord:\n"<<
        "4- Guardar Gimnasio:\n"<<
        "5- Cargar Gimnasio:\n"<<
        "* -Salir\n"<<
        "Seleccionar una opción (de 1 a 5, cualquier otro número termina el programa): ";
        cin>>num;

        switch (num)
        {
            case 1:
                // Insertar un nuevo luchador en la lista dinámica
                // de forma ordenada por puntaje (victorias - derrotas).
                luchador=ingresar_luchador();
                cargar_ordenado(lista,luchador);
                break;
            
            case 2:
                // Copiar los primeros 5 luchadores de la lista dinámica
                // a un arreglo estático para representar los combates estelares.
                actualizar_ranking(vec,lista);

                cout<<"Los luchadores que participarán en las peleas estelares:"<<endl;
                for (int i = 0; i < 5; i++)
                {
                    cout<<"Top "<<i+1<<": "<<vec[i].nombre<<endl;
                }
                break;
            
            case 3:
                // Buscar un luchador por ID y modificar su contador
                // de victorias y derrotas.
                cin>>id;
                luchador=busqueda_id_secuencial(lista,id);
                
                if (luchador.id < 0 )
                {
                    cout<<"El ID del luchador no existe"<<endl;
                }
                else
                {
                    /*
                    Aquí se deberían modificar los contadores
                    de victorias y derrotas del luchador.
                    Puede hacerse con una función o directamente aquí.
                    */
                    
                    // "Actualización"
                    liberar_memoria(lista,id); // Elimino la versión vieja del nodo
                    cargar_ordenado(lista,luchador); // Inserto el luchador actualizado
                }
                break;

            case 4:
                // Guardar la lista dinámica en un archivo.
                break;

            case 5:
                // Al iniciar el programa, se debe leer el archivo
                // y reconstruir la lista en memoria.
                break;
            
            default:
                // Condición de salida del menú:
                // Si el usuario ingresa un número fuera del rango 1-5
                salida = true;
        }

    }while (!salida);
    /*
    El bucle se mantiene mientras salida sea FALSE.
    
    Ejemplo:
    - ¿Quiere salir del menú? FALSE → while (!FALSE) → continúa el bucle.
    - ¿Quiere salir del menú? TRUE → while (!TRUE) → termina el bucle.
    */
}

void cargar_ordenado(NodoLuchadorSE *&lista, Luchador &luchador) 
{
    NodoLuchadorSE *paux=lista;
    NodoLuchadorSE *anterior=NULL;
    
    // Mientras el puntero no sea NULL y el puntaje del nuevo luchador
    // sea mayor que el de la lista, continúo avanzando.
    while (paux && (paux->info.victorias - paux->info.derrotas) < 
           (luchador.victorias - luchador.derrotas))
    {
        anterior=paux;
        paux=paux->sgte;
    }

    // Verifico si el nuevo nodo no debe ir al principio
    if (paux !=lista)
    {
        anterior->sgte= new NodoLuchadorSE();
        anterior->sgte->info=luchador;
        anterior->sgte->sgte=paux;
    }
    else
    {
        // Si el nuevo luchador debe ir al principio de la lista
        lista= new NodoLuchadorSE();
        lista->info=luchador;
        lista->sgte=paux;
    }
}

void actualizar_ranking(Luchador vec[],NodoLuchadorSE *&lista)
{
    NodoLuchadorSE *paux=lista;

    // Copio los elementos de la lista al arreglo
    for (int i = 0; i < 10 && paux != NULL; i++)
    {
        vec[i]=paux->info;
        paux=paux->sgte;
    }
}

void liberar_memoria(NodoLuchadorSE *&lista, int id)
{
    NodoLuchadorSE* actual=lista;
    NodoLuchadorSE* anterior=NULL;
    NodoLuchadorSE* eliminar=NULL;

    // Si el nodo a eliminar es el primero
    if (actual->info.id ==id)
    {
        eliminar=lista;
        lista=lista->sgte;
        delete eliminar;
    }
    else
    {
        // Busco el nodo con el ID a eliminar
        while (actual->info.id !=id)
        {
            anterior=actual;
            actual=actual->sgte;
        }
        
        // El nodo actual es el que se debe eliminar
        eliminar=actual;
        actual=actual->sgte;
        //quedando asi anterior-> nodo a eliminar ->actual

        // El nodo anterior salta al siguiente
        anterior->sgte=actual;
        //  quedando asi anterior-> actual

        // Libero la memoria
        delete eliminar;
    }
}

Luchador busqueda_id_secuencial(NodoLuchadorSE *&lista, int id)
{
    NodoLuchadorSE *paux=lista;

    // Busco en la lista el ID indicado
    while (paux && paux->info.id !=id)
    {
        paux=paux->sgte;
    }

    // Si lo encontró, lo retorno
    if (paux && paux->info.id ==id)
    {
        return paux->info;
    }

    // Si no lo encuentra, retorno un luchador inexistente
    Luchador no_existe;
    no_existe.id =-1;
    return no_existe;
}
