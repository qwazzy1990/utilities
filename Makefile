

CC = gcc
CFLAGS = -Wall -std=c11 -g -pedantic


program: makeprogram runprogram

makeprogram:
	$(CC) $(CFLAGS) -Iinclude src/utilities.c src/Numbers.c src/DynamicString.c test/testmain.c -o bin/prog

runprogram:
	./bin/prog

test: makeprogram runtest

runtest: makeprogram
	valgrind -v --leak-check=full ./bin/prog

clean:
	rm bin/prog
