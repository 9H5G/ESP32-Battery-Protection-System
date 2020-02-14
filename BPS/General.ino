void FlashLed(int number)
{
  for (int i = 0; i < number; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay (50);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void testBuzz(int number)
{
  for (int i = 0; i < number; i++) {
    dit();
    vTaskDelay (50);
  }
}

void dit() {
  digitalWrite(BUZZERPIN, HIGH);
  vTaskDelay (50);
  digitalWrite(BUZZERPIN, LOW);
  vTaskDelay (50);
}

void dah() {
  digitalWrite(BUZZERPIN, HIGH);
  vTaskDelay (150);
  digitalWrite(BUZZERPIN, LOW);
  vTaskDelay (50);
}
 void mqBuzz()//M
 {
  dah();
  dah();
 }

void rebootBuzz()//B
{
  dah();
  dit();
  dit();
  dit();
}

void reconnectBuzz()// R
{
  dit();
  dah();
  dit();
}

void disconnectBuzz()//D
{
  dah();
  dit();
  dit();
  }
  
void testVoltages()
{

  if ((Cell[0] == 3600) || (Cell[0] == 2500)) {
    inc = inc * -1;
  }
  /*
    Cell[0] = Cell[0] +( 10 * inc);

    Cell[1] = Cell[1]+( 10 * inc);
    Cell[2] = Cell[2]+( 10 * inc);
    Cell[3] = Cell[3]+( 10 * inc);
  */
  /* Cell[0] = 3355;

    Cell[1] = 3355;
    Cell[2] = 3345;
    Cell[3] = 3345;
  */
}
