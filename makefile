# author: Bonino, Francisco Ignacio.
# version: 1.0
# since: 2022-01-14

# Flags a utilizar.
CC = gcc
CFLAGS = -Wall -Werror -pedantic
SLIBF = ar rcs

all: mmap # En caso de ejecutar 'make' sin argumento, se aplica el target indicado.

# Directorios donde se guardarán los archivos.
build_folders:
	mkdir -p ./obj ./bin ./slib

# Librería estática propia: utilities.
lib_utilities.a: utilities.o
	$(SLIBF) slib/lib_utilities.a obj/utilities.o

utilities.o: src/include/utilities.c src/include/utilities.h
	$(CC) $(CFLAGS) -c src/include/utilities.c -o obj/utilities.o

#Ejecutable final
mmap: build_folders mmap.o lib_utilities.a
	$(CC) $(CFLAGS) -o bin/mmap obj/mmap.o slib/lib_utilities.a

mmap.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o obj/mmap.o

# Limpieza de archivos y carpetas creados
clean:
	rm -r ./bin
	rm -r ./obj
	rm -r ./slib