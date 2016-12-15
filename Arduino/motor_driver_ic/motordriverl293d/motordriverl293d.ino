#define PINL1 8  //left motor pin 1
#define PINL2 9  //left motor pin 2
#define PINR1 10  //right motor pin 1
#define PINR2 11  //right motor pin 2
 
void setup()
{
  //Set motor pinouts as output
  pinMode(PINL1,OUTPUT);
  pinMode(PINL2,OUTPUT);
  pinMode(PINR1,OUTPUT);
  pinMode(PINR2,OUTPUT);
  Serial.begin(9600);  
}  
 
void forward()
{
  digitalWrite(PINL1,HIGH);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,HIGH);
  digitalWrite(PINR2,LOW);
}
void backward()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,HIGH);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,HIGH);
}
void right()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,HIGH);
  digitalWrite(PINR1,HIGH);
  digitalWrite(PINR2,LOW);
}
void left()
{
  digitalWrite(PINL1,HIGH);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,HIGH);
}
void pause()
{
  digitalWrite(PINL1,LOW);
  digitalWrite(PINL2,LOW);
  digitalWrite(PINR1,LOW);
  digitalWrite(PINR2,LOW);
}
 
void loop()
{
  if(Serial.available()) //the loop() is interrupted when Arduino receives data
  {
    int c = Serial.read();  //'c' stores the character received 
    switch(c)
    {
      case 'w': forward(); Serial.println('w'); break;
      case 's': backward(); Serial.println('s');  break;
      case 'a': left(); Serial.println('a'); break;
      case 'd': right(); Serial.println('d'); break;
      case 'o': pause(); Serial.println('o'); break;
      default: Serial.println("Invalid"); break;
    } 
  }
}
