var ARDUINO_URL = "http://192.168.0.25"
var DEBUG = true;
var arduinoData;

// --------------------------------------------
function setup()
{
	var myCanvas = createCanvas(600, 400);
  	myCanvas.parent('temperature');  	
  	setInterval(loadData,1000);
  	loadData();
}

// --------------------------------------------
function draw()
{
	this.drawingContext.clearRect(0 , 0, width, height);
	if (arduinoData){
		var h = map(arduinoData.temperature,0,30,0,height-30);	
		var x = 220;	
		noStroke();
		fill(255);
		rect(x,height-h,30,h);
		text(arduinoData.temperature+"°C",x,height-h-20);
	}
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
	if (DEBUG)
		console.log(arduinoData);
}

