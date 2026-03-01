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
void main_card(NodoLuchadorSE *&, Luchador [][5], int []);


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

    //esto es para la "2- Generar Main Card:
    Luchador lucha_estelar[8][5];
    int contadores[8];
    struct categorias_peso
    {
        char peso[11];
    };

    categorias_peso categoria[8] = {{"Mosca"},{"Gallo"},{"Pluma"},{"Ligero"},{"Wélter"},{"Medio"},{"Semipesado"},{"Pesado"}};

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

                cout<<"Los luchadores que participarán en las peleas estelares:"<<endl;

                main_card(lista, lucha_estelar, contadores);

                for (int i = 0; i < 8; i++)
                {
                    cout << "Categoria " << categoria[i].peso << endl;

                    if (contadores[i] == 0)
                        cout << "No hay luchadores\n";
                    else
                    {
                        for (int j = 0; j < contadores[i]; j++)
                        {
                            cout << "Top " << j+1 << endl;
                            cout << "ID: " << lucha_estelar[i][j].id << endl;
                            cout << "Nombre: " << lucha_estelar[i][j].nombre << endl;
                            cout<< "Victorias: " << lucha_estelar[i][j].victorias << endl;
                            cout<< "Derrotas: "<< lucha_estelar[i][j].derrotas<< endl;
                        }
                    }
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
    //verifico si la lista esta vacio (=NULL)
    if (!lista) 
    return;

    //si no esta basia sige el choclo

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
        while (actual && actual->info.id !=id)
        {
            anterior=actual;
            actual=actual->sgte;
        }
        //Si no encontro el id.
        if (!actual){
            cout << "ID no encontrado\n";
            return;
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


void main_card(NodoLuchadorSE *& lista, Luchador v[8][5], int contadores[8])
{ /*
    Peso Mosca (Flyweight): hasta 125 lbs (56.7 kg).
    Peso Gallo (Bantamweight): hasta 135 lbs (61.2 kg).
    Peso Pluma (Featherweight): hasta 145 lbs (65.8 kg).
    Peso Ligero (Lightweight): hasta 155 lbs (70.3 kg).
    Peso Wélter (Welterweight): hasta 170 lbs (77.1 kg).
    Peso Medio (Middleweight): hasta 185 lbs (83.9 kg).
    Peso Semipesado (Light Heavyweight): hasta 205 lbs (93.0 kg).
    Peso Pesado (Heavyweight): 206 a 265 lbs (93.4 - 120.2 kg).
    */
   NodoLuchadorSE *paux= lista;
    for (int i = 0; i < 8; i++)
    {
        contadores[i] = 0;
    }

    while (paux)
    {
        int categoria = -1;

        if (paux->info.peso <=56.7)
        categoria = 0;
        else if (paux->info.peso <=61.2) 
        categoria = 1;
        else if (paux->info.peso <=65.8) 
        categoria = 2;
        else if (paux->info.peso <=70.3) 
        categoria = 3;
        else if (paux->info.peso <=77.1) 
        categoria = 4;
        else if (paux->info.peso <=83.9) 
        categoria = 5;
        else if (paux->info.peso <=93.0) 
        categoria = 6;
        else if (paux->info.peso <=120.2) 
        categoria = 7;

        if (categoria != -1 && contadores[categoria] < 5)
        {
            v[categoria][contadores[categoria]] = paux->info;
            contadores[categoria]++;
        }

        paux = paux->sgte;
    }

}
