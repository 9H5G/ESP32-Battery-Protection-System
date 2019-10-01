void OneWireSetup() {
  sensors.begin();  // Start up the library
  Serial.begin(9600);

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  /*  Serial.print(deviceCount, DEC);
    Serial.println(" devices.");
    Serial.println("");
  */
}

void getTemperatures() {
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures();

  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    /*    Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(" : ");
    */
    tempC = sensors.getTempCByIndex(i);
    temperatures[i] = tempC;
    /*
      Serial.print(tempC);
      Serial.print((char)176);//shows degrees character
      Serial.print("C  |  ");
      Serial.print(DallasTemperature::toFahrenheit(tempC));
      Serial.print((char)176);//shows degrees character
      Serial.println("F");
    */
  }

  //  Serial.println("");
}

void runTemperatureAlarm()
{
  for (int i = 0 ; i < deviceCount; i++) {
    if (temperatures[i] > tooHot)
    {
      relays(lowcut);
      relays(highcut);
    }
    
    if (temperatures[i] < 0)//Inhibit charging
    {
      relays(highcut);
    }

      if (temperatures[i] > tempWarn)
    {
xQueueSend(ChirpQueue, &tempWarn, 0);
    }
  }
}
