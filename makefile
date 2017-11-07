run:
	./main

clean:
	rm -rf *.o ./main LEITOR-EXIBIDOR/*.o

bild:
	gcc -std=c99 -g -c -o LEITOR-EXIBIDOR/exibidor.o LEITOR-EXIBIDOR/exibidor.c
	gcc -std=c99 -g -c -o LEITOR-EXIBIDOR/leitor.o LEITOR-EXIBIDOR/leitor.c
	gcc -std=c99 -g -c -o LEITOR-EXIBIDOR/funcoes.o LEITOR-EXIBIDOR/funcoes.c
	gcc -std=c99 -g -o main main.c LEITOR-EXIBIDOR/exibidor.o LEITOR-EXIBIDOR/leitor.o LEITOR-EXIBIDOR/funcoes.o

debug:
	gdb ./main

all:
	make clean
	make bild

dall:
	make clean
	make bild