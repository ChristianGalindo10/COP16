#include<WiFi.h>
#include <WebSocketsServer.h>
#include<HTTPClient.h>

const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

int readValue;
int anterior;
int anterior2;
int estado;
int estado2;

#define pinbot 27
#define pinbot2 34
WiFiClient client;
unsigned long temporizador;
unsigned long temporizador2;
unsigned long tiemporebote = 40;


HTTPClient http;
String url = "https://geoapps.esri.co/cop16sockets/sendMessage";
char* jsondata = "{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}";




void setup() {
  Serial.begin(115200);
  pinMode(pinbot, INPUT_PULLUP);
  pinMode(pinbot2, INPUT_PULLUP);
  estado = HIGH;
  anterior = HIGH;
  estado2 = HIGH;
  anterior2 = HIGH;
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("¡WiFi no conectado!");
  }
  Serial.println("¡WiFi conectado!");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());
  WiFi.mode(WIFI_STA);
}

void loop() {
  estado = digitalRead(pinbot);
  if ( anterior == HIGH && estado == LOW ) {
    Serial.print("Botón 1 pulsado");
    http.begin(url);
    http.addHeader("Content-Type", "text/plain");
    int httpResponseCode = http.POST("1"); //Send the actual POST request

    if (httpResponseCode > 0) {
      String response = http.getString();  //Get the response to the request
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);

      http.end();

    }
    delay(1000);
  }
  anterior = estado;
  estado2 = digitalRead(pinbot2);
  if ( anterior2 == HIGH && estado2 == LOW ) {
    Serial.print("Botón 2 pulsado");
    http.begin(url);
    http.addHeader("Content-Type", "text/plain");
    int httpResponseCode = http.POST("2"); //Send the actual POST request

    if (httpResponseCode > 0) {
      String response = http.getString();  //Get the response to the request
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);

      http.end();

    }
    delay(1000);
  }
  anterior2 = estado2;
}