#include <LiquidCrystal.h>
#include <arduino-timer.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

/*
 * On LCD, cmm and cm blink
 * if(button_state) doesn't do anything
 */
const int TRIG = 9;
const int ECHO = 10;
long duration;
int cm, distanceInch;

//for button setup-------
const int buttonPinLength = 12;
const int buttonPinWidth = 13;
int buttonState_1 = 0;
int room_length = 0;
int room_width = 0;
int buttonState_2 = 0;
//----------------------

void setup() {
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);
//Serial.begin(9600);
//for button--------------
pinMode(buttonPinLength, INPUT);
pinMode(buttonPinWidth, INPUT);
digitalWrite(buttonPinLength, HIGH);
digitalWrite(buttonPinWidth, HIGH);
}

void loop() {
lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
// read the state of the pushbutton value:
buttonState_1 = digitalRead(buttonPinLength);

//=================================Length Measurement===================================
//if we say (buttonState_1 == LOW)then, we first measure distance; upon button press, "Measuring length" text appears.
//Serial.println("first button");
if (buttonState_1 == HIGH) {
  lcd.print("Measuring length: ");
}
else {
   //Serial.println("start ELSE condition");
   digitalWrite(TRIG, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);

   duration = pulseIn(ECHO, HIGH);
   cm = (duration/2) * 0.0343;
  //distanceInch = duration*0.0133/2;
   lcd.print("Distance: "); // Prints string "Distance" on the LCD
   lcd.print(cm); // Prints the distance value from the sensor
   lcd.print("  cm");
   delay(10);
   room_length = cm;
  // lcd.clear();
}
//Serial.println("outside ELSE condition");

//=========================================================================================

//=================================Width Measurement===================================

buttonState_2 = digitalRead(buttonPinWidth);
if (buttonState_2 == HIGH) {
  lcd.print("Measuring width: ");
  //Serial.println("if statementsecond button");
}
else {
   digitalWrite(TRIG, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);

   duration = pulseIn(ECHO, HIGH);
   cm = (duration/2) * 0.0343;
  //distanceInch = duration*0.0133/2;
   lcd.print("Distance: "); // Prints string "Distance" on the LCD
   lcd.print(cm); // Prints the distance value from the sensor
   lcd.print("  cm");
   delay(10);
   
}
//=========================================================================================
}
