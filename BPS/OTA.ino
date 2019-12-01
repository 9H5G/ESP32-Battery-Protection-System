void OTA_Setup(){
  
  ArduinoOTA.setHostname(Host);

  ArduinoOTA.onStart([]() {
    String type;

    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    //    DEBUGPRINTLN3("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    //    DEBUGPRINTLN3("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    //    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) DEBUGPRINTLN3("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) DEBUGPRINTLN3("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) DEBUGPRINTLN3("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) DEBUGPRINTLN3("Receive Failed");
    else if (error == OTA_END_ERROR) DEBUGPRINTLN3("End Failed");
  });
  ArduinoOTA.begin();
}
