#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 2000; 
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  Serial.begin(9600);
  lcd.setBacklight(255);
  pinMode(8,INPUT);
  starttime = millis(); 
  lcd.begin(16, 2);
  lcd.print("Group-3");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Starting...");
  delay(5000);
}

void loop() {

  lcd.clear();
  lcd.display();
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  //if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    lcd.print("Conc : ");
    lcd.print(concentration);
    lcd.setCursor(0,1);
    lcd.print(" pcs/0.01cf");
    lcd.print("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
  }
  delay(2000);
}
