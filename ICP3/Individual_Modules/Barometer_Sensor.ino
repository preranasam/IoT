#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(9,10); 
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP280 bmp; // I2C

#define SSID "Android"     // "SSID-WiFiname" 
#define PASS "9899023214"       // "password"
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "GET /update?key=ULUGZSEDJBID7CKZ";

float Temperature,Pressure,Altitude;


void setup() {
  lcd.setBacklight(255);
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  lcd.begin(16, 2);
  lcd.print("Group-3");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  Serial.begin(9600); //or use default 115200.
  esp8266.begin(115200);
  Serial.println("AT");
  esp8266.println("AT");
  delay(5000);
  if(esp8266.find("OK")){
    connectWiFi();
  }
}

void loop() {
/*    Serial.print(F("Temperature = "));
    Temperature = bmp.readTemperature();
    Serial.print(Temperature);
    Serial.println(" *C");
*/  lcd.clear();
    lcd.display();
    lcd.print(F("P :"));
    Pressure = bmp.readPressure();
    lcd.print(Pressure);
    lcd.print(" Pa");
    lcd.setCursor(0, 1);
    lcd.print(F("Alt "));
    Altitude = bmp.readAltitude(1013.25);
    lcd.print(Altitude); // this should be adjusted to your local forcase
    lcd.print(" m");
    
    Serial.println();
    delay(2000);
}

void update(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error")){
    return;
  }
  cmd = msg ;
  cmd += "&field1=";   
  cmd += Temperature;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  Serial.print(cmd);
  esp8266.print(cmd);
}

boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  esp8266.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(5000);
  if(esp8266.find("OK")){
    Serial.println("OK");
    return true;    
  }else{
    return false;
  }
}
