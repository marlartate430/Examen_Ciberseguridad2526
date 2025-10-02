#include <stdio.h>
#include <stdint.h>

#define CANTIDAD_LETRAS_ABECEDARIO 27
#define OFFSET_PRIMERA_LETRA 'A' // FIJATE BIEN SI ESTA EN MAYUSCULAS O EN MINUSCULAS
#define CANTIDAD_LETRAS_POR_LEER 100

void obtener_cantidad_letras(uint32_t* const p_array_numero_letras, const uint8_t p_tamaino_array, FILE* const p_archivo);
void imprimir_cantidad_letras(uint32_t* const p_array_numero_letras, const uint8_t p_tamaino_array);
void limpiar_array_entero_u32bit(uint32_t* const p_array_entero, const uint8_t p_tamaino_array);
void limpiar_array_entero_u8bit(uint8_t* const p_array_entero, const uint8_t p_tamaino_array);
void ordenar_array_letras(uint32_t *const p_array_numero_letras, const uint8_t p_tamaimo_array, char* const p_resultado);
void imprimir_letras_ordenadas(char* const p_array_letras, const uint8_t p_tamaino_array);
void reemplazar_letras(char* const p_array_letras, FILE* const p_archivo_cifrado,char* const p_array_reemplazo, const uint8_t p_tamaino_array);
void reemplazar_letra(char* const p_array_letras, char* const p_array_reemplazo, const char p_letra, const uint8_t p_tamaino_array);
void obtener_abecedario(char* const p_resultado);
void obtener_array_sin_reemplazo(char * const p_array, const uint8_t p_tamano);

int main(void)
{
        char* nombre_archivo = "mensaje_cifrado.txt";

        FILE* archivo_cifrado = fopen(nombre_archivo, "r");

        if ( archivo_cifrado != NULL )
        {
                uint32_t cantidad_letras[CANTIDAD_LETRAS_ABECEDARIO];
                char letras_ordenadas_por_frecuencia[CANTIDAD_LETRAS_ABECEDARIO];

                obtener_cantidad_letras(cantidad_letras, CANTIDAD_LETRAS_ABECEDARIO, archivo_cifrado);

                printf("Cantidad de veces que se repite cada letra:\n");
                imprimir_cantidad_letras(cantidad_letras, CANTIDAD_LETRAS_ABECEDARIO);
                printf("\n");

                ordenar_array_letras(cantidad_letras, CANTIDAD_LETRAS_ABECEDARIO, letras_ordenadas_por_frecuencia);

                printf("Orden de letras en funcion de la frecuencia de forma descendente:\n");
                imprimir_letras_ordenadas(letras_ordenadas_por_frecuencia, CANTIDAD_LETRAS_ABECEDARIO);
                printf("\n");

                rewind(archivo_cifrado); // Reiniciamos el puntero al archivo para poder volver a leerlo

                char abecedario[CANTIDAD_LETRAS_ABECEDARIO];

                obtener_abecedario(abecedario);

                char array_reemplazo[CANTIDAD_LETRAS_ABECEDARIO] = {
                        ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']',
                        ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']',
                        ']', ']', ']', ']', ']'
                };

                /*
                 char array_reemplazo[CANTIDAD_LETRAS_ABECEDARIO] = {
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                        'W', 'X', 'Y', 'Z', '['
                };

                La '[', que es menor que 128(signed char), representa las EINES,
                porque la letra original no entra en un char().
                */

                /*
                 * char array_reemplazo[CANTIDAD_LETRAS_ABECEDARIO];
                 * obtener_array_sin_reemplazo(array_reemplazo, CANTIDAD_LETRAS_ABECEDARIO);
                 */

                printf("Mensaje:\n");
                reemplazar_letras(abecedario, archivo_cifrado, array_reemplazo, CANTIDAD_LETRAS_ABECEDARIO);

                fclose(archivo_cifrado);
        }
        else
        {
                printf("No se puede abrir el archivo %s\n", nombre_archivo);
        }

        return 0;
}

