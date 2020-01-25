#include<Servo.h>
Servo myservo;
const int trigPin=9;
const int echoPin=10;
#define led 6
int thresh=30;
long duration;
int distance;
int lid_status;
int pos=0;
int input;
void setup() 
{
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  lid_status=0;
  Serial.begin(9600);
}
int lid_open(int stat)
{
  for (pos = 0; pos <= 90; pos += 1)
  {
    myservo.write(pos);
  }
  return stat;
}

int lid_close()
{
  if(distance>=thresh && lid_status==1)
  {
    for (pos = 180; pos >= 0; pos -= 1)
    {
      myservo.write(pos);
      
    }
    return 0;
  }
  else
  {
    return 1;
  }
}

void loop()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration=pulseIn(echoPin,HIGH);

  distance=duration*0.034/2;
  //Serial.println(distance);
  if(Serial.available()>0)
  {
    Serial.println("on");
    input=Serial.read();
    Serial.println(input);
    if(input==49 && lid_status==0)
    {
      lid_status=lid_open(2);
    }
    if(input==48 && lid_status==2)
    {
      lid_status=lid_close();
    }
  }
    
  if(distance<=thresh && lid_status==0)
  {
    lid_status=lid_open(1);
    
  }
  else if( distance>thresh && lid_status==1)
  {
    delay(1000);
    lid_status=lid_close();
    Serial.println(distance);
  }
}
