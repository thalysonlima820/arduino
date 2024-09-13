#include <IRremote.h>

int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

int pinSensor = 11;

IRrecv sensorIR(pinSensor);  // Inicializa o sensor IR no pino 11
decode_results comando;      // Variável para armazenar os comandos IR recebidos

// Função para exibir o número usando LEDs (display de 7 segmentos)
void numeros(int numero) {
  switch (numero) {
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
  }
}

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  Serial.begin(9600);        // Inicializa a comunicação serial
  sensorIR.begin(pinSensor); // Inicializa o receptor IR
  Serial.println("SERIAL ATIVO");   // Mensagem indicando que o IR está pronto
}

void loop() {
  // Verifica se algum comando IR foi recebido
  if (sensorIR.decode()) {         
    Serial.print("Comando recebido: ");
    Serial.println(sensorIR.decodedIRData.command, HEX);  // Exibe o valor do comando IR recebido em hexadecimal

    // Mapeando o valor do comando para o número correspondente
    switch(sensorIR.decodedIRData.command) {
      case 0x45:  // Ajuste conforme o código hexadecimal recebido para o número 1
        numeros(1);
        break;
      case 0x46:  // Ajuste conforme o código hexadecimal recebido para o número 2
        numeros(2);
        break;
      case 0x47:
        numeros(3);
        break;
      case 0x44:
        numeros(4);
        break;
      case 0x40:
        numeros(5);
        break;
      case 0x43:
        numeros(6);
        break;
      case 0x7:
        numeros(7);
        break;
      case 0x15:
        numeros(8);
        break;
      case 0x9:
        numeros(9);
        break;
      case 0x19:  // Ajuste conforme o código hexadecimal recebido para o número 0
        numeros(0);
        break;
      default:
        Serial.println("Comando não reconhecido");
    }

    sensorIR.resume();  // Prepara o receptor IR para receber o próximo comando
  }
}
