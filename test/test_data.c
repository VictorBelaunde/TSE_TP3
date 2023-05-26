#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include "writer.h"
#include "save_file.h"
#include "reader.h"

//1. El proceso debe escribir "19.9" de ingreso y concatenar con el formato DATA:XX.X, verificar concatenación.
void test_concatena_mensaje_consola(void)
{   
    int actual = prepara_mensaje("19.9");
    TEST_ASSERT_EQUAL_STRING("DATA:19.9", mensaje_final);
}

//2. el proceso write.c debe permitir ingresar una temperatura numerica 10.0 y verificar que valida numerico
void test_ingreso_temperatura_correcta(void)
{
    bool numero_ok = validar("10.0");
    TEST_ASSERT_TRUE(numero_ok);
}

//3. el proceso write.c debe ingresar una temperatura no valida "hola" y verificar que valida no numerico
void test_ingreso_temperatura_incorrecta(void)
{
    bool numero_ok = validar("hola");
    TEST_ASSERT_FALSE(numero_ok);
}

//4. Se carga un dato con el formato homologado "DATA:11.1" y el archivo "log.txt" y  verificar que se graba correctamente
void test_comprueba_grabacion_archivo(void)
{
char * archivo_txt = "log.txt";
int escritura_correcta = escribe_archivo("DATA:11.1", archivo_txt);
TEST_ASSERT_EQUAL_INT(0, escritura_correcta);
}

//5. Se carga un dato con el formato homologado "DATA:11.1" y el archivo NULL y  verificar que no se graba archivo
void test_comprueba_NO_grabacion_archivo(void)
{
char * archivo_txt = NULL;
int escritura_correcta = escribe_archivo("DATA:11.1", archivo_txt);
TEST_ASSERT_EQUAL_INT(1, escritura_correcta);
}

//6. Comprobar parseo de dato "DATA:11.1" con el separador ":" y verificar que es correcto
void test_parseo_correcto_con_separador(void)
{
    char cadena_sin_parsear[] = "DATA:11.1";
    char delimitado_por[] = ":";
    int parseado_ok = parser_cadena(cadena_sin_parsear, delimitado_por);
    TEST_ASSERT_EQUAL_INT(1, parseado_ok);
}

//7. Ingresar 10 datos y luego verificar que permita continuar
void test_los_ingresos_llegan_al_tope(void)
{
    bool valida_ingresos = 0;
   for (int i = 0; i < 10; i++)
   {
        valida_ingresos = cuenta_ingresos();
   }
    TEST_ASSERT_TRUE(valida_ingresos);
}

//8. Ingresar 11 datos y luego verificar que NO permita continuar
void test_los_ingresos_superan_el_tope(void)
{
    bool valida_ingresos = 0;
    int datos_tope = 11;
   for (int i = 0; i < datos_tope; i++)
   {
        valida_ingresos = cuenta_ingresos();
   }
    TEST_ASSERT_FALSE(valida_ingresos);
}