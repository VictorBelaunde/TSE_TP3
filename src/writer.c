#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>
#include "writer.h"


#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 300
#define MENSAJE_SIGN1 "SIGN:1"
#define MENSAJE_SIGN2 "SIGN:2"
#define INGRESOS_ACEPTADOS 10

char outBuffer[BUFFER_SIZE];

uint32_t bytesEscritos;
int32_t returnCode;
int32_t fd; //FileDescriptor del named fifo
int ingresos = 0;



void handler_signal1(int num_signal)
{
    //como no puedo asignar directamente una palabra a la matriz tengo que usar la funcion de copiar strcpy
    strcpy(mensaje_final, MENSAJE_SIGN1);
    
    //Escribe en el buffer del fifo. Strlen - 1 para evitar enviar el char \n 
    if ((bytesEscritos = write(fd, mensaje_final, strlen(mensaje_final))) == -1)
        {
			perror("write");
        }
    else
        {
			printf("writer: escribió %d bytes\n", bytesEscritos);
        }
}

void handler_signal2(int num_signal)
{
    //como no puedo asignar directamente una palabra a la matriz tengo que usar la funcion de copiar strcpy
    strcpy(mensaje_final, MENSAJE_SIGN2);
    
    //Escribe en el buffer del fifo. Strlen - 1 para evitar enviar el char \n 
    if ((bytesEscritos = write(fd, mensaje_final, strlen(mensaje_final))) == -1)
    {
		perror("write");
    }
    else
    {
		printf("writer: escribió %d bytes\n", bytesEscritos);
    }
}

/*
El programa comunicará dos eventos por medio de un named fifo.
El proceso Writer podrá recibir texto por la consola y signals.
*/
int main_OLDD(void)
{
    //para enviar un signal desde comando ejecutar "kill -sn pid" sn=SIGUSR1 o SIGUSR2
    signal(SIGUSR1, &handler_signal1);
    signal(SIGUSR2, &handler_signal2);

    /* Crea el named fifo. Si -1 significa que ya existe, por lo tanto no hay acción */
    if ( (returnCode = mknod(FIFO_NAME, S_IFIFO | 0666, 0) ) < -1 ) //tambien el código puede ser 0644
    {
        printf("Error creacion named fifo: %d\n", returnCode);
        exit(1);
    }

	printf("waiting for reader...\n");
    /* Abre named fifo y se Bloquea hasta que otro proceso lo abre */
	if ( (fd = open(FIFO_NAME, O_WRONLY) ) < 0 )
    {
        printf("Error de apertura archivo named fifo : %d\n", fd);
        exit(1);
    }
    
    /* Se abre la llamada y retorna sin error -> otro proceso se unió al named fifo*/
	printf("Se conectó un reader. Escribir mensaje...\n");

	while (1)
	{
        // Obtener un texto de la consola 
		fgets(outBuffer, BUFFER_SIZE, stdin);

        //Supervisa que no superen los 10 datos ingresados
        if ((cuenta_ingresos()) == false)
        {
            printf("Fin ingresos\n");
            break;
        }

        if ((validar(outBuffer)) == false)
        {
            printf("Ingrese numero valido\n");
        }
        
        //funcion para adicionar DATA listar para fifo
        if ((prepara_mensaje(outBuffer)) == 0)
        {
            perror("completa mensaje");
        }
        else 
        {
            printf("mensaje preparado OK \n");
        }

        //Escribe en el buffer del fifo. Strlen - 1 para evitar enviar el char \n 
        if ((bytesEscritos = write(fd, mensaje_final, strlen(mensaje_final)-1)) == -1)
        {
			perror("write");
        }
        else
        {
			printf("writer: escribió %d bytes\n", bytesEscritos);
        }
	}
	return 0;
}

int prepara_mensaje(char mensaje_consola[300])
{   
    //sprintf: funcion que agrega una palabra a un char
    sprintf(mensaje_final, "DATA:%s", mensaje_consola);

    return 1;
}

bool validar(char num[])
{
    int valido = true;
    for (int i = 0; i < strlen(num); i++)
    {
        if(!isdigit(num[i]) ) 
        {
            if (num[i] != '.')
            {
                valido = false;
                return valido;
            }
        }
    }
    return valido;
}

bool cuenta_ingresos (void)
{   
    bool ingresos_ok = true;
    ingresos++;
    if (ingresos > INGRESOS_ACEPTADOS)
    {
        ingresos_ok = false;
    }
    return ingresos_ok;
}

