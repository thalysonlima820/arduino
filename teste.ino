#include <Servo.h>

#define pinVRx A2
#define pinVRy A1
#define pinSW 2



int pos = 0;

Servo servo_9;

void setup()
{
    pinMode(pinVRx, INPUT);
    pinMode(pinVRy, INPUT);
    pinMode(pinSW, INPUT);
  
  Serial.begin(9600);

  Serial.println("Serial tudo ok");

   servo_9.attach(9);
}

void loop()
{
 
 int valorVRx = analogRead(pinVRx);
 int valorVRy = analogRead(pinVRy);
 bool statusSW = digitalRead(pinSW);

 int v = (map(valorVRx, 0,1023, 0,180));

 int c = (map(valorVRy, 0,1023, 0,180));

  if(v < 80){
      servo_9.write(v);
      Serial.println(v);
  }
  if(v > 100){
      servo_9.write(v);
      Serial.println(v);
  }

    if(c < 80){
      servo_9.write(c);
      Serial.println(c);
  }
  if(c > 100){
      servo_9.write(c);
      Serial.println(c);
  }

  // if(!statusSW) {
  //   Serial.println("  apertou");
  // } else{
  //   Serial.println("  solto");
  // }
  
}