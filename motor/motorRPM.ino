#include <Stepper.h>

// Definindo o número de passos por revolução
const int stepsPerRevolution = 2048; 

// Inicializando o motor de passo (conectado aos pinos 8, 9, 10, 11 do Arduino)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Definindo a velocidade do motor
  myStepper.setSpeed(15); // 10 RPM
}

void loop() {
  myStepper.setSpeed(15);
  myStepper.step(stepsPerRevolution);
  delay(1000);

  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution);
  delay(1000);
}
