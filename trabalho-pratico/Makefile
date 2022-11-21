#$(CC) = gcc
#
#
#compile:
#		 $(CC) src/main.c  src/parser.c src/drivers.c src/rides.c src/users.c -o programa-principal
#
#Clean:
#		rm *.o programa-principal

$(CC) = gcc
PNTC=$(wildcard src/* .c)
PNTH=$(wildcard Include/* .h)
FLAGS=-Wall -IInclude -Wextra

programa-principal:
					$(CC) $(FLAGS) -o programa-principal $(PNTC) $(PNTH)

#testes:

clean:
		rm *.o programa-principal

