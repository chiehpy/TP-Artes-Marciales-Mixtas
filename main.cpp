#include <iostream>
using namespace std;

//structs del programa
struct Luchador
{
    int id;
    char nombre[30+1];
    char apodo[30+1]; 
    float peso; 
    int victorias;
    int derrotas;
};

struct NodoLuchadorSE
{
    Luchador info;
    NodoLuchadorSE *sgte;
};

//funciones del programa
void menu(Luchador[], NodoLuchadorSE*& lista);
Luchador busqueda_id_secuencial(NodoLuchadorSE*& lista, int id);
void liberar_memoria(NodoLuchadorSE*& lista, int id);
void cargar_ordenado(NodoLuchadorSE*& lista, Luchador& luchador);
void actualizar_ranking(Luchador[], NodoLuchadorSE*& lista);
void mainCard(NodoLuchadorSE* lista, Luchador[]);
void mostrar_lista(NodoLuchadorSE* lista);
void guardar_gimnasio(NodoLuchadorSE* lista);
void cargarGimnasio(NodoLuchadorSE*& lista);
void corteDePeso(NodoLuchadorSE*& lista);

// Función sugerida
Luchador ingresar_luchador(NodoLuchadorSE* lista) {
    NodoLuchadorSE* paux = lista;
    
    Luchador nuevo;
    cout << "\n Ingresar datos del nuevo atleta: " << endl;
    

    int aux = 0;
    while(paux!=NULL){
        if(paux->info.id > aux){
            aux = paux->info.id;
        }paux = paux->sgte;
    }

    nuevo.id = aux+1;

    cout << "Nombre (max 10 caracteres): "<< endl; //Se acepta un nombre, por eso no uso getinline...
    cin >> nuevo.nombre;

    cin.ignore();

    cout << "Apodo (max 10 caracteres): ";
    cin.getline(nuevo.apodo, 31);
        
    cout << "Peso: "<< endl;
    cin >> nuevo.peso;

    cout << "Cantidad de Victorias: "<< endl;
    cin >> nuevo.victorias;

    cout << "Cantidad de Derrotas: "<< endl;
    cin >> nuevo.derrotas;

    return nuevo;
}


