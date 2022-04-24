#include <LiquidCrystal.h>
#include <arduino-timer.h>
#include <string.h>
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
const int buttonPinArea = 11;
const int buttonPinReset = 8;

int Length_buttonState = 0;
int Width_buttonState = 0;
int Reset_buttonState = 0;
int Area_buttonState = 0;
int room_length = 0;
int room_width = 0;
//----------------------
byte newCharSquare[8] = {
  B01100,
  B10010,
  B00100,
  B01000,
  B11110,
  B00000,
  B00000,
  B00000
};

void setup() {
  lcd.createChar(0, newCharSquare);
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  //Serial.begin(9600);
  //for button--------------
  pinMode(buttonPinLength, INPUT);
  pinMode(buttonPinWidth, INPUT);
  pinMode(buttonPinReset, INPUT);
  pinMode(buttonPinArea, INPUT);
  digitalWrite(buttonPinLength, HIGH);
  digitalWrite(buttonPinWidth, HIGH);
  digitalWrite(buttonPinReset, HIGH);
  digitalWrite(buttonPinArea, HIGH);
}

void loop() {
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  //----------------------------Reset Button-------------------------------------------
  if((room_length == 0) && (room_width == 0)) {
    lcd.print("Ready to measure");
  }
  Reset_buttonState = digitalRead(buttonPinReset);
  if (Reset_buttonState == LOW) {
    room_length = 0;
    room_width = 0;
}

//=================================Length Measurement===================================
Length_buttonState = digitalRead(buttonPinLength);
if (Length_buttonState == LOW) {
   digitalWrite(TRIG, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);

   duration = pulseIn(ECHO, HIGH);
   room_length = (duration/2) * 0.0343;
   lcd.clear();
   lcd.print("Length: "); // Prints string "Distance" on the LCD
   lcd.print(room_length); // Prints the distance value from the sensor
   lcd.print("  cm");
   delay(10);
   //room_length = cm;
}
//Serial.println("outside ELSE condition");

//=========================================================================================

//=================================Width Measurement===================================

Width_buttonState = digitalRead(buttonPinWidth);
if (Width_buttonState == LOW){
   digitalWrite(TRIG, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);

   duration = pulseIn(ECHO, HIGH);
   room_width = (duration/2) * 0.0343;
  //distanceInch = duration*0.0133/2;
   lcd.clear();
   lcd.print("Width: "); // Prints string "Distance" on the LCD
   lcd.print(room_width); // Prints the distance value from the sensor
   lcd.print("  cm");
   delay(10);
}
//============================Area Calculation=========================================================
Area_buttonState = digitalRead(buttonPinArea);
if (Area_buttonState == LOW) {
  int area = room_length * room_width;
  //Preparing the display:
  String area_to_str = String(area);
  int area_string_length = area_to_str.length();
  int cell_number = 9 + area_string_length;
  lcd.clear();
  lcd.print("Area: ");
  lcd.print(area);
  lcd.print(" cm");
  lcd.setCursor(cell_number,0);
  lcd.write((byte)0);
}
}
