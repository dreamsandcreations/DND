int helloWorld(String args){
    //turn LED on
    digitalWrite(D7, HIGH);
}
int goodbyeWorld(String args){
    //turn LED off
    digitalWrite(D7, LOW);
}

void setup() {
    //D7 is connected to the onboard LED of the Spark Core
    pinMode(D7, OUTPUT);
    //turn LED off
    digitalWrite(D7, LOW);
    
    Spark.function("helloWorld", helloWorld);
    Spark.function("goodbyeWorld", goodbyeWorld);
}

void loop() {
    
}