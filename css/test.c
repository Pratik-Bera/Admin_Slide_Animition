int blue = 0;  // for incoming serial data
int moisture_sensor  = A0;
int moisture;
int limit = 500;
int pump = 3;
int led = 13;
int pump_time = 3000;

int bluer=0;
int rain_sensor=A4;
int rain;
int limitr=200;
int cover=5;
int cover_time=3000;
void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(moisture_sensor,INPUT);
  pinMode(pump,OUTPUT);
  pinMode(led,OUTPUT);

  Serial1.begin(9600);
  pinMode(rain_sensor,INPUT);
  pinMode(cover,OUTPUT);
}

void loop() 
{
  moisture = analogRead(moisture_sensor);
  Serial.print("Moisture=");
  Serial.print(moisture);
  Serial.println();
  
  while(Bluetooth()==1)
  {
    Pump(1);
    blue = 0;
    break;
  }
  while(Bluetooth()==0)
  {
    if(moisture<limit)
    {
      Pump(1);
      break;  
    }
    else
    { 
      Pump(0);
      break;
    }
  }

    rain=analogRead(rain_sensor);
    Serial1.print("Rain=");
    Serial1.print(rain);
    Serial1.println();

    while(Bluetoothr()==1)
  {
    Cover(1);
    bluer = 0;
    break;
  }
  while(Bluetoothr()==0)
  {
    if(rain<limitr)
    {
      Cover(1);
      break;  
    }
    else
    { 
      Cover(0);
      break;
    }
  }



}

int Bluetooth()
{
   // send data only when you receive data:
   if(Serial.available() > 0) 
   {
    // read the incoming byte:
    blue = Serial.read();

    // say what you got:
    Serial.print("Bluetooth");
    Serial.println(blue);
    if(blue == 48)
      return 0;
    if(blue == 49)
      return 1;
  }
  else 
  return 0;
}

int Bluetoothr()
{
   // send data only when you receive data:
   if(Serial1.available() > 0) 
   {
    // read the incoming byte:
    bluer = Serial1.read();

    // say what you got:
    Serial1.print("Bluetoothr");
    Serial1.println(bluer);
    if(bluer == 48)
      return 0;
    if(bluer == 49)
      return 1;
  }
  else 
  return 0;
}

void Pump(int stat)
{
  if(stat == 0)
  {
    digitalWrite(pump,stat);
    digitalWrite(led,stat);
    Serial.println("Pump OFF");
  }
  if(stat == 1)
  {
    digitalWrite(pump,stat);
    digitalWrite(led,stat);
    Serial.println("Pump ON");
    delay(pump_time);
  }
}



void Cover(int stat)
{
  if(stat == 0)
  {
    digitalWrite(cover,stat);
    // digitalWrite(led,stat);
    Serial1.println("cover OFF");
  }
  if(stat == 1)
  {
    digitalWrite(cover,stat);
    // digitalWrite(led,stat);
    Serial.println("cover ON");
    delay(cover_time);
  }
}