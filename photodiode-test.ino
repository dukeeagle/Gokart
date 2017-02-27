#include <Average.h>

int sensorPin = A0;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int count = 0;
int scaled = 0;
bool oldState = false;
bool newState; //true = dark
int deltas[];
int rollingAverage;
unsigned long oldTimeSince = 0;
int timeBetween;
unsigned long newTimeSince;

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:

  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);

  scaled = map(sensorValue, 19, 60, 0, 10);

  //Serial.println(scaled);
  if (scaled < 5) {
    newState = true;
  } else {
    newState = false;
  }
  if (newState ^ oldState) {
    count++;
    newState = oldState;
    newTimeSince = millis();
    int newTimeSinceInt = (int) newTimeSince;
    int oldTimeSinceInt = (int) oldTimeSince;
    
    timeBetween = newTimeSinceInt - oldTimeSinceInt;
    oldTimeSince = newTimeSince;
    
    deltas[count] = timeBetween;
    rollingAverage = rollingAverage(deltas, 2, 3);
    Serial.println(rollingAverage);
    //Serial.println(timeBetween);
    //Serial.println(count);
    delay(250);
    
  }

  

}
