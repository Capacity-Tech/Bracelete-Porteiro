#include <VirtualWire.h>

// Definição de pinos e variáveis hardcoded
int transmRF = 2;
int sensorSom = 4;
char *mensagem = "ATIVAR";

void setup() {
  // Prepara pino conectado ao sensor de som para entrada de dados 
  pinMode(sensorSom, INPUT);  

  // Define pino de saída conectado ao transmissor
  vw_set_tx_pin(transmRF);
  // Define frequência de bytes por transmissão
  vw_setup(2000);
}

void loop() {
  // Obtem output do sensor de som
  int som = digitalRead(sensorSom);  

  // Se saída do sensor for positiva, ativar transmissão de rádio
  if (som) {
    vw_send((uint8_t *)mensagem, strlen(mensagem));
    // Espera a transmissão de rádio ser enviada
    vw_wait_tx();
    delay(10000);
  }
}
