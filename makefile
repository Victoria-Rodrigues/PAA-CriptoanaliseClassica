all:
	gcc main.c -o run sources/analiseFrequencia.c sources/criptografado.c
	./run