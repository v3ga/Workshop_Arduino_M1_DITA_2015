var ARDUINO_URL = "http://192.168.0.25"
var arduinoData;

// --------------------------------------------
function setup()
{
  	createCanvas(500, 500);
  	setInterval(loadData,1000);
}

// --------------------------------------------
function draw()
{
	this.drawingContext.clearRect(0 , 0, width, height);
}

// --------------------------------------------
function loadData()
{
	loadJSON(ARDUINO_URL, onDataLoaded); 
}

// --------------------------------------------
function onDataLoaded(data)
{
	arduinoData = data;
}

