lisp_int: main.o parser.o
	gcc -o lisp_int main.o parser.o

parser.o: parser.c
	gcc -c parser.c 

main.o: main.c
	gcc -c main.c

clean:
	rm *.o
