#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

// Definindo os pinos dos LEDs
int ladvermelho = 6;
int ladverde = 7;

// Definindo os pinos do RFID
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

    pinMode(ladvermelho, OUTPUT);
    pinMode(ladverde, OUTPUT);

    // Certifique-se de que ambos os LEDs estão apagados no início
    digitalWrite(ladvermelho, LOW);
    digitalWrite(ladverde, LOW);

    servo_9.attach(9);

    Serial.begin(9600);

    SPI.begin();
    rfid.PCD_Init();

    Serial.print("APROXIME");
    Serial.println();
}

void acenderVermelho()
{
    // Apaga o verde e acende o vermelho
    digitalWrite(ladverde, LOW); // Certifica que o verde está desligado
    digitalWrite(ladvermelho, HIGH); // Liga o vermelho
}

void acenderVerde()
{
    // Apaga o vermelho e acende o verde
    digitalWrite(ladvermelho, LOW); // Certifica que o vermelho está desligado
    digitalWrite(ladverde, HIGH); // Liga o verde
}

void loop()
{
    int valorVRx = analogRead(pinVRx);
    int valorVRy = analogRead(pinVRy);
    bool statusSW = digitalRead(pinSW);

        // Verificação de LEDs (acende o verde se já estiver ligado)
    // Verifica se há um novo cartão presente
    if (!rfid.PICC_IsNewCardPresent()) {
    
      acenderVermelho();
        return; 
    }

    // Tenta ler o cartão
    if (rfid.PICC_ReadCardSerial()) {
      
      acenderVerde();
    }

    if(!rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      return;
    } 

    String conteudo = "";

    for (byte i = 0; i < rfid.uid.size; i++)
    {
        conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " "));
        conteudo.concat(String(rfid.uid.uidByte[i], HEX));
    }

    // Verifica o conteúdo do cartão
    if (conteudo == " 08 31 ea 03" || conteudo == " 39 2a 54 7a")
    {
        acenderVerde(); // Acende o LED verde se o cartão for válido

        int VRx = map(valorVRx, 0, 1023, 0, 180);
        int VRy = map(valorVRy, 0, 1023, 0, 180);

        // Frente e trás (usando VRx)
        if (VRx < 70)
        {
            if (pos > 0)
            {
                pos -= 5;
                servo_9.write(pos);
            }
            Serial.println(pos);
        }
        if (VRx > 110)
        {
            if (pos < 180)
            {
                pos += 5;
                servo_9.write(pos);
            }
            Serial.println(pos);
        }

        // Direita e esquerda (usando VRy)
        if (VRy < 70)
        {
            if (pos > 0)
            {
                pos -= 5;
                servo_9.write(pos);
            }
            Serial.println(pos);
        }
        if (VRy > 110)
        {
            if (pos < 180)
            {
                pos += 5;
                servo_9.write(pos);
            }
            Serial.println(pos);
        }

        // Verifica se o botão foi pressionado
        if (!statusSW)
        {
            Serial.println("Apertou");

            for (pos = 0; pos <= 180; pos += 1)
            {

                servo_9.write(pos);
                delay(15);
            }
            for (pos = 180; pos >= 0; pos -= 1)
            {
                servo_9.write(pos);
                delay(15);
            }
        }
    }
}
