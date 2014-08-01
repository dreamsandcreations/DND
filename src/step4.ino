// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX/Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_LEDBackpack.h"

//init 7-segment variable
Adafruit_7segment segment1;
Adafruit_8x8matrix matrix;


void setup() {
    //set AO as output port, A0 is connected to the piezoelectric buzzer
    pinMode(A0, OUTPUT);

    //connect segment on i2c address 0x70;
    segment1.begin(0x70);
    //sent number to segment
    segment1.print(2014);
    //write display
    segment1.writeDisplay();
    
    //connect matrix on i2c address 0x71;
    matrix.begin(0x71);
    //clear the matrix;
    matrix.clear();
    
    //loop over the 64 leds and turn them on one by one.
    for(int8_t y=0; y < 8; y++){
        for(int8_t x=0; x < 8; x++){
            //turn LED on coördinate X and Y on
            matrix.drawPixel(x,y, LED_ON);
            //write display
            matrix.writeDisplay();
            //wait for 10ms
            delay(10);
        }
    }
    
}

void loop() {
    //repeat for hearable sound
    for(int i = 0; i < 500; i++){
        //set HIGH to buzzer
        analogWrite(A0, 250);
        //delay
        delayMicroseconds(240);
        //set LOW to buzzer
        analogWrite(A0, 0);
        //delay
        delayMicroseconds(240);
    }
    
    delay(5000);
}