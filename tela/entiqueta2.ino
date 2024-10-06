#include <GxEPD2_3C.h>  // Inclui a biblioteca para displays com três cores (branco, preto e vermelho)
#include <Fonts/FreeMonoBold18pt7b.h>  // Fonte para o preço
#include <Fonts/FreeMonoBold12pt7b.h>  // Fonte para o nome do produto
#include <Fonts/FreeMonoBold9pt7b.h>  // Fonte para o código de barras
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// Configuração para o display de 2.9'' com resolução 296x128
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=*/ D8, /*DC=*/ D2, /*RST=*/ D1, /*BUSY=*/ D0));

// Defina o nome da rede Wi-Fi e a senha
const char* ssid = "TCH";
const char* password = "75315922a";

// Defina o host e o caminho da API
const char* host = "api.devbr.site";
const char* url = "/api_preco_biasi/public/v1/preco";

// Variáveis para armazenar os dados da API
String produto = "TESTE";
String valor = "";
String codbarra = "";
String codproduto = "";

// Instância do WiFiClient
WiFiClient client;

// Array de bytes para a imagem gerada (90x70px)
const unsigned char epd_bitmap_biasi_image [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x83, 
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xf0, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0xff, 
	0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x80, 0x00, 0xc7, 0xff, 0xff, 
	0xfc, 0xff, 0xff, 0xff, 0x80, 0x03, 0xe3, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xf3, 
	0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x38, 0x00, 0xb1, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfe, 0x10, 
	0x01, 0xb1, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfe, 0x10, 0x01, 0xa1, 0xff, 0xff, 0xfc, 0xff, 0xff, 
	0xfe, 0x18, 0x01, 0x21, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfe, 0x18, 0x01, 0x61, 0xff, 0xff, 0xfc, 
	0xff, 0xff, 0xfe, 0x08, 0x03, 0x41, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfe, 0x0f, 0xfe, 0x41, 0xff, 
	0xff, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 0xc1, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 
	0xc3, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x07, 0xff, 0x83, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0x87, 0xff, 0x07, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xc3, 0x06, 0x07, 0xff, 0xff, 0xfc, 0xff, 
	0xff, 0xff, 0xc1, 0x02, 0x0f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 
	0xfc, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfe, 0x01, 0xff, 
	0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0xe0, 0x01, 0xf0, 0xff, 0x8f, 0xff, 0x00, 0x0e, 0x1c, 0xc0, 0x00, 0xf0, 0xff, 0x07, 0xfc, 0x00, 
	0x0e, 0x1c, 0xc0, 0x00, 0x70, 0xff, 0x03, 0xfc, 0x00, 0x1e, 0x1c, 0xff, 0xfc, 0x70, 0xfe, 0x03, 
	0xfc, 0x0e, 0x7e, 0x1c, 0xff, 0xfc, 0x70, 0xfe, 0x21, 0xf8, 0x3f, 0xfe, 0x1c, 0xe0, 0x00, 0x70, 
	0xfc, 0x31, 0xfc, 0x00, 0x3e, 0x1c, 0xe0, 0x00, 0xf0, 0xf8, 0x70, 0xfc, 0x00, 0x1e, 0x1c, 0xc0, 
	0x00, 0x70, 0xf8, 0x78, 0xfe, 0x00, 0x0e, 0x1c, 0xc0, 0x00, 0x30, 0xf0, 0xf8, 0x7f, 0x80, 0x0e, 
	0x1c, 0xc3, 0xfc, 0x30, 0xf1, 0xfc, 0x3f, 0xff, 0x06, 0x1c, 0xc0, 0x00, 0x30, 0xe1, 0x80, 0x3f, 
	0x00, 0x06, 0x1c, 0xc0, 0x00, 0x70, 0xc3, 0x00, 0x1e, 0x00, 0x0e, 0x1c, 0xc0, 0x00, 0x70, 0xc3, 
	0x00, 0x1c, 0x00, 0x1e, 0x1c, 0xe0, 0x01, 0xf0, 0x86, 0x00, 0x0c, 0x00, 0x3e, 0x1c, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc
};


