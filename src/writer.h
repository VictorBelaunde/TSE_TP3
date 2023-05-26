#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>

#define BUFFER_SIZE_FINAL 305

char mensaje_final[BUFFER_SIZE_FINAL];

bool validar(char num[]);
int prepara_mensaje(char mensaje_consola[300]);
bool cuenta_ingresos (void);

#endif