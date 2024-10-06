#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// Defina os pinos corretos do Wemos D1 Mini para o LCD
const int rs = D6, en = D5, d4 = D4, d5 = D3, d6 = D2, d7 = D1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Defina o nome da rede Wi-Fi e a senha
const char* ssid = "TCH";
const char* password = "75315922a";

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
  Serial.begin(115200);  // Certifique-se de que o Serial Monitor está configurado para 115200 baud
  Serial.println("Iniciando sistema...");

  // Inicializa o LCD
  lcd.begin(16, 2);
  lcd.clear();  // Limpa qualquer conteúdo no LCD
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 1);
  lcd.print("Conectando...");
  
  // Aguarda a conexão com o Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // Imprime "." a cada meio segundo enquanto tenta se conectar
  }

  // Exibe uma mensagem quando estiver conectado
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Conectado");
  Serial.println("\nWiFi Conectado com sucesso!");

  // Mostra a mensagem de "WiFi Conectado" por 2 segundos antes de exibir os dados
  delay(2000);

  // Chama a função para obter os dados da API
  getDataFromAPI();
}

void loop() {
  // Atualiza o LCD com os dados obtidos da API
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Exibe o nome do produto (limite de 16 caracteres)
  if (produto.length() > 16) {
    lcd.print(produto.substring(0, 16));  
  } else {
    lcd.print(produto);
  }

  lcd.setCursor(0, 1);
  lcd.print("R$ ");
  lcd.print(valor);  // Exibe o valor do produto

  // Faz uma nova consulta à API a cada 60 segundos
  delay(60000);
  getDataFromAPI();
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

