#include <GxEPD2_3C.h>  // Inclui a biblioteca para displays com três cores (branco, preto e vermelho)
#include <Fonts/FreeMonoBold12pt7b.h>  // Fonte maior para o display
#include <ESP8266WiFi.h>  // Biblioteca para Wi-Fi
#include <ArduinoJson.h>  // Biblioteca para processar JSON

// Configuração para o display de 2.9'' com resolução 296x128
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=*/ D8, /*DC=*/ D2, /*RST=*/ D1, /*BUSY=*/ D0));

// Defina o nome da rede Wi-Fi e a senha
// const char* ssid = "TCH";
// const char* password = "75315922a";
const char* ssid = "TCH_TC";
const char* password = "B12486001!1";

// Defina o host e o caminho da API
const char* host = "api.devbr.site";
const char* url = "/api_preco_biasi/public/v1/preco";

// Variáveis para armazenar o produto e o preço retornados pela API
String produto = "TESTE";
String valor = "";

// Instância do WiFiClient
WiFiClient client;

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");

  // Inicializa o display e-paper
  display.init(115200);
  display.setRotation(3); // Ajusta a rotação para 90 graus

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
  delay(60000);
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

            // Só atualiza as variáveis se não forem nulas ou vazias
            if (novoProduto != "" && novoValor != "") {
              produto = novoProduto;
              valor = novoValor;
            }

            Serial.println("Produto: " + produto);
            Serial.println("Valor: " + valor);
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

// Função para atualizar o display com o produto e valor
void atualizarDisplay() {
  // Limpa a tela e prepara para exibir as informações
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);   // Preenche a tela com branco

    // Exibe o nome do produto em preto
    display.setCursor(10, 50);  // Posiciona o texto do produto na tela
    display.setFont(&FreeMonoBold12pt7b);  // Define a fonte maior
    display.setTextColor(GxEPD_BLACK);  // Define o texto para preto
    display.print(produto);

    // Exibe o valor do produto em vermelho
    display.setCursor(10, 100);  // Posiciona o valor do produto abaixo do nome
    display.setTextColor(GxEPD_RED);  // Define o texto para vermelho
    display.print("R$ " + valor);

  } while (display.nextPage());  // Atualiza a tela uma única vez com todas as mudanças

  display.hibernate();  // Coloca o display em modo de hibernação após a exibição
}
