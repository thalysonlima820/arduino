#include <LiquidCrystal.h>

// Definição dos pinos utilizados para conexão ao display LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Cria um objeto LiquidCrystal com os pinos especificados
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
  
  // Define a posição do cursor na primeira linha e primeira coluna (0,0)
  lcd.setCursor(0, 0);
  // Exibe o nome do produto "ARROZ BIASI 5K" na primeira linha
  lcd.print("ARROZ BIASI 5K");
  
  // Define a posição do cursor na segunda linha e primeira coluna (0,1)
  lcd.setCursor(0, 1);
  // Exibe o preço do produto "R$ 56.38" na segunda linha
  lcd.print("R$ 56.38");
  
  // Aguarda 2 segundos antes de iniciar o movimento
  delay(2000);
}

void loop() {
  // Faz o texto "ARROZ BIASI 5K" mover-se da direita para a esquerda
  lcd.scrollDisplayLeft();  // Move o conteúdo da tela para a esquerda
  delay(500);               // Intervalo de tempo para o movimento (300 ms)
}
