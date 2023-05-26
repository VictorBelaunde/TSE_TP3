
#include <stdio.h>
#include "save_file.h"
//#include "reader.h"


int escribe_archivo(char dato_ingreso[BUFFER_DATO], char *nombreArchivo)
{
    /*
     * Podemos poner la ruta completa o el nombre, si ponemos
     * solo el nombre entonces se refiere al directorio en donde
     * se ejecuta el programa
     */
    char *modo = "a";// w es para sobrescribir, a+ es para añadir al existente
    FILE *archivo = fopen(nombreArchivo, modo);
    // Si por alguna razón el archivo no fue abierto, salimos inmediatamente
    if (archivo == NULL) {
        printf("Error abriendo archivo %s", nombreArchivo);
        return 1;
    }
    /*
     * Escribir el contenido usando fprintf.
     * */
    fprintf(archivo, "%s\n", dato_ingreso);
   
    // Al final, cerramos el archivo
    fclose(archivo);
    puts("Contenido escrito correctamente"); //funcion similar a printf pero solo para caracteres
    return 0;
}