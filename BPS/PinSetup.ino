void PinSetup() {
  //Wire.begin( mySDA,mySCL);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(HVCOFFPIN, OUTPUT);
  digitalWrite(HVCOFFPIN, LOW);

  pinMode(HVCONPIN, OUTPUT);
  digitalWrite(HVCONPIN, LOW);

  pinMode(LVCONPIN, OUTPUT);
  digitalWrite(LVCONPIN, LOW);

  pinMode(LVCOFFPIN, OUTPUT);
  digitalWrite(LVCOFFPIN, LOW);

  pinMode(LEDPINLVC, INPUT);
  pinMode(LEDPINHVC, INPUT);

  pinMode(BUZZERPIN, OUTPUT);
  digitalWrite(BUZZERPIN, LOW);

  pinMode(GPIO1, OUTPUT);
  digitalWrite(GPIO1, LOW);

  pinMode(GPIO2, OUTPUT);
  digitalWrite(GPIO2, LOW);

  pinMode(TEMPSIG1, INPUT);
  pinMode(TEMPSIG2, INPUT);

  pinMode(ADC1, INPUT);
  pinMode(ADC2, INPUT);
  pinMode(ADC3, INPUT);
  pinMode(ADC4, INPUT);

  pinMode(ADC_SW, OUTPUT);
}
/*
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(HVCOFFPIN, OUTPUT);
  pinMode(HVCONPIN, OUTPUT);
  pinMode(LVCONPIN, OUTPUT);
  pinMode(LVCOFFPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(GPIO1, OUTPUT);
  pinMode(GPIO2, OUTPUT);
  
  const int LVCONPIN  = 4;
  const int LVCOFFPIN  = 16;
  const int LEDPINLVC = 26;

  const int mySCL = 22;
  const int mySDA = 21;

  const int GPIO2 = 12;
  const int GPIO1 = 13;

  const int LEDPINHVC = 25;
  const int HVCOFFPIN = 17;
  const int HVCONPIN = 5;

  const int TEMPSIG1 = 23;
  const int TEMPSIG2 = 27;

  const int BUZZERPIN = 32;

  const int TOUCH1 = 31;
  const int TOUCH2 = 30;
  const int TOUCH3 = 29;

  const int ADC_SW = 33;
  const int ADC1 = 35;
  const int ADC2 = 34;
  const int ADC3 = 39;
  const int ADC4 = 36;
*/
