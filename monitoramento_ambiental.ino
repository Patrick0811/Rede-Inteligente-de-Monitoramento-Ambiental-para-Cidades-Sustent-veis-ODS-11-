#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "patrick/monitoramento";

#define DHTPIN 4
#define DHTTYPE DHT22

#define LED_VERDE 18
#define LED_AMARELO 19
#define LED_VERMELHO 21
#define BUZZER 23

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);=

void setupWiFi() {

  Serial.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {

  while (!client.connected()) {

    Serial.print("Conectando MQTT... ");

    String clientId = "ESP32-";
    clientId += String(random(1000, 9999));

    if (client.connect(clientId.c_str())) {

      Serial.println("Conectado!");

    } else {

      Serial.print("Falhou. Código: ");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  dht.begin();

  ledcAttach(BUZZER, 2000, 8);

  setupWiFi();

  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Sistema iniciado!");
}

void loop() {

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler DHT22");
    delay(2000);
    return;
  }

  String statusAtual;

  if (temperatura <= 35) {

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);

    ledcWriteTone(BUZZER, 0);

    statusAtual = "NORMAL";
  }

  else if (temperatura <= 60) {

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

    ledcWriteTone(BUZZER, 0);

    statusAtual = "ATENCAO";
  }

  else {

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    ledcWriteTone(BUZZER, 1000);

    statusAtual = "ALERTA CRITICO";
  }

  String mensagem = "{";
  mensagem += "\"temperatura\":";
  mensagem += String(temperatura, 1);
  mensagem += ",";
  mensagem += "\"umidade\":";
  mensagem += String(umidade, 1);
  mensagem += ",";
  mensagem += "\"status\":\"";
  mensagem += statusAtual;
  mensagem += "\"}";

  Serial.println("--------------------------------");
  Serial.println(mensagem);

  bool enviado = client.publish(mqtt_topic, mensagem.c_str());

  if (enviado) {
    Serial.println("Mensagem enviada com sucesso!");
  } else {
    Serial.println("Falha ao enviar mensagem!");
  }

  delay(2000);
}
