// ------------------------------------------------------
var websocket;

// ------------------------------------------------------
function connect(server)
{
	websocket = new WebSocket(server);
	
	websocket.onmessage = function(e)
	{
		if (typeof onMessage == 'function')
		{
		  	onMessage( e.data );
		}
	}

	websocket.onerror = function(e)
	{
		console.log("websocket.js - erreur : "+e);
	}
}
