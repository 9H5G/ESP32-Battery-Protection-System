bool loadConfig() {

  if (defaultsettings) {
    listDir(SPIFFS, "/", 0);
    //SPIFFS.remove("/config.json");
    //DEBUGPRINTLN3("File Deleted");
    //listDir(SPIFFS, "/", 0);
    saveConfig();
    defaultsettings = false;
  }

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    DEBUGPRINTLN3("Failed to open config file for reading");
    return false;
  }

  printFile("/config.json");
  size_t size = configFile.size();
  if (size > 1024) {
    DEBUGPRINTLN3("Config file size is too large");
    return false;
  }
  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<600> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    DEBUGPRINTLN3("Failed to parse config file");
    return false;
  }

  Version = json["Version"];

  DEBUGPRINT3("Vers: ");
  DEBUGPRINTLN3(vers);
  DEBUGPRINTLN3(Version);

  strcpy(WifiSSID, json["WifiSSID"]);
  strcpy(WifiKey, json["WifiKey"]);
  strcpy(ControllerUser, json["ControllerUser"]);
  strcpy(ControllerPassword, json["ControllerPassword"]);
  strcpy(MQTT_client, json["MQ_client"]);
  strcpy(BrokerIP, json["BrokerIP"]);

  high_cellwarn = json["high_cellwarn"];
  low_cellwarn = json["low_cellwarn"];
  high_cellcutoff = json["high_cellcutoff"];
  low_cellcutoff = json["low_cellcutoff"];
  high_bankwarn = json["high_bankwarn"];
  low_bankwarn = json["low_bankwarn"];
  high_bankcutoff = json["high_bankcutoff"];
  low_bankcutoff = json["low_bankcutoff"];
  reportrate = json["reportrate"];
  deltacutoff = json["deltacutoff"];

  gpio_1 = json["gpio_1"];
  gpio_2 = json["gpio_2"];

  DEBUGPRINTLN3();
  DEBUGPRINTLN3("--- Loading Config ---");
  DEBUGPRINTLN3(Version);
  DEBUGPRINTLN3(WifiSSID);
  DEBUGPRINTLN3(WifiKey);
  DEBUGPRINTLN3(ControllerUser);
  DEBUGPRINTLN3(ControllerPassword);
  DEBUGPRINTLN3(Host);
  DEBUGPRINTLN3(MQTT_client);
  DEBUGPRINTLN3(mqtt_server);

  DEBUGPRINT3("high_cellcutoff: ");
  DEBUGPRINTLN3(high_cellcutoff);

  DEBUGPRINT3("low_cellcutoff: ");
  DEBUGPRINTLN3(low_cellcutoff);

  DEBUGPRINT3("high_bankwarn: ");
  DEBUGPRINTLN3(high_bankwarn);

  DEBUGPRINT3("low_bankwarn: ");
  DEBUGPRINTLN3(low_bankwarn);
  DEBUGPRINTLN3(reportrate);
  DEBUGPRINTLN3("--- Config Loaded ---");
  DEBUGPRINTLN3();

  return true;
}

bool saveConfig() {
  StaticJsonBuffer<600> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  DEBUGPRINT3("--- Saving version: ");
  DEBUGPRINT3(vers);
  DEBUGPRINTLN3(" ---");

  DEBUGPRINTLN3(ssid);
  DEBUGPRINTLN3(password);
  DEBUGPRINTLN3(MQ_user);
  DEBUGPRINTLN3(MQ_pass);
  DEBUGPRINTLN3(Host);
  DEBUGPRINTLN3(mqtt_server);
  DEBUGPRINTLN3(MQ_client);
  DEBUGPRINTLN3(high_cellcutoff);
  DEBUGPRINTLN3(low_cellcutoff);
  DEBUGPRINTLN3(high_bankwarn);
  DEBUGPRINTLN3(low_bankwarn);
  json["WifiSSID"] = ssid;
  json["WifiKey"] = password;
  json["ControllerUser"] = MQ_user;
  json["ControllerPassword"] = MQ_pass;
  json["Host"] = Host;
  json["BrokerIP"] = mqtt_server;
  json["Version"] = vers;
  json["MQ_client"] = MQ_client;

  json["high_cellwarn"] = high_cellwarn;
  json["low_cellwarn"] = low_cellwarn;
  json["high_cellcutoff"] = high_cellcutoff;
  json["low_cellcutoff"] = low_cellcutoff;

  json["high_bankwarn"] = high_bankwarn;
  json["low_bankwarn"] = low_bankwarn;
  json["high_bankcutoff"] = high_bankcutoff;
  json["low_bankcutoff"] = low_bankcutoff;
  json["reportrate"] = reportrate;
  json["deltacutoff"] = deltacutoff;
  json["gpio_1"] = gpio_1;
  json["gpio_2"] = gpio_2;
  DEBUGPRINTLN3(reportrate);

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    DEBUGPRINTLN3("Failed to open config file for writing");
    return false;
  }

  if (json.printTo(configFile) == 0) {
    DEBUGPRINTLN3(F("Failed to write to file"));
  }
  configFile.close();
  printFile("/config.json");

  return true;
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename);
  if (!file) {
    DEBUGPRINTLN3(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    //if(DEBUGLEVEL >0){
    DEBUGPRINT3((char)file.read());
    //}
  }
  DEBUGPRINTLN3();

  // Close the file (File's destructor doesn't close the file)
  file.close();
}
