int ledPin = 9;  // Pino do LED
int buttonPin = 2; // Pino do botão
int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}


void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(ledPin, LOW); // Desliga o LED quando o botão é pressionado
  } else {
    digitalWrite(ledPin, HIGH); // Liga o LED quando o botão não é pressionado
  }
}