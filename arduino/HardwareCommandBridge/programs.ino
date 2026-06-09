int Blink(int pin, int num, int rate) {
  int numBlinks = 0;
  int pinNo = 13;
  if (pin > 2 && pin <= LED_BUILTIN) pinNo = pin;

  for (int i = 0; i < num; i++) {
    digitalWrite(pinNo, HIGH);
    delay(rate);
    digitalWrite(pinNo, LOW);
    delay(rate);
    numBlinks++;
  }
  return numBlinks;
}

bool Morse(int pin, char* msg) {
  int pinNo = 13;
  if (pin > 2 && pin <= LED_BUILTIN) pinNo = pin;

  int len = (int)strlen(msg);
  for (int i = 0; i < len; i++) {
    int morse = char2Morse(msg[i]);

    // if space, do gap
    if (morse == 100) {
      delay(WORD_GAP * MORSE_SPEED);
    }
    else if (morse >= 0) {
      for (int j = 0; j < CHARS[morse].length; j++) {
        digitalWrite(pinNo, HIGH);
        delay(CHARS[morse].sequence[j] * MORSE_SPEED);
        digitalWrite(pinNo, LOW);
        delay(GAP);
      }
      delay(LETTER_GAP * MORSE_SPEED);
    } else {
      return false;
    }
  }
  return true;
}