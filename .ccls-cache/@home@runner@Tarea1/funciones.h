#ifndef FUNCIONES_H
#define FUNCIONES_H


//Definicion de las estructuras que utilizaremos
typedef struct {
    char titulo[51];
    char autor[51];
    char genero[51];
    char ISBN[51];
    char ubicacion[51];
    char estado[51];
    char reservas[255]; // lista de estudiantes separados por comas
} Libro;

typedef struct {
    Libro *libros;
    int cantidad;
} Biblioteca;


void registrarLibro(Biblioteca *biblioteca);
void mostrarDatosLibro(Biblioteca biblioteca);
char* get_csv_field(char * tmp, int k);
void mostrarTodosLosLibros(Biblioteca biblioteca);
void reservarLibro(Biblioteca *biblioteca);
void cancelarReservaLibro(Biblioteca *biblioteca);
void retirarLibro(Biblioteca *biblioteca);
void devolverLibro(Biblioteca *biblioteca);
void mostrarLibrosPrestados(Biblioteca biblioteca);
void importarLibrosDesdeCSV(Biblioteca *biblioteca, char *nombre_archivo);
void exportarLibrosACSV(Biblioteca biblioteca, char *nombre_archivo);


#endif