void obtener_cantidad_letras(uint32_t* const p_array_numero_letras, const uint8_t p_tamaino_array, FILE* const p_archivo)
{
        if ( p_array_numero_letras != NULL && p_archivo != NULL )
        {
                limpiar_array_entero_u32bit(p_array_numero_letras, p_tamaino_array);

                char linea_actual[CANTIDAD_LETRAS_POR_LEER];
                char* cadena_obtenida;

                while ( ( cadena_obtenida=fgets(linea_actual, CANTIDAD_LETRAS_POR_LEER, p_archivo) ) != NULL )
                {
                        uint8_t caracter_actual; 
                        uint8_t indice = 0;

                        while ( (caracter_actual = (uint8_t)(cadena_obtenida[indice])) != '\0' )
                        {
                                if ( caracter_actual == 195 )
                                {
                                        p_array_numero_letras[p_tamaino_array-1]++;
                                }
                                else
                                {
                                        const uint8_t posicion_letra = (uint8_t)(caracter_actual - OFFSET_PRIMERA_LETRA);

                                        if ( posicion_letra < p_tamaino_array )
                                        {
                                                p_array_numero_letras[posicion_letra]++;
                                        }
                                }

                                indice++;
                        }
                }
        }
}

void imprimir_cantidad_letras(uint32_t* const p_array_numero_letras, const uint8_t p_tamaino_array)
{
        if ( p_array_numero_letras != NULL )
        {
                for ( uint8_t indice_actual = 0; indice_actual < p_tamaino_array; indice_actual++ )
                {
                        const char caracter_actual = (char)(indice_actual + OFFSET_PRIMERA_LETRA);
                        printf("%c: %u\n", caracter_actual, p_array_numero_letras[indice_actual]);
                }
        }
}

void imprimir_letras_ordenadas(char* const p_array_letras, const uint8_t p_tamaino_array)
{
        if ( p_array_letras != NULL )
        {
                const uint8_t ultimo_indice = (uint8_t)(p_tamaino_array - 1);
                for ( uint8_t indice_actual = 0; indice_actual < ultimo_indice; indice_actual++ )
                {
                        printf("%c,", p_array_letras[indice_actual]);
                }

                printf("%c\n", p_array_letras[ultimo_indice]);
        }
}

void limpiar_array_entero_u32bit(uint32_t* const p_array_entero, const uint8_t p_tamaino_array)
{
        if ( p_array_entero != NULL )
        {
                for ( uint8_t indice = 0; indice < p_tamaino_array; indice++ )
                {
                        p_array_entero[indice] = 0;
                }
        }
}

void limpiar_array_entero_u8bit(uint8_t* const p_array_entero, const uint8_t p_tamaino_array)
{
        if ( p_array_entero != NULL )
        {
                for ( uint8_t indice = 0; indice < p_tamaino_array; indice++ )
                {
                        p_array_entero[indice] = 0;
                }
        }
}

void ordenar_array_letras(uint32_t *const p_array_numero_letras, const uint8_t p_tamaino_array, char* const p_resultado)
{
        if ( p_array_numero_letras != NULL )
        {
                uint8_t indice_resultado = 0;
                uint8_t seleccionados[p_tamaino_array];
                limpiar_array_entero_u8bit(seleccionados, p_tamaino_array);

                while ( indice_resultado < p_tamaino_array )
                {
                        uint8_t indice_mayor = 0;

                        while ( seleccionados[indice_mayor] )
                        {
                                indice_mayor++;
                        }

                        uint8_t indice_actual = 0;

                        while ( indice_actual < p_tamaino_array )
                        {
                                if ( p_array_numero_letras[indice_actual] > p_array_numero_letras[indice_mayor] && !seleccionados[indice_actual] )
                                {
                                        indice_mayor = indice_actual;
                                }
                                indice_actual++;
                        }

                        p_resultado[indice_resultado] = (char)(indice_mayor + OFFSET_PRIMERA_LETRA);
                        seleccionados[indice_mayor] = 1;

                        indice_resultado++;
                }
        }
}

