
// RACE-X AI Motorsport Platform
// ESP32 Telemetry + Battery Monitoring Firmware
// Author: Vaishnavi Khose
// Sensor Pin Definitions

const int voltagePin = 34;     // Battery voltage sensor
const int tempPin = 35;        // Battery temperature sensor
const int rpmPin = 32;         // RPM sensor
const int currentPin = 33;     // Current sensor

// ----------------------
// Variables
// ----------------------
float voltage = 0;
float temperature = 0;
float rpm = 0;
float current = 0;

// ----------------------
// Setup
// ----------------------
void setup() {
  Serial.begin(115200);

  pinMode(voltagePin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(rpmPin, INPUT);
  pinMode(currentPin, INPUT);

  Serial.println("RACE-X Telemetry System Initialized...");
}

// ----------------------
// Main Loop
// ----------------------
void loop() {

  // Read raw analog values
  int voltageRaw = analogRead(voltagePin);
  int tempRaw = analogRead(tempPin);
  int rpmRaw = analogRead(rpmPin);
  int currentRaw = analogRead(currentPin);

  // Convert to engineering values
  voltage = (voltageRaw * 3.3 / 4095.0) * 2.0;     // Voltage divider scaling
  temperature = (tempRaw * 3.3 / 4095.0) * 100.0;  // Approx temp conversion
  rpm = map(rpmRaw, 0, 4095, 0, 12000);            // RPM estimate
  current = (currentRaw * 3.3 / 4095.0) * 50.0;    // Current estimate

  // ----------------------
  // Serial Output for Python Dashboard
  // ----------------------
  Serial.print("Voltage:");
  Serial.print(voltage, 2);

  Serial.print(",Temp:");
  Serial.print(temperature, 2);

  Serial.print(",RPM:");
  Serial.print(rpm, 0);

  Serial.print(",Current:");
  Serial.println(current, 2);

  // ----------------------
  // Safety Alerts
  // ----------------------
  if (temperature > 60) {
    Serial.println("WARNING: Battery Overheating!");
  }

  if (voltage < 40) {
    Serial.println("WARNING: Low Battery Voltage!");
  }

  // Delay
  delay(500);
}
