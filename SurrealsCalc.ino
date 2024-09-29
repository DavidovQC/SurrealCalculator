// mapping suggestion for Arduino MEGA
//BUSY -> 7, RST -> 9, DC -> 8, CS-> 53, CLK -> 52, DIN -> 51
/*

To do: 
-Design keypad position
-

*/
// include library, include base class, make path known
#include <GxEPD.h>

#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>

#include GxEPD_BitmapExamples

GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9);
GxEPD_Class display(io, /*RST=*/ 9, /*BUSY=*/ 7); // default selection of (9), 7

#include "image.h" //Powerdown screen


//#define DEMO_DELAY 3*60 // seconds
//#define DEMO_DELAY 1*60 // seconds
int DEMO_DELAY = 10;

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init(115200); // enable diagnostic output on Serial
  Serial.println("setup done");

  // //Regular draw
  display.drawBitmap(gImage_Ordinals, sizeof(gImage_Ordinals));
  // delay(DEMO_DELAY * 1000);
  //display.powerDown();

}

int box_x = 0;
int box_y = 0;
int box_w = 1000;
int box_h = 19;

String inputString = "OK";
String outputString = "";


void loop(){
  display.eraseDisplay();
  
  //display.drawPagedToWindow(showValueBoxCallback, box_x, box_y, box_w, box_h);
  // display.setTextColor(GxEPD_BLACK);
  display.drawPagedToWindow(printInputString, box_x, box_y, box_w, box_h);
  // // for(int i= 0; i < 10; i++){
  // //   inputString = inputString + "count ";

  // display.setCursor(box_x, box_y);
  // display.println("Surreal Numbers");
  // delay(DEMO_DELAY * 3000);
  delay(DEMO_DELAY * 1000);
  // // }
  // // display.powerDown(); //power down
}

void printBox(){
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
}

void printInputString(){  
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(10, 10);
  display.print("Hello World");
}

