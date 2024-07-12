#include <Wire.h>
#include <RTClib.h>

// Define the pins
const int pirPin = 12; // PIR sensor output pin
const int ledPin = 13; // LED pin

RTC_DS3231 rtc;

void setup() {
  // Initialize the PIR sensor pin as an input
  pinMode(pirPin, INPUT);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Start the serial communication for debugging
  Serial.begin(115200);

  // Initialize I2C communication
  Wire.begin();

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Check if the RTC lost power and if so, set the time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  // Read the state of the PIR sensor (HIGH when motion is detected)
  int motionState = digitalRead(pirPin);
  
  if (motionState == HIGH) {
    // Motion detected, turn on the LED
    digitalWrite(ledPin, HIGH);
    
    // Get the current time
    DateTime now = rtc.now();
    Serial.print("Motion detected! LED is ON. Current time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  } else {
    // No motion, turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("No motion. LED is OFF.");
  }
  
  // Small delay to avoid excessive serial prints
  delay(500);
}
