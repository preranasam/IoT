#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Arduino code is available to download - link below the video.

// UV index explanation: http://www2.epa.gov/sunwise/uv-index-scale
// UV index explanation: http://www.epa.gov/sunwise/doc/what_is_uvindex.html

/* 
Connection:

 Arduino           Ultraviolet (UV) sensor
 A0 (Analog 0)          SIG
 +5V                    VCC
 GND                    GND
*/

float Vsig;

void setup(){
  Serial.begin(9600);
  lcd.setBacklight(255);
  lcd.begin(16, 2);
  lcd.print("Group-3");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Starting...");
  delay(5000);
}
 
void loop()
{  
  lcd.clear();
  lcd.display();
  int sensorValue;
  long  sum=0;
  for(int i=0;i<1024;i++)
   {  
      sensorValue=analogRead(A0);
      sum=sensorValue+sum;
      delay(2);
   }   
 sum = sum >> 10;
 Vsig = sum*4980.0/1023.0; // Vsig is the value of voltage measured from the SIG pin of the Grove interface
 Serial.print("The voltage value: ");
 Serial.print(Vsig);
 Serial.print(" mV    --   ");
 
if (Vsig < 50) {
    lcd.print("UV Index: 0 "); lcd.print("NONE (You're probably at home!) ");
 }
if (Vsig > 50 && Vsig < 227) {
    lcd.print("UV Index: 1 "); lcd.print("LOW (You're probably at home!) ");
 }
if (Vsig > 227 && Vsig < 318) {
    lcd.print("UV Index: 2 "); lcd.print("LOW (You can go outside and have fun!) ");
 }
if (Vsig > 318 && Vsig < 408) {
    lcd.print("UV Index: 3 "); lcd.print("MODERATE (Sun starts to annoy you) ");
 }
if (Vsig > 408 && Vsig < 503) {
    lcd.print("UV Index: 4 "); lcd.print("MODERATE (Sun starts to annoy you) ");
 }
if (Vsig > 503 && Vsig < 606) {
    lcd.print("UV Index: 5 "); lcd.print("MODERATE (Sun starts to annoy you) ");
 }
if (Vsig > 606 && Vsig < 696) {
    lcd.print("UV Index: 6 "); lcd.print("HIGH (Get out from the sunlight! get out now!) ");
 }
if (Vsig > 696 && Vsig < 795) {
    lcd.print("UV Index: 7 "); lcd.print("HIGH (Get out from the sunlight! get out now!) ");
 }
if (Vsig > 795 && Vsig < 881) {
    lcd.print("UV Index: 8 "); lcd.print("VERY HIGH (Get out from the sunlight! get out now!) ");
 }
if (Vsig > 881 && Vsig < 976) {
    lcd.print("UV Index: 9 "); lcd.print("VERY HIGH (If you value your health, don't go outside, just stay at home!) ");
 }
if (Vsig > 976 && Vsig < 1079) {
    lcd.print("UV Index: 10 "); lcd.print("VERY HIGH (If you value your health, don't go outside, just stay at home!) ");
 }
if (Vsig > 1079 && Vsig < 1170) {
    lcd.print("UV Index: 11 "); lcd.print("EXTREME (If you value your health, don't go outside, just stay at home!) ");
 }
if (Vsig > 1170) {
    lcd.print("UV Index: 11+ "); lcd.print("EXTREME (You will probably die in 3, 2, 1... Just JOKING, don't be scared...) - intensity of sunlight is really at maximum ");
 }
 delay(5000);
}
