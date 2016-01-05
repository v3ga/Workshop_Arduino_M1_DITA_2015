

// ------------------------------------------------
// https://learn.adafruit.com/adafruit-cap1188-breakout/using-with-arduino
// Librairie qui permet de capter les «touch» capacitifs
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// Or...Use I2C, with reset pin
Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);


// ------------------------------------------------
// Librairie qui permet d'accéder aux fonctionnalités
// pour piloter la ledrings
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Propriétés pour la ledring
// «pin» digital sur laquelle elle est connectée
#define PIN            6
// nombre de pixels
#define NUMPIXELS      25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// ------------------------------------------------
// Démarrage de la carte
void setup() 
{
  // Port série
  Serial.begin(9600);

  // Initialisation boutons capacitifs
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
 
  // initialisation de la ledring
  pixels.begin();
}

// ------------------------------------------------
// Boucle d'exécution
void loop() 
{
  // ##############################################
  // >>>> CODE INTERFACE BOUTONS CAPACITIFS
  // ##############################################
  uint8_t touched = cap.touched();

  // Si le bouton 1 est actif
  if (isButtonTouch(touched,1)) 
  {
    // on pilote la couleur du led ring
    // ici on allume les pixels 0,1,2 en rouge
    // le modèle couleur est le modèle RGB 
    pixels.setPixelColor(0, pixels.Color(100,0,0)); // (100,0,0) correspond au rouge
    pixels.setPixelColor(1, pixels.Color(100,0,0));
    pixels.setPixelColor(2, pixels.Color(100,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    
    // puis on envoie un SMS particulier
    // (code à écrire) 
    // >
    
  } 
  // Si le bouton 2 est actif (on suppose ici que le bouton 1 est inactif)
  else if (isButtonTouch(touched,2)) 
  {
    // on éteint les pixels par exemple ici
    // ( = mettre leur couleur en noir)
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // (0,0,0) correspond au noir
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  // Si le bouton 3 est actif (mais 1 & 2 inactifs)
  else  if (isButtonTouch(touched,3)) 
  {
    // Faire quelque chose pour le bouton 03
  } // Si le bouton 4 est actif (mais 1 & 2 & 3 inactifs)
  else if (isButtonTouch(touched,4)) 
  {
    // Faire quelque chose pour le bouton 04
  }
  // etc ...
  
  
  // ##############################################
  // >>>> CODE RÉCEPTION SMS
  // ##############################################
  // (code à écrire)
  // si le SMS reçu est «je pense à toi» alors  ...

  // On attend un petit peu
  delay(100);
}

// ------------------------------------------------
bool isButtonTouch(uint8_t touched, uint8_t i)
{
    return (touched & (1 << i));
}


