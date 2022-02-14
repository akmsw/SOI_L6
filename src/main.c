/**
 * @file main.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Programa principal del laboratorio #6 de Sistemas Operativos I.
 * @version 1.0
 * @since 2022-01-03
 */

/* ---------- Librerías a utilizar -------------- */

#include "include/utilities.h"
#include <sys/mman.h>
#include <sys/stat.h>

/* ---------- Estructuras útiles ---------------- */

/**
 * @brief Estructura que almacena información sobre lecturas
 *        hechas por el radar meteorológico RMA1.
 */
struct data_str
{
//  DATA TYPE                   NAME                DESCRIPTION                                     SIZE [B]
    unsigned short int          version;        //  Versión del dato n1.                            2
    unsigned short int          drxVersion;     //  Versión del DRX que generó el dato n1.          2
    const int                   RESERVED_1;     //  -.                                              4
    double                      initCW;         //  Inicio de la ventana de recepción, en segundos. 8
    float                       azimuth;        //  Apuntamiento acimut en grados.                  4
    float                       elevation;      //  Apuntamiento elevación en grados.               4
    unsigned short int          idVolumen;      //  Identificador de volumen.                       2
    unsigned short int          idBarrido;      //  Identificador de barrido.                       2
    unsigned short int          idCnjunto;      //  Identificador de conjunto.                      2
    unsigned short int          idGrupo;        //  Identificador de grupo.                         2
    unsigned short int          idPulso;        //  Identificador de pulso.                         2
    bool                        iniBarrido;     //  Bandera del primer pulso de barrido.            1
    bool                        finBarrido;     //  Bandera del último pulso de barrido.            1
    bool                        finGrupo;       //  Bandera del último pulso del grupo.             1
    bool                        inhibido;       //  Bandera de transmisión inhibida.                1
    unsigned short int          validSamples;   //  Cantidad de muestras complejas válidas.         2
    unsigned short int          nroAdquisicion; //  Contador de adquisiciones.                      2
    const unsigned short int    RESERVED_2;     //  -.                                              2
    unsigned int                nroSecuencia;   //  Número de secuencia.                            4
    unsigned long int           readTime_high;  //  Campo alto de la marca de tiempo.               8
    unsigned long int           readTime_low;   //  Campo bajo de la marca de tiempo.               8
    const unsigned long int     RESERVED_3[8];  //  -.                                              64
    //  TOTAL STRUCT SIZE [B]: 128
};

/**
 * @brief Estructura que contiene tantas instancias
 *        de estructuras de datos como se hayan hayado
 *        en el archivo abierto.
 */
struct block_str
{
    struct data_str *d1;
    struct data_str *d2;
    struct data_str *d3;
};

/**
 * @brief Función principal del programa.
 *
 * @details Abrimos el archivo de datos en modo lectura,
 *          obtenemos su número de file descriptor, y
 *          creamos las estructuras necesarias para
 *          recopilar la información necesaria.
 *          Se determina la cantidad de estructuras
 *          contenidas en el archivo, se mapea a memoria
 *          RAM los datos obtenidos, se muestran los
 *          campos 'validSamples' de cada estructura
 *          obtenida y finalmente se promedian los
 *          valores obtenidos de estos campos.
 *          Antes de finalizar el programa se libera
 *          la memoria reservada.
 *
 * @param argc Cantidad de argumentos recibidos.
 * @param argv Vector con los argumentos recibidos.
 *
 * @returns Si la ejecución del programa fue exitosa
 */
int main(int argc, char **argv)
{
    FILE *raw_data = NULL;

    if (!open_file_r(&raw_data, "./rawdata/datos"))
        show_err("Could not open such file.", _FATAL_ERR_);

    int rd_fd = fileno(raw_data);

    if (rd_fd == -1)
        show_err("Could not get file descriptor number.", _FATAL_ERR_);

    struct stat sb;

    /* ---------- Stats -------------- */

    if (fstat(rd_fd, &sb) == -1)
        show_err("Could not get the file size.", _FATAL_ERR_);

    struct data_str *data;
    struct block_str block;

    int avg_samples = 0;
    int f_size = sb.st_size;
    int data_str_size = sizeof(struct data_str);
    int frames_amount = (f_size / sizeof(struct data_str));
    int valid_samples[3];

    fprintf(stdout, "File size: %d [B].\nStruct size: %d [B].\nTotal amount of data frames contained: %d.\n",
            f_size, data_str_size, frames_amount);

    /* ---------- Memory mapping ----- */

    data = mmap(NULL, f_size, PROT_READ, MAP_PRIVATE, rd_fd, 0);

    block.d1 = data;
    block.d2 = data + 1;
    block.d3 = data + 2;

    valid_samples[0] = block.d1->validSamples;
    valid_samples[1] = block.d2->validSamples;
    valid_samples[2] = block.d3->validSamples;

    for (int i = 0; i < frames_amount; i++)
        avg_samples += valid_samples[i];

    avg_samples /= 3;

    for (int i = 0; i < frames_amount; i++)
        fprintf(stdout, "valid_samples[%d]: %d\n", i, valid_samples[i]);

    fprintf(stdout, "valid_samples average: %d\n", avg_samples);

    fclose(raw_data);

    munmap(data, f_size);

    return 0;
}