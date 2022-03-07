#include <SoftwareSerial.h>

//DHT
#include "DHT.h"
#define DHTPIN 7 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//float h,t;

//LCD
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Mosture
int sensorPin1 = A0;
int sensorPin2 = A2; 

//int sensorValue1,sensorValue2;


//LDR
const int ldr = A1;
//int ldrstatus;

SoftwareSerial nodemcu(2,3);
 
 
String cdata; // complete data, consisting of sensors values
 
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
dht.begin();

 //Display Setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(2000);
 
}
 
void loop()
{
 float h = dht.readHumidity();
 float t = dht.readTemperature();

 int sensorValue1 = analogRead(sensorPin1);
 sensorValue1 = abs(map(sensorValue1,550,0,0,100));

 int sensorValue2 = analogRead(sensorPin1);
 sensorValue2 = abs(map(sensorValue1,550,0,0,100));
 
 int ldrstatus = analogRead(ldr);
  



//Serial.println(ldrstatus); 
 
   cdata = cdata + sensorValue1+","+sensorValue2+","+ldrstatus+","+h+","+t; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(2000); // 100 milli seconds
   cdata = ""; 
   //Display();
 
}

void Display(){
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.print("Temperature- ");
//  display.print();
  display.print("C");
  display.display();
  delay(2000);
  display.clearDisplay();
//  
//  display.setTextSize(2);      // Normal 1:1 pixel scale
//  display.setTextColor(SSD1306_WHITE); // Draw white text
//  display.setCursor(0, 0);     // Start at top-left corner
//  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.print("Humidity -");
//  display.print(h);
  display.print(" %");
  display.display();
  delay(2000);
  display.clearDisplay();
   
  display.print("Mosture 1- ");
  display.print(sensorValue1);
  display.print("%");
  display.display();
  delay(2000);
  display.clearDisplay();
 
  display.print("Mosture 2- ");
  display.print(sensorValue2);
  display.print("%");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.print("Light- ");
  display.print(ldrstatus);
  display.display();
  delay(1000);
  display.clearDisplay();

}
