/**
 * @file utilities.h
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Header de librería con funciones útiles generales
 *        (versión adaptada para el laboratorio #6).
 * @version 3.8
 * @since 2021-08-18
 */

#ifndef __UTILITIES__
#define __UTILITIES__

/* ---------- Librerías a utilizar -------------- */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ---------- Definición de constantes ---------- */

// COLORES DE PRIMER PLANO (LETRAS)
#define _FG_COLOR_WHITE_ "\x1b[37m"

// COLORES DE SEGUNDO PLANO (FONDO)
#define _BG_COLOR_LGRAY_ "\x1b[100m"

// FORMATOS DE TEXTO
#define _FORMAT_BOLD_ "\033[1m"
#define _FORMAT_RESET_ALL_ "\033[0m"

#define _STR_MAX_LEN_ 509
#define _HOST_MAX_LEN_ 253

#define _NORM_ERR_ 0
#define _FATAL_ERR_ 1

/* ---------- Prototipado de funciones ---------- */

void show_err(char *, int);
void try_write(int, char *);

char *mk_err_msg(char *, int);

bool open_file_r(FILE **, char *);

#endif