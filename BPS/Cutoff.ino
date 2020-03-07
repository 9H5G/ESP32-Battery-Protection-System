int readled(int ledpin)
{
  int res = digitalRead(ledpin);
  //snprintf (msg, 75, "LED %d, %d", ledpin, res);
  // MQ_Publish("bps/outTopic", msg);
  return res;
}

void relays(int mtype)
{
  int mpin = 0;

  if (mtype != 0) {

    if (mtype == highcut) {
      mpin = HVCOFFPIN;
    }
    if (mtype == lowcut) {
      mpin = LVCOFFPIN;
    }
    if (mtype == highon) {
      mpin = HVCONPIN;
    }
    if (mtype == lowon) {
      mpin = LVCONPIN;
    }
    if (mpin == 0)
    {
      snprintf (msg, 75, "Zero Pin %d", mpin);
      MQ_Publish(CUTOFF, msg);

    } else {
      snprintf (msg, 75, "Relays #%d", mpin);
      MQ_Publish(CUTOFF, msg);

      digitalWrite(mpin, HIGH);
      if (pulseLength > 0) {
        vTaskDelay(pulseLength);
        digitalWrite(mpin, LOW);
        snprintf (msg, 75, "Relays %i :#%d", mpin, LOW);
        MQ_Publish(CUTOFF , msg);
      }
      DEBUGPRINT3("--- Switch --- ");
      DEBUGPRINTLN3(mpin);
      //Switch_GPIO(GPIO1,mtype);
      //Switch_GPIO(GPIO2,mtype);

    }
    /*
       Update relay status on dashboard
    */

    int answer = 100;

    snprintf (msg, 75, "%d", LEDPINHVC);
    MQ_Publish("ReadLEDHVC", msg);

    snprintf (msg, 75, "%d", answer);
    MQ_Publish("ReadLEDResult", msg);

    answer = (readled(LEDPINHVC) == 0) ? 1 : 0;
    snprintf (msg, 75, "%d", answer);
    MQ_Publish(HVCLED, msg);

    answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
    snprintf (msg, 75, "%d", answer);
    MQ_Publish(LVCLED, msg);

    answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
    snprintf (msg, 75, "%d", LEDPINLVC);
    MQ_Publish("ReadLEDLVC", msg);

    answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
    snprintf (msg, 75, "%d", answer);
    MQ_Publish("ReadLEDResult", msg);

  }
}
void updateLed()
{
  int answer = 100;
  answer = (readled(LEDPINHVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%d", answer);
  MQ_Publish("HVCled", msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%d", answer);
  MQ_Publish("LVCled", msg);
}

void output_Test()
{

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(HVCOFFPIN, OUTPUT);
  pinMode(HVCONPIN, OUTPUT);
  pinMode(LVCONPIN, OUTPUT);
  pinMode(LVCOFFPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(GPIO1, OUTPUT);
  pinMode(GPIO2, OUTPUT);

  pinMode(LEDPINLVC, INPUT);
  pinMode(LEDPINHVC, INPUT);
  pinMode(TEMPSIG1, INPUT);
  pinMode(TEMPSIG2, INPUT);
  pinMode(ADC1, INPUT);
  pinMode(ADC2, INPUT);
  pinMode(ADC3, INPUT);
  pinMode(ADC4, INPUT);

  pinMode(ADC_SW, OUTPUT);

  digitalWrite(LVCONPIN, HIGH);
  digitalWrite(LVCOFFPIN, HIGH);
  digitalWrite(HVCOFFPIN, HIGH);
  digitalWrite(HVCONPIN, HIGH);
  digitalWrite(GPIO1, HIGH);
  digitalWrite(GPIO2, HIGH);
  digitalWrite(BUZZERPIN, LOW);
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);

  digitalWrite(BUZZERPIN, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("ONNNN");
  vTaskDelay(2000);

  digitalWrite(BUZZERPIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  digitalWrite(LVCONPIN, LOW);
  digitalWrite(LVCOFFPIN, LOW);
  digitalWrite(HVCOFFPIN, LOW);
  digitalWrite(HVCONPIN, LOW);
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);

  Serial.print("OFFFF");
}
