// Arduino-based ohm meter and distance meter
// Developed by Maxim Bortnikov
// For more information visit: https://github.com/Northstrix/Arduino-based_ohm_meter_and_distance_meter
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);
int analogPin= 2; // Resistor's pin
int raw= 0;
int Vin= 5;
float Vout= 0;
float R1= 5000; // Value of your equivalent resistor in ohms
float R2= 0;
float buffer= 0;
int echoPin = 11; // Set a echo pin
int trigPin = 12; // Set a trig pin
void setup() {
display.begin();
display.clearDisplay();
display.display();
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
}

void loop() {
float duration, inch, inc,ft,foot,cm;
int feet,q,m;
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); 
inch = duration / 147.32; // some math down here
cm = duration / 58;
ft = inch / 12;
feet = ft;
q = 12;
foot = q * feet;
inc = inch -  foot;
display.clearDisplay();
delay(50);
display.setContrast(255);
  if (feet >= 2) {
  display.setCursor(0,8); 
display.println("feet");
display.display();
}
  else {
    display.setCursor(0,8); 
display.println("foot");
display.display();
  }// Displaying all units
display.setTextSize(1);
display.setTextColor(BLACK);
display.setCursor(0,0); 
display.println("distance:");
display.display();
display.setCursor(30,8); 
display.println(feet);
display.display();
display.setCursor(30,16); 
display.println(inc);
display.display();
display.setCursor(0,16); 
display.println("inch.");
display.display();
display.setCursor(0,16); 
display.println("inch.");
display.display();
display.setCursor(0,24); 
display.println("Europian unit:");
display.display();
display.setCursor(0,32); 
display.println("cm");
display.display();
display.setCursor(30,32); 
display.println(cm);
display.display();

raw= analogRead(analogPin); // Calculating the value of the second resistor
if(raw) 
{
buffer= raw * Vin;
Vout= (buffer)/1024.0;
buffer= (Vin/Vout) -1;
R2= R1 * buffer;
Serial.print("Vout: ");
Serial.println(Vout);
Serial.print("R2: ");
Serial.println(R2);
buffer= 0;
tone(9, R2); // Convert the resistor's value to the frequency (1ohm=1hz). Delete this string if you don't like squeak
display.clearDisplay();
delay(50);
display.setContrast(255);
display.setTextSize(1);
display.setTextColor(BLACK);
display.setCursor(0,40);
display.println("R=");
display.display();
display.setContrast(255);
display.setTextSize(1);
display.setTextColor(BLACK);
display.setCursor(12,40); 
display.println(R2);
display.display();
}
}
