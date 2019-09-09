#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


int light;

void setup()
{
  lcd.setBacklight(255);
Serial.begin(9600);
pinMode(A1,INPUT);
 lcd.begin(16, 2);
  lcd.print("Group-3");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Starting...");
}

void loop()
{
  lcd.clear();
  lcd.display();
  light=analogRead(A1);
  lcd.print("Light: ");
  Serial.print(light);
  lcd.print(light);
  delay(500);
}
