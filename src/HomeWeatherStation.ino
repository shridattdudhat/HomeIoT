// This #include statement was automatically added by the Particle IDE.
#include <SparkTime.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_Si7021.h>
#include <Adafruit_GFX.h>

#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256

#include "blynk.h"

char auth[] = "55eff345a94e4b27afc68b11b99ca245";
//long rssi = WiFi.RSSI();

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long locTime;


bool resetFlag = false;
int cloudResetFunction(String Command);
int cloudTweetFunction(String Command);

Adafruit_Si7021 sensor = Adafruit_Si7021();
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

 void setup()
 {
    Particle.function("reboot",cloudResetFunction);
    Particle.function("tweet",cloudTweetFunction);
    sensor.begin();
    Blynk.begin(auth);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    Time.zone(+5.50);
    //Serial.begin(9600);
   
    display.display();
    delay(2000);

    //Clear the buffer.
    display.clearDisplay();
    display.setTextSize(1.8);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
 }

 void loop()
 {
    locTime = Time.local();
    Blynk.run();
    if (resetFlag)
    {
        System.reset();
    }
        
    float hum = sensor.readHumidity();
    float temp = sensor.readTemperature();
     
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, hum);
     
    display.setCursor(2, 4);
    display.print(Time.format(Time.now(), "%Y-%m-%d | %I:%M%p"));
     
    display.setCursor(5, 16);
    display.print("Home Weather Station");
    display.setCursor(5, 24);
    display.print("--------------------");
    
    display.setCursor(0, 32);
    display.print("Temperature");
    display.setCursor(80, 32);
    display.print("Humidity");
     
    display.setCursor(0, 42);
    display.print(temp);display.print("*C");
    display.setCursor(80, 42);
    display.print(hum);display.print("%");
     
    display.setCursor(0,56);
    display.print("WiFi : Connected !");

    display.display(); //you have to tell the display to...display
    delay(2000);
    display.clearDisplay();

    //Particle.publish("Temp",String(temp), PRIVATE);
    //Particle.publish("Hum",String(hum), PRIVATE);
    //Repeat after a 1 second pause
 }


int cloudResetFunction(String command)
{
  if (command == "reboot")
  resetFlag = true;
  return 1;
}

int cloudTweetFunction(String command)
{   
    float hum = sensor.readHumidity();
    float temp = sensor.readTemperature();
    if (command == "tweet")
    Blynk.tweet("Tweet from HomeWeatherStation :: 'Hey, My #RaspberryPi can tweet now!' | #Blynk #Particle");
    else if(command == "tweetTempHum")
    Blynk.tweet(String("Tweet from HomeWeatherStation :: \n Temperature >>") + temp +"*C | Humidity >>" + hum +"% |\n #Ahmedabad #Weather #ElectronicsFun");
    Particle.publish("Tweet",String("Tweet Done!"), PRIVATE);
    return 1;
}