void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");

  // Inicializa o display e-paper
  display.init(115200);
  display.setRotation(3); // Ajusta a rotação para 90 graus (tente ajustar se necessário)

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // Imprime "." enquanto tenta se conectar
  }
  Serial.println("\nWiFi Conectado com sucesso!");

  // Chama a função para obter os dados da API
  getDataFromAPI();

  // Atualiza o display com os dados recebidos
  atualizarDisplay();
}

void loop() {
  // Faz uma nova consulta à API a cada 60 segundos
  delay(43200000);
  getDataFromAPI();
  atualizarDisplay();
}

// Função para obter os dados da API usando WiFiClient diretamente
void getDataFromAPI() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado ao WiFi, tentando acessar a API...");

    // Conecta ao servidor na porta 80 (HTTP)
    if (!client.connect(host, 80)) {
      Serial.println("Conexão ao host falhou");
      return;
    }

    // Envia a requisição HTTP GET
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");

    // Espera a resposta do servidor
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);

        // Captura a linha do JSON
        if (line.startsWith("[")) {  // Verifica se o JSON é um array
          Serial.println("Resposta JSON recebida:");
          Serial.println(line);  // Exibe a resposta no monitor serial
          
          // Processa o JSON
          DynamicJsonDocument doc(256);
          DeserializationError error = deserializeJson(doc, line);

          // Verifica se houve erro ao processar o JSON
          if (!error) {
            // Acessa o primeiro elemento do array
            JsonObject obj = doc[0];

            String novoProduto = obj["PRODUTO"].as<String>();
            String novoValor = obj["VALOR"].as<String>();
            String novoCodBarra = obj["CODBARRA"].as<String>();
            String novoCodProduto = obj["CODPRODUTO"].as<String>();

            // Só atualiza as variáveis se não forem nulas ou vazias
            if (novoProduto != "" && novoValor != "") {
              produto = novoProduto;
              valor = novoValor;
              codbarra = novoCodBarra;
              codproduto = novoCodProduto;
            }

            Serial.println("Produto: " + produto);
            Serial.println("Valor: " + valor);
            Serial.println("CodBarra: " + codbarra);
            Serial.println("CodProduto: " + codproduto);
          } else {
            Serial.println("Erro ao analisar o JSON");
          }
        }
      }
    }

    // Fecha a conexão
    client.stop();
  } else {
    Serial.println("Falha na conexão com o WiFi.");
  }
}

// Função para atualizar o display com o produto, valor e códigos
void atualizarDisplay() {
  // Limpa a tela e prepara para exibir as informações
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);   // Preenche a tela com branco

    // Exibe o nome do produto
    display.setFont(&FreeMonoBold12pt7b);
    display.setTextColor(GxEPD_BLACK);
    centralizarTexto(produto.c_str(), 20);

    // Exibe o preço maior e simula o efeito de negrito desenhando várias vezes
    display.setFont(&FreeMonoBold18pt7b);
    display.setTextColor(GxEPD_RED);
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        display.setCursor(10 + dx, 75 + dy);
        display.print("R$ " + valor);
      }
    }

    // Exibe o código de barras
    display.setFont();  // Usa a fonte padrão embutida
    display.setTextSize(1.8);  // Define o tamanho do texto como 1 (pequeno)
    display.setCursor(10, 115);  // Posiciona o preço abaixo da linha
    display.setTextColor(GxEPD_BLACK);
    display.print(codbarra);

    // Exibe o código do produto
    display.setFont();  // Usa a fonte padrão embutida
    display.setTextSize(1);  // Define o tamanho do texto como 1 (pequeno)
    display.setCursor(260, 115);  // Posiciona o preço abaixo da linha
    display.setTextColor(GxEPD_BLACK);
    display.print(codproduto);

    // Desenha a imagem no display nas coordenadas X=200, Y=40
    display.drawBitmap(200, 40, epd_bitmap_biasi_image, 90, 70, GxEPD_BLACK);

  } while (display.nextPage());

  display.hibernate();  // Coloca o display em modo de hibernação
}

// Função para centralizar o texto
void centralizarTexto(const char* texto, int posY) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(texto, 0, 0, &x1, &y1, &w, &h);
  int posX = (display.width() - w) / 2;
  display.setCursor(posX, posY);
  display.print(texto);
}
