/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will print the IP address of your WiFi Shield (once connected)
  to the Serial monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 5.

  If the IP address of your shield is yourAddress:
  http://yourAddress/H turns the LED on
  http://yourAddress/L turns it off

  This example is written for a network using WPA encryption. For
  WEP or WPA, change the Wifi.begin() call accordingly.

*/

#include <WiFi.h>

const char* ssid     = "RIDEthelightning";
const char* password = "R@p!dR@((00n021";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(5, OUTPUT);// set the pin mode
  pinMode(14, OUTPUT);// set the pin mode
  pinMode(16, OUTPUT);// set the pin mode
  pinMode(17, OUTPUT);// set the pin mode
  digitalWrite(14, HIGH);// turn off relay

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("tf");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/5on\">here</a> to turn pin 5 on.<br>");
            client.print("Click <a href=\"/5off\">here</a> to turn pin 5 off.<br>");
            client.print("Click <a href=\"/14on\">here</a> to turn pin 14 on.<br>");
            client.print("Click <a href=\"/14off\">here</a> to turn pin 14 off.<br>");
            client.print("Click <a href=\"/16on\">here</a> to turn pin 16 on.<br>");
            client.print("Click <a href=\"/16off\">here</a> to turn pin 16 off.<br>");
            client.print("Click <a href=\"/17on\">here</a> to turn pin 17 on.<br>");
            client.print("Click <a href=\"/17off\">here</a> to turn pin 17 off.<br>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was to alter LED or relay state:
        if (currentLine.endsWith("GET /5on")) {
          digitalWrite(5, LOW);               // GET /5on turns the pin 5 on
        }
        if (currentLine.endsWith("GET /5off")) {
          digitalWrite(5, HIGH);                // GET /5off turns pin 5 off
        }
        if (currentLine.endsWith("GET /14on")) {
          digitalWrite(14, LOW);               // GET /14on turns pin 14 on
        }
        if (currentLine.endsWith("GET /14off")) {
          digitalWrite(14, HIGH);                // GET /14off turns pin 14 off
        }
        if (currentLine.endsWith("GET /16on")) {
          digitalWrite(16, LOW);               // GET /16on turns pin 16 on
        }
        if (currentLine.endsWith("GET /16off")) {
          digitalWrite(16, HIGH);                // GET /16off turns pin 16 off
        }
        if (currentLine.endsWith("GET /17on")) {
          digitalWrite(17, LOW);               // GET /17on turns pin 17 on
        }
        if (currentLine.endsWith("GET /17off")) {
          digitalWrite(17, HIGH);                // GET /17off turns pin 17 off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
