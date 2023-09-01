#include <stdio.h>
#include <stdlib.h>

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
// funcion para leer csv
char* get_csv_field(char * tmp, int k);
// Funciones principales
void registrarLibro(Biblioteca *biblioteca) {  //permite al usuario ingresar los detalles de un nuevo libro y lo guarda en el csv
    Libro nuevoLibro;
    FILE *archivo;

    printf("Ingrese el título del libro: ");
    scanf(" %[^\n]", nuevoLibro.titulo);

    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoLibro.autor);

    printf("Ingrese el género del libro: ");
    scanf(" %[^\n]", nuevoLibro.genero);

    printf("Ingrese el ISBN del libro: ");
    scanf(" %[^\n]", nuevoLibro.ISBN);

    printf("Ingrese la ubicación del libro en la biblioteca: ");
    scanf(" %[^\n]", nuevoLibro.ubicacion);

    strcpy(nuevoLibro.estado, "Disponible");
    strcpy(nuevoLibro.reservas, "");

    archivo = fopen("biblioteca.csv", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s\n", nuevoLibro.titulo, nuevoLibro.autor, nuevoLibro.genero, nuevoLibro.ISBN, nuevoLibro.ubicacion, nuevoLibro.estado, nuevoLibro.reservas);
    fclose(archivo);

    printf("Libro registrado exitosamente en el archivo CSV.\n");
}
void mostrarDatosLibro(Biblioteca biblioteca) { //busca un libro por nombre y autro y muestra los detalles
    char tituloBuscado[51];
    char autorBuscado[51];
    char linea[512];
    int encontrado = 0;
    FILE *archivo;

    printf("Ingrese el título del libro que desea buscar: ");
    scanf(" %[^\n]", tituloBuscado);

    printf("Ingrese el autor del libro que desea buscar: ");
    scanf(" %[^\n]", autorBuscado);

    archivo = fopen("biblioteca.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", biblioteca.libros->titulo, biblioteca.libros->autor, biblioteca.libros->genero, biblioteca.libros->ISBN, biblioteca.libros->ubicacion, biblioteca.libros->estado, biblioteca.libros->reservas);
        if (strcmp(biblioteca.libros->titulo, tituloBuscado) == 0 && strcmp(biblioteca.libros->autor, autorBuscado) == 0) {
            printf("Título: %s\n", biblioteca.libros->titulo);
            printf("Autor: %s\n", biblioteca.libros->autor);
            printf("Género: %s\n", biblioteca.libros->genero);
            printf("ISBN: %s\n", biblioteca.libros->ISBN);
            printf("Ubicación: %s\n", biblioteca.libros->ubicacion);
            printf("Estado: %s\n", biblioteca.libros->estado);
            printf("Reservas: %s\n", biblioteca.libros->reservas);
            encontrado = 1;
            break;
        }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("No se encontró el libro con el título '%s' y autor '%s'.\n", tituloBuscado, autorBuscado);
    }
}

