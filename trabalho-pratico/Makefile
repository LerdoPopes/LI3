##$(CC) = gcc
##
##
##compile:
##		 $(CC) src/main.c  src/parser.c src/drivers.c src/rides.c src/users.c -o programa-principal
##
##Clean:
###		rm *.o programa-principal
##
#
#$(CC) = gcc
#PNTC=$(wildcard src/* .c)
#PNTH=$(wildcard Include/* .h)
#FLAGS= -IInclude `pkg-config --cflags glib-2.0`
#
#compile: Resultados
#	$(CC) $(FLAGS) -g -o programa-principal $(PNTC) $(PNTH) `pkg-config --libs glib-2.0` -lncurses
#
##testes:
#Resultados:
#	mkdir -p $@
#
#clean:
#	rm -rf *.o programa-principal Resultados

$(CC) = gcc
PNTC=$(wildcard src/* .c)
PNTH=$(wildcard Include/* .h)
FLAGS= -IInclude `pkg-config --cflags glib-2.0`
DIREC:=objetos/
PNTO=$(PNTH:src/%.c=$(DIREC)%.o)

coiso: $(PNTO) Resultados teste
	$(CC) $(PNTC) $(FLAGS) -lncurses -g -o programa-principal `pkg-config --libs glib-2.0` -lncurses

compile: coiso Resultados
	./programa-principal

teste: Resultados
	$(CC) testmode/testes.c src/dates.c src/drivers.c src/erros.c src/parser.c src/queries.c src/rides.c src/statistics.c users.c userinterface.c -lncurses -g -o programa-teste `pkg-config --libs glib-2.0` -lncurses

objetos:
	mkdir -p $@

Resultados:
	mkdir -p $@

$(DIREC)%.o: src/.c | objetos
	$(CC) -o "$@" -c "$<"

clean:
	rm -rf $(DIREC) programa-principal Resultados teste
