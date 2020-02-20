void ADC_Setup() {
  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  ads.begin();
  ads.setSPS(ADS1115_DR_8SPS);
}

int32_t adcFilter(int adc) {
  int32_t reading = 0;
  int32_t result = 0;
  bool valid = false;

  /*
      If reading out of range, dump it
  */
  while (valid == false) {
    reading = ads.readADC_SingleEnded(adc);

    if (reading < 65534) {
      valid = true;
      result = result + reading;
    }
  }
  return result ;
}

void readVoltage()
{
  uint16_t adc0 = 0, adc1 = 0, adc2 = 0, adc3 = 0;
  uint16_t ADC[] = {0, 0, 0, 0};
  char mymsg[50];
  int iterations = 1;
  unsigned long uptimeStart;
  uptimeStart =  esp_timer_get_time();

  for (int i = 0; i < 4 ; i++) {// For each cell

    //ADC[i] = ads.readADC_SingleEnded(i);// Read each cell to get rid of previous value

   // for (int j = 0; j < iterations; j++) {// Do up to x readings

      ADC[i] = adcFilter(i);
      //    cellAve[i] = (cellAve[i] * 3 / 4) + (ADC[i] / 4);
      cellAve[i] = ADC[i];
 /*     if (abs( cellAve[i] - ADC[i]) < 3) {
        j = iterations ;
      }
   */
 //}
  }
  /*
     Convert to Voltage
  */
  ADC[0] = cellAve[0] * 2 * 2048 / 32768 ;
  ADC[1] = cellAve[1] * 4 * 2048 / 32768 ;
  ADC[2] = cellAve[2] * 6 * 2048 / 32768 ;
  ADC[3] = cellAve[3] * 8 * 2048 / 32768 ;

  ADC[0] = ADC[0] + 20;//27;
  ADC[1] = ADC[1] + 50;//60;
  ADC[2] = ADC[2] + 40;//57;
  ADC[3] = ADC[3] + 48;//70;

#ifdef TESTING
  snprintf (msg, 50, " % d", ADC[0] );
  MQ_Publish( "bps/adc0", msg);
  snprintf (msg, 50, " % d", ADC[1]  );
  MQ_Publish( "bps/adc1", msg);
  snprintf (msg, 50, " % d", ADC[2]   );
  MQ_Publish( "bps/adc2", msg);
  snprintf (msg, 50, " % d", ADC[3] );
  MQ_Publish( "bps/adc3", msg);
#endif

  Cell[0] = ADC[0] ;//- 8 ;
  Cell[1] = ADC[1] - ADC[0]  ;//- 4;
  Cell[2] = ADC[2] - ADC[1]  ; //- 9;
  Cell[3] = ADC[3] - ADC[2]  ; //+ 33;
  bank = ADC[3] ;//+ 15;

#ifdef TESTINGVOLTAGE
  Cell[0] = testCell[0] ;
  Cell[1] = testCell[1] ;
  Cell[2] = testCell[2] ;
  Cell[3] = testCell[3] ;
  bank = testCell[0] + testCell[1] + testCell[2] + testCell[3];
#endif

  highcell = CellMax(Cell, sizeof(Cell) / sizeof(Cell[0]));
  lowcell = CellMin(Cell, sizeof(Cell) / sizeof(Cell[0]));
  cellsum = Cell[0] + Cell[1] + Cell[2] + Cell[3];
  highcellv = Cell[highcell];
  lowcellv = Cell[lowcell];
  delta = highcellv - lowcellv;

  if (millis() > 10000) {
    if (millis() > reportTimer)
    {
      reportTimer = millis() + 5000;

      snprintf (msg, 50, " % d", Cell[0]);
      MQ_Publish(CELL1, msg);
      Serial.println(msg);
      snprintf (msg, 50, " % d", Cell[1]);
      MQ_Publish(CELL2, msg);
      Serial.println(msg);
      snprintf (msg, 50, " % d", Cell[2]);
      MQ_Publish(CELL3, msg);
      Serial.println(msg);
      snprintf (msg, 50, " % d", Cell[3]);
      MQ_Publish(CELL4, msg);
      Serial.println(msg);

      snprintf (msg, 50, " % d", bank);
      MQ_Publish(BANK, msg);
      Serial.println(msg);
      snprintf (msg, 50, " % d", delta);
      MQ_Publish(DELTA, msg);
      snprintf (msg, 50, " % d", highcell + 1);
      MQ_Publish(HICELL, msg);
      snprintf (msg, 50, " % d", lowcell + 1);
      MQ_Publish(LOCELL, msg);
      snprintf (msg, 50, " % d", cellsum + 1);
      MQ_Publish(CELLSUM, msg);
    }
  }

  uptime =  esp_timer_get_time();

  snprintf (msg, 50, " % u", (uptime - uptimeStart));
  MQ_Publish("bps/readtime", msg);

  snprintf (msg, 50, " % u", (uptime / 1000000));
  MQ_Publish(UPTIME, msg);
}

