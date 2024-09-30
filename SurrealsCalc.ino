/* Research notes:
Sept 30th: When you write to the display with drawPagedToWindow, the cursor and color are reset. 
Sept 30th: One LCD has 15 lines whenever I move down by 20 units.



*/



/*







// mapping suggestion for Arduino MEGA
//BUSY -> 7, 
RST -> 9, 
DC -> 8, 
CS-> 53, 
CLK -> 52, 
DIN -> 51







*/


/*










To do: 
-Design keypad positioning
-Model case
-Write code to update line









*/


/*












Notes: display.drawPagedToWindow takes the following arguments: void function, int x, int y, int w, int h.
the first argument must be a void element. I intialized a string called inputString and wrote a void function which writes that string to the display.













*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include library, include base class, make path known //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 8, /*RST=*/ 9);
GxEPD_Class display(io, /*RST=*/ 9, /*BUSY=*/ 7); // default selection of (9), 7

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////import start image/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "image.h" //Powerdown screen

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//line where each piece of text is printed structure

//Box for top line (probably add ~10 to y value to get to next line)
int box_x = 0;
int box_y = 0;
int box_w = 1000;
int box_h = 19;


//Strings:
String inputString = "OK";
String outputString = "";
String currString = "Rabbit season!";
bool rightJustified = true;

int cursor_x = box_x + 10;
int cursor_y = box_y + 10;

int DEMO_DELAY = 3;


///Note Sept 30th: When the display is printed to, the cursor and color settings are reset! 


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


  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(10, 10);

}


void loop(){
 
  printOnCurrentLine("Duck season!");
  nextLine();
  printOnCurrentLine("Rabbit season!");
  nextLine();

}

//creates box
void printBox(){
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
}

//Sends string to display
void printString(){
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(cursor_x, cursor_y);
  display.print(currString);
}


//Prints on current line
void printOnCurrentLine(String stg){
  currString = stg;
  display.drawPagedToWindow(printString, box_x, box_y, box_w, box_h);
}

//Moves to next line
void nextLine(){
  rightJustified = !rightJustified;
  cursor_y = cursor_y + 20;
  box_y = box_y + 20;
}