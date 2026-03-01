#include <iostream>
using namespace std;

//structs del programa
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

//funciones del programa
void menu(Luchador [],NodoLuchadorSE *&);
Luchador busqueda_id_secuencial(NodoLuchadorSE *&, int);
void liberar_memoria(NodoLuchadorSE *&, int);
void cargar_ordenado(NodoLuchadorSE *&, Luchador&);
void actualizar_ranking(Luchador [],NodoLuchadorSE *&);
void main_card(NodoLuchadorSE *&, Luchador [][5], int []);
void mostrar_lista(NodoLuchadorSE *lista);
void guardar_gimnasio(NodoLuchadorSE *lista);
void cargarGimnasio(NodoLuchadorSE *&lista);

// Función sugerida
Luchador ingresar_luchador() {
    
    Luchador nuevo;
    cout << "\n Ingresar datos del nuevo atleta: " << endl;
    
    cout << "ID: ";
    cin >> nuevo.id;
    cin.ignore(); 

    cout << "Nombre (max 10 caracteres): "; //Se acepta un nombre, por eso no uso getinline...
    cin >> nuevo.nombre;

    cout << "Apodo (max 10 caracteres): ";
    cin.getline(nuevo.apodo, 11);
    
    cout << "Peso: ";
    cin >> nuevo.peso;

    cout << "Cantidad de Victorias: ";
    cin >> nuevo.victorias;

    cout << "Cantidad de Derrotas: ";
    cin >> nuevo.derrotas;

    return nuevo;
}


int main()
{
    Luchador ranking[10]; // asigno cuantos luchadores va a almacenar el ranking
    NodoLuchadorSE *lista=NULL;
    cargarGimnasio(lista);
    mostrar_lista(lista);
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
                // Me pide buscar un luchador por ID y modificar su contador de victorias y derrotas
                cout << "Ingrese el ID del luchador a actualizar: ";
                cin >> id; //ingreso el ID del luchador a actualizar
                
                luchador = busqueda_id_secuencial(lista, id); //busco al luchador por ID en la lista
                
                if (luchador.id < 0) //confirmo si existe el id ingresado
                {
                    cout << "El ID del luchador no existe" << endl; 
                }
                else
                {
                    cout << "Luchador encontrado: " << luchador.nombre << endl;
                    cout << "Victorias actuales: " << luchador.victorias << endl;
                    cout << "Derrotas actuales: " << luchador.derrotas << endl;
                    //datos actuales del luchador encontrado

                    cout << "\nIngrese nuevas victorias: "; cin >> luchador.victorias; 
                    cout << "Ingrese nuevas derrotas: "; cin >> luchador.derrotas;
                    //actualizo los datos del luchador encontrado

                    liberar_memoria(lista, id); // Tengo q eliminar la versión vieja del nodo
                    cargar_ordenado(lista, luchador); // se inserta al luchador actualizado y se reordena automáticamente
                    
                    cout << "Récord actualizado exitosamente." << endl;
                }
                break;

            case 4:
                // Guardar la lista dinámica en un archivo.
                guardar_gimnasio(lista);
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