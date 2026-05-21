int Blink(int num, int rate) {
  int numBlinks = 0;
  for (int i = 0; i < num; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(rate);
    digitalWrite(LED_BUILTIN, LOW);
    delay(rate);
    numBlinks++;
  }
  return numBlinks;
}