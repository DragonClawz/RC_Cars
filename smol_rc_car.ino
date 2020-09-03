#include <LiquidCrystal.h>//For the LCD I2C
#include <Wire.h> 
#include<LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
//I2C pins declaration

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial BT(10, 11); //TX, RX respetively

String readdata;

//LiquidCrystal lcd(8,9,4,5,6,7);   //defining lcd pins

const int dataIN = 2; //IR sensor INPUT
const int redPin = 12;
const int bluePin = 8;
int ledDelay = 50;

//speed = 3.15159*(D/100000)*(rpm*60) // speed in km/hr

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long lcdrefresh; // To store time for lcd to refresh

float rpm; // RPM value
float speedy; //value of speed
//int h_r;
//int h_l;

int nana;

boolean currentstate; // Current state of IR input scan
boolean prevstate; // State of IR sensor in previous scan

void setup()
{
  pinMode(dataIN,INPUT);
  lcd.begin(16,2);     
  lcd.backlight();
  prevmillis = 0;
  prevstate = LOW;
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(3, OUTPUT); // connect to input 1 of l293d
  pinMode(4, OUTPUT); // connect to input 4 of l293d
  pinMode(5, OUTPUT); // connect to input 3 of l293d
  pinMode(6, OUTPUT); // connect to input 2 of l293d  
  pinMode (redPin, OUTPUT);
  pinMode (bluePin, OUTPUT);
}

