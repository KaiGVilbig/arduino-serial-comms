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