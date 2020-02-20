void Task1(void * parameter ) {
  int oldalarmstatus = 0;
  for (;;) {
    if (millis() > timervar) {
      runEachTimer(oldalarmstatus);
    }
    client.loop();
    ArduinoOTA.handle();
    vTaskDelay(50);
  }
}

void ServiceAlarmQueue(void * parameter) {
  char mymsg[75];
  int currentChirp = 0;
  int  chirpTimer = 0;
  for (;;) {
    int element = 0;
    if (millis() > chirpTimer) {
      chirpTimer = 0;
      currentChirp = 0;
    }
    xQueueReceive(ChirpQueue, &element, portMAX_DELAY);
    if (element > 0) {

      if (element > currentChirp) {// If its a higher priority alarm reset timer and chirp this alarm
        currentChirp = element;
        chirpTimer = millis() + 2000;
        snprintf (msg, 75, "CurrentChirp %ld", currentChirp);
        MQ_Publish(STATUS, msg);
      }

      while ((millis() < chirpTimer)) {

        Chirp(currentChirp);

        vTaskDelay(2000);

        if ( xQueuePeek( ChirpQueue, &element , ( TickType_t ) 10 ) ) {
          if (element != currentChirp) {
            chirpTimer = 0; //bail from the loop and get the next message
            currentChirp = 0;
            /* snprintf (msg, 75, "Bailing %ld : %ld", millis(), chirpTimer);
              MQ_Publish(STATUS, msg);
            */
          } else {
            xQueueReceive (ChirpQueue, &element,  ( TickType_t ) 10 );// Get it out of the queue if its the same
          }
        }
      }

    } else {
      /*#ifdef TESTING
            snprintf (msg, 75, "Bailing %ld : %ld", millis(), chirpTimer);
            MQ_Publish(STATUS, msg);
        #endif
      */
    }
  }
}

void SerialPrintTask(void * parameter) {
  char mymsg[50];
  for (;;) {
    char element[32] = "";
    xQueueReceive(PrintQueue, &element, portMAX_DELAY);
  }
}

void PrintMessage(char *msgbuff) {
  if (wifi) {
    xQueueSend(PrintQueue, msgbuff, 0);
    DEBUGPRINT3("mymessage triggered");
  }
}

void MQ_Publish(char *mytopic, char *mymsg) {
  struct MQMessage mqMessage;
  if (wifi) {
    strcpy(mqMessage.topic , mytopic);
    strcpy(mqMessage.message , mymsg);
    xQueueSend(MQ_Queue, &mqMessage, ( TickType_t ) 10);
  }
}

void wifiReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    int count = 0;
    WiFi.begin(ssid, password);

    disconnectBuzz();

    while (WiFi.status() != WL_CONNECTED) {
      DEBUGPRINT3("+");
      vTaskDelay(200);
      count++;

      if (count > 600) {
        ESP.restart();
      }
    }
  }
  mqttconnect(false);
}

void MQTT_Handle(void * parameter) {
  //Runs as a task
  struct MQMessage myMessage;
  char msg[50];

  for (;;) {
    if (wifi) {
      //Check connections
      wifiReconnect();
      //Receive topic and msg from Queue
      xQueueReceive(MQ_Queue, &myMessage, portMAX_DELAY);
      vTaskDelay(10);
      client.publish(myMessage.topic, myMessage.message);
      static uint32_t maxUsed = 0;
      uint32_t stackUsed = uxTaskGetStackHighWaterMark(NULL);
      if (stackUsed > maxUsed) {
        Serial.printf("MQTT_Handler increased Stack usage = %d\n", stackUsed);
      }
      maxUsed = stackUsed;
    }
    client.loop();
  }
}

/*
  void ChirpSilence(void * parameter) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 10;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount ();
  for ( ;; )
  {
    xQueueReceive(ChirpSilenceQ, &ChirpBeep, portMAX_DELAY);

    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, xFrequency );

    // Perform action here.
  }
  }
*/
