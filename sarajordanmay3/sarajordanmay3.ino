#include <Wire.h>
#include <Adafruit_AMG88xx.h>

#define RELAY_POSITIVE_PIN 5  // Positive pin of the relay

Adafruit_AMG88xx amg;

const float TEMPERATURE_THRESHOLD = 70;  // Temperature threshold to trigger relay (in °F)

void setup() {
  Serial.begin(9600);

  // Initialize the AMG8833 sensor
  bool status = amg.begin();
  if (!status) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1);
  }

  pinMode(RELAY_POSITIVE_PIN, OUTPUT);
}

void loop() {
  // Read the temperature data from the sensor
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  amg.readPixels(pixels);

  // Find the highest temperature
  float highestTemp = -273.15;  // Initialize to absolute zero
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    if (pixels[i] > highestTemp) {
      highestTemp = pixels[i];
      highestTemp = highestTemp*(9.0/5.0)+32;
    }
  }

  // Print the highest temperature
  Serial.print("Highest Temperature: ");
  Serial.print(highestTemp);
  Serial.println(" °F");

  // Check if the highest temperature exceeds the threshold
  if (highestTemp > TEMPERATURE_THRESHOLD) {
    // Turn on the relay by setting the positive pin to LOW
    digitalWrite(RELAY_POSITIVE_PIN, HIGH);
    Serial.println("Temperature is above the threshold. Turning on the relay.");
  } else {
    // Turn off the relay by setting the positive pin to HIGH
    digitalWrite(RELAY_POSITIVE_PIN, LOW);
    Serial.println("Temperature is below the threshold. Turning off the relay.");
  }

  delay(1000); // Wait for a short time before taking the next reading
}