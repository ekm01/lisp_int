lisp_int: main.o parser/parser.o evaluator/evaluator.o
	gcc -o lisp_int main.o parser/parser.o evaluator/evaluator.o

parser.o: parser/parser.c
	gcc -c parser/parser.c 

evaluator.o: evaluator/evaluator.c
	gcc -c evaluator/evaluator.c

main.o: main.c
	gcc -c main.c

clean:
	rm *.o parser/*.o evaluator/*.o
