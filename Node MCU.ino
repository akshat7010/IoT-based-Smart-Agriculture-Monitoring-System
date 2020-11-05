/* Comment this out to disable prints and save space */
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "Your auth key";
char ssid[] = "proj";//replace with your id & pass
char pass[] = "cool7010";
BlynkTimer timer;
SoftwareSerial s(D6,D5);
String data;
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
void sendSensor()
{
  s.write("s");
  if (s.available()>0)
    data=s.readString();
  String xval = getValue(data, '&', 0);
String yval = getValue(data, '&', 1);
String zval = getValue(data, '&', 2);
String wval = getValue(data, '&', 3);
  int h = xval.toFloat();
  int t = yval.toFloat();
  int m = zval.toFloat();
  int l = wval.toFloat();
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V2, m);
  Blynk.virtualWrite(V3, l);
    // Send EMAIL 
  // and PUSH Notification

  if(h > 35){
    Blynk.email("example@gmail.com", "ESP8266 Alert", "Temperature over 35C!");
    Blynk.notify("ESP8266 Alert - Temperature over 35C!Turning the fan ON");
  }
    if(m <30 && l<100)
    {
      Blynk.email("example@gmail.com", "ESP8266 Alert", "Soil is dry");
    Blynk.notify("ESP8266 Alert - Moisture level is below 30%!Turning the pump ON");
    }
}
void setup()
{
  s.begin(115200);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