void mostrarTodosLosLibros(Biblioteca biblioteca) {//muestra una lista de todos los libros registrados
    printf("Lista de libros registrados:\n");
    for (int i = 0; i < biblioteca.cantidad; i++) {
        printf("%d. Título: %s - Autor: %s\n", i+1, biblioteca.libros[i].titulo, biblioteca.libros[i].autor);
    }
}
void reservarLibro(Biblioteca *biblioteca) {// premite reservar un libro escribiendo el nombre de quien hace la reserva
    char tituloBuscado[51];
    char autorBuscado[51];
    char estudiante[51];
    int encontrado = 0;

    printf("Ingrese el título del libro que desea reservar: ");
    scanf(" %[^\n]", tituloBuscado);

    printf("Ingrese el autor del libro que desea reservar: ");
    scanf(" %[^\n]", autorBuscado);

    printf("Ingrese el nombre del estudiante que reserva: ");
    scanf(" %[^\n]", estudiante);

    for (int i = 0; i < biblioteca->cantidad; i++) {
        if (strcmp(biblioteca->libros[i].titulo, tituloBuscado) == 0 && strcmp(biblioteca->libros[i].autor, autorBuscado) == 0) {
            strcat(biblioteca->libros[i].reservas, estudiante);
            strcat(biblioteca->libros[i].reservas, ",");
            if (strcmp(biblioteca->libros[i].estado, "Disponible") == 0) {
                strcpy(biblioteca->libros[i].estado, "Reservado");
            }
            printf("Libro reservado exitosamente.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el libro con el título '%s' y autor '%s'.\n", tituloBuscado, autorBuscado);
    }
}
void cancelarReservaLibro(Biblioteca *biblioteca) { //permite cancelar una reserva
    char tituloBuscado[51];
    char autorBuscado[51];
    char estudiante[51];
    int encontrado = 0;

    printf("Ingrese el título del libro cuya reserva desea cancelar: ");
    scanf(" %[^\n]", tituloBuscado);

    printf("Ingrese el autor del libro cuya reserva desea cancelar: ");
    scanf(" %[^\n]", autorBuscado);

    printf("Ingrese el nombre del estudiante que cancela la reserva: ");
    scanf(" %[^\n]", estudiante);

    for (int i = 0; i < biblioteca->cantidad; i++) {
        if (strcmp(biblioteca->libros[i].titulo, tituloBuscado) == 0 && strcmp(biblioteca->libros[i].autor, autorBuscado) == 0) {
            char *pos = strstr(biblioteca->libros[i].reservas, estudiante);
            if (pos) {
                size_t len = strlen(estudiante);
                memmove(pos, pos + len + 1, strlen(pos + len + 1) + 1);
                printf("Reserva cancelada exitosamente.\n");
            } else {
                printf("El estudiante %s no tiene una reserva para este libro.\n", estudiante);
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el libro con el título '%s' y autor '%s'.\n", tituloBuscado, autorBuscado);
    }
}

void retirarLibro(Biblioteca *biblioteca) {//permite buscar un libro y ver si se puede retirar
    char tituloBuscado[51];
    char autorBuscado[51];
    char estudiante[51];
    int encontrado = 0;

    printf("Ingrese el título del libro que desea retirar: ");
    scanf(" %[^\n]", tituloBuscado);

    printf("Ingrese el autor del libro que desea retirar: ");
    scanf(" %[^\n]", autorBuscado);

    printf("Ingrese el nombre del estudiante que retira: ");
    scanf(" %[^\n]", estudiante);

    for (int i = 0; i < biblioteca->cantidad; i++) {
        if (strcmp(biblioteca->libros[i].titulo, tituloBuscado) == 0 && strcmp(biblioteca->libros[i].autor, autorBuscado) == 0) {
            if (strcmp(biblioteca->libros[i].estado, "Disponible") == 0 || (strcmp(biblioteca->libros[i].estado, "Reservado") == 0 && strncmp(biblioteca->libros[i].reservas, estudiante, strlen(estudiante)) == 0)) {
                strcpy(biblioteca->libros[i].estado, "Prestado");
                char *pos = strstr(biblioteca->libros[i].reservas, estudiante);
                if (pos) {
                    size_t len = strlen(estudiante);
                    memmove(pos, pos + len + 1, strlen(pos + len + 1) + 1);
                }
                printf("Libro retirado exitosamente.\n");
            } else {
                printf("El libro no está disponible para ser retirado por el estudiante %s.\n", estudiante);
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el libro con el título '%s' y autor '%s'.\n", tituloBuscado, autorBuscado);
    }
}

void devolverLibro(Biblioteca *biblioteca) {//permite gestionar la devolucion de los libros
    char tituloBuscado[51];
    char autorBuscado[51];
    int encontrado = 0;

    printf("Ingrese el título del libro que desea devolver: ");
    scanf(" %[^\n]", tituloBuscado);

    printf("Ingrese el autor del libro que desea devolver: ");
    scanf(" %[^\n]", autorBuscado);

    for (int i = 0; i < biblioteca->cantidad; i++) {
        if (strcmp(biblioteca->libros[i].titulo, tituloBuscado) == 0 && strcmp(biblioteca->libros[i].autor, autorBuscado) == 0) {
            if (strcmp(biblioteca->libros[i].estado, "Prestado") == 0) {
                if (strlen(biblioteca->libros[i].reservas) > 0) {
                    strcpy(biblioteca->libros[i].estado, "Reservado");
                } else {
                    strcpy(biblioteca->libros[i].estado, "Disponible");
                }
                printf("Libro devuelto exitosamente.\n");
            } else {
                printf("El libro no estaba prestado.\n");
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el libro con el título '%s' y autor '%s'.\n", tituloBuscado, autorBuscado);
    }
}

void mostrarLibrosPrestados(Biblioteca biblioteca) {// muestra una lista de todos los libros prestados
    printf("Libros actualmente prestados:\n");
    int contador = 0;
    for (int i = 0; i < biblioteca.cantidad; i++) {
        if (strcmp(biblioteca.libros[i].estado, "Prestado") == 0) {
            printf("%d. Título: %s - Autor: %s\n", ++contador, biblioteca.libros[i].titulo, biblioteca.libros[i].autor);
        }
    }
    if (contador == 0) {
        printf("No hay libros prestados en este momento.\n");
    }
}

void importarLibrosDesdeCSV(Biblioteca *biblioteca, char *nombre_archivo) {//importa los libros desde un archivo csv y los añade a los libros registrados
    FILE *archivo = fopen(nombre_archivo, "r");
    
    if (!archivo) {
        printf("Error al abrir el archivo %s.\n", nombre_archivo);
        return;
    }

    char linea[512];
    while (fgets(linea, sizeof(linea), archivo)) {
        // eliminar posibles terminaciones \r\n o \n
        linea[strcspn(linea, "\r\n")] = 0;

        if (strcmp(linea, "Título,Autor,Género,ISBN,Ubicación,Estado,Reservas") == 0) {
            // si es el encabezado, continuar con la siguiente línea
            continue;
        }

        biblioteca->libros = realloc(biblioteca->libros, (biblioteca->cantidad + 1) * sizeof(Libro));
        strcpy(biblioteca->libros[biblioteca->cantidad].titulo, get_csv_field(linea, 0));
        strcpy(biblioteca->libros[biblioteca->cantidad].autor, get_csv_field(linea, 1));
        strcpy(biblioteca->libros[biblioteca->cantidad].genero, get_csv_field(linea, 2));
        strcpy(biblioteca->libros[biblioteca->cantidad].ISBN, get_csv_field(linea, 3));
        strcpy(biblioteca->libros[biblioteca->cantidad].ubicacion, get_csv_field(linea, 4));
        strcpy(biblioteca->libros[biblioteca->cantidad].estado, get_csv_field(linea, 5));
        strcpy(biblioteca->libros[biblioteca->cantidad].reservas, get_csv_field(linea, 6));
        biblioteca->cantidad++;
    }

    fclose(archivo);
    printf("Libros importados exitosamente desde %s.\n", nombre_archivo);
}



void exportarLibrosACSV(Biblioteca biblioteca, char *nombre_archivo) {//exporta la lista actual de libros a un archivo csv
    FILE *archivo = fopen(nombre_archivo, "w");
    if (!archivo) {
        printf("Error al abrir el archivo %s para escritura.\n", nombre_archivo);
        return;
    }

    fprintf(archivo, "Título,Autor,Género,ISBN,Ubicación,Estado,Reservas\n");
    for (int i = 0; i < biblioteca.cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s\n",
                biblioteca.libros[i].titulo,
                biblioteca.libros[i].autor,
                biblioteca.libros[i].genero,
                biblioteca.libros[i].ISBN,
                biblioteca.libros[i].ubicacion,
                biblioteca.libros[i].estado,
                biblioteca.libros[i].reservas);
    }

    fclose(archivo);
    printf("Libros exportados exitosamente a %s.\n", nombre_archivo);
}


char* get_csv_field(char * tmp, int k) { //extrae campos de un archivo csv
    int open_mark = 0;
    char* ret = (char*) malloc(100 * sizeof(char));
    char* ptr = tmp;
    char* ptrRet = ret;
    int i = 0;
    int j = 0;
    while(*ptr && j < k) {
        if(*ptr == '\"') {
            open_mark = !open_mark;
        }
        if(*ptr == ',' && !open_mark) {
            j++;
        }
        ptr++;
    }
    while(*ptr && (open_mark || *ptr != ',')) {
        if(*ptr == '\"') {
            open_mark = !open_mark;
        }
        ret[i++] = *ptr++;
    }
    ret[i] = 0;
    return ret;
}

int main() {
    Biblioteca biblioteca;
    biblioteca.libros = NULL;
    biblioteca.cantidad = 0;



    
    int opcion;
    do {
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

        switch(opcion) {
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
