#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Luchador {
    int id;
    char nombre[11];
    char apodo[11]; 
    float peso; 
    int victorias;
    int derrotas;
};

int main() {
    FILE *f = fopen("luchadores.dat", "wb");
    if (!f) return 1;

    Luchador atletas[15];

    atletas[0]  = {1,  "Mateo",   "The Hammer", 95.5, 50, 6}; 
    atletas[1]  = {2,  "Marcos",  "Bad Boy",    70.0, 5, 20};
    atletas[2]  = {3,  "Lucas",   "El Profeta", 65.0, 20, 5};
    atletas[3]  = {4,  "Juan",    "The Killer", 95.5, 50, 6}; 
    atletas[4]  = {5,  "Pablo",   "El Mago",    85.0, 10, 6}; 
    atletas[5]  = {6,  "Pedro",   "The Rock",   97.0, 20, 6}; 
    atletas[6]  = {7,  "Lazaro",  "El Fenix",   90.5, 40, 6}; 
    atletas[7]  = {8,  "Marta",   "Iron Lady",  92.5, 6, 6}; 
    atletas[8]  = {9,  "Maria",   "La Brava",   75.5, 17, 6}; 
    atletas[9]  = {10, "Dina",    "La Diabla",  65.0, 9, 6}; 
    atletas[10] = {11, "Daniela", "The Queen",  70.0, 8, 6}; 
    atletas[11] = {12, "Debora",  "La Shark",   100.5, 32, 16}; 
    atletas[12] = {13, "Ester",   "Red Alert",  95.0, 13, 5}; 
    atletas[13] = {14, "Morena",  "The Boss",   67.5, 55, 9}; 
    atletas[14] = {15, "Mirta",   "The Legend", 63.5, 70, 4};

    int cantidad = 15;
    fwrite(&cantidad, sizeof(int), 1, f);
    fwrite(atletas, sizeof(Luchador), 15, f);
    fclose(f);

    cout << "Archivo 'luchadores.dat' generado con 3 luchadores para testear." << endl;
    return 0;
}