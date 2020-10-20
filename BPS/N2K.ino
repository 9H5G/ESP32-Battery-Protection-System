
void SendN2kBattery() {
  static unsigned long TempUpdated = millis();
  tN2kMsg N2kMsg;

  if ( TempUpdated + BatUpdatePeriod < millis() ) {
    TempUpdated = millis();
    double volts = float(bank) / 1000;
    Serial.println(bank);

    Serial.println(volts);
    SetN2kDCBatStatus(N2kMsg, 1, volts, 0, 273+temperatures[0], 1);
    NMEA2000.SendMsg(N2kMsg);
    SetN2kDCStatus(N2kMsg, 1, 1, N2kDCt_Battery, 56, 92, 38500, 0.012, 00);
    NMEA2000.SendMsg(N2kMsg);
    SetN2kBatConf(N2kMsg, 1, N2kDCbt_AGM, N2kDCES_No, N2kDCbnv_12v, N2kDCbc_LiIon, AhToCoulomb(540), 90, 1.01, 90);
    NMEA2000.SendMsg(N2kMsg);
    /*
         SetN2kDCStatus(N2kMsg, 1, 1, N2kDCt_Battery, 56, 92, 38500, 0.012, 00);
         NMEA2000.SendMsg(N2kMsg);
         SetN2kBatConf(N2kMsg, 1, N2kDCbt_Gel, N2kDCES_Yes, N2kDCbnv_12v, N2kDCbc_LeadAcid, AhToCoulomb(420), 53, 1.251, 75);
         NMEA2000.SendMsg(N2kMsg);
    */
    Serial.print(millis()); Serial.println(", Battery sent");
  }
}
