/*
   Interrupts code
*/

void IRAM_ATTR isr() {
  cancel_alarm.cancelTimer = millis() + ChirpSilencePeriod*1000;
  cancel_alarm.pressed = true;
}

void setup_interrupts() {
  pinMode(cancel_alarm.PIN, INPUT_PULLUP);
  attachInterrupt(cancel_alarm.PIN, isr, FALLING);
}

/*void loop() {
  if (cancel_alarm.pressed) {
      //Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
      cancel_alarm.pressed = false;
  }

  //Detach Interrupt after 1 Minute
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(cancel_alarm.PIN);
  Serial.println("Interrupt Detached!");
  }
  }
*/
