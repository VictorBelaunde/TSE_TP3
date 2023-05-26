#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include "reader.h"
#include "compara_data.h"

char caracter_delimitador[] = ":";
char *token;
char *token2;

int main_OLD(void)
{    
    /* Crea named fifo. -1 devuelve si ya existe, por lo tanto no hace nada */
    if ( (returnCode = mknod(FIFO_NAME, S_IFIFO | 0666, 0) ) < -1  )
    {
        printf("Error creating named fifo: %d\n", returnCode);
        exit(1);
    }
    
    /* Open named fifo. Se bloquea hasta que otro proceso lo abre */
	printf("waiting for writers...\n");
	if ( (fd = open(FIFO_NAME, O_RDONLY) ) < 0 )
    {
        printf("Error opening named fifo file: %d\n", fd);
        exit(1);
    }
    
    /* open syscalls returned without error -> other process attached to named fifo */
	printf("tengo escritura\n");

    /* Loop hasta que read syscall devuelva un valor <= 0 */
	do
	{   
        /* lee el dato de laa fifo y lo agrega al buffer */
		if ((bytesRead = read(fd, inputBuffer, BUFFER_SIZE)) == -1)
        {
			perror("read");
        }
        else
		{   
			inputBuffer[bytesRead] = '\0';
            strcpy(mensaje_original, inputBuffer);
            
            if ((parser_cadena(inputBuffer,caracter_delimitador)) == 0)
            {
                perror("error parser");
            }

            //int coincide_ok = verifica_cabecera(token); *** habilitar 

		}
	}
	while (bytesRead > 0);

	return 0;
}

int parser_cadena(char cadena[], char delimitador[])
{
    int parser_ok = 1;
    token = strtok(cadena, delimitador);
    if(token != NULL){
        printf("token: %s",token);
    }
    else
    {
        token = NULL;
        return parser_ok;
    }
    return parser_ok;
}


