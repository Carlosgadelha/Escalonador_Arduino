#include<Escalonador.h>
#include<Thread.h>
#include <dht.h>

// definição dos pinos dos sensores
#define    dht_pin    5
dht   my_dht;
#define reflet 7

int    temperatura = 0x00,
       umidade     = 0x00;
int ldrpin = 1;
int ldrvalor = 0;


 /* Inicializando as Threads */
Thread t1 = Thread();
Thread t2 = Thread();
Thread t3 = Thread();
Thread t4 = Thread();


Escalonador  equipe1; // inicia um objeto do tipo escalonado responsavel por gerenciar as Threads

/* Sensor de Temperatura*/
void sensor_temperatura(){
   my_dht.read11(dht_pin);
   temperatura = my_dht.temperature;
   Serial.print("1, "); // refere - se  ao 1 sensor
   Serial.println(temperatura); // valor

}

/* Sensor de Umidade*/
void sensor_umidade(){
   my_dht.read11(dht_pin); 
   umidade     = my_dht.humidity;
   Serial.print("2, "); //refere - se  ao 2 sensor
   Serial.println(umidade); //valor

}

/* Sensor de Luminosidade*/
void sensor_luminus(){
ldrvalor = analogRead(ldrpin);
Serial.print("3, "); //refere - se  ao 3 sensor
Serial.println(ldrvalor); //valor

}

/* Sensor de presença*/
void sensor_presenca(){
bool estadoSen = digitalRead(reflet);
int a;
if(estadoSen==1){
  a = 1;
  }
else{
  a = 0;
 }
Serial.print("4, "); //refere - se  ao 4 sensor
Serial.println(a); //valor

 }

void setup() {
  Serial.begin(9600);
  pinMode(reflet, INPUT); // definindo pino como entrada
  
/* inicializando as Threads*/
  t1.onRun(sensor_temperatura);
  t2.onRun(sensor_umidade);
  t3.onRun(sensor_luminus);
  t4.onRun(sensor_presenca);


/* Funcionamento do add
 *  .add(Thread,tempo,prioridade)
 *  Para os algoritmos Fifo,Round Robin e aleatorio, o campo "prioridade" como zero ou qualquer outro valor, pois ser descosiderada 
 *  Para o algoritmo de escalonamento por prioridades, o terceiro campo controla a prioridade....
 */

  equipe1.add(&t1,3,2);
  equipe1.add(&t2,15,1);
  equipe1.add(&t3,9,3);
  equipe1.add(&t4,7,4);

}

void loop() {
  
  /*  tipo de escalonador
   * 1 --> Executa em formato de fila
   * 2 --> Executa por prioridade
   * 3 --> Executa Round Robin  
   * 4 --> Executa o Aleatório
  */
  
  equipe1.run(4); // Executando o escalonador, passando como paramnetro o tipo de escalonador a ser executado....
  delay(500);

}
