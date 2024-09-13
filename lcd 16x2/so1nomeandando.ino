#include <LiquidCrystal.h>

// Definição dos pinos utilizados para conexão ao display LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Cria um objeto LiquidCrystal com os pinos especificados
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Texto que será movido
char texto[] = "ARROZ BIASI 5K";

void setup() {
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);

  // Exibe o preço do produto "R$ 56.38" na segunda linha
  lcd.setCursor(0, 1);
  lcd.print("R$ 56.38");

  // Aguarda 2 segundos antes de iniciar o movimento
  delay(2000);
}

void loop() {
  // Percorre cada posição para mover o texto da direita para a esquerda
  for (int pos = 0; pos <= 16; pos++) {
    // Limpa apenas a primeira linha
    lcd.setCursor(0, 0);
    lcd.clear();

    // Reexibe o preço fixo na segunda linha
    lcd.setCursor(0, 1);
    lcd.print("R$ 56.38");

    // Move o texto na primeira linha
    lcd.setCursor(16 - pos, 0);  // Move o texto para a esquerda
    lcd.print(texto);

    // Aguarda 300ms para controlar a velocidade do movimento
    delay(500);

    // Verifica se o texto está na posição 0 e aplica a pausa
    if (pos == 16) {
      delay(800);  // Pausa de 800ms quando o texto chegar na posição 0
    }
  }
}
