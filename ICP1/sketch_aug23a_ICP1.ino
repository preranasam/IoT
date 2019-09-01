void setup() {
  // Pin Configurations
  pinMode(3, OUTPUT); //Red
  pinMode(4, OUTPUT); //Green
  pinMode(5, OUTPUT); //Yellow
 
}

void loop() {
  // Traffic lights 

  digitalWrite(3, HIGH); //Red LED
  digitalWrite(4, LOW); //Green LED
  digitalWrite(5, LOW); //Yellow/Amber LED
  delay(1000);
  
  digitalWrite(3, LOW); //Red LED
  digitalWrite(4, HIGH); //Green LED
  digitalWrite(5, LOW); //Yellow/Amber LED
  delay(1000);

  digitalWrite(3, LOW); //Red LED
  digitalWrite(4, LOW); //Green LED
  digitalWrite(5, HIGH); //Yellow/Amber LED
  delay(1000);

}
