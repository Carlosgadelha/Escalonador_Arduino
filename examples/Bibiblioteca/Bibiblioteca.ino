
#include<Escalonador.h>
#include<Thread.h>



 /* Inicializando as Threads */
 
Thread t1 = Thread();
Thread t2 = Thread();
Thread t3 = Thread();
Thread t4 = Thread();


Escalonador Alfa; // inicia um objeto do tipo escalonado responsavel por gerenciar as Threads



/* Função da Thread 1*/
void msg1() {
  Serial.println("Mensagem 1...");
}

/* Função da Thread 2*/
void msg2() {
  Serial.println("Mensagem 2...");
  
}

/* Função da Thread 2*/
void msg3() {
  Serial.println("Mensagem 3...");
 
}

/* Função da Thread 2*/
void msg4() {
  Serial.println("Mensagem 4...");
}

void setup() {
  Serial.begin(9600);

/* inicializando as Threads*/
  t1.onRun(msg1);
  t2.onRun(msg2);
  t3.onRun(msg3);
  t4.onRun(msg4);



/* Funcionamento do add
 *  .add(Thread,tempo,prioridade)
 *  Para os algoritmos Fifo,Round Robin e aleatorio, o campo "prioridade" como zero ou qualquer outro valor, pois ser descosiderada 
 *  Para o algoritmo de escalonamento por prioridades, o terceiro campo controla a prioridade....
 */
 
  Alfa.add(&t1,3,2);
  Alfa.add(&t2,15,1);
  Alfa.add(&t3,9,3);
  Alfa.add(&t4,7,4);

}

void loop() {

    /*  tipo de escalonador
   * 1 --> Executa em formato de fila
   * 2 --> Executa por prioridade
   * 3 --> Executa Round Robin  
   * 4 --> Executa o Aleatório
  */

  Alfa.run(4);
  delay(500);

}
