#define DEBUGLEVEL 3
#include <DebugUtils.h>
#include "credentials.h"
const long vers = 32600;

#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <ArduinoOTA.h>
#include <FS.h>
#include <PubSubClient.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define CELL1       "bps/cell1"
#define CELL2       "bps/cell2"
#define CELL3       "bps/cell3"
#define CELL4       "bps/cell4"
#define BANK        "bps/bank"
#define DELTA       "bps/delta"
#define HICELL      "bps/hicell"
#define LOCELL     "bps/locell"
#define CELLSUM  "bps/cellsum"
#define STATUS     "bps/status"
#define LVCLED     "bps/LVCled"
#define HVCLED    "bps/HVCled"
#define CUTOFF    "bps/cutoff"
#define UPTIME     "bps/uptime"
#define TEMP1      "bps/temp1"
#define TEMP2      "bps/temp2"
#define ALARM      "bps/alarm"
#define DELTASUM  "bps/deltaSum"

#define FORMAT_SPIFFS_IF_FAILED true

#define  TESTING 1

int inc = 1;

long runcounter = 0;

bool defaultsettings = false;
bool outputTest = false;
unsigned long uptime;
int pulseLength = 250;

/*
   Alarmcodes
*/
int normal = 0;
int lowchirp = 1;
int chirp = 2;
int highchirp = 3;

//Temperature warnings
int tempWarn = 40; //High temperature warning if T>40
int tooHot = 50;

/*
   Pins
*/

const int lowcut = 20;
const int lowon = 21;

const int highcut = 30;
const int highon = 31;

const int LVCONPIN = 17;
const int LVCOFFPIN = 5;

const int LEDPINLVC = 26;
const int LEDPINHVC = 25;

const int HVCOFFPIN = 16;
const int HVCONPIN = 4;

//const int mySCL = 22;
//const int mySDA = 21;

const int GPIO2 = 18;
const int GPIO1 = 19;

const int TEMPSIG1 = 23;
const int TEMPSIG2 = 27;

const int BUZZERPIN = 19;

const int TOUCH1 = 31;
const int TOUCH2 = 30;
const int TOUCH3 = 29;

const int ADC_SW = 33;
const int ADC1 = 35;
const int ADC2 = 34;
const int ADC3 = 39;
const int ADC4 = 36;

const int JTAG1 = 13;
const int JTAG2 = 12;
const int JTAG3 = 14;
const int JTAG4 = 15;

const int CANCELALARM = 13;
/*
   Copy to credentials.ino and fill in your details

  const char* ssid = "";
  const char* password = "";
  const char* Host = "";
  const char* MQ_client = "";       // your MQTT Client ID
  const char* MQ_user = "";//"mosquitto";       // your MQTT password
  const char* MQ_pass = "";       // your network password
  const char* mqtt_server = "192.168.0.4";
*/

const bool  wifi = true;

char          WifiSSID[32];
char          WifiKey[32];
char          WifiAPKey[32];
char          ControllerUser[32];
char          ControllerPassword[32];
char          MQTT_client[32];
char          Broker[32];
char          BrokerIP[32];
long          Version;

bool boot = true;
/*
   Values controlling behaviour of GPIO - Drivers
   0 == do nothing
   20 == operate with LVC in low - high - low
   21 == operate with LVC stay high
   22 == operate with LVC stay low

   30 == operate with HVC in low - high - low
   31 == operate with HVC stay high
   32 == operate with HVC stay low

*/
int gpio_1 = 0;
int gpio_2 = 0;

/*
   Defaults
*/
int oldbank = 13000;
int olddelta = 0;
int change = 0;
int bank = 13000;
int highcell = 0;
int lowcell = 0;
int16_t cellsum = 0;
int highcellv = 0;
int lowcellv = 0;
int delta = 0;
int Cell[] = {3250, 3251, 3252, 3253};
int cellAve[] = {3250, 3251, 3252, 3253};
int deltaSum = 0;

#ifdef TESTING
int testCell[] = {3300, 3300, 3340, 3300};
#endif

int ChirpSilencePeriod = 30; //seconds
unsigned long timervar = 0;

long          high_cellwarn = 3500;
long          high_cellcutoff = 3550;
long          low_cellwarn = 2600;
long          low_cellcutoff = 2500;
long          high_bankwarn = 13850;
long          high_bankcutoff = 14200;
long          low_bankwarn = 12000;
long          low_bankcutoff = 11500;
long          deltawarn = 100;
long          deltacutoff = 150;

int             reportrate = 2;
char msg[75];

struct MQMessage {
  char topic[32];
  char message[32];
};

