#include "Thread.h"
#include "Escalonador.h"
#include "time.h"

Escalonador::Escalonador(unsigned long _interval): Thread(){
	cached_size = 0;

	clear();
	setInterval(_interval);

	#ifdef USE_THREAD_NAMES
		// Overrides name
		ThreadName = "Escalonador ";
		ThreadName = ThreadName + ThreadID;
	#endif
}

void Escalonador::run(int t){//irá executar os sensores de acordo com o escalonador escolhido
	// Run this thread before
	if(_onRun != NULL)
		_onRun();

	unsigned long time1 = millis();		
		int checks;
		if(t == 1){//Executa em formato de fila
			checks = 0;
			for(int i = 0; i < MAX_THREADS && checks < cached_size; i++){
				// Object exists? Is enabled? Timeout exceeded?
				//unsigned long time2 = millis();		
				if(thread[i]){
					checks++;
					if(thread[i]->shouldRun(time1)){														
						thread[i]->run();
					}
				}			
			}
		}
		
		if(t == 2){//Executa por prioridade
			checks = 0;
			int n = cached_size, i, remain, t2, flag = 0;			
			int p[n];
			int at[n];//tempo de chegada
			
			for(i=0; i < n; i++){
		  		at[i] = i+1;		  		
		  	}
			
			for(i = 0; i < n; i++){//cópia do vetor de prioridade
				p[i] = prioridade[i];
			}
			
			remain = n;//quantidade de processos que restam executar
			for(i = 0, t2 = 0; remain!=0;){//roda enquanto existirem processos pra executar
				if(p[i] == 1 && remain == n){//executa o processo com prioridade 1					
					thread[i]->run();					
					flag = 1;
					p[i] = 0;
					t+=1;
				}
				else if(p[i] == 2 && remain == n-1){//executa o processo com prioridade 2					
					thread[i]->run();					
					flag = 1;
					p[i] = 0;
					t+=1;
				}
				else if(p[i] == 3 && remain == n-2){//executa o processo com prioridade 3					
					thread[i]->run();					
					flag = 1;
					p[i] = 0;
					t+=1;
				}
				else if(p[i] == 4 && remain == n-3){//executa o processo com prioridade 4					
					thread[i]->run();					
					flag = 1;
					p[i] = 0;
					t+=1;
				}		
				if(p[i] == 0 && flag == 1){//condição que indica que o processo foi executado
					remain--;//quantidade de processos restantes é diminuida
					flag = 0;//flag volta a ser zero
				}
				if(i == n-1){//chegamos no ultimo processo, então voltamos para o primeiro para ver se ainda tem algo pra executar
					i = 0;
				}
				else if(at[i] <= t2){//se não chegamos no último podemos passar para o próximo processo
					i++;
				}
				else{
					i++;
				}
			}
		}
			
		if(t == 3){//Executa Round Robin
			//quantum é o tempo que cada processo vai executar
			//remain: processos que ainda não executaram por completo
			//flag: indica que um processo terminou de executar
			//time2: conta o tempo total de execuções
			int count, quantum = 3, remain, flag = 0, time2;

			//rt é o vetor auxiliar que armazena o tempo de execução de cada processo, e at armazena o tempo de chegada de cada processo
			int rt[15], at[15];
			remain = cached_size;
			
			for(count = 0; count < cached_size; count++){//gerando os tempos de chegada
				at[count] = count + 1;
			}			
						
			for(count = 0; count < cached_size; count++){//obtendo o tempo de execução de cada processo
				rt[count] = bt[count];
			}
			
			for(count = 0, time2 = 0; remain!=0;){//irá executar enquanto os processos não tiverem executado por completo
				if(rt[count] <= quantum && rt[count] > 0){//se a quantidade de tempo restante que um processo tem que executar é menor ou igual ao quantum, mas maior que zero
					thread[count]->run();//executa o processo
					time2+=rt[count];//incrementa o time2
					rt[count] = 0;//zera o tempo de execução do processo
					flag = 1;//ativa a flag, indicando que o processo já terminou de executar
				}
				else if(rt[count] > quantum){//se o quantidade restante de tempo que um processo tem que executar é maior que o quantum
					thread[count]->run();//executa o processo					
					rt[count] -= quantum;//diminui o tempo que ele ainda tem que executar de acordo com o quantum
					time2 += quantum;//incrementa o time2
				}
				if(rt[count] == 0 && flag == 1){//se o processo terminou de executar					
					remain--;//agora restam n-1 processos a executar, considerando n o número de processos
					flag = 0;//flag desativada					
				}				
				if(count == cached_size - 1){//caso isso ocorra, chegamos ao último processo, temos que voltar ao primeiro
					count = 0;
				}								
				else if(at[count + 1] <= time2){//o tempo de execução do proximo processo é menor que o tempo de execução total, então o próximo processo ainda tem que executar					
					count++;//incrementa o count, o que na próxima iteração nos levará para a execução do próximo processo
				}
				else{					
					count = 0;
				}				
			}
		}
		
		if(t == 4){//escalona o Aleatório
			int n = cached_size;//quantidade de processos			
			int i, num = 0, r = n, t = 0;
			int at[n];//tempo de chegada de cada processo
			int flag[n];//pra saber se cada processo foi executado
						
		  for(i=0; i < n; i++){
		  	at[i] = i+1;
		  	flag[i] = 0;
		  }
		  
		  for (i=0; r != 0;)
		  {  	
		  	num = rand() % n;//gera número aleatório para selecionar o processo		  	
		  	if(flag[num] != 1){//se o processo não tiver sido executado sua flag será diferente de 1		  		
		  		thread[num]->run();//executa o processo
		  		flag[num] = 1;//processo executado sua flag passa ser 1
		  		r--;//diminui o número de processos restantes
		  		t++;
			}
			else if(i == n - 1){//chegamos ao último processo temos que voltar ao primeiro
				i = 0;
			}			
			else if(t >= at[i]){//ainda há processos pra executar
				i++;
			}
		  	
		  }		  
		}
	
	// ThreadController extends Thread, so we should flag as runned thread
	runned();
}


/*
	List controller (boring part)
*/
bool Escalonador::add(Thread* _thread, int tempo, int p){//o parâmetro tempo é o tempo de execução de cada processo adicionado e p é a prioridade
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
			bt[i] = tempo;//recebendo o tempo de execução de cada processo
			prioridade[i] = p;
			return true;
		}
	}

	// Array is full
	return false;
}

void Escalonador::clear(){
	for(int i = 0; i < MAX_THREADS; i++){
		thread[i] = NULL;
	}
	cached_size = 0;
}

