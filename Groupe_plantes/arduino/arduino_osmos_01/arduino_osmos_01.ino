#include <Wire.h>
#include <SPI.h>
#include <Ethernet2.h>
#include "Adafruit_HDC1000.h"
#include "Adafruit_MPR121.h"

// --------------------------------------------------------------------
// Ethernet
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xFD, 0x39 };
EthernetServer server(80);
int countPrint = 0;

// --------------------------------------------------------------------
// Connect Vin to 3-5VDC
// Connect GND to ground
// Connect SCL to I2C clock pin (A5 on UNO)
// Connect SDA to I2C data pin (A4 on UNO)
// Capteur Humidité
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

// --------------------------------------------------------------------
// Capteur Capacitif
Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


// --------------------------------------------------------------------
// Data
float temperature = 0.0;
int uv = 0.0;
float humidite = 0.0;
int compteur = 0;

// --------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);

  // Démarrage capteur de température
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  Serial.println("Sensor temperature found!");

  // Démarrage capteur capacitif
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  // Démarrage capteur UV
  pinMode(A3,INPUT);
  Serial.println("Capteur UV sur A3");


  // Démarrage Ethernet
  Ethernet.begin(mac);
  server.begin();

  Serial.print("Server address:");
  Serial.println(Ethernet.localIP());
}

// --------------------------------------------------------------------
void loop()
{
  listenForEthernetClients();
  countTouch();
  delay(50);
}

// --------------------------------------------------------------------
void countTouch()
{
  // Capteur capacitif
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) 
  {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
//      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      compteur += 1;
      Serial.print(i); Serial.print(" // compteur="); Serial.println(compteur);
    }
  }

  // reset our state
  lasttouched = currtouched;
}

// --------------------------------------------------------------------
void readData()
{
  uv = analogRead(A3);
  temperature = hdc.readTemperature();
  humidite = hdc.readHumidity();

  if (countPrint<2)
  {
    Serial.print("temperature=");Serial.println(temperature);  
    Serial.print("uv=");Serial.println(uv);  
    Serial.print("humidite=");Serial.println(humidite);
    Serial.print("compteur=");Serial.println(compteur);
    Serial.println("");
    countPrint++;
  }
}

// --------------------------------------------------------------------
void listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
    //Serial.println("Got a client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          readData();
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/plain");
          client.println("Access-Control-Allow-Origin: *");
          client.println();
          // print the current readings, in HTML format:
          client.print("{\"temperature\":");
          client.print(temperature);
          client.print(",");
          client.print("\"uv\":");
          client.print(uv);
          client.print(",");
          client.print("\"humidite\":");
          client.print(humidite);
          client.print(",");
          client.print("\"compteur\":");
          client.print(compteur);
          client.print("}");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}


