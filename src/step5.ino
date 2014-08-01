// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX/Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX/Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_LEDBackpack.h"
#include "math.h"

int inittime = 0;
int runningtime = inittime;

int starttime;
int targettime;
int currenttime;

int dosound = true;
int switchState = 0;

int varminutes = 0;
int varseconds = 0;

bool colon = true;

Adafruit_7segment segment1;

Adafruit_8x8matrix matrix; // = Adafruit_8x8matrix();

int startDND(String args){
    
    matrix.clear();
    for(int8_t y=0; y < 8; y++){
        for(int8_t x=0; x < 8; x++){
            matrix.drawPixel(x,y, LED_ON);
            matrix.writeDisplay();
            delay(10);
        }
    }
    
    
    if(args == ""){
        inittime = 15*60;
    }else{
        inittime = args.toInt() * 60;
    }
    
    dosound = true;
    runningtime = inittime;
    
    starttime = Time.now();
    targettime = starttime + inittime;
  
    
   
    return 200; 
}

void setup() {
    
    starttime = Time.now();
    targettime = starttime + inittime;
    
    pinMode(A5,OUTPUT);
    pinMode(A4,OUTPUT);
    pinMode(A6, OUTPUT);
    
    pinMode(A0, OUTPUT);
    
    pinMode(D6, INPUT);
    
    pinMode(D7, OUTPUT);
    digitalWrite(D7, LOW);
    
    segment1.begin(0x70);
    matrix.begin(0x71);
   
    segment1.print(1995);
    segment1.writeDisplay();
    
    matrix.clear();
    matrix.writeDisplay();
    
    
    
    Spark.variable("minutes", &varminutes, INT);
    Spark.variable("secondes", &varseconds, INT);
    
    Spark.function("startDND", startDND);
    
    Serial.begin(9600);
    Serial.println("Hello Computer");
}



void loop() {
    //runningtime = 40;
    
    Serial.println("Hello Computer x");
    
    runningtime++;
    currenttime = Time.now();
    
    switchState = digitalRead(D6);
    
    if(switchState == LOW){
        
    }else{
       /* dosound = true;
        runningtime = inittime;
        
        starttime = Time.now();
        targettime = starttime + inittime;
        
        Serial.println("reset");*/
    }
    
    if(targettime > currenttime + inittime /  2){
        analogWrite(A5, 255);
        analogWrite(A4, 0);
        analogWrite(A6, 0);
    }else{
        analogWrite(A5, 0);
        analogWrite(A4, 255);
        analogWrite(A6, 0);
    }
    
    if(targettime < currenttime){
        analogWrite(A4, 0);
        analogWrite(A5, 0);
        analogWrite(A6, 255);
        
        if(dosound){
            for(int i = 0; i < 200; i++){
                analogWrite(A0, 250);
                delayMicroseconds(956/4);
                analogWrite(A0, 0);
                delayMicroseconds(956/4);
            }
            dosound = false;
        }
        
        Serial.println("done");
        
        segment1.clear();
        segment1.writeDisplay();
      
    }else{
        int sec_num = targettime-currenttime;
        int hours = floor(sec_num / 3600);
        int minutes = floor((sec_num - (hours * 3600)) / 60);
        int seconds = sec_num - (hours * 3600) - (minutes * 60);
        
        //String hoursx = String(hours);
        String minutesx = String(minutes);
        String secondsx = String(seconds);
        
        if (hours   < 10) {
           // hoursx = "0" + hours;
        }
       if (minutes < 10) {
            minutesx = "0"+String(minutes);
        }
        if (seconds < 10) {
            secondsx = "0"+ String(seconds);
        }
        
        varminutes = minutes;
        varseconds = seconds;
        
        
        String timwstring  = "" +minutesx+":"+secondsx;
        
        Serial.println("minutes");
        Serial.println(minutes);
        
        Serial.println("seconds");
        Serial.println(seconds);
        
        Serial.println("final");
        Serial.println(timwstring);
        
       
        
        segment1.writeDigitNum(0, String(minutesx.charAt(0)).toInt()  );
        segment1.writeDigitNum(1, String(minutesx.charAt(1)).toInt()   );
        segment1.writeDigitNum(3, String(secondsx.charAt(0)).toInt()  );
        segment1.writeDigitNum(4, String(secondsx.charAt(1)).toInt()   );
        
        
       
        segment1.drawColon(true);
    
        segment1.writeDisplay();
        
        float a = (currenttime) - (starttime);
        float b = (targettime) - (starttime);
        
        float percent = a/b;
        float numberOfLights = floor(percent * 64);
        
        Serial.println("calculeer tijd");
        Serial.println(String(a));
        Serial.println(String(b));
        
        Serial.println("percent");
        
        Serial.println(String(percent));
        Serial.println("lights");
        
        matrix.clear();
        int matrixIndex = 0;
        bool stopLoop = false;
        
        for(int8_t y=0; y < 8; y++){
            for(int8_t x=0; x < 8; x++){
                matrix.drawPixel(x,y, LED_ON);
            }
        }
        
        for(int8_t y=0; y < 8; y++){
            for(int8_t x=0; x < 8; x++){
                matrix.drawPixel(x,y, LED_OFF);
                matrixIndex++;
                if(matrixIndex > numberOfLights - 1){
                    stopLoop = true;
                    break;
                }
            }
            if(stopLoop){
                break;
            }
        }
        matrix.writeDisplay();
        
        Serial.println(String(numberOfLights));
        

    }
    
    
    delay(100);
    
}