void reemplazar_letras(char* const p_array_letras, FILE* p_archivo_cifrado, char* const p_array_reemplazo, const uint8_t p_tamaino_array)
{
        if ( p_array_letras != NULL && p_archivo_cifrado != NULL )
        {
                char linea_obtenida[CANTIDAD_LETRAS_POR_LEER];
                char* cadena_obtenida;

                while ( ( cadena_obtenida = fgets(linea_obtenida, CANTIDAD_LETRAS_POR_LEER, p_archivo_cifrado) ) != NULL )
                {
                        uint8_t indice_cadena_obtenida = 0;
                        while ( cadena_obtenida[indice_cadena_obtenida] != '\0' )
                        {
                                // En el caso de que haya que reemplazar eines
                                if ( (uint8_t)(cadena_obtenida[indice_cadena_obtenida]) == 195) 
                                {
                                        if ( p_array_reemplazo[p_tamaino_array-1] != ']')
                                        {
                                                printf("%c", p_array_reemplazo[p_tamaino_array-1]);
                                        }
                                        else
                                        {
                                                printf("Ñ");
                                        }

                                        indice_cadena_obtenida++;
                                        /*
                                         * Las eines en C requieren de dos bytes.
                                         * Pero cadena_obtenida es un puntero a 
                                         * char(1 byte), entonces obtenemos un
                                         * caracter extraino que nos sobra, ya que
                                         * en el primer byte se lee la letra
                                         * perfectamente.
                                         */
                                }
                                else
                                {
                                        const uint8_t filtro_caracter = (uint8_t)(cadena_obtenida[indice_cadena_obtenida] - OFFSET_PRIMERA_LETRA);
                                        if ( filtro_caracter >= p_tamaino_array )
                                        {
                                                printf("%c", cadena_obtenida[indice_cadena_obtenida]);
                                        }
                                        else
                                        {
                                                reemplazar_letra(p_array_letras, p_array_reemplazo, cadena_obtenida[indice_cadena_obtenida], p_tamaino_array);
                                        }
                                }

                                indice_cadena_obtenida++;
                        }
                        printf("\n");
                }
        }
}

void obtener_abecedario(char * const p_resultado)
{
        if ( p_resultado != NULL )
        {
                for ( uint8_t indice = 0; indice < CANTIDAD_LETRAS_ABECEDARIO; indice++ )
                {
                        p_resultado[indice] = (char)(OFFSET_PRIMERA_LETRA + indice);
                }
        }
}

void obtener_array_sin_reemplazo(char * const p_array, const uint8_t p_tamano)
{
        if ( p_array != NULL )
        {
                for (uint8_t indice_actual = 0; indice_actual < p_tamano; indice_actual++ )
                {
                        p_array[indice_actual] = ']';
                }
        }
}

void reemplazar_letra(char* const p_array_letras, char* const p_array_reemplazo, const char p_letra, const uint8_t p_tamaino_array)
{
        if ( p_array_letras != NULL && p_array_reemplazo != NULL )
        {
                uint8_t indice_array_letras = 0;
                uint8_t encontrado = 0;
                uint8_t parar = 0;
                while ( indice_array_letras < p_tamaino_array && !encontrado && !parar )
                {
                        if ( p_array_letras[indice_array_letras] == p_letra )
                        {
                                if ( p_array_reemplazo[indice_array_letras] != ']' )
                                {
                                        printf("%c", p_array_reemplazo[indice_array_letras]);
                                        encontrado = !encontrado;
                                }
                                else
                                {
                                        parar = !parar;
                                }
                        }
                        else
                        {
                                indice_array_letras++;
                        }
                }

                if ( !encontrado )
                {
                        printf("%c", p_letra);
                }
        }
}
