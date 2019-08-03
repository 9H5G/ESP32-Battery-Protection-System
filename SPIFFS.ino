
void SPIFFSSetup(){
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    DEBUGPRINTLN3("Failed to mount file system");
    return;
  }
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        DEBUGPRINTLN3("- failed to open directory");
        return;
    }
    
    if(!root.isDirectory()){
        DEBUGPRINTLN3(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            DEBUGPRINT3("  DIR : ");
            DEBUGPRINTLN3(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            DEBUGPRINT3("  FILE: ");
            DEBUGPRINT3(file.name());
            DEBUGPRINT3("\tSIZE: ");
            DEBUGPRINTLN3(file.size());
        }
        file = root.openNextFile();
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        DEBUGPRINTLN3("File deleted");
    } else {
        DEBUGPRINTLN3("Delete failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        DEBUGPRINTLN3("Failed to open file for reading");
        return;
    }

    DEBUGPRINT3("Read from file: ");
    while(file.available()){
    Serial.write(file.read());
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        DEBUGPRINTLN3("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        DEBUGPRINTLN3("File written");
    } else {
        DEBUGPRINTLN3("Write failed");
    }
}

void fileSystemCheck(fs::FS &fs, const char * dirname, uint8_t levels)
{

    DEBUGPRINTLN3("SPIFFS Mount successful");
    listDir(SPIFFS, "/", 0);
    readFile(SPIFFS, "/config.json");

    File f = fs.open("/config.json");
    if (!f)
    {
      DEBUGPRINTLN3("Failed to open Config");
      File f = fs.open("/config.json", FILE_WRITE);
      if (f)
      {
        DEBUGPRINTLN3("Writing blank Config");
        for (int x = 0; x < 32768; x++)
          f.write(0);
        f.close();
      }else{
         DEBUGPRINTLN3("Writing blank Config Failed");
      }
    }else{
      DEBUGPRINTLN3("Found Config");
    }
}
