#include <LiquidCrystal_I2C.h>
#include <Preferences.h>
#include "menu.h"
#include "display.h"
#include "database.h"


void setup() {
  pref.begin("led_config", false);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  for (int i = 0; i < numLED; i++) {
    pinMode(ledpin[i], OUTPUT);
  }

  pinMode(button1, INPUT_PULLDOWN);
  pinMode(button2, INPUT_PULLDOWN);
  pinMode(button3, INPUT_PULLDOWN);
  pinMode(button4, INPUT_PULLDOWN);
  pinMode(button5, INPUT_PULLDOWN);

  loadConfig();

  numSteps[0] = 8;
  saveConfig();
}

void loop() {
  unsigned long currentMillis = millis();

  int buttonNext = digitalRead(button1);
  int buttonPrev = digitalRead(button2);
  int buttonEnter = digitalRead(button3);
  int buttonBack = digitalRead(button4);
  int buttonBtS = digitalRead(button5);

  if (currentMillis - prevMillis >= Interval) {
    prevMillis = currentMillis;

    // Button Config
    if (buttonEnter == 1) {
        lcd.clear();
        menuStart++;              // To change from cursor up to down
        if (menuState == 1) {
          counter++;              // For the in setting display
          if (counter >= 2) {
            menuState = 2;
            menuStart = 2;
            counter = 2;
          }
        } else if (menuStart > 3) {
          menuStart = 3;
        } else if (menuStart == 3) {
          cursorPos++;
        }
    } else if (buttonBack == 1) {
      lcd.clear();
      if (menuStart == 3) {
        menuStart--;
        saveConfig();
      } else if (menuState == 2 && menuStart == 2) {
        menuState--;
        menuStart--;
      } else if (menuStart == 1) {
        menuStart--;
      } else if (menuState == 1 && menuStart == 0) {
        menuState--;
      } else if (menuState == 3 && menuStart == 2) {
        menuStart--;
        menuState = 0;
        isRunning = false;
        for (int i = 0; i < numLED; i++) {
          digitalWrite(ledpin[i], LOW);
        }
      } 
    } else if (buttonBtS == 1) {         // To bring it back to default
      lcd.clear();
      if (menuState == 2) {
        saveConfig();
      } else if (isRunning) {
        isRunning = false;
        for (int i = 0; i < numLED; i++) {
          digitalWrite(ledpin[i], LOW);
        }
      }
      lcd.clear();
      menuState = 0;
      menuStart = 0;
      counter = 0;
      cursorPos = 0;
      currentStep = 0;
    }
//==================================================================
    // Cursor Config
    if (menuStart == 2) {
      cursorPos = 0;
    }
//==================================================================
    // Running Config
    if (isRunning && menuState == 3) {
      updateRunning();
    }
//==================================================================
    modeMenu1();
    modeMenu2();
    stepMenu();
    cursorMenu();
//===================================================================
    // Menu Config
    if (buttonNext == 1 && menuStart == 0) {  //button for next
      menuState++;
      if (menuState > 1) {
      menuState = 0;
      } 
    } else if (buttonPrev == 1 && menuStart == 0) { //button for prev
      menuState--;
      if (menuState < 0) {
        menuState = 1;
      }
    }

    if (menuState == 0 && menuStart == 2) {
      isRunning = true;
      menuState = 3;
      currentStep = 0;
    }
//====================================================================
  }
  switchMenu();
  resetpref();

  Serial.println(currentStep);
}

void switchMenu() {
  switch (menuState) {
    case 0:
      lcdDisplay1();
      break;

    case 1:
      lcdDisplay2();
      break;

    case 2:
      StepDisplay();
      break;

    case 3:
      runningDisplay();
      break;
  }
}