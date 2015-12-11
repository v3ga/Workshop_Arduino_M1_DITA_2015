

var degrees = 0;

// --------------------------------------------
function setup()
{
  	createCanvas(500, 500);

  	// Compas
	Compass.watch(function (heading) 
	{
  		degrees = heading;
	});

	// Position
	if(geoPosition.init())
	{
		geoPosition.getCurrentPosition(success_callback,error_callback,{enableHighAccuracy:true});
	}
}

// --------------------------------------------
function draw()
{
	background( map(degrees,0,360,0,255) );
}

// --------------------------------------------
function success_callback(p)
{
	console.log(p.coords.latitude + ";" + p.coords.longitude);
}

// --------------------------------------------
function error_callback(p)
{
}