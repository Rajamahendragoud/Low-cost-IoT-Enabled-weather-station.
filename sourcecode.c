#include <SoftwareSerial.h>
#include  <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // 8-RS, 9-EN, 10-D4, 11-D5, 12-D6, 13-D7


SoftwareSerial esp8266(6,7);

#define soil         2
#define rain         3
#define watermotor   4
#define coolant      5

#define buzzer       8

void title(void)
{
  lcd.clear();
  lcd.print("SMART AGRICULTE");
  lcd.setCursor(0,1);
  lcd.print("& WEATHER MONTG");
}

void setup() 
  {
  lcd.init();
   lcd.backlight();
   lcd.print("");
  sendData("AT+CWSAP=\"IOT_AGRICULTURE\",\"12345678\",5,3\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
   
  lcd.begin(16, 2);
  pinMode(soil, INPUT);
  pinMode(rain, INPUT);
  pinMode(watermotor, OUTPUT);
  pinMode(coolant, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  title();
  delay(3000);
  lcd.clear();
}


void loop() {

     int readData = DHT.read11(dataPin);
          lcd.setCursor(0,0); 
          lcd.print("Tmp:"); 
          lcd.print(temp); 
          lcd.print((char)223); //degree symbol
          lcd.print("C ");

          lcd.setCursor(10,0);
          lcd.print("Hm:");
          lcd.print(hum);
          lcd.print("% ");


          if(temp>33)
          {
            digitalWrite(coolant,HIGH);
          }
          else
          {
             digitalWrite(coolant,LOW);
          }

         
 
      if(soil_flag==0)
      {
      lcd.setCursor(8,1);
      lcd.print("SOIL:WET");
      digitalWrite(watermotor,LOW);
      }
     else
     {
       lcd.setCursor(8,1);
      lcd.print("SOIL:DRY");
      digitalWrite(watermotor,HIGH);
     }

       if(rain_flag==0)
      {
      lcd.setCursor(0,1);
      lcd.print("RAIN:YS");
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
      }
     else
     {
      lcd.setCursor(0,1);
      lcd.print("RAIN:No");
      digitalWrite(buzzer,LOW);
     
     }


      webpage +=  "<center><h1 style=\"color:red;text-align:center\">IOT BASED AGRICULTURE & WEATHER FORECASTING</h1>";
            ///webpage += "<p><h2 style=\"color:green;text-align:center\">By NEC ECE BATCH B7</h2>";

        webpage += "<p><h2>";
      if (rain_flag == 1)
        webpage+= "RAIN_STATUS:NO";
      else
        webpage+= "RAIN_STATUS:YES";
      webpage += "</p></h2>";

       webpage += "<p><h2>";
      if (soil_flag == 1)
        webpage+= "SOIL_STATUS:DRY";
      else
        webpage+= "SOIL_STATUS:WET";
      webpage += "</p></h2>";

       webpage += "<p><h2>";
      webpage+= "Temperature:";
      webpage+= temp;
      webpage+= (char)223;
      webpage+= " C";
      webpage += "</p></h2>";
      
       webpage += "<p><h2>";
       webpage += "Humidity:";
       webpage += hum;
       webpage+= "%";

  }
  else
  {
    
    
  }
  if(digitalRead(soil) == LOW)
      soil_flag = 0;
       else
      soil_flag = 1;

      if(digitalRead(rain) == LOW)
      rain_flag = 0;
       else
      rain_flag = 1;

      

     }
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = ""; 
    if(debug)
    {
      Serial.print(response);
    }
    return response;
}


}
