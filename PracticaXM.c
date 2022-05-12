/*------------------------------------------------------------------------
   PracticaXM.c   Programa que genera un archivo de prueba con bytes
                  en valores de 0 a 255 y de regreso.
  ------------------------------------------------------------------------
   Parametros:  1 - Archivo de salida.
		          2 - Tamaño del archivo (en bytes).
                3 - Numero de veces que repite cada caracter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SI         (1==1)
#define NO         (1!=1)

int main (int argc,
          char *argv[])
   {
   FILE *a_salida;
   size_t long_sal,
          long_max,
          max_repeticiones,
          num_repeticiones;
	unsigned char ch;
   int aumenta;

	/* Se controla la existencia de los parametros */
	if (argc != 4)
		{
		printf("Número incorrecto de parámetros\n");
      printf("Formato: PracticaXM <salida> <max_size> <repeticiones>\n\n");
      exit (1);
		};

   /* Se obtiene la dimension del archivo */
	if (!sscanf(argv[2], "%u", &long_max))
		{
		printf("Error al decodificar el tamaño del archivo: %s\n", argv[2]);
      exit (1);
		};

   /* Se obtiene el n£mero de repeticiones */
	if (!sscanf(argv[3], "%u", &max_repeticiones))
		{
		printf("Error al decodificar el número de repeticiones: %s\n", argv[3]);
      exit (1);
		};

	/* Se abre el archivo de salida*/
	if ((a_salida = fopen(argv[1], "wb")) == NULL)
		{
		printf("Error al abrir el archivo de salida: %s\n", argv[1]);
      exit (1);
		};


   for (long_sal = 0, ch = 0, aumenta = SI, num_repeticiones = 0;
        long_sal < long_max;
        ++long_sal)
      {
      putc(ch, a_salida);
      ++num_repeticiones;
      if (num_repeticiones >= max_repeticiones)
         {
         if (aumenta)
            if (ch < 255)
               ++ch;
               else
               {
               --ch;
               aumenta = NO;
               }
            else
            if (ch > 0)
               --ch;
               else
               {
               ++ch;
               aumenta = SI;
               };
         num_repeticiones = 0;
         };
      };


	fclose(a_salida);

   exit (0);
   return 0;
	}