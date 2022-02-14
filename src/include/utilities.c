/**
 * @file utilities.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones útiles generales
 *        (versión adaptada para el laboratorio #6).
 * @version 3.8
 * @since 2021-08-18
 */

#include "utilities.h"

/**
 * @brief Esta función muestra el mensje solicitado en pantalla
 *        y termina la ejecución del programa si es necesario.
 *
 * @param msg Mensaje a mostrar.
 * @param err_type Gravedad del error.
 */
void show_err(char *msg, int err_type)
{
    try_write(STDERR_FILENO, mk_err_msg(msg, err_type));

    if (err_type == _FATAL_ERR_)
        exit(EXIT_FAILURE);
}

/**
 * @brief Esta función se encarga de intentar escribir un
 *        mensaje en pantalla de manera thread-safe.
 *        Si no se logra, se imprime un mensaje de error
 *        y se aborta el programa.
 *
 * @param stdx Stream en el que se escribirá el mensaje.
 * @param msg Mensaje a mostrar.
 */
void try_write(int stdx, char *msg)
{
    if (write(stdx, msg, strlen(msg)) == -1)
    {
        fprintf(stderr, "\nFatal error on write inscruction --- ABORTING\n");

        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Esta función se encarga de armar un mensaje de error.
 *
 * @details Se almacena memoria inicializada con ceros para evitar
 *          error con strcat. Se sobrescribe con el formato
 *          correspondiente para un mensaje de error y el mensaje
 *          que indica la falla, recibido por parámetro.
 *
 * @param msg Mensaje de error a mostrar.
 * @param err_type Gravedad del error.
 *
 * @returns El mensaje de error formateado con el texto recibido por parámetro.
 */
char *mk_err_msg(char *msg, int err_type)
{
    char *err_msg;

    if (err_type == _FATAL_ERR_)
    {
        // + 8 por "\nERROR ", + 7 por "[FATAL]", + 3 por " > " y + 4 por "\n\n"
        err_msg = (char *)calloc(strlen(_FORMAT_BOLD_) + strlen(_FG_COLOR_WHITE_) + (strlen(_FORMAT_RESET_ALL_) * 2) +
                                 strlen(msg) + sizeof(NULL) + (sizeof(char) * 22), sizeof(char));

        if (!err_msg)
        {
            fprintf(stderr, "\nFatal calloc error --- ABORTING\n");

            exit(EXIT_FAILURE);
        }

        strcat(err_msg, _FORMAT_BOLD_);
        strcat(err_msg, _FG_COLOR_WHITE_);
        strcat(err_msg, "\nERROR ");
        strcat(err_msg, _BG_COLOR_LGRAY_);
        strcat(err_msg, "[FATAL]");
    }
    else
    {
        // + 7 por "\nERROR", + 3 por " : " y + 4 por "\n\n"
        err_msg = (char *)calloc(strlen(_FORMAT_BOLD_) + (strlen(_FORMAT_RESET_ALL_) * 2) +
                                 strlen(msg) + sizeof(NULL) + 14, sizeof(char));

        if (!err_msg)
        {
            fprintf(stderr, "\nFatal calloc error --- ABORTING\n");

            exit(EXIT_FAILURE);
        }

        strcat(err_msg, _FORMAT_BOLD_);
        strcat(err_msg, _FG_COLOR_WHITE_);
        strcat(err_msg, "\nERROR");
    }

    strcat(err_msg, _FORMAT_RESET_ALL_);
    strcat(err_msg, _FG_COLOR_WHITE_);
    strcat(err_msg, " > ");
    strcat(err_msg, msg);
    strcat(err_msg, _FORMAT_RESET_ALL_);
    strcat(err_msg, "\n\n");

    return err_msg;
}

/**
 * @brief Esta función se encarga de abrir el archivo que queremos
 *        en modo lectura.
 *
 * @param file Archivo con el que se trabajará.
 * @param dir Directorio del archivo que queremos abrir.
 *
 * @returns Si se pudo abrir exitosamente el archivo.
 */
bool open_file_r(FILE **file, char *dir)
{
    *file = fopen(dir, "r");

    // Si hubo un error al leer el archivo, mostramos un mensaje de error y salimos del programa
    if (!*file)
    {
        char err_msg[_STR_MAX_LEN_];

        if (sprintf(err_msg, "Failed attempting to open file: %s", dir) < 0)
            show_err("Could not make error message", _FATAL_ERR_);

        show_err(err_msg, _NORM_ERR_);

        return false;
    }

    return true;
}