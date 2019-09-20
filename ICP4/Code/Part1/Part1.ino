// Starting of Program
int led = 8;    // Use digital pin8 to connect the LED
char val;

void setup()
{

pinMode(led, OUTPUT);  // Digital pin 8 set as output Pin

Serial.begin(9600);   // Baud rate set as 9600

}
void loop()
{
  while (Serial.available() > 0)  //Get the number of bytes (characters) available for reading from the serial port 
  {
  val = Serial.read();            //Read incoming serial data
  Serial.println(val);            //Print data to serial port
  }
  if( val == '1') // Forward      // Check if data sent is 1
    {
      digitalWrite(led, HIGH);    //Turn ON the LED
    }
  else if(val == '2') // Backward //Check if data sent is 2
    {
      digitalWrite(led, LOW);     // Turn OFF the LED
    }
}
// End of program
