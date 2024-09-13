#include <LiquidCrystal.h>

const int rs =12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7= 2;
LiquidCrystal lcd(rs, en, d4, d5,d6,d7);


void setup()
{
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("ARROZ BIASI 5K");
  lcd.setCursor(0,1);
  lcd.print("R$ 56.38");
  
}

void loop()
{
 
  
}