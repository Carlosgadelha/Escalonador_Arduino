/*
 	Escalonador.h - Escalona uma lista de threads em m�todos diferentes
	
	Criado com base no C�digo de Ivan Seidel Gomes, March, 2013.
	
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

	// run() M�todo que executa o escalonamento de acordo com o i passado
	void run(int i);

	// Adiciona a thread na primeira posi��o v�lida de um vetor e armazena seu tempo de execu��o e prioridade
	// Retorna um boleano para indicar se a thread pode ser adicionada ou n�o
	bool add(Thread* _thread, int tempo, int p);//'tempo' � o tempo de execu��o e p � a prioridade
		

	// Remove todas as threads
	void clear();
		

};

#endif
