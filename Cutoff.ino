void relays(int mtype)
{
  //mtype = alarmcode

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
      //mpin = LED_BUILTIN;

    }
    if (mtype == lowon) {
      mpin = LVCONPIN;
    }
    snprintf (msg, 75, " #%d", mpin);
    client.publish(CUTOFF, msg);

    digitalWrite(mpin, HIGH);
    vTaskDelay(pulseLength);
    digitalWrite(mpin, LOW);

    DEBUGPRINT3("--- Switch --- ");
    DEBUGPRINTLN3(mpin);
    //Switch_GPIO(GPIO1,mtype);
    //Switch_GPIO(GPIO2,mtype);

  }
  /*
     Update relay status on dashboard
  */

  int answer = 100;

  snprintf (msg, 75, "%ld", LEDPINHVC);
  MQ_Publish("ReadLEDHVC", msg);

  snprintf (msg, 75, "%ld", answer);
  MQ_Publish("ReadLEDResult", msg);

  answer = (readled(LEDPINHVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish(HVCLED, msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish(LVCLED, msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", LEDPINLVC);
  MQ_Publish("ReadLEDLVC", msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish("ReadLEDResult", msg);

}

int readled(int ledpin)
{
  int res = digitalRead(ledpin);
  return res;
}
void updateLed()
{
  int answer = 100;
  answer = (readled(LEDPINHVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish("HVCled", msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
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

  digitalWrite(LVCONPIN, HIGH);
  digitalWrite(LVCOFFPIN, HIGH);
  digitalWrite(HVCOFFPIN, HIGH);
  digitalWrite(HVCONPIN, HIGH);
  digitalWrite(GPIO1, HIGH);
  digitalWrite(GPIO2, HIGH);
  digitalWrite(BUZZERPIN, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("ONNNN");
  vTaskDelay(500);

  digitalWrite(LVCONPIN, LOW);
  digitalWrite(LVCOFFPIN, LOW);
  digitalWrite(HVCOFFPIN, LOW);
  digitalWrite(HVCONPIN, LOW);
  digitalWrite(GPIO1, LOW);
  digitalWrite(GPIO2, LOW);
  digitalWrite(BUZZERPIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("OFFFF");
}
