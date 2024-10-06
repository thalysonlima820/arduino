#include <GxEPD2_3C.h>  // Inclui a biblioteca para displays com três cores (branco, preto e vermelho)
#include <Fonts/FreeMonoBold9pt7b.h>

// Configuração para o display de 2.9'' com resolução 296x128
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=*/ D8, /*DC=*/ D2, /*RST=*/ D1, /*BUSY=*/ D0));

void setup() {
  display.init(115200); // Inicializa o display e-paper
  display.setRotation(3); // Ajusta a rotação para 90 graus (tente ajustar para 0, 1, 2 ou 3 se necessário)

  // Configura a janela para usar a tela toda
  display.setFullWindow();

  // Primeiro ciclo para limpar a tela e fazer todas as atualizações de uma vez
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);   // Preenche a tela com branco

    // Exibe o texto "ARROZ BIASI" em preto
    display.setCursor(20, 50);  // Posiciona o texto "ARROZ BIASI" na tela
    display.setFont(&FreeMonoBold9pt7b);  // Define a fonte
    display.setTextColor(GxEPD_BLACK);  // Define o texto para preto
    display.print("ARROZ BIASI");

    // Exibe o valor "R$ 58,96" em vermelho
    display.setCursor(20, 100);  // Posiciona o valor "R$ 58,96" abaixo do nome
    display.setTextColor(GxEPD_RED);  // Define o texto para vermelho
    display.print("R$ 58,96");

  } while (display.nextPage());  // Atualiza a tela uma única vez com todas as mudanças

  display.hibernate();  // Coloca o display em modo de hibernação após a exibição
}

void loop() {
  // O loop está vazio, pois só queremos mostrar o texto uma vez
}
