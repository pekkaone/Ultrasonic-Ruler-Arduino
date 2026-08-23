byte words[4][7] = {
  {0, 1, 1, 0, 1, 1, 0}, //c
  {0, 1, 1, 1, 1, 1, 1}, //o
  {1, 1, 0, 1, 1, 0, 1}, //н
  {1, 1, 1, 1, 1, 0, 1}, //я
};

byte digits[10][7] = {
  //g, f, a, b, e, d, c
  {0, 1, 1, 1, 1, 1, 1}, // 0
  {0, 0, 0, 1, 0, 0, 1}, // 1
  {1, 0, 1, 1, 1, 1, 0}, // 2
  {1, 0, 1, 1, 0, 1, 1}, // 3
  {1, 1, 0, 1, 0, 0, 1}, // 4
  {1, 1, 1, 0, 0, 1, 1}, // 5
  {1, 1, 1, 0, 1, 1, 1}, // 6 {1, 1, 1, 0, 1, 1, 1},
  {0, 0, 1, 1, 0, 0, 1}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9 {1, 1, 1, 1, 0, 1, 1} 
};

const int trigPin = A1;
const int echoPin = A2;

int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};
int Dpins[] = {12,11,10,9};
int nums[4];
unsigned long lastmillis;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(Dpins[i], OUTPUT);
  }

}

void loop() {
  if (millis() - lastmillis > 50){

    // put your main code here, to run repeatedly:

    // establish variables for duration of the ping, and the distance result
    // in inches and centimeters:
    long duration, inches, cm;

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    
    duration = pulseIn(echoPin, HIGH);

    // convert the time into a distance
    cm = microsecondsToCentimeters(duration);

    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    nums[0] = cm % 10;
    nums[1] = (cm / 10) % 10;
    nums[2] = cm / 100;
    nums[3] = 0;
    lastmillis = millis();
  }

  for (int j = 0; j <= 4; j++) {
      digitalWrite(Dpins[0], HIGH);
      digitalWrite(Dpins[1], HIGH);
      digitalWrite(Dpins[2], HIGH);
      digitalWrite(Dpins[3], HIGH);
      digitalWrite(Dpins[j], LOW);

      for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], digits[nums[j]][i]);
      }
      delay(3);
    }
    
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}