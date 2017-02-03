all: Matsui_algo

Matsui_algo:	Matsui_algo_main.o Matsui_algo_fun.o
	gcc Matsui_algo_main.c Matsui_algo_fun.c -o Matsui_algo

Matsui_algo_main.o:	Matsui_algo_main.c
	gcc -c Matsui_algo_main.c

Matsui_algo_fun.o:	Matsui_algo_fun.c
	gcc -c Matsui_algo_fun.c

clean:	
	rm -rf *o Matsui_algo 
