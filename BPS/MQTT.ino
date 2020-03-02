void receivedCallback(char* topic, byte* payload, unsigned int length) {

  char buf[80];
  // handle message arrived
  int i = 0;
  for ( i = 0; i < length; i++) {
    buf[i] = payload[i];
  }
  buf[i] = '\0';

  char ntopic[20];

  strcpy (ntopic, topic);
  MQ_Publish(STATUS, ntopic);

  if (strcmp(ntopic, "LVC") == 0) {
    dit();
    dah();
    dit();
    dit();

    int res = readled(LEDPINLVC);

    if (readled(LEDPINLVC) == 0) {
      //its ON - switch off
      relays(lowcut);
      snprintf (msg, 75, "Manual: %s", "LVC");
      MQ_Publish("bps/outTopic", msg);
    } else {
      relays(lowon);
      snprintf (msg, 75, "Manual: %s", "LVCon");
      MQ_Publish("bps/outTopic", msg);
    }
  }

  if (strcmp(ntopic, "HVC") == 0) {
    dit();
    dit();
    dit();
    dit();
    int res = readled(LEDPINHVC);
    snprintf (msg, 75, "%ld", res);
    MQ_Publish("readledhvc", msg);

    if (readled(LEDPINHVC) == 0) {
      //its ON - switch off
      relays(highcut);
      snprintf (msg, 75, "Manual: %s", "HVC");
      MQ_Publish("bps/outTopic", msg);
    } else {
      relays(highon);
      snprintf (msg, 75, "Manual: %s", "HVCon");
      MQ_Publish("bps/outTopic", msg);
    }
  }

  if (strcmp(ntopic, "bps/restart") == 0) {
    snprintf (msg, 75, "Reboot: %s", "Now");
    MQ_Publish("bps/outTopic", msg);
    vTaskDelay(200);
    ESP.restart();
  }

#ifdef TESTING
  if (strcmp(ntopic, "bps/testbuzz") == 0) {
    testBuzz(2);
    //snprintf (msg, 75, "%s", "Buzz");
    //  client.publish("outTopic", "Buzzz");
    testCell[3] = testCell[3] - 1;

    MQ_Publish(STATUS, msg);
    MQ_Publish("bps/outtopic", msg);
  }

  if (strcmp(ntopic, "test2/cell1") == 0) {
    testCell[0] = atoi(buf);
    //snprintf (msg, 75, "%ld", Cell[0]);
    //client.publish("outTopic", msg);
    DEBUGPRINT3("Cell[0]: ");
    DEBUGPRINTLN3(Cell[0]);
    //return;
  }
  if (strcmp(ntopic, "test2/cell2") == 0) {
    testCell[1] = atoi(buf);
    DEBUGPRINTLN3(Cell[1]);
    //return;
  }
  if (strcmp(ntopic, "test2/cell3") == 0) {
    testCell[2] = atoi(buf);
    DEBUGPRINTLN3(Cell[2]);
    //return;
  }
  if (strcmp(ntopic, "test2/cell4") == 0) {
    testCell[3] = atoi(buf);
    DEBUGPRINTLN3(Cell[3]);
    DEBUGPRINTLN3();
    //return;
  }

  //outputTest
  if (strcmp(ntopic, "test2/outputTest") == 0) {
    output_Test();
  }
#endif

}

void mqttconnect(bool boot) {
  char msg[75];
  int count = 0;

  /* Loop until reconnected */
  while (!client.connected()) {
    //  DEBUGPRINTLN3("MQTT connecting ...");
    count++;
    if (client.connect(Host, MQ_user, MQ_pass)) {
      if (boot) {
        snprintf (msg, 75, "MQTT Connected, Version: %ld", vers);
        MQ_Publish(STATUS, msg);
        // reconnectBuzz();
        //  mqBuzz();
        client.subscribe("LVC");
        client.subscribe("HVC");
        client.subscribe("bps/beat");
        client.subscribe("bps/restart");

      } else {
        if (count > 1500) {
          ESP.restart();
        }
        vTaskDelay(200);
        reconnectBuzz();
        //  mqBuzz();
      }
      client.subscribe("LVC");
      client.subscribe("HVC");
      client.subscribe("bps/beat");
      client.subscribe("bps/restart");
     
    }
  }

  //client.subscribe("bps/reboot");

#ifdef TESTING
  client.subscribe("test2/cell1");
  client.subscribe("test2/cell2");
  client.subscribe("test2/cell3");
  client.subscribe("test2/cell4");
  client.subscribe("test2/outputTest");
  client.subscribe("bps/testbuzz");
#endif
}
