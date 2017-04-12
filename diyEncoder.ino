//Code for keeping track of gokart speed

int sensorPin = A4;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int count = 0;
int scaled = 0;
bool oldState = false;
bool newState; //true = dark
//int deltas[];
int rollingAverage;
unsigned long oldTimeSince = 0;
int timeBetween;
unsigned long newTimeSince;


const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

int inputPin = A4;

int finalOutput;

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  
   finalOutput = smoother(timeSince());
   Serial.println(finalOutput);
    
 

}

int timeSince(){
  //subtract last value
  // read the value from the sensor:

  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);

  scaled = map(sensorValue, 65, 165, 0, 10);

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
    /*deltas[count] = timeBetween;
    rollingAverage = rollingAverage(deltas, 2, 3);
    Serial.println(rollingAverage);
    //Serial.println(timeBetween);
    //Serial.println(count);
    delay(250);*/
    return timeBetween;
  }else{
    return 0;
  }
}

int smoother(int time){
  return time;
 // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = time;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //stringValue = "Average: " + average;
  //Serial.println(average);
  return average;
  //delay(1);        // delay in between reads for stability
  }

