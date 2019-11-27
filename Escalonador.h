#ifndef Escalonador_h
#define Escalonador_h

#include "Thread.h"
#include "inttypes.h"

#define MAX_THREADS		15

 class Escalonador: public Thread{
    protected:
	Thread* thread[MAX_THREADS];
	int cached_size;
    public:
	Escalonador(unsigned long _interval = 0);

		// O método run () é substituído
	void run();
	void rr();
	void pilha();

	// Adiciona um thread no primeiro slot disponível (remova primeiro)
	// Retorna se o Thread pode ser adicionado ou não
	bool add(Thread* _thread);


	// remova o thread (dado o Thread * ou ThreadID)
	void remove(int _id);
	void remove(Thread* _thread);

	// Remove todos as threads
	void clear();

	// Retornar a quantidade de Threads
	int size(bool cached = true);

	// Retorne o I Thread na matriz
	// Retorna NULL se nenhum encontrado
	Thread* get(int index);
 };

#endif