struct Button {
  const uint8_t PIN;
  unsigned long cancelTimer;
  bool pressed;
};

Button cancel_alarm = {CANCELALARM, 0, false};

Adafruit_ADS1115 ads;

QueueHandle_t ChirpQueue, PrintQueue, MQ_Queue, ChirpSilenceQ;
TaskHandle_t TaskA, TaskB, TaskC, TaskD , TaskE;

WiFiClient espClient;
PubSubClient client(espClient);

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(TEMPSIG1);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;
int temperatures[2];

void runEachTimer(int oldAlarmStatus)
{
  timervar = millis() + (reportrate * 1000);

  if (wifi) {
    int count = 0;

    while (WiFi.status() != WL_CONNECTED) {

      vTaskDelay(500);
      count++;
      DEBUGPRINT3("+");
      WiFi.begin(ssid, password);
      if (count > 20) {
        ESP.restart();
      }
    }

    if (!client.connected()) {
      void mqttconnect();
    }
  }

  myreadvoltage();

  int alarmstatus = 0;

  alarmstatus = (int) calculate_alarms();
  
  oldAlarmStatus = alarmstatus;
  DEBUGPRINT3("Final AlarmStatus: ");
  DEBUGPRINTLN3(alarmstatus);

  runalarms(alarmstatus, oldAlarmStatus);

  int answer = 100;
  answer = (readled(LEDPINHVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish(LVCLED, msg);

  answer = (readled(LEDPINLVC) == 0) ? 1 : 0;
  snprintf (msg, 75, "%ld", answer);
  MQ_Publish(HVCLED, msg);

  getTemperatures();
  runTemperatureAlarm();

  snprintf (msg, 75, "%d", temperatures[0]);
  MQ_Publish(TEMP1, msg);
  snprintf (msg, 75, "%d", temperatures[1]);
  MQ_Publish(TEMP2, msg);

  updateLed();
  ArduinoOTA.handle();

}

void setup()
{
  setup_interrupts();
  ADC_Setup();
  PinSetup();
  OneWireSetup();

  ChirpQueue = xQueueCreate( 10, sizeof( int ));
  PrintQueue = xQueueCreate( 10, 32);
  MQ_Queue = xQueueCreate(15, sizeof(struct MQMessage));
  // ChirpSilenceQ = xQueueCreate(5, sizeof( bool ));

  Serial.begin(115200);
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    DEBUGPRINTLN3("Failed to mount file system");
    return;
  }

  loadConfig();

  if (wifi) {
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(Host);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(500);
      Serial.print(ssid);
    }

    /* configure the MQTT server with IPaddress and port */
    DEBUGPRINTLN3(mqtt_server);

    client.setServer(mqtt_server, 1883);
    /* this receivedCallback function will be invoked
      when client received subscribed topic */
    client.setCallback(receivedCallback);
    mqttconnect(boot);
    boot = false;
  }


  OTA_Setup();


  if (wifi) {

    xTaskCreatePinnedToCore(
      MQTT_Handle,
      "MQTT_Task",
      8192,
      NULL,
      5,
      &TaskD,
      tskNO_AFFINITY);//0
    vTaskDelay(500);

  }

  xTaskCreatePinnedToCore(
    Task1,
    "RunTimer_Task",
    8192,
    NULL,
    6,
    &TaskA,
    1);//1

  vTaskDelay(500);

  xTaskCreatePinnedToCore(
    ServiceAlarmQueue,
    "ChirpTask",
    8192,
    NULL,
    6,
    &TaskB,
    tskNO_AFFINITY);//1

  vTaskDelay(500);

  xTaskCreatePinnedToCore(
    SerialPrintTask,
    "PrintTask",
    8192,
    NULL,
    6,
    &TaskC,
    tskNO_AFFINITY);//1

  vTaskDelay(500);
  /*
    xTaskCreatePinnedToCore(
      ChirpSilence,
      "ChirpSilence",
      8192,
      NULL,
      6,
      &TaskE,
      1);//1
    vTaskDelay(500);
  */
  DEBUGPRINTLN3(uxTaskGetNumberOfTasks());
  DEBUGPRINTLN3(eTaskGetState(TaskA));
  DEBUGPRINTLN3(eTaskGetState(TaskB));
  DEBUGPRINTLN3(eTaskGetState(TaskC));
  DEBUGPRINTLN3(eTaskGetState(TaskD));
  //  DEBUGPRINTLN3(eTaskGetState(TaskE));
  DEBUGPRINTLN3("SetupCompleted");

  updateLed();
  rebootBuzz();

}

void loop(void)
{
  // client.loop();
  vTaskDelay(2000);

}
