/*

        Thread.h - um objeto executável

        O thread é responsável por manter a "ação" de alguma coisa,
        Além disso, ele responde se "deve" ou "não deve" executar, com base em
        a hora atual;

        Para obter instruções, acesse https://github.com/ivanseidel/ArduinoThread

        Criado por Ivan Seidel Gomes, março de 2013.
        Lançado em domínio público.


*/

#ifndef Thread_h
#define Thread_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
//	#include <WProgram.h>
#endif

#include <inttypes.h>

/*

        Descomente esta linha para habilitar ThreadName Strings.

        Pode ser útil se você estiver registrando um thread com Serial,
        ou exibindo uma lista de threads ...
*/
// #define USE_THREAD_NAMES	1

class Thread{
protected:
	// Intervalo desejado entre execuções
	unsigned long interval;

	// Último tempo executado em Ms
	unsigned long last_run;

	// Execução programada em Ms (DEVE SER CACHED)
	unsigned long _cached_next_run;

	/*


                IMPORTANTE! Executar após todas as chamadas para run ()
                Atualiza last_run e cache na próxima execução.
                NOTA: DEVE ser chamado se estender
                esta classe e implementando o método run ()

	*/
	void runned(unsigned long time);

	// O padrão é marcá-lo como "agora"
	void runned() { runned(millis()); }

	// retorno de chamada para run () se não estiver implementado
	void (*_onRun)(void);

public:

	// Se a Thread atual esta ativada ou não
	bool enabled;

	// ID do segmento (inicializado a partir da memória adr.)
	int ThreadID;

	#ifdef USE_THREAD_NAMES
		// Thread Name (usado para melhorar a interface do usuário).
		String ThreadName;
	#endif

	Thread(void (*callback)(void) = NULL, unsigned long _interval = 0);

	// defina o intervalo desejado para as chamadas e atualize _cached_next_run
	virtual void setInterval(unsigned long _interval);

	// Retornar se o Thread deve ser executado ou não
	virtual bool shouldRun(unsigned long time);

	// O padrão é verificar se ele deve ser executado "agora"
	bool shouldRun() { return shouldRun(millis()); }

	// Conjunto de retorno de chamada
	void onRun(void (*callback)(void));

	// Runs Thread
	virtual void run();
};

#endif
