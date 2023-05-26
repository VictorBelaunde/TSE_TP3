#include "src/reader.h"
#include "src/save_file.h"
#include "src/writer.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void test_concatena_mensaje_consola(void)

{

    int actual = prepara_mensaje("19.9");

    UnityAssertEqualString((const char*)(("DATA:19.9")), (const char*)((mensaje_final)), (((void*)0)), (UNITY_UINT)(12));

}





void test_ingreso_temperatura_correcta(void)

{

    _Bool numero_ok = validar("10.0");

    do {if ((numero_ok)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);

}





void test_ingreso_temperatura_incorrecta(void)

{

    _Bool numero_ok = validar("hola");

    do {if (!(numero_ok)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(26)));}} while(0);

}





void test_comprueba_grabacion_archivo(void)

{

char * archivo_txt = "log.txt";

int escritura_correcta = escribe_archivo("DATA:11.1", archivo_txt);

UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((escritura_correcta)), (((void*)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}





void test_comprueba_NO_grabacion_archivo(void)

{

char * archivo_txt = ((void*)0);

int escritura_correcta = escribe_archivo("DATA:11.1", archivo_txt);

UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((escritura_correcta)), (((void*)0)), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

}





void test_parseo_correcto_con_separador(void)

{

    char cadena_sin_parsear[] = "DATA:11.1";

    char delimitado_por[] = ":";

    int parseado_ok = parser_cadena(cadena_sin_parsear, delimitado_por);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((parseado_ok)), (((void*)0)), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

}





void test_los_ingresos_llegan_al_tope(void)

{

    _Bool valida_ingresos = 0;

   for (int i = 0; i < 10; i++)

   {

        valida_ingresos = cuenta_ingresos();

   }

    do {if ((valida_ingresos)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(62)));}} while(0);

}





void test_los_ingresos_superan_el_tope(void)

{

    _Bool valida_ingresos = 0;

    int datos_tope = 11;

   for (int i = 0; i < datos_tope; i++)

   {

        valida_ingresos = cuenta_ingresos();

   }

    do {if (!(valida_ingresos)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(74)));}} while(0);

}
