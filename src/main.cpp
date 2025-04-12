#include <Arduino.h>

const int PWM_PIN = D5;
const int TENS_PIN = D6;
const int FEEDBACK_PIN = A1;

// PWM config
const uint32_t PWM_FREQ = 700000; // 700 kHz
const uint8_t PWM_RES = 4;        // 4-bit resolution = 0–15
const uint8_t PWM_CHANNEL = 0;    // Channel 0 for PWM
float pwmFloat = 0.85;            // Start at 85% duty

// Feedback system
float targetVoltage = 40.0;       // Default target V
const float ADC_REF = 3.3;
const int ADC_RES = 4095;
const float DIVIDER_RATIO = (47.0 + 2.7) / 2.7; // ≈18.41

// TENS pulsing config
const uint32_t TENS_FREQ = 30;
uint32_t tensInterval = 1000 / (TENS_FREQ * 2);
unsigned long lastToggle = 0;
bool tensState = false;

// Function declarations
void handleSerial();
void updateFeedbackPWM();
void handleTensPulse();

void setup() {
  Serial.begin(115200);
  pinMode(TENS_PIN, OUTPUT);
  pinMode(FEEDBACK_PIN, INPUT);

  // Setup PWM properly
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  uint8_t initialDuty = pwmFloat * ((1 << PWM_RES) - 1);
  ledcWrite(PWM_CHANNEL, initialDuty);

  digitalWrite(TENS_PIN, LOW);
  Serial.println("✅ PWM active on D5: 700kHz @ ~85% duty");
  Serial.println("✅ 30Hz pain gate active on D6");
  Serial.println("📡 Use 'v <voltage>' in Serial Monitor to set target");
}

void loop() {
  handleSerial();
  updateFeedbackPWM();
  handleTensPulse();
}

void handleTensPulse() {
  unsigned long now = millis();
  if (now - lastToggle >= tensInterval) {
    tensState = !tensState;
    digitalWrite(TENS_PIN, tensState);
    lastToggle = now;
  }
}

void updateFeedbackPWM() {
  int raw = analogRead(FEEDBACK_PIN);
  float v_adc = (raw / (float)ADC_RES) * ADC_REF;
  float v_out = v_adc * DIVIDER_RATIO;

  // Basic float-based control loop
  float error = targetVoltage - v_out;
  float adjust = error * 0.01; // feedback gain
  pwmFloat += adjust;
  pwmFloat = constrain(pwmFloat, 0.05, 0.95); // limit duty to safe range

  uint8_t pwmDuty = pwmFloat * ((1 << PWM_RES) - 1);
  ledcWrite(PWM_CHANNEL, pwmDuty);

  // Debug output
  Serial.print("Target: "); Serial.print(targetVoltage);
  Serial.print(" V | Actual: "); Serial.print(v_out, 2);
  Serial.print(" V | Duty: "); Serial.println(pwmFloat * 100, 1);

  delay(10);
}

void handleSerial() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("v ")) {
      float newTarget = input.substring(2).toFloat();
      if (newTarget > 0 && newTarget < 80) {
        targetVoltage = newTarget;
        Serial.print("🎯 New target voltage set: ");
        Serial.print(targetVoltage); Serial.println(" V");
      } else {
        Serial.println("⚠️ Voltage must be between 0 and 80");
      }
    }
  }
}
