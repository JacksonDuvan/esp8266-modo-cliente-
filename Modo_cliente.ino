#include <ESP8266WiFi.h>

const char* ssid = "ARRIS-2692";
const char* password = "**********";

const char* host = "www.instagram.com";


void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Conectando con %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado a red WiFi: ");
  Serial.print(ssid);
}


void loop()
{
  // Declaramos o instanciamos un cliente que se conectará al Host
  WiFiClient client;

  Serial.printf("\n[Conectando con %s ... ", host);
  // Intentamos conectarnos
  if (client.connect(host, 80))
  {
    Serial.println("Conectado]");

    Serial.println("[Enviando una solicitud]");
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Conexion: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Respuesta:]");
    // Mientras la conexion perdure
    while (client.connected())
    {
      // Si existen datos disponibles
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    // Una vez el servidor envia todos los datos requeridos se desconecta y el programa continua
    client.stop();
    Serial.println("\n[Desconectado]");
  }
  else
  {
    Serial.println("Fallo Conexion!]");
    client.stop();
  }
  delay(10000);
}
