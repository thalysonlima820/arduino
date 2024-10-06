#include <LiquidCrystal.h>


// Defina os pinos corretos do Wemos D1 Mini
const int rs = D6, en = D5, d4 = D4, d5 = D3, d6 = D2, d7 = D1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("ARROZ BIASI 5K");
  lcd.setCursor(0,1);
  lcd.print("R$ 56.38");
  
}


void loop() {
  // Loop vazio, pois a mensagem é estática
}