/*
  void readvoltage()
  {
  char mymsg[50];
  int32_t adc0, adc1, adc2, adc3;
  int32_t ADC[] = {0, 0, 0, 0};

  int ifault = 1;

  if (!testing) {
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);

    while (ifault > 0) {
      ifault = 0;
      ADC[0] = 0;
      ADC[1] = 0;
      ADC[2] = 0;
      ADC[3] = 0;

      int adc = 0;

      for (int i = 0; i < 4 ; i++) {
        ADC[i] =  adcFilter(i);// read and gross filter
        DEBUGPRINTLN3(ADC[i]);
      }

      /* snprintf (msg, 50, " % d", ADC[0]);
        MQ_Publish("bps / adc0", msg);
        snprintf (msg, 50, " % d", ADC[1]);
        MQ_Publish("bps / adc1", msg);
        snprintf (msg, 50, " % d", ADC[2]);
        MQ_Publish("bps / adc2", msg);
        snprintf (msg, 50, " % d", ADC[3]);
        MQ_Publish("bps / adc3", msg);

      /*
        Convert to voltage

      ADC[0] = ADC[0] * 2 * 2048 / 32768 ;
      ADC[1] = ADC[1] * 4 * 2048 / 32768 ;
      ADC[2] = ADC[2] * 6 * 2048 / 32768 ;
      ADC[3] = ADC[3] * 8 * 2048 / 32768 ;

      for (int i = 0; i < 4 ; i++) {

        if (abs( cellAve[i] - ADC[i]) > 10) {
          ifault++;
        }
        else
        {
          if (ifault > 0) {
            ifault--;
          }
        }

        cellAve[i] = cellAve[i] * 2 / 3 + ADC[i] / 3;

        DEBUGPRINT3("ADC: ");
        DEBUGPRINT3(i);
        DEBUGPRINT3("  : ");
        DEBUGPRINT3(ADC[i]);
        DEBUGPRINT3("  : ");
        DEBUGPRINTLN3(cellAve[i]);

        ADC[i] = cellAve[i];
        DEBUGPRINT3("ADC: ");
        DEBUGPRINT3(i);
        DEBUGPRINT3("  : ");
        DEBUGPRINT3(ADC[i]);
        DEBUGPRINT3("  : ");
        DEBUGPRINTLN3(cellAve[i]);
      }
    }
  }

  // Calculate cell values and publish
  if (!testing) {
    Cell[0] = ADC[0] ;
    Cell[1] = ADC[1] + 1 - Cell[0];
    Cell[2] = ADC[2] - 6 - Cell[1] - Cell[0] ;
    Cell[3] = ADC[3] + 5 - Cell[1] - Cell[0] - Cell[2];
    /*DEBUGPRINTLN3("Calculated");
      DEBUGPRINTLN3(Cell[0]);
      DEBUGPRINTLN3(Cell[1]);
      DEBUGPRINTLN3(Cell[2]);
      DEBUGPRINTLN3(Cell[3]);

  } else {

    testVoltages();

    ADC[3] = Cell[0] + Cell[1] + Cell[2] + Cell[3];
    /* DEBUGPRINTLN3("Calculated");
      DEBUGPRINTLN3(Cell[0]);
      DEBUGPRINTLN3(Cell[1]);
      DEBUGPRINTLN3(Cell[2]);
      DEBUGPRINTLN3(Cell[3]);

  }


  DEBUGPRINTLN3("Final: ");
  for (int i = 0; i < 4 ; i++) {
    DEBUGPRINT3("Cell: ");
    DEBUGPRINT3(i);
    DEBUGPRINT3("  : ");
    DEBUGPRINTLN3(Cell[i]);
  }
  DEBUGPRINTLN3();

  bank = ADC[3];
  highcell = CellMax(Cell, sizeof(Cell) / sizeof(Cell[0]));
  lowcell = CellMin(Cell, sizeof(Cell) / sizeof(Cell[0]));
  cellsum = Cell[0] + Cell[1] + Cell[2] + Cell[3];
  highcellv = Cell[highcell];
  lowcellv = Cell[lowcell];
  delta = highcellv - lowcellv;

  snprintf (msg, 50, " % d", Cell[0]);
  MQ_Publish(CELL1, msg);
  snprintf (msg, 50, " % d", Cell[1]);
  MQ_Publish(CELL2, msg);
  snprintf (msg, 50, " % d", Cell[2]);
  MQ_Publish(CELL3, msg);
  snprintf (msg, 50, " % d", Cell[3]);
  MQ_Publish(CELL4, msg);

  snprintf (msg, 50, " % d", bank);
  MQ_Publish(BANK, msg);
  snprintf (msg, 50, " % d", delta);
  MQ_Publish(DELTA, msg);
  snprintf (msg, 50, " % d", highcell + 1);
  MQ_Publish(HICELL, msg);
  snprintf (msg, 50, " % d", lowcell + 1);
  MQ_Publish(LOCELL, msg);

  snprintf (msg, 50, " % d", reportrate);
  MQ_Publish("test/reportrate", msg);

  }
*/
int CellMax( int arry[], int arrysize) {
  int result = 0;
  int i;
  for (i = 1; i < arrysize ; i++) {
    /*    DEBUGPRINT3("arry[i] : ");
      DEBUGPRINT3(arry[i - 1]);
      DEBUGPRINT3(" result : ");
      DEBUGPRINTLN3(arry[result]);
    */
    if (arry[i] > arry[result]) {
      result = i;
    }
  }
  return result;
}

int CellMin( int arry[], int arrysize) {
  int result = 0;
  int i ;
  for ( i = 1; i < arrysize ; i++) {
    /*    DEBUGPRINT3("arry[i] : ");
      DEBUGPRINT3(arry[i - 1]);
      DEBUGPRINT3(" result : ");
      DEBUGPRINTLN3(arry[result]);
    */
    if (arry[i] < arry[result]) {
      result = i;
    }
  }
  return result;
}
