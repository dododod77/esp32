LiquidCrystal_I2C lcd(0x27, 16, 2);

Preferences pref;

void lcdDisplay1() {
  //first display
  lcd.setCursor(2, 0);
  if (menuState == 0 && menuStart == 0) {
    lcd.print(" [Start] ");
  } else {
    lcd.print("  Start");
    lcd.print("   ");
  }

  lcd.setCursor(3, 1);
  if (menuState == 0 && menuStart == 1) {
    lcd.print("[Mode ");
    lcd.print(currentMode + 1);
    lcd.print("] ");
  } else {
    lcd.print(" Mode ");
    lcd.print(currentMode + 1);
    lcd.print("  ");
  }

  lcd.setCursor(12, 1);       // Fix: Cetak numSteps[currentMode], bukan currentStep
  lcd.print("(");
  lcd.print(numSteps[currentMode]);
  lcd.print(")");
}

void lcdDisplay2() {
  //second display
  lcd.setCursor(2, 0);
  if (menuState == 1 && menuStart == 0) {
    lcd.print("[Setting]");
  } else {
    lcd.print(" Setting");
    lcd.print("  ");
  }

  lcd.setCursor(3, 1);
  if (menuState == 1 && menuStart == 1) {
    lcd.print("[Mode ");
    lcd.print(currentMode + 1);
    lcd.print("] ");
  } else {
    lcd.print(" Mode ");
    lcd.print(currentMode + 1);
    lcd.print("  ");
  }

  lcd.setCursor(12, 1);       // Fix: Cetak numSteps[currentMode]
  lcd.print("(");
  lcd.print(numSteps[currentMode]);
  lcd.print(")");
}

void StepDisplay() {
  //in setting display
  lcd.setCursor(3, 0);
  if (menuState == 2 && menuStart == 2) {
    lcd.print(" [Step");
    lcd.print(currentStep + 1);
    lcd.print("]  ");
  } else {
    lcd.print("  Step");
    lcd.print(currentStep + 1);
    lcd.print("   ");
  }

  // Fix: Cetak 8 LED state dari ledPattern, dengan cursorPos
  int ledPositions[8] = {0,2,4,6,8,10,12,14};
  for (int i = 0; i < numLED; i++) {
    lcd.setCursor(ledPositions[i], 1);
    bool state = ledPattern[currentMode][currentStep][i];  // Fix: Gunakan ledPattern
    if (menuState == 2 && cursorPos == i + 1) {
      lcd.print(">");  // Cursor
      lcd.print(state ? "1" : "0");
    } else {
      lcd.print(" ");
      lcd.print(state ? "1" : "0");
    }
  }
}

// Running display
void runningDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Running Mode ");
  lcd.print(currentMode + 1);

  lcd.setCursor(0, 1);
  lcd.print("Step ");
  lcd.print(currentStep + 1);
  lcd.print("/");
  lcd.print(numSteps[currentMode]);
}