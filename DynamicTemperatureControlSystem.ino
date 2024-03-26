#include <LiquidCrystal.h>  // Include the LiquidCrystal library if using an LCD display

// Define the pins
const int sensorPin = A0;      // Temperature sensor pin
const int relayPin = 7;        // Relay control pin
const int potPin = A1;         // Potentiometer pin

// Define variables
int setTemp = 25;              // Set initial temperature
int potValue = 0;              // Variable to store potentiometer value

// Initialize LCD if using
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Initialize the LCD with the numbers of the interface pins

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  
  // Initialize LCD if using
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
}

void loop() {
  // Read the temperature sensor
  int sensorValue = analogRead(sensorPin);
  
  // Convert the sensor value to temperature in Celsius
  float temperatureC = (sensorValue * 5.0 / 1024.0) * 100.0;
  
  // Read the potentiometer value
  potValue = analogRead(potPin);
  
  // Map the potentiometer value to a temperature range (e.g., 20°C to 30°C)
  setTemp = map(potValue, 0, 1023, 20, 30);
  
  // Print temperature and set temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" °C\t Set Temperature: ");
  Serial.print(setTemp);
  Serial.println(" °C");
  
  // Display temperature and set temperature on LCD if using
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Set Temp: ");
  lcd.print(setTemp);
  lcd.print(" C");
  
  // Check if temperature exceeds set temperature
  if (temperatureC > setTemp) {
    // Turn on the relay (heater/cooler)
    digitalWrite(relayPin, HIGH);
  } else {
    // Turn off the relay
    digitalWrite(relayPin, LOW);
  }
  
  // Delay for stability
  delay(1000);
}
