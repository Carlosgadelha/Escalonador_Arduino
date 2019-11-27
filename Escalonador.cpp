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

/*
	ThreadController run() (cool stuf)
*/



void Escalonador::pilha(){
	
	unsigned long time = millis();
	
	int checks = cached_size;
	while( checks >= 0){

		if(thread[checks]){
			checks--;
			if(thread[checks]->shouldRun(time)){
			    thread[checks]->run();
		}
		
}
}
	runned();

}
void Escalonador::rr(){
	int quantum = 1000;
	
	unsigned long time = millis();
	
	int checks = 0;
	for(int i = cached_size; i >= 0; i--){
		if(thread[i]){
			checks++;
			if(thread[i]->shouldRun(time) && time%1000 != 0){
			    thread[i]->run();
		}
		
}
}
}

void Escalonador::run(){
	// Run this thread before
	if(_onRun != NULL)
		_onRun();

	unsigned long time = millis();
	int checks = 1;
	for(int i = 1; i <= MAX_THREADS && checks <= cached_size; i++){
		// Object exists? Is enabled? Timeout exceeded?
		if(thread[i]){
			checks++;
			if(thread[i]->shouldRun(time)){
				if(i%2 == 1){
					thread[i]->run();
			    }else{
					if(i < cached_size)
					thread[i+1]->run();
				}
				
			}
		}
	}

	// ThreadController extends Thread, so we should flag as runned thread
	runned();
}


/*
	List controller (boring part)
*/
bool Escalonador::add(Thread* _thread){
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

void Escalonador::remove(int id){
	// Find Threads with the id, and removes
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i]->ThreadID == id){
			thread[i] = NULL;
			cached_size--;
			return;
		}
	}
}

void Escalonador::remove(Thread* _thread){
	remove(_thread->ThreadID);
}

void Escalonador::clear(){
	for(int i = 0; i < MAX_THREADS; i++){
		thread[i] = NULL;
	}
	cached_size = 0;
}

int Escalonador::size(bool cached){
	if(cached)
		return cached_size;

	int size = 0;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i])
			size++;
	}
	cached_size = size;

	return cached_size;
}

Thread* Escalonador::get(int index){
	int pos = -1;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL){
			pos++;

			if(pos == index)
				return thread[i];
		}
	}

	return NULL;
}
