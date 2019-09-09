
//Libraries
#include <DHT.h>
#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(9,10); 
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define SSID "a"     // "SSID-WiFiname" 
#define PASS "11111111"       // "password"
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "GET /update?key=BK3YJQUG7548CWCQ";

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup()
{
  lcd.setBacklight(255);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Group-3");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  Serial.begin(9600); //or use default 115200.
  esp8266.begin(115200);
  Serial.println("AT");
  esp8266.println("AT");
  delay(3000);
  if(esp8266.find("OK")){
    connectWiFi();
  }
}

void loop()
{   
  delay(500);
  lcd.clear();
  
  lcd.display();
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.println(" C");
    update();
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
  cmd += "&field2=";   
  cmd += hum;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  Serial.print(cmd);
  esp8266.print(cmd);

  delay(2000);
  
  cmd = msg ;
  cmd += "&field1=";   
  cmd += temp;
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
