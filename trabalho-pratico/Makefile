#$(CC) = gcc
#
#
#compile:
#		 $(CC) src/main.c  src/parser.c src/drivers.c src/rides.c src/users.c -o programa-principal
#
#Clean:
##		rm *.o programa-principal
#

$(CC) = gcc
PNTC=$(wildcard src/* .c)
PNTH=$(wildcard Include/* .h)
FLAGS=-Wall -IInclude `pkg-config --cflags glib-2.0`

compile: Resultados
		$(CC) $(FLAGS) -o programa-principal $(PNTC) $(PNTH) `pkg-config --cflags glib-2.0`

#testes:
Resultados:
		mkdir -p $@

clean:
		rm -rf *.o programa-principal Resultados