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
 // numéro de la «pin» digital sur Arduino
 int pin_bouton_01 = 0;

// ------------------------------------------------
// Démarrage de la carte
void setup() 
{
  // Bouton digital en input
  pinMode(pin_bouton_01, INPUT);
  
  // initialisation de la ledring
  pixels.begin();
}

// ------------------------------------------------
// Boucle d'exécution
void loop() 
{
  // ##############################################
  // >>>> CODE INTERFACE BOUTONS
  // ##############################################

  // On regarde l'état du bouton 01
  int etat_bouton_01 = digitalRead(pin_bouton_01);
  // S'il est appuyé
  if (etat_bouton_01 == HIGH) 
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
  else 
  {
    // on éteint les pixels par exemple ici
    // ( = mettre leur couleur en noir)
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // (0,0,0) correspond au noir
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  
  // ##############################################
  // >>>> CODE RÉCEPTION SMS
  // ##############################################
  // (code à écrire)
  // si le SMS reçu est «je pense à toi» alors  ...
  
}
