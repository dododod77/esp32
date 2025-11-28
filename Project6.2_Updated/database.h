unsigned long prevMillis = 0;
const long Interval = 200;

const long resetComplete = 3000;

// Load config
void loadConfig() {
  size_t size = pref.getBytesLength("patterns");
  if (size == sizeof(ledPattern)) {
    pref.getBytes("patterns", ledPattern, sizeof(ledPattern));
  } else {
    // Default: Chasing per mode
    for (int m = 0; m < 8; m++) {
      numSteps[m] = 8;
      for (int s = 0; s < 8; s++) {
        for (int i = 0; i < numLED; i++) {
          ledPattern[m][s][i] = false;
        }
        ledPattern[m][s][s % numLED] = true;  // Chasing
      }
    }
  }
  // Load numSteps
  for (int m = 0; m < 8; m++) {
    String key = "steps" + String(m);
    numSteps[m] = pref.getInt(key.c_str(), 8);
    if (numSteps[m] < 1 || numSteps[m] > 8) numSteps[m] = 8;
  }
  Serial.println("Config loaded");
}

// Save config
void saveConfig() {
  pref.putBytes("patterns", ledPattern, sizeof(ledPattern));
  for (int m = 0; m < 8; m++) {
    String key = "steps" + String(m);
    pref.putInt(key.c_str(), numSteps[m]);
  }
  Serial.println("Config saved");
}

void resetpref() {
  static unsigned long pressStart = 0;
  static bool resetTriggered = false;

  bool buttonState = digitalRead(button5);
  unsigned long currentMillis = millis();

  if (buttonState == HIGH && pressStart == 0) {
    pressStart = currentMillis;
    resetTriggered = false;
  }

  if (buttonState == HIGH && !resetTriggered) {
    if (currentMillis - pressStart >= resetComplete) {
      pref.clear();
      menuState = 0;
      menuStart = 0;
      cursorPos = 0;
      currentStep = 0;
      isRunning = false;
      for (int i = 0; i < numLED; i++) {
        digitalWrite(ledpin[i], LOW);
      }
      Serial.println("Reset Success");
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Reset Success");
      delay(1500);
      lcd.clear();

      ESP.restart();

      resetTriggered = true;  // Supaya gak diulang terus
    }
  }

  if (buttonState == LOW) {
    if (pressStart != 0 && !resetTriggered && (currentMillis - pressStart < resetComplete)) {
      Serial.println("Short press detected (no reset)");
    }
    pressStart = 0;
  }
}