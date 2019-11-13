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

	void run();
    //void fila();
    bool add(Thread* _thread);

 };

#endif
