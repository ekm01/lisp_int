lisp_int: main.o parser/parser.o
	gcc -o lisp_int main.o parser/parser.o

parser.o: parser/parser.c
	gcc -c parser/parser.c 

main.o: main.c
	gcc -c main.c

clean:
	rm *.o parser/*.o
