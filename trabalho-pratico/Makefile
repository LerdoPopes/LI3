$(CC) = gcc

compile:
		 $(CC) `pkg-config --cflags glib-2.0` src/main.c  src/parser.c src/drivers.c src/rides.c src/users.c src/dates.c -o programa-principal `pkg-config --libs glib-2.0`

Clean:
		rm *.o programa-principal