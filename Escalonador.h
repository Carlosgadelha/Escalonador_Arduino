/*
 	Escalonador.h - Escalona uma lista de threads em métodos diferentes
	
	Criado com base no Código de Ivan Seidel Gomes, March, 2013.
	
*/

#ifndef Escalonador_h
#define Escalonador_h

#include "Thread.h"
#include "inttypes.h"

#define MAX_THREADS		15

class Escalonador: public Thread{
protected:
	Thread* thread[MAX_THREADS];
	int cached_size;
	int bt[MAX_THREADS];//Vetor para armazenar os tempos dos processos
	int prioridade[MAX_THREADS];//prioridade dos processos
public:
	Escalonador(unsigned long _interval = 0);

	// run() Método que executa o escalonamento de acordo com o i passado
	void run(int i);

	// Adiciona a thread na primeira posição válida de um vetor e armazena seu tempo de execução e prioridade
	// Retorna um boleano para indicar se a thread pode ser adicionada ou não
	bool add(Thread* _thread, int tempo, int p);//'tempo' é o tempo de execução e p é a prioridade
		

	// Remove todas as threads
	void clear();
		

};

#endif
