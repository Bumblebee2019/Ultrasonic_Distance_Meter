#define trigPin 10
#define echoPin 13

float duration, distance;
//duration of the signal we get back
//distance is the final result in cm

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Pulse for the HC-SR04 Echo Pin
  //Send te 10 microseconds pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;
  //Send results to serial monitor

  Serial.print("Distance = ");
  if(distance >= 400 || distance <= 2) {
    Serial.println("Out of range");
  }
  else {
    //Serial.print("distance");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);
}
