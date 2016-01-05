// ------------------------------------------------
#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>

// ------------------------------------------------
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// ------------------------------------------------
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

// ------------------------------------------------
String number = "0671737735";

// ------------------------------------------------
void setup()
{
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  // make it slow so its easy to read!
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));

  // Print SIM card IMEI number.
  char imei[15] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }
  Serial.println("FONA Ready");
  delay(500);


  // Test envoi
  //fona.unlockSIM("1234");
  sendSMS("0671737735", "Hello");
}

// ------------------------------------------------
void loop()
{
}

// ------------------------------------------------
void sendSMS(char* number, char* text)
{
  Serial.print(F("Sending to "));
  Serial.print(number);

  if (!fona.sendSMS(number, text)) {
    Serial.println(F("Failed :("));
  } else {
    Serial.println(F("Sent! :)"));
  }
  
}
