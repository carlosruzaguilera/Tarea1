#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicialización de la biblioteca
    Biblioteca biblioteca;
    biblioteca.libros = NULL;
    biblioteca.cantidad = 0;



    // Menú principal del programa
    int opcion;
    do { //mostrar las opciones
        printf("1. Registrar libro\n");
        printf("2. Mostrar datos de libro\n");
        printf("3. Mostrar todos los libros\n");
        printf("4. Reservar libro\n");
        printf("5. Cancelar reserva de libro\n");
        printf("6. Retirar libro\n");
        printf("7. Devolver libro\n");
        printf("8. Mostrar libros prestados\n");
        printf("9. Importar libros desde un archivo CSV\n");
        printf("10. Exportar libros a un archivo CSV\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {//la opcion seleccionada llama a las funciones
            case 1:
                registrarLibro(&biblioteca);
                break;
            case 2:
                mostrarDatosLibro(biblioteca);
                break;
            case 3:
                mostrarTodosLosLibros(biblioteca);
                break;
            case 4:
                reservarLibro(&biblioteca);
                break;
            case 5:
                cancelarReservaLibro(&biblioteca);
                break;
            case 6:
                retirarLibro(&biblioteca);
                break;
            case 7:
                devolverLibro(&biblioteca);
                break;
            case 8:
                mostrarLibrosPrestados(biblioteca);
                break;
            case 9:
                {
                    char nombre_archivo[255];
                    printf("Ingrese el nombre del archivo para importar: ");
                    scanf("%s", nombre_archivo);
                    importarLibrosDesdeCSV(&biblioteca, nombre_archivo);
                }
                break;
            case 10:
                {
                    char nombre_archivo[255];
                    printf("Ingrese el nombre del archivo para exportar: ");
                    scanf("%s", nombre_archivo);
                    exportarLibrosACSV(biblioteca, nombre_archivo);
                }
                break;
        }
    } while(opcion != 0);

    return 0;
}
