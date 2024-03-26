// Include necessary libraries
#include <LiquidCrystal.h>  // LCD display library
#include <ESP8266WiFi.h>    // Wi-Fi library (if using ESP8266)
#include <PubSubClient.h>   // MQTT library (if using MQTT for remote monitoring)

// Define pins
const int trigPin = 11;        // Ultrasonic sensor trigger pin
const int echoPin = 12;        // Ultrasonic sensor echo pin
const int rs = 7;              // LCD RS pin
const int en = 6;              // LCD enable pin
const int d4 = 5;              // LCD data pin 4
const int d5 = 4;              // LCD data pin 5
const int d6 = 3;              // LCD data pin 6
const int d7 = 2;              // LCD data pin 7
const int buzzerPin = 8;       // Buzzer pin
const char* ssid = "YOUR_SSID"; // Wi-Fi network SSID
const char* password = "YOUR_PASSWORD"; // Wi-Fi password
const char* mqtt_server = "YOUR_MQTT_SERVER"; // MQTT server address

// Define variables
long duration;
int distance;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Initialize LCD
WiFiClient espClient;   // Initialize Wi-Fi client (if using ESP8266)
PubSubClient client(espClient);  // Initialize MQTT client (if using MQTT)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LCD
  lcd.begin(16, 2);

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connect to MQTT server
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    if (client.connect("arduinoClient")) {
      Serial.println("Connected to MQTT server");
    } else {
      Serial.print("Failed to connect to MQTT server, rc=");
      Serial.print(client.state());
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  // Read liquid level
  int liquidLevel = readLiquidLevel();

  // Log liquid level data
  logData(liquidLevel);

  // Display liquid level on LCD
  displayLiquidLevel(liquidLevel);

  // Check for abnormal liquid level
  checkLiquidLevel(liquidLevel);

  // Check for MQTT messages
  client.loop();
}

int readLiquidLevel() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  return distance;
}

void logData(int liquidLevel) {
  // Log liquid level data to MQTT topic
  String payload = String(liquidLevel);
  client.publish("liquid_level", payload.c_str());
}

void displayLiquidLevel(int liquidLevel) {
  // Display liquid level on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Liquid Level:");
  lcd.setCursor(0, 1);
  lcd.print(liquidLevel);
  lcd.print(" cm");
}

void checkLiquidLevel(int liquidLevel) {
  // Define upper and lower threshold levels
  const int upperThreshold = 20;  // Adjust as needed
  const int lowerThreshold = 5;   // Adjust as needed

  // Check if liquid level exceeds upper threshold
  if (liquidLevel > upperThreshold) {
    // Trigger alarm
    triggerAlarm();
  }
  // Check if liquid level falls below lower threshold
  else if (liquidLevel < lowerThreshold) {
    // Trigger alarm
    triggerAlarm();
  }
}

void triggerAlarm() {
  // Activate alarm (e.g., sound buzzer)
  tone(buzzerPin, 1000); // Adjust frequency as needed
  delay(1000); // Alarm duration
  noTone(buzzerPin); // Turn off buzzer
}
