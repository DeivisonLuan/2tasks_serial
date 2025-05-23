/*
2 - Adicionar uma task para o user fornecer a frequencia de pelo terminal serial e
um botão que ao ser apertado mostra no serial o valor analógico lido de um ------potenciometro---------
    (usar DIH: ISR + semaforo)
*/

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

SemaphoreHandle_t SMF;
TaskHandle_t handlePWM_t, handleBlink_t, handletask_t;

//Definição dos pinos
#define LedG 2 //pino do led Verde
#define LedR 5 //pino do led Amarelo
#define ButtonPin 13 //Pino do botão

//Rotina de interrupção
void IRAM_ATTR Pressed(){
  xSemaphoreGiveFromISR(SMF, NULL);
}

void handlePWM();
void handleBlink();
void handletask(void* z);


void setup() {
  //inicialização dos pinos
  pinMode(LedG, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);

  //inicia interrupção
  attachInterrupt(ButtonPin, Pressed, FALLING);

  //inicia semaforo binário
  SMF = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(handletask, "handletask", 4096, NULL, 1, &handletask_t, 0);
}

void loop() {
  
}

void handletask(void* z){

}

void handlePWM(){
  while(true){
    for(byte i=0; i<=255 ; i++){
      analogWrite(LedG, i);
      delay(50);
    }
    for(byte i=255; i>=0 ; i--){
      analogWrite(LedG, i);
      delay(50);
    }
  }
}

void handleBlink(){
  digitalWrite(LedR, HIGH);
  delay(300);
  digitalWrite(LedR,LOW);
  delay(300);
}