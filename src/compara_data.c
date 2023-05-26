#include <string.h>
#include <stdio.h>
#include "compara_data.h"
#include "save_file.c"
#include "reader.h"

int verifica_cabecera(char *dato_verifica)
{
    int grabo = 1;
    if (strcmp(palabra1, dato_verifica)== 0)
    {
        char nombreArchivo[] = ARCHIVO_SIGN;
        if (escribe_archivo(mensaje_original, nombreArchivo) == 0)
        {
            printf("grabo %s\n", palabra1);
        }
    } 
    else if (strcmp(palabra2, dato_verifica)== 0)
    {
        char nombreArchivo[] = ARCHIVO_DATA;
        if (escribe_archivo(mensaje_original, nombreArchivo) == 0)
        {
            printf("grabo %s\n", palabra2);
        }
    }
    else
    {
        perror("error guardado\n");
        grabo = 0;
    }
    return grabo;
}

