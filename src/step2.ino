// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX/Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_LEDBackpack.h"

//init 7-segment variable
Adafruit_7segment segment1;


void setup() {

    //connect segment on i2c address 0x70;
    segment1.begin(0x70);
    //sent number to segment
    segment1.print(2015);
    //write display
    segment1.writeDisplay();
}

void loop() {
    
}