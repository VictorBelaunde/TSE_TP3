#include <stdio.h>
#include <string.h>
char parser_cadena(char cadena[], char delimitador[]);
char *token;
char cadena[] = "DATA:1";
char delimitador[] = ":";
int main(void)
{
    token = strtok(cadena, delimitador);
    if(token != NULL){
        printf("token: %s",token);
    }
    else
    {
        token = NULL;
    }
}