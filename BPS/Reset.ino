/*
   Print last reset reason of ESP32
   =================================

   Use either of the methods print_reset_reason
   or verbose_print_reset_reason to display the
   cause for the last reset of this device.

   Public Domain License.

   Author:
   Evandro Luis Copercini - 2017
*/

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */

void print_reset_reason(RESET_REASON reason)
{
  char msg[75];

  switch ( reason)
  {
    case 1 : snprintf (msg, 75, "Reset: %s", "POWERON_RESET"); break; /**<1,  Vbat power on reset*/
    case 3 : snprintf (msg, 75, "Reset:%i : %s", reason,"SW_RESET"); break;              /**<3,  Software reset digital core*/
    case 4 : snprintf (msg, 75, "Reset:%i : %s", reason,"OWDT_RESET"); break;            /**<4,  Legacy watch dog reset digital core*/
    case 5 : snprintf (msg, 75, "Reset:%i : %s", reason,"DEEPSLEEP_RESET"); break;       /**<5,  Deep Sleep reset digital core*/
    case 6 : snprintf (msg, 75, "Reset:%i : %s", reason,"SDIO_RESET"); break;            /**<6,  Reset by SLC module, reset digital core*/
    case 7 : snprintf (msg, 75, "Reset:%i : %s", reason,"TG0WDT_SYS_RESET"); break;      /**<7,  Timer Group0 Watch dog reset digital core*/
    case 8 : snprintf (msg, 75, "Reset:%i : %s", reason,"TG1WDT_SYS_RESET"); break;      /**<8,  Timer Group1 Watch dog reset digital core*/
    case 9 : snprintf (msg, 75, "Reset:%i : %s", reason,"RTCWDT_SYS_RESET"); break;      /**<9,  RTC Watch dog Reset digital core*/
    case 10 : snprintf (msg, 75, "Reset:%i : %s", reason,"INTRUSION_RESET"); break;      /**<10, Instrusion tested to reset CPU*/
    case 11 : snprintf (msg, 75, "Reset:%i : %s", reason,"TGWDT_CPU_RESET"); break;      /**<11, Time Group reset CPU*/
    case 12 : snprintf (msg, 75, "Reset:%i : %s", reason,"SW_CPU_RESET"); break;         /**<12, Software reset CPU*/
    case 13 : snprintf (msg, 75, "Reset:%i : %s", reason,"RTCWDT_CPU_RESET"); break;     /**<13, RTC Watch dog Reset CPU*/
    case 14 : snprintf (msg, 75, "Reset:%i : %s", reason,"EXT_CPU_RESET"); break;        /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : snprintf (msg, 75, "Reset:%i : %s", reason,"RTCWDT_BROWN_OUT_RESET"); break; /**<15, Reset when the vdd voltage is not stable*/
    case 16 : snprintf (msg, 75, "Reset:%i : %s", reason,"RTCWDT_RTC_RESET"); break;     /**<16, RTC Watch dog reset digital core and rtc module*/
    default : snprintf (msg, 75, "Reset:%i : %s", reason,"NO_MEAN");
  }
   Serial.println (msg);
   MQ_Publish("bps/restartreason", msg);
}

void verbose_print_reset_reason(RESET_REASON reason)
{
  char msg[75];
  switch ( reason)
  /*{
    case 1  : snprintf (msg, 75, "Reset %s",  "Vbat power on reset"); break;
    case 3  : snprintf (msg, 75, "Reset:%i : %s", reason,  "Software reset digital core"); break;
    case 4  : snprintf (msg, 75, "Reset:%i : %s", reason,  "Legacy watch dog reset digital core"); break;
    case 5  : snprintf (msg, 75, "Reset:%i : %s", reason, "Deep Sleep reset digital core"); break;
    case 6  : snprintf (msg, 75, "Reset:%i : %s", reason, "Reset by SLC module, reset digital core"); break;
    case 7  : snprintf (msg, 75, "Reset:%i : %s", reason, "Timer Group0 Watch dog reset digital core"); break;
    case 8  : snprintf (msg, 75, "Reset:%i : %s", reason, "Timer Group1 Watch dog reset digital core"); break;
    case 9  : snprintf (msg, 75, "Reset:%i : %s", reason, "RTC Watch dog Reset digital core"); break;
    case 10 : snprintf (msg, 75, "Reset:%i : %s", reason, "Instrusion tested to reset CPU"); break;
    case 11 : snprintf (msg, 75, "Reset:%i : %s", reason, "Time Group reset CPU"); break;
    case 12 : snprintf (msg, 75, "Reset:%i : %s", reason, "Software reset CPU"); break;
    case 13 : snprintf (msg, 75, "Reset:%i : %s", reason, "RTC Watch dog Reset CPU"); break;
    case 14 : snprintf (msg, 75, "Reset:%i : %s", reason, "for APP CPU, reset by PRO CPU"); break;
    case 15 : snprintf (msg, 75, "Reset:%i : %s", reason, "Reset when the vdd voltage is not stable"); break;
    case 16 : snprintf (msg, 75, "Reset:%i : %s", reason, "RTC Watch dog reset digital core and rtc module"); break;
    default : snprintf (msg, 75, "Reset:%i : %s", reason, "NO_MEAN");
  }*/
  {
    case 1  : snprintf (msg, 75, "Reset: %s",  "Vbat power on reset"); break;
    case 3  : snprintf (msg, 75, "Reset: %s",  "Software reset digital core"); break;
    case 4  : snprintf (msg, 75, "Reset: %s",   "Legacy watch dog reset digital core"); break;
    case 5  : snprintf (msg, 75, "Reset: %s",  "Deep Sleep reset digital core"); break;
    case 6  : snprintf (msg, 75, "Reset: %s",  "Reset by SLC module, reset digital core"); break;
    case 7  : snprintf (msg, 75, "Reset: %s",  "Timer Group0 Watch dog reset digital core"); break;
    case 8  : snprintf (msg, 75, "Reset: %s",  "Timer Group1 Watch dog reset digital core"); break;
    case 9  : snprintf (msg, 75, "Reset: %s",  "RTC Watch dog Reset digital core"); break;
    case 10 : snprintf (msg, 75, "Reset: %s",  "Instrusion tested to reset CPU"); break;
    case 11 : snprintf (msg, 75, "Reset: %s",  "Time Group reset CPU"); break;
    case 12 : snprintf (msg, 75, "Reset: %s",  "Software reset CPU"); break;
    case 13 : snprintf (msg, 75, "Reset: %s",  "RTC Watch dog Reset CPU"); break;
    case 14 : snprintf (msg, 75, "Reset: %s",  "for APP CPU, reset by PRO CPU"); break;
    case 15 : snprintf (msg, 75, "Reset: %s",  "Reset when the vdd voltage is not stable"); break;
    case 16 : snprintf (msg, 75, "Reset: %s",  "RTC Watch dog reset digital core and rtc module"); break;
    default : snprintf (msg, 75, "Reset: %s",  "NO_MEAN");
  }
   Serial.println (msg);
   MQ_Publish("bps/restartreason", msg);
}
