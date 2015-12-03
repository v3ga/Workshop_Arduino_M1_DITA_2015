// ------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>
#include <WebSocket.h>

// ------------------------------------------------------
// Enabe debug tracing to Serial port.
#define DEBUG
#define MAX_FRAME_LENGTH 64

// ------------------------------------------------------
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xFD, 0x39 };

// ------------------------------------------------------
// Variable qui va contenir par exemple la valeur récupérée d'un capteur
int capteur_valeur = 0;

// ------------------------------------------------------
// Message que l'on va envoyer au client
String message = "";

// ------------------------------------------------------
WebSocketServer wsServer;

// ------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }  
  
  Serial.println(Ethernet.localIP());

  wsServer.registerConnectCallback(&onConnect);
  wsServer.registerDataCallback(&onData);
  wsServer.registerDisconnectCallback(&onDisconnect);  
  wsServer.begin();

  delay(100); // Give Ethernet time to get ready
}

// ------------------------------------------------------
void loop() 
{
  // Should be called for each loop.
  wsServer.listen();
    Serial.println("*");

  // Do other stuff here, but don't hang or cause long delays.
  delay(100);

  // Mise à jour de la variable
  // (devrait plutot etre quelquechose comme capteur_valeur = analogRead(A0) par exemple)
  capteur_valeur = (capteur_valeur+1)%1024;

  // S'il y a des clients connectés, on constitue le message
  // et on l'envoi
  if (wsServer.connectionCount() > 0) 
  {
    message = String(capteur_valeur);
    wsServer.send((char*)message.c_str(), message.length());
  }
}

// ------------------------------------------------------
// You must have at least one function with the following signature.
// It will be called by the server when a data frame is received.
void onData(WebSocket &socket, char* dataString, byte frameLength) 
{

#ifdef DEBUG
  Serial.print("Got data: ");
  Serial.write((unsigned char*)dataString, frameLength);
  Serial.println();
#endif

  // Just echo back data for fun.
  socket.send(dataString, strlen(dataString));
}

// ------------------------------------------------------
void onConnect(WebSocket &socket) 
{
  Serial.println("onConnect called");
}

// ------------------------------------------------------
void onDisconnect(WebSocket &socket) 
{
  Serial.println("onDisconnect called");
}


