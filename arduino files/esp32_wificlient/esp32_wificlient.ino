#include <WiFi.h>

const char* ssid     = "testnet";
const char* password = "AFKLJCouq41if829u9ejjnchb:>ZOWij7208u2";

const char* host = "192.168.1.14";
const char* deviceId   = "8fhuijcbjqiu48930uehiuhdnqij9984";
const char* privateKey = "98u9duihbfhu4e984370urhfyhuy348489u94uuhf8yh828udurhufhufucdiuci";
const char* value = "value";
void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);// set the LED pin mode
  pinMode(14, OUTPUT);// set the Relay pin mode
  digitalWrite(14, HIGH);// turn off relay
  connectWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connectWifi() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void pushData() {
    
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
  }

  // We now create a URI for the request
  String url = "/dev/";
  url += deviceId;
  url += "?private_key=";
  url += privateKey;
  url += "&value=";
  url += value;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
     }
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

}
