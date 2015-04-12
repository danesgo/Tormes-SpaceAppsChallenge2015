#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int i=0,j=0;
int Mat[62];

void setup(){                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop(){ 
    while(true)
    {   
      for(i=0;i<=62;i++)
      {
        Esquema();
        j=30*cos(0.1*i);
        display.drawPixel(i,j+32,WHITE);
        display.drawLine(64,i,71,i,WHITE);
        display.drawPixel(73+i,random(20,44),WHITE);
        display.display();  
      }
     display.display();
     display.clearDisplay();
    }
}

void Esquema()
{    
    display.drawRect(0,0,127,63, WHITE);
    display.drawRect(63,0,10,63,WHITE);
    display.display();
}
