#include <VirtualWire.h>

// Definição de pinos e variáveis hardcoded
int recepRF = 2;
int led = 4;
int motorVib = 5;
int stopBtn = 6;
char mensagem[] = "ATIVAR";

void setup() {
  // Prepara pino conectado ao LED para saída
  pinMode(led, OUTPUT);
  // Prepara pino conectado ao motor para saída
  pinMode(motorVib, OUTPUT);
  // Prepara pino conectado ao botão de parar alarme para entrada
  pinMode(stopBtn, INPUT);

  // Define pino de saída conectado ao receptor
  vw_set_rx_pin(recepRF);
  // Define frequência de bytes por transmissão
  vw_setup(2000);
  // Começa a rodar o receptor
  vw_rx_start();
}

void loop() {
  // Inicia a variável da saída do receptor
  byte message[VW_MAX_MESSAGE_LEN];

  // Verifica saída do receptor
  vw_get_message(message, VW_MAX_MESSAGE_LEN)

  // Faz o decode da mensagem recebida em chars 
  char msg[VW_MAX_MESSAGE_LEN];
  for (int i = 0; i < VW_MAX_MESSAGE_LEN; i ++)
    msg[i] = (char)message[i];
  
  // Compara se mensagem recebida foi palavra de ativação
  if (strcmp(mensagem, msg) == 0)
  {
    // Inicia variável de tempo limite de alerta
    int time = 0;

    // Roda loop de alerta enquanto usuário não apertar botão de parar ou o tempo limite acabar
    while (digitalRead(stopBtn) != HIGH && time != 30) {
      // Ativa LED e motor de vibração por 500 milisegundos
      digitalWrite(led, HIGH);
      digitalWrite(motorVib, HIGH);
      delay(500);

      // Desativa LED e motor de vibração por 500 milisegundos
      digitalWrite(led, LOW);
      digitalWrite(motorVib, LOW);
      delay(500);

      // Adiciona um segundo passado ao tempo
      time++;
    }
  }
  else {
    // Caso mensagem não tenha sido código de ativação, mantêm LED e motor de vibração desativados
    digitalWrite(led, LOW);
    digitalWrite(motorVib, LOW);
  }
}