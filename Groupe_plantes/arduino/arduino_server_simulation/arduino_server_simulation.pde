// Sketch qui simule une arduino envoyant des données sur le résau
// via le protocole «websockets»

// ------------------------------------------------------
import org.webbitserver.*;

// ------------------------------------------------------
// Serveur qui traite les réceptions + transmissions de données
WebSocketServerP5 socket;

// ------------------------------------------------------
void setup() 
{
  size( 400, 400 );
  loadDestinations();
  socket = new WebSocketServerP5( this, 12345 );
  frame.setTitle("Serveur simulation");
}

// ------------------------------------------------------
void draw() 
{
  background(255);

  // Imprime la liste des connexions
  String s="";
  synchronized(socket.connections)
  {
    for (WebSocketConnection connection : socket.connections)
    {
      s+= socket.getIP( connection )+"\n";
    }
  }
  fill(0);
  text(s,5,12);

  // Envoie d'un message d'exemple (position de la souris)
  // Le message pourrait contenir des informations captées sur la plante
  socket.sendAll(""+mouseX);
}

// ------------------------------------------------------
synchronized void stop() 
{
  socket.stop();
}


// ------------------------------------------------------
void loadDestinations()
{
  //XML xml = loadXML(config);
}

// ------------------------------------------------------
void websocketOnMessage(WebSocketConnection con, String msg) 
{
}

// ------------------------------------------------------
void websocketOnOpen(WebSocketConnection con) 
{
  println("A client joined : "+ socket.getIP(con) );
}

// ------------------------------------------------------
void websocketOnClosed(WebSocketConnection con) 
{
   // println("A client left");
}