int main()
{
    Luchador ranking[10]; // asigno cuantos luchadores va a almacenar el ranking
    NodoLuchadorSE *lista=NULL;
    cargarGimnasio(lista);
    mostrar_lista(lista);
    menu(ranking, lista);
    while (lista)  // Libero la memoria
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
        "6- Actualizar excedidos de peso según categoria:\n"<<        
        "0- Abortar programa\n"<<
        "Seleccionar una opción (de 1 a 5, cualquier otro número termina el programa): ";
        cin>>num;

        switch (num)
        {
            case 1:
                luchador=ingresar_luchador(lista);
                cargar_ordenado(lista,luchador);
                break;
            
            case 2:
                cout<<"Los luchadores que participarán en las peleas estelares:"<<endl;
                mainCard(lista, vec);
                for (int i = 0; i < 5; i++)
                {
                    cout << "Nombre: " << vec[i].nombre << endl;
                    cout << "Top " << i+1 << endl;
                    cout << "Puntaje: " << vec[i].victorias-vec[i].derrotas << endl;
                    cout << "ID: " << vec[i].id << endl;
                    cout << "Victorias: " <<vec[i].victorias << endl;
                    cout << "Derrotas: " << vec[i].derrotas << endl;
                    cout << "=============================" << endl;
                }
                break;
            
            case 3:
                cout << "Ingrese el ID del luchador a actualizar: ";
                cin >> id;
                luchador = busqueda_id_secuencial(lista, id);
                if (luchador.id < 0)
                {
                    cout << "El ID del luchador no existe" << endl; 
                }
                else
                {
                    cout << "Luchador encontrado: " << luchador.nombre << endl;
                    cout << "Victorias actuales: " << luchador.victorias << endl;
                    cout << "Derrotas actuales: " << luchador.derrotas << endl;
                    cout << "\nIngrese nuevas victorias: "; cin >> luchador.victorias; 
                    cout << "Ingrese nuevas derrotas: "; cin >> luchador.derrotas;
                    liberar_memoria(lista, id);
                    cargar_ordenado(lista, luchador);
                    cout << "Récord actualizado exitosamente." << endl;
                }
                break;

            case 4:
                guardar_gimnasio(lista);
                break;

            case 5:
                while (lista)
                {
                    liberar_memoria(lista, lista->info.id);
                }
                cargarGimnasio(lista);
                break;
            case 6:
                corteDePeso(lista);
                break;

            case 0:
                salida = true;
                break;

            default:
                cout << "Ingresar un numero correcto" << endl;
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
    while (paux && (paux->info.victorias - paux->info.derrotas) > 
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



void mostrar_lista(NodoLuchadorSE *lista)
{
    if (!lista)
    {
        cout << "La lista está vacía." << endl;
        return;
    }

    NodoLuchadorSE *paux = lista;
    int contador = 1;

    cout << "\n=== LISTA DE LUCHADORES ===" << endl;
    
    while (paux)
    {
        cout << "\nLuchador #" << contador << endl;
        cout << "ID: " << paux->info.id << endl;
        cout << "Nombre: " << paux->info.nombre << endl;
        cout << "Apodo: " << paux->info.apodo << endl;
        cout << "Peso: " << paux->info.peso << " kg" << endl;
        cout << "Victorias: " << paux->info.victorias << endl;
        cout << "Derrotas: " << paux->info.derrotas << endl;
        cout << "Puntaje: " << (paux->info.victorias - paux->info.derrotas) << endl;
        
        paux = paux->sgte;
        contador++;
    }
    cout << "\n" << endl;
}

void guardar_gimnasio(NodoLuchadorSE *lista)
{
    if (!lista)
    {
        cout << "La lista está vacía. No hay nada que guardar." << endl;
        return;
    }

    FILE *archivo = fopen("luchadores.dat", "wb");
    
    if (archivo == NULL)
    {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    NodoLuchadorSE *paux = lista;
    int cantidad = 0;

    // Cuento cuántos luchadores hay
    while (paux)
    {
        cantidad++;
        paux = paux->sgte;
    }

    fwrite(&cantidad, sizeof(int), 1, archivo); // Escribo la cantidad de luchadores

    // Escribo cada luchador
    paux = lista;
    while (paux)
    {
        fwrite(&(paux->info), sizeof(Luchador), 1, archivo);
        paux = paux->sgte;
    }

    fclose(archivo);
    cout << "Gimnasio guardado exitosamente en 'luchadores.dat'" << endl;
}

/* funcion cargarGimanasio:
1. Abrir el archivo
2. Comprobamos que el archivo exista
3. Leemos cantidad de luchadores fread almacena cantidad
4. Bucle de iteracion, cada vez que corra almacena un luchador
5. Se carga en "lista" en memoria
6. Cerrar el archivo
*/



void cargarGimnasio(NodoLuchadorSE *&lista){
    FILE* archivo = fopen("luchadores.dat", "rb");

    if(archivo == NULL){
        cout << "El archivo no existe, no hay nada que cargar"<< endl;
        return;
    }
    int cantidad;
    fread(&cantidad, sizeof(int), 1, archivo);
    Luchador luchador;
    for(int i = 0; i < cantidad; i++){
        fread(&luchador, sizeof(Luchador), 1, archivo);
        cargar_ordenado(lista, luchador);

    }
    fclose(archivo);
    cout << "Los luchadores fueron cargados en la lista"<< endl;
    return;
}

void mainCard(NodoLuchadorSE* lista, Luchador V[]){

    NodoLuchadorSE* paux=lista;
    for(int i = 0; i < 5; i++){
        V[i] = paux->info;
        paux = paux->sgte;
    }

}

void corteDePeso(NodoLuchadorSE*& lista){

    int opcion;
    float limite;


    cout << "\nSeleccione la categoria de peso:" << endl;
    cout << "1- Peso Mosca (hasta 56.7 kg)" << endl;
    cout << "2- Peso Gallo (hasta 61.2 kg)" << endl;
    cout << "3- Peso Pluma (hasta 65.8 kg)" << endl;
    cout << "4- Peso Ligero (hasta 70.3 kg)" << endl;
    cout << "5- Peso Welter (hasta 77.1 kg)" << endl;
    cout << "6- Peso Medio (hasta 83.9 kg)" << endl;
    cout << "7- Peso Semipesado (hasta 93.0 kg)" << endl;
    cout << "8- Peso Pesado (hasta 120.2 kg)" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    switch(opcion){
        case 1: limite = 56.7; break;
        case 2: limite = 61.2; break;
        case 3: limite = 65.8; break;
        case 4: limite = 70.3; break;
        case 5: limite = 77.1; break;
        case 6: limite = 83.9; break;
        case 7: limite = 93.0; break;
        case 8: limite = 120.2; break;
        default:
            cout << "Opcion invalida" << endl;
            return;
    }
    

    FILE* archivo = fopen("excedidos.dat", "ab");

    if(archivo == NULL){
        cout << "Error al abrir el archivo de excedidos" << endl;
        return;
    }


    NodoLuchadorSE* paux = lista;

    while(paux != NULL){
        if(paux->info.peso > limite){
            fwrite(&(paux->info), sizeof(Luchador), 1, archivo);
            NodoLuchadorSE* siguiente = paux->sgte;
            liberar_memoria(lista, paux->info.id);
            paux = siguiente;
        }
        else{
            paux = paux->sgte;
        }
    }

    fclose(archivo);


    cout << "El archivo de excedidos fue actualizado con exito" << endl;
    return;
}