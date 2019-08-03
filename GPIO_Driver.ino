// Drives GPIO Pins according to HVC/LVC

void Switch_GPIO(int gpio, int command) {

  if ((command % 10) == 0) {
    digitalWrite(gpio, HIGH);
    vTaskDelay(250);
    digitalWrite(gpio, LOW);
  }

}
