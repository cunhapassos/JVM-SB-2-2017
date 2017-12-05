OBJ = exibidor.o leitor.o funcoes.o virtualMachine.o pilhas_listas.o instrucoes.o decoder.o
DEP = exibidor.h leitor.h funcoes.h virtualMachine.h pilhas_listas.h instrucoes.h configuracao.h decoder.h
CC = gcc
CFLAGS = -std=c99 -g
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer -static-libasan

run:
	./main

clean:
	rm -rf *.o ./main *.o

bild: $(OBJ)
	$(CC) $(CFLAGS) -o main main.c $(OBJ) -I ../JVM-SB-2-2017 -lm

../JVM-SB-2-2017/%.o: %.c
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
	$(CC) $(CFLAGS) -o main main.c $(OBJ) -I ../JVM-SB-2-2017 -lm $(ASANFLAGS)

asan: 
	make clean
	make asan_comp