#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

const int TRIG = 9;
const int ECHO = 10;
long duration;
int cm, distanceInch;

void setup() {
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);
}

void loop() {
  
digitalWrite(TRIG, LOW);
delayMicroseconds(2);
digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);

duration = pulseIn(ECHO, HIGH);
cm = (duration/2) * 0.0343;
//distanceInch = duration*0.0133/2;

lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd.print("Distance: "); // Prints string "Distance" on the LCD
lcd.print(cm); // Prints the distance value from the sensor
lcd.print("  cm");
delay(10);
//lcd.setCursor(0,1);
//lcd.print("Distance: ");
//lcd.print(distanceInch);
//lcd.print("inch");
//delay(10);

}
