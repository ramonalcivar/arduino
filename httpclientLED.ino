#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

const char* ssid = "Ramon";
const char* password = "koke9530";
const char* serverAddress = "192.168.0.14"; // Cambia esto a la dirección IP de tu servidor Flask

int port = 5000;
int ledPin = 12;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(12,OUTPUT);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado exitosamente a la red Wi-Fi");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:+
  httpGET();

}

void httpGET(){
  client.get("/estado_led");

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc,response);

  if(!error){
    const char* estado = doc["estado"];
    if (strcmp(estado, "ON") == 0){
      Serial.println("Encendiendo LED");
      digitalWrite(ledPin,HIGH);
    }
    else if (strcmp(estado, "OFF") == 0) {
      Serial.println("Apagando LED");
      digitalWrite(ledPin, LOW);  // Apagar LED
    }     
  }

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("Response: ");
  Serial.println(response);
  Serial.println("Wait five seconds");
  delay(250);
}

void httpPOST(){
  
}

