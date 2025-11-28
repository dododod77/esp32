int layer[4] = {26,25,33,32};
int col[16] = {27,14,12,13,23,22,1,21,19,18,5,17,16,4,2,15};

unsigned long prevMillis = 0;
const long Interval = 200;

int counter = 0;
int flr = 3;


void setup() {
  Serial.begin(9600);

  for (int i = 0; i<4; i++) {
    pinMode(layer[i], OUTPUT);
  }
  for (int i = 0; i<16; i++) {
    pinMode(col[i], OUTPUT);
  }
}

void loop() {
  flow();
  Serial.println(counter);
}


void flow() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= Interval) {
    prevMillis = currentMillis;

    counter++;
    if (counter > 15) {
      counter = 0;
      flr--;
      if (flr < 0) {
        flr = 3;
      }
    }

  }

  switch (counter) {
    case 0:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[0], 0);
      break;

    case 1:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[1], 0);
      break;

    case 2:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[2], 0);
      break;

    case 3:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[3], 0);
      break;

    case 4:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[7], 0);
      break;

    case 5:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[11], 0);
      break;

    case 6:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[15], 0);
      break;

    case 7:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[14], 0);
      break;

    case 8:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[13], 0);
      break;

    case 9:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[12], 0);
      break;

    case 10:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[8], 0);
      break;

    case 11:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[4], 0);
      break;

    case 12:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[5], 0);
      break;

    case 13:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[6], 0);
      break;

    case 14:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[10], 0);
      break;

    case 15:
      for (int i = 0; i<4; i++) {
        digitalWrite(layer[i], 0);
      }
      digitalWrite(layer[flr], 1);
      for (int i = 0; i<16; i++) {
        digitalWrite(col[i], 1);
      }

      digitalWrite(col[9], 0);
      break;
  }
}



// void on() {
//   for (int i = 0; i<4; i++) {
//     digitalWrite(layer[i], 1);
//   }
//   for (int i = 0; i<16; i++) {
//     digitalWrite(col[i], 0);
//   }
// }


// void off() {
//   for (int i = 0; i<4; i++) {
//     digitalWrite(layer[i], 0);
//   }
//   for (int i = 0; i<16; i++) {
//     digitalWrite(col[i], 1);
//   }
// }


