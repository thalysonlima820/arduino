#include <Servo.h>

//tag
#include <MFRC522.h>
#include<SPI.h>
#define PINO_RST 8
#define PINO_SDA 10

MFRC522 rfid(PINO_SDA, PINO_RST);

int pos = 90; // Começar no meio (90 graus)

Servo servo_9;

#define pinVRx A2
#define pinVRy A1
#define pinSW 2

void setup()
{
    pinMode(pinVRx, INPUT);
    pinMode(pinVRy, INPUT);
    pinMode(pinSW, INPUT);

    servo_9.attach(9);
  
    Serial.begin(9600);

    SPI.begin();
    rfid.PCD_Init();

    Serial.print("APROXIME");
    Serial.println();
}


void loop()
{

    int valorVRx = analogRead(pinVRx);
    int valorVRy = analogRead(pinVRy);
    bool statusSW = digitalRead(pinSW);

  if(!rfid.PICC_IsNewCardPresent())
  {
    return;
  }

  if(!rfid.PICC_ReadCardSerial())
  {
     return;
  }

  String conteudo = "";

  for(byte i = 0; i < rfid.uid.size; i++){
    conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " "));
    conteudo.concat(String(rfid.uid.uidByte[i], HEX));
  }

  // Serial.println(conteudo);


if(conteudo == " 08 31 ea 03"){

      int VRx = map(valorVRx, 0, 1023, 0, 180);
    int VRy = map(valorVRy, 0, 1023, 0, 180);

    // Frente e trás (usando VRx)
    if (VRx < 70) {

        if(pos > 0){
          pos-=5;
          servo_9.write(pos);
        }
        Serial.println(pos);
    } 
    if (VRx > 110 ) {

        if(pos < 180){
          pos+=5;
          servo_9.write(pos);
        }
        Serial.println(pos);
    }

    // Direita e esquerda (usando VRy)
    if (VRy < 70 ) {

        if(pos > 0){
          pos-=5;
          servo_9.write(pos);
        }
        Serial.println(pos);
    } 
    if (VRy > 110) {

        if(pos < 180){
          pos+=5;
          servo_9.write(pos);
        }
        Serial.println(pos);
    }

    // Verifica se o botão foi pressionado
    if (!statusSW) {
        Serial.println("Apertou");

        for( pos = 0; pos <= 180; pos+=1) {
          servo_9.write(pos);
          delay(15);
        }
        for(pos = 180; pos >= 0; pos-=1) {
          servo_9.write(pos);
          delay(15);
        }
        
    } 
}

}
