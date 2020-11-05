//Arduino code
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>
#include <dht.h>
dht DHT;
SoftwareSerial s(11,10);
 int resval = 0;  // holds the value
int respin = A5; // sensor pin used
int sensor_pin = A0;
int output_value ;
LiquidCrystal lcd(2,3,4,5,6,7);
void setup() {
  s.begin(115200);
  Serial.begin(115200);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  lcd.begin(16, 2);
}
 
void loop() {
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
  lcd.setCursor(0, 0);
    lcd.clear();
  if (resval<=100){ lcd.print("WL: Empty");}
  else if (resval>100 && resval<=135){ lcd.print("WL: Low"); } 
  else if (resval>135 && resval<=170){ lcd.print("WL: Medium"); }
  else if (resval>170){   lcd.print("WL: High"); digitalWrite(9, LOW);}
  if(DHT.temperature>35)
      digitalWrite(12, HIGH);
  else
      digitalWrite(12, LOW);
    int chk = DHT.read11(8);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
   output_value= analogRead(sensor_pin);
   output_value = map(output_value,550,0,0,100);
   if(output_value<0)
    output_value=0;
   if(output_value <30 && resval<100)
    {
      digitalWrite(9, HIGH); 
    }
   Serial.print("Moisture : ");
   Serial.print(output_value);
   Serial.println("%");
   String str =String(DHT.temperature)+"&"+
   String(DHT.humidity)+"&"+
   String(output_value)+"&"+
   String(resval)+"&";
   if(s.available()>0)
  {
   s.print(str);
  }
lcd.print("T: ");
lcd.print(DHT.temperature);
 lcd.setCursor(0, 1);
lcd.print("M: ");
   lcd.print(output_value);
   lcd.println("%");
lcd.print("H: ");
lcd.print(DHT.humidity);
  delay(3000); 
}
  
