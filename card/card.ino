
//tag
#include <MFRC522.h>
#include<SPI.h>
#define PINO_RST 8
#define PINO_SDA 10

MFRC522 rfid(PINO_SDA, PINO_RST);


void setup()
{
    Serial.begin(9600);

    SPI.begin();
    rfid.PCD_Init();

    Serial.print("APROXIME");
    Serial.println();
}


void loop()
{

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

}

}