void loop()
{
  
  
  


  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  
  if (readdata.length() > 0) {
    Serial.println(readdata); // print data to serial monitor
// if data received as forward move robot forward

if (readdata == "reverse"){
  nana = 1;
}
else if (readdata == "forward") {
  nana = 2;
}
else if (readdata == "right") {
  nana = 3;
}
else if (readdata == "left") {
  nana = 4;
}
else if (readdata == "stop") {
  nana = 0;
}
else if (readdata == "1") {

    Serial.println(readdata);
    digitalWrite(redPin, HIGH); // turn the red light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(redPin, LOW); // turn the red light off
    delay(ledDelay); // wait 50 ms

    digitalWrite(redPin, HIGH); // turn the red light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(redPin, LOW); // turn the red light off
    delay(ledDelay); // wait 50 ms

    digitalWrite(redPin, HIGH); // turn the red light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(redPin, LOW); // turn the red light off
    delay(ledDelay); // wait 50 ms

    delay(100); // delay midpoint by 100ms

    digitalWrite(bluePin, HIGH); // turn the blue light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(bluePin, LOW); // turn the blue light off
    delay(ledDelay); // wait 50 ms

    digitalWrite(bluePin, HIGH); // turn the blue light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(bluePin, LOW); // turn the blue light off
    delay(ledDelay); // wait 50 ms

    digitalWrite(bluePin, HIGH); // turn the blue light on
    delay(ledDelay); // wait 50 ms

    digitalWrite(bluePin, LOW); // turn the blue light off
    delay(ledDelay); // wait 50 ms
 
}
else if (readdata == "2") {
  Serial.println(readdata);
  
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
}

   while (nana = 1) {
    while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  
  Serial.println(readdata);
     // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  //Serial.println(dataIN);

  if (readdata != "reverse") {
    nana = 0;
    digitalWrite (3, LOW);
    digitalWrite (5, LOW);
    digitalWrite (4, LOW);
    digitalWrite (6, LOW);
    delay(100);
    break;
  }
  
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         
         speedy = (3.14*(0.3)*(rpm/60)); // speed in m/s
         
         prevmillis = micros(); // store time for next revolution calculation

         
         
      
       }
 
   }
   /*if ( currentstate == 0)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed of Motor");
      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(0);         
      lcdrefresh = 0;
     }   */
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-lcdrefresh ) >= 100 )
    {
      //speedy = 3.14159*(38/100)*(rpm/60); // speed in m/s
     // lcd.begin(16,2);     
    //lcd.backlight();
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed = ");
      lcd.print(speedy);
      
      /*lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);         
      lcdrefresh = millis(); */  
    }
     digitalWrite (3, HIGH);
     digitalWrite (5, HIGH);
     digitalWrite (4, LOW);
     digitalWrite (6, LOW);
     delay(100);

    
  
  }
  // if data received as reverse move robot reverse

  while (nana = 2) {
    while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  
  Serial.println(readdata);
     // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  //Serial.println(dataIN);

  if (readdata != "forward") {
    nana = 0;
    digitalWrite (3, LOW);
    digitalWrite (5, LOW);
    digitalWrite (4, LOW);
    digitalWrite (6, LOW);
    delay(100);
    break;
  }
  
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         
         speedy = (3.14*(0.3)*(rpm/60)); // speed in m/s
         
         prevmillis = micros(); // store time for next revolution calculation

         
         
      
       }
 
   }
   /*if ( currentstate == 0)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed of Motor");
      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(0);         
      lcdrefresh = 0;
     }   */
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-lcdrefresh ) >= 100 )
    {
      //speedy = 3.14159*(38/100)*(rpm/60); // speed in m/s
     // lcd.begin(16,2);     
    //lcd.backlight();
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed = ");
      lcd.print(speedy);
      lcd.print(" m/s");

      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);
     
      
      /*lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);         
      lcdrefresh = millis(); */  
    }
     digitalWrite (3, LOW);
     digitalWrite (5, LOW);
     digitalWrite (4, HIGH);
     digitalWrite (6, HIGH);
     delay(100);

    
  
  }
 while (nana = 3) {
    while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  
  Serial.println(readdata);
     // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  //Serial.println(dataIN);

  if (readdata != "right") {
    nana = 0;
    digitalWrite (3, LOW);
    digitalWrite (5, LOW);
    digitalWrite (4, LOW);
    digitalWrite (6, LOW);
    delay(100);
    break;
  }
  
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         
         speedy = (3.14*(0.3)*(rpm/60)); // speed in m/s
         
         prevmillis = micros(); // store time for next revolution calculation

         
         
      
       }
 
   }
   /*if ( currentstate == 0)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed of Motor");
      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(0);         
      lcdrefresh = 0;
     }   */
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-lcdrefresh ) >= 100 )
    {
      //speedy = 3.14159*(38/100)*(rpm/60); // speed in m/s
     // lcd.begin(16,2);     
    //lcd.backlight();
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed = ");
      lcd.print(speedy);
      lcd.print(" m/s");

      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);
     
      
      /*lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);         
      lcdrefresh = millis(); */  
    }
     digitalWrite (3, LOW);
     digitalWrite (5, HIGH);
     digitalWrite (4, HIGH);
     digitalWrite (6, LOW);
     delay(100);

    
  
  }
  while (nana = 4) {
    while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  
  Serial.println(readdata);
     // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  //Serial.println(dataIN);

  if (readdata != "left") {
    nana = 0;
    digitalWrite (3, LOW);
    digitalWrite (5, LOW);
    digitalWrite (4, LOW);
    digitalWrite (6, LOW);
    delay(100);
    break;
  }
  
 if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         
         rpm = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         
         speedy = (3.14*(0.3)*(rpm/60)); // speed in m/s
         
         prevmillis = micros(); // store time for next revolution calculation

         
         
      
       }
 
   }
   /*if ( currentstate == 0)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed of Motor");
      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(0);         
      lcdrefresh = 0;
     }   */
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-lcdrefresh ) >= 100 )
    {
      //speedy = 3.14159*(38/100)*(rpm/60); // speed in m/s
     // lcd.begin(16,2);     
    //lcd.backlight();
      //lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Speed = ");
      lcd.print(speedy);
      lcd.print(" m/s");

      lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);
     
         
      /*lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print(rpm);         
      lcdrefresh = millis(); */  
    }
     digitalWrite (3, HIGH);
     digitalWrite (5, LOW);
     digitalWrite (4, LOW);
     digitalWrite (6, HIGH);
     delay(100);

    
  
  }

  } /*else if (readdata == "1")
 {
   digitalWrite (headlight_r, HIGH);
   digitalWrite (headlight_l, HIGH);


 }

  else if (readdata == "2")
 {
   digitalWrite (headlight_r, LOW);
   digitalWrite (headlight_l, LOW);


 }*/




readdata="";
 lcd.setCursor(0,0);
      lcd.print("Speed = ");
      lcd.print("0.00");
      lcd.print(" m/s");

 lcd.setCursor(0,1);
      lcd.print("RPM = ");
      lcd.print("0.00");
  
}
