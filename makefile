OBJ = LEITOR-EXIBIDOR/exibidor.o LEITOR-EXIBIDOR/leitor.o LEITOR-EXIBIDOR/funcoes.o LEITOR-EXIBIDOR/virtualMachine.o LEITOR-EXIBIDOR/pilhas_listas.o LEITOR-EXIBIDOR/instrucoes.o LEITOR-EXIBIDOR/decoder.o
DEP = LEITOR-EXIBIDOR/exibidor.h LEITOR-EXIBIDOR/leitor.h LEITOR-EXIBIDOR/funcoes.h LEITOR-EXIBIDOR/virtualMachine.h LEITOR-EXIBIDOR/pilhas_listas.h LEITOR-EXIBIDOR/instrucoes.h LEITOR-EXIBIDOR/configuracao.h LEITOR-EXIBIDOR/decoder.h
CC = gcc
CFLAGS = -std=c99 -g
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer -static-libasan

run:
	./main

clean:
	rm -rf *.o ./main LEITOR-EXIBIDOR/*.o

bild: $(OBJ)
	$(CC) $(CFLAGS) -o main main.c $(OBJ) -I LEITOR-EXIBIDOR -lm

LEITOR-EXIBIDOR/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

debug:
	gdb ./main

all:
	make clean
	make bild

dall:
	make clean
	make bild

asan_comp: $(OBJ)
	$(CC) $(CFLAGS) -o main main.c $(OBJ) -I LEITOR-EXIBIDOR -lm $(ASANFLAGS)

asan: 
	make clean
	make asan_comp