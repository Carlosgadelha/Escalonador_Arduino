#include "Arduino.h"
#include "Escalonador.h"
#include "Thread.h"


Escalonador::Escalonador(unsigned long _interval): Thread(){
	cached_size = 0;

	clear();
	setInterval(_interval);

	#ifdef USE_THREAD_NAMES
		// Overrides name
		ThreadName = "ThreadController ";
		ThreadName = ThreadName + ThreadID;
	#endif
}


// Construtor, chamado na inicializacao da biblioteca/classe
void Escalonador::run(){
    bool ThreadController::add(Thread* _thread){
	// Check if the Thread already exists on the array
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL && thread[i]->ThreadID == _thread->ThreadID)
			return true;
	}

	// Find an empty slot
	for(int i = 0; i < MAX_THREADS; i++){
		if(!thread[i]){
			// Found a empty slot, now add Thread
			thread[i] = _thread;
			cached_size++;
			return true;
		}
	}

	// Array is full
	return false;
}
	// Execute este encadeamento antes
	if(_onRun != NULL)
		_onRun();

	unsigned long time = millis();
	int checks = 0;
	for(int i = 0; i < MAX_THREADS && checks < cached_size; i++){
		//Objeto existe? Está ativado? Tempo limite excedido?
		if(thread[i]){
			checks++;
			if(thread[i]->shouldRun(time)){
				thread[i]->run();
			}
		}
	}

	// ThreadController extends Thread, so we should flag as runned thread
	runned();
}
