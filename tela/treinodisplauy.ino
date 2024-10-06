#include <GxEPD2_3C.h>  // Inclui a biblioteca para displays com três cores (branco, preto e vermelho)
#include <Fonts/FreeMonoBold18pt7b.h>  // Fonte para o preço
#include <Fonts/FreeMonoBold12pt7b.h>  // Fonte para o nome do produto
#include <Fonts/FreeMonoBold9pt7b.h>  // Fonte para cod barra

// Configuração para o display de 2.9'' com resolução 296x128
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=*/ D8, /*DC=*/ D2, /*RST=*/ D1, /*BUSY=*/ D0));

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");

  // Inicializa o display e-paper
  display.init(115200);
  display.setRotation(3); // Ajusta a rotação para 90 graus

  // Atualiza o display com a mensagem
  atualizarDisplay();
}

void loop() {
  // O loop está vazio, pois não há necessidade de repetição
}

// Função para atualizar o display e centralizar o texto
void atualizarDisplay() {
  // Limpa a tela e prepara para exibir as informações
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);   // Preenche a tela com branco

    // Define a fonte e a cor preta para o nome do produto
    display.setFont(&FreeMonoBold12pt7b);
    display.setTextColor(GxEPD_BLACK);

    // Centraliza e exibe o texto "ARROZ BIASI T2 5KG"
    centralizarTexto("ARROZ BIASI T2 5KG", 20);  // Exibe o texto na linha Y=20

    // Desenha uma linha vertical no meio da tela
    display.drawLine(190, 128, 190, 100, GxEPD_BLACK); //vertical
    display.drawLine(0, 100, 190, 100, GxEPD_BLACK); //horizontal

    // Exibe o preço maior e simula o efeito de negrito desenhando várias vezes
    display.setFont(&FreeMonoBold18pt7b);  // Define uma fonte maior para o preço
    display.setTextColor(GxEPD_RED);  // Define o texto para vermelho
    
    // Simulação de negrito (ajustando a altura para Y=40 a Y=80)
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        display.setCursor(10 + dx, 75 + dy);  // Ajusta o Y para ficar entre 40 e 80
        display.print("R$ 25,39");
      }
    }

    display.setFont(&FreeMonoBold9pt7b);  // Define uma fonte maior para o preço
    display.setCursor(10, 122);  // Posiciona o preço abaixo da linha
    display.setTextColor(GxEPD_BLACK);  // Define o texto para vermelho
    display.print("78954892541");

  } while (display.nextPage());  // Atualiza a tela uma única vez com todas as mudanças

  display.hibernate();  // Coloca o display em modo de hibernação após a exibição
}

// Função para centralizar o texto
void centralizarTexto(const char* texto, int posY) {
  // Obter a largura do texto
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(texto, 0, 0, &x1, &y1, &w, &h);

  // Calcula a posição X centralizada
  int posX = (display.width() - w) / 2;

  // Configura o cursor para a posição centralizada
  display.setCursor(posX, posY);

  // Exibe o texto
  display.print(texto);
}