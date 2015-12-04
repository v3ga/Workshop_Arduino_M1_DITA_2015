import processing.serial.*;


float timeScale = 60*5;
float timeStart = 0;

int hourStart = 4;
int minStart = 59;
int secondStart = 0;

void setup()
{
  size(600,600);
  timeStart = millis();
}

void draw()
{
  float t = hourStart * 3600 + minStart*60 + secondStart + (millis() - timeStart)/1000.0 * timeScale;  


  int H = getHours(t);
  int MN = getMinutes(t);
  int S = getSeconds(t);

  if (H<5)
    background(255);
  else 
  if (H>=5)
  {
    if (MN<1)
      background(255,0,0);
    else
      background(0,255,0);
  }

  fill(0);
  text(nf(H,2)+"h "+nf(MN,2)+"mn " + nf(S,2)+"s",5,12);
}

int getHours(float s)
{
  return int(s / 3600.0);
}

int getMinutes(float s)
{
  s = s - 3600*getHours(s);
  return int(s / 60.0);
}

int getSeconds(float s)
{
  s = s - 3600*getHours(s) - 60*getMinutes(s);
  return int(s);
}
