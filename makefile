OBJ = LEITOR-EXIBIDOR/exibidor.o LEITOR-EXIBIDOR/leitor.o LEITOR-EXIBIDOR/funcoes.o LEITOR-EXIBIDOR/virtualMachine.o LEITOR-EXIBIDOR/pilhas_listas.o
run:
	./main

clean:
	rm -rf *.o ./main LEITOR-EXIBIDOR/*.o

bild: $(OBJ)
	gcc -std=c99 -g -o main main.c $(OBJ)

LEITOR-EXIBIDOR/%.o: %.c
	gcc -std=c99 -g -c -o $@ $<R-EXIBIDOR/funcoes.o LEITOR-EXIBIDOR/funcoes.c

debug:
	gdb ./main

all:
	make clean
	make bild

dall:
	make clean
	make bild