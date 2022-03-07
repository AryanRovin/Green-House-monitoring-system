

#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>





String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

 



void setup()
{
  // Debug console
  Serial.begin(9600);


}

void loop()
{
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String m1 = getValue(myString, ',', 0);
String m2 = getValue(myString, ',', 1);
String ldr = getValue(myString, ',', 2); 
String h = getValue(myString, ',', 3); 
String t = getValue(myString, ',', 4); 


int sensorValue1= m1.toFloat();
int sensorValue2 = m2.toFloat();
int ldrstatus = ldr.toFloat();
float humidity = h.toFloat();
float temp = t.toFloat();

  myString = "";
  Serial.println(sensorValue1);
// end new code
    }
  }

 
 

}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
