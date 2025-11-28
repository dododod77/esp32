const int numLED = 8;
int ledpin[numLED] = {19,18,5,17,16,4,2,15};

const int button1 = 14;
const int button2 = 27;
const int button3 = 26;
const int button4 = 25;
const int button5 = 34;

int currentMode = 0;
int numSteps[8];  // Diubah dari step[numLED] jadi numSteps per mode (0-7)
int cursorPos = 0;  // Diubah dari cursor[numLED], satu cursor global
int menuState = 0;  // 0:Start, 1:Setting, 2:Step, 3:Running (tambah)
int menuStart = 0;
int counter = 0;
bool ledPattern[8][8][8];  // mode x step x LED (true=ON)
bool isRunning = false;  // flag running
int currentStep = 0;  // step aktif untuk edit/running
int runDelay = 200;  // delay running


void modeMenu1() {
  if (digitalRead(button1) == 1) {
    if (menuStart == 1 && menuState == 0) {
      currentMode++;
      if (currentMode > 7) {
        currentMode = 0;
      }
    }
  } else if (digitalRead(button2) == 1) {
    if (menuStart == 1 && menuState == 0) {
      currentMode--;
      if (currentMode < 0) {
        currentMode = 7;
      }
    }
  }
}
  
void modeMenu2() {
  if (digitalRead(button1) == 1) {
    if (menuStart == 1 && menuState == 1) {
      currentMode++;
      if (currentMode > 7) {
        currentMode = 0;
      }
    }
  } else if (digitalRead(button2) == 1) {
    if (menuStart == 1 && menuState == 1) {
      currentMode--;
      if (currentMode < 0) {
        currentMode = 7;
      }
    }
  }
}

void stepMenu() {
  if (digitalRead(button1) == 1) {
    if (menuStart == 2 && menuState == 2) {
      currentStep++;
      if (currentStep >= numSteps[currentMode]) {
        currentStep = 0;
      }
    }
  } else if (digitalRead(button2) == 1) {
    if (menuStart == 2 && menuState == 2) {
      currentStep--;
      if (currentStep < 0) {
        currentStep = numSteps[currentMode] - 1;
      }
    }
  }
}

void cursorMenu() {
  
  if (digitalRead(button1) == 1) {
    if (menuStart == 3 && menuState == 2) {
      cursorPos++;
      if (cursorPos > 8) {
        cursorPos = 1;
      }
    }
  } else if (digitalRead(button2) == 1) {
    if (menuStart == 3 && menuState == 2) {
      cursorPos--;
      if (cursorPos < 1) {
        cursorPos = 8;
      }
    }
  }
  if (digitalRead(button3) == 1 && menuState == 2 && menuStart == 3) {
    ledPattern[currentMode][currentStep][cursorPos - 1] = !ledPattern[currentMode][currentStep][cursorPos - 1];
  }
}


void updateRunning() {
  static unsigned long runMillis = 0;
  if (millis() - runMillis < runDelay) return;
  runMillis = millis();

  // Matikan semua LED
  for (int i = 0; i < numLED; i++) {
    digitalWrite(ledpin[i], LOW);
  }

  // Nyalakan sesuai pola
  for (int i = 0; i < numLED; i++) {
    if (ledPattern[currentMode][currentStep][i]) {
      digitalWrite(ledpin[i], HIGH);
    }
  }

  currentStep = (currentStep + 1) % numSteps[currentMode];
}