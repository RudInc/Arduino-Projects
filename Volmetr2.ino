#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

float fResA , fResV;
int iU, iA;
void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  delay(300);
  display.begin(SSD1306_SWITCHCAPVCC);  // Initialize display with the I2C address of 0x3C
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();  // Clear the buffer
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  display.setTextWrap(false);  
  display.setTextSize(2);
  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)
}



void loop() 
{
 display.clearDisplay();

  display.setCursor(0, 10);  // (x,y)
  iU = analogRead(A0);
  iA = analogRead(A1);
  
  
  if(iU!=1023)
  {
  fResV = 1.1 * iU/1023 * 10.8;
  Serial.print("U="); Serial.println(fResV);Serial.println(" V");
  display.print("U="); display.print(fResV); display.setCursor(90, 10); display.print("V");
  }
  else
  {
    display.print("High V!");
  }
  display.setCursor(0, 30);
  
  if(iA!=1023)
  {
  fResA = 1.1 * iA/1023 * 9.5;
  display.print("I="); display.print(fResA); display.setCursor(90, 30); display.print("A");
  }
  else
  {
    display.print("High A!");
  }
  if(iA!=1023&&iU!=1023)
  {
    display.setCursor(0, 50);
    display.print("P="); display.print(fResA*fResV); display.setCursor(90, 50); display.print("VA");
    
  }
  display.display();
 delay(300);
}
