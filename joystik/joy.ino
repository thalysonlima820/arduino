#define pinVRx A2
#define pinVRy A1
#define pinSW 2


void setup()
{
    pinMode(pinVRx, INPUT);
    pinMode(pinVRy, INPUT);
    pinMode(pinSW, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
 
 int valorVRx = analogRead(pinVRx);
 int valorVRy = analogRead(pinVRy);
 bool statusSW = digitalRead(pinSW);

 Serial.print("  Valor VRx :  ");
 Serial.print(map(valorVRx, 0,1023, 0,180));
 Serial.print("  Valor VRy:  ");
 Serial.print(map(valorVRy, 0,1023, 0,180));

if(!statusSW) {
  Serial.println("  apertou");
} else{
  Serial.println("  solto");
}
  
}