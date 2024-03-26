#include <Servo.h>

// Define motor control pins
const int motorPin1 = 9;   // Motor control pin 1
const int motorPin2 = 10;  // Motor control pin 2

// Define ultrasonic sensor pins
const int trigPin = 11;    // Ultrasonic sensor trigger pin
const int echoPin = 12;    // Ultrasonic sensor echo pin

// Define servo motor pin
const int servoPin = 6;    // Servo motor control pin

// Define sorting criteria (e.g., distance threshold)
const int distanceThreshold = 10; // Distance threshold for object detection and sorting (adjust as needed)

Servo sortingServo; // Create a servo object to control the sorting mechanism

void setup() {
  // Set motor control pins as output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo motor to its pin
  sortingServo.attach(servoPin);
}

void loop() {
  // Check for object detection
  if (detectObject()) {
    // Sort the detected object
    sortObject();
  } else {
    // Run the conveyor belt forward if no object detected
    conveyorForward();
  }
}

// Function to detect object using ultrasonic sensor
bool detectObject() {
  long duration, distance;
  
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the pulse duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance
  distance = duration * 0.034 / 2;
  
  // Check if object is within threshold distance
  if (distance <= distanceThreshold) {
    return true;
  } else {
    return false;
  }
}

// Function to sort the detected object
void sortObject() {
  // Stop the conveyor belt
  conveyorStop();
  
  // Activate the sorting mechanism (e.g., move the servo motor)
  sortingServo.write(90); // Move servo to neutral position
  
  // Delay for sorting operation
  delay(1000); // Adjust delay as needed
  
  // Resume conveyor belt operation after sorting
  conveyorForward();
}

// Function to run the conveyor belt forward
void conveyorForward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

// Function to stop the conveyor belt
void conveyorStop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
