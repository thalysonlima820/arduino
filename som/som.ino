#define pinorele 7
#define pinosom 4

bool rele;
bool estadoSomAnterior = LOW;

void setup()
{
  pinMode(pinorele, OUTPUT);
  pinMode(pinosom, INPUT);
  rele = false;
  digitalWrite(pinorele, rele);

  Serial.begin(9600);
  Serial.print("ok");
}

void loop()
{
  bool estadoSomAtual = digitalRead(pinosom);

  if (estadoSomAtual == HIGH && estadoSomAnterior == LOW) {
    rele = !rele;
    delay(200);
  }

  digitalWrite(pinorele, rele);
  estadoSomAnterior = estadoSomAtual;
}
