int layer[4] = {26,25,33,32};
int col[16] = {27,14,12,13,23,22,1,21,19,18,5,17,16,4,2,15};

unsigned long prevMillis = 0;
const long Interval = 200;
int counter = 0;

void setup() {
  for (int i = 0; i<4; i++) {
    pinMode(layer[i], OUTPUT);
  }
   for (int i = 0; i<16; i++) {
    pinMode(col[i], OUTPUT);
  }
}

void loop() {
  aika();
}

void aika() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= Interval) {
    prevMillis = currentMillis;

    counter++;
    if (counter > 23) {
      counter = 0;
    }
  }


  switch (counter) {
    case 0:
      brightness(0, 20);
      aLet();
      break;

    case 1:
      brightness(1, 80);
      aLet();
      break;

    case 2:
      brightness(2, 160);
      aLet();
      break;

    case 3:
      brightness(3, 255);
      aLet();
      break;

    case 4:
      brightness(3, 255);
      aLet();
      break;

    case 5:
      brightness(3, 255);
      aLet();
      break;

    case 6:
      brightness(0, 20);
      iLet();
      break;

    case 7:
      brightness(1, 80);
      iLet();
      break;

    case 8:
      brightness(2, 160);
      iLet();
      break;

    case 9:
      brightness(3, 255);
      iLet();
      break;

    case 10:
      brightness(3, 255);
      iLet();
      break;

    case 11:
      brightness(3, 255);
      iLet();
      break;

    case 12:
      brightness(0, 20);
      kLet();
      break;

    case 13:
      brightness(1, 80);
      kLet();
      break;

    case 14:
      brightness(2, 160);
      kLet();
      break;

    case 15:
      brightness(3, 255);
      kLet();
      break;

    case 16:
      brightness(3, 255);
      kLet();
      break;

    case 17:
      brightness(3, 255);
      kLet();
      break;

    case 18:
      brightness(0, 20);
      aLet();
      break;

    case 19:
      brightness(1, 80);
      aLet();
      break;

    case 20:
      brightness(2, 160);
      aLet();
      break;

    case 21:
      brightness(3, 255);
      aLet();
      break;

    case 22:
      brightness(3, 255);
      aLet();
      break;

    case 23:
      brightness(3, 255);
      aLet();
      break;
  }
}

void brightness(int flr, int brg) {
  for (int i = 0; i<4; i++) {
        analogWrite(layer[i], 0);
      }
      analogWrite(layer[flr], brg);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }
}

void aLet() {
  digitalWrite(col[0], 0);
  digitalWrite(col[2], 0);
  digitalWrite(col[4], 0);
  digitalWrite(col[5], 0);
  digitalWrite(col[6], 0);
  digitalWrite(col[8], 0);
  digitalWrite(col[10], 0);
  digitalWrite(col[13], 0);
}

void iLet() {
  digitalWrite(col[0], 0);
  digitalWrite(col[1], 0);
  digitalWrite(col[2], 0);
  digitalWrite(col[5], 0);
  digitalWrite(col[9], 0);
  digitalWrite(col[12], 0);
  digitalWrite(col[13], 0);
  digitalWrite(col[14], 0);
}

void kLet() {
  digitalWrite(col[0], 0);
  digitalWrite(col[2], 0);
  digitalWrite(col[5], 0);
  digitalWrite(col[6], 0);
  digitalWrite(col[9], 0);
  digitalWrite(col[10], 0);
  digitalWrite(col[12], 0);
  digitalWrite(col[14], 0);
}