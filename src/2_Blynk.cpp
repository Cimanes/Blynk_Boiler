#include "2_Blynk.h"

/*
 * The device sends data to the App using Blynk.virtualWrite(pin, value).
 * The device receives data from the App using BLYNK_WRITE(vPIN).
 */

//--------------------------------------------
//  Libraries
//--------------------------------------------
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
// #include <TimeLib.h>
#include <WidgetRTC.h>

#include "0_Global_config.h"
#include "1_Timers.h"

//--------------------------------------------
//  Variables and constants
//--------------------------------------------
const char auth[] = BLYNK_AUTH_TOKEN  ;
char Time[20] ; // Formatted time (YYYY-MM-DD hh:mm).
WidgetRTC rtc;

//--------------------------------------------
//  Virtual pin definitions
//--------------------------------------------
#if defined(Cespedal) || defined(Toledo)
  #define vpin_run V6     // V6(Cespedal), V18(Bºoscuro) = Boiler power ON / OFF (1 = ON).
  #define vpin_period V8  // V8(Cespedal), V20(Bºoscuro) = Control period (seconds).
  #define vpin_winter V9  // V9(Cespedal), V21(Bºoscuro) = Summer / Winter operation mode (1 = winter).
#endif
#ifdef Barrioscuro
  #define vpin_run V18     // V6(Cespedal), V18(Bºoscuro) = Boiler power ON / OFF (1 = ON).
  #define vpin_period V20  // V8(Cespedal), V20(Bºoscuro) = Control period (seconds).
  #define vpin_winter V21  // V9(Cespedal), V21(Bºoscuro) = Summer / Winter operation mode (1 = winter).
#endif

//--------------------------------------------
//  Receive data from Blynk when these virtual pins change
//--------------------------------------------
BLYNK_WRITE(vpin_run) {
  boiler = param.asInt()      ;
  #ifdef debug
    Serial.print(F(">Run: ")) ;
    Serial.println(boiler)    ;
  #endif
}

BLYNK_WRITE(vpin_period) {
  Dt_control = param.asInt()*1000     ; // Convert to milliseconds.   ;
  refresh_dt = 1                      ;         
  #ifdef debug
    Serial.print(F(">Period: "))      ;
    Serial.println(Dt_control / 1000) ;
  #endif
}

BLYNK_WRITE(vpin_winter) {
  winter = param.asInt()        ;
  #ifdef debug
    Serial.print(F(">Winter: "));
    Serial.println(winter)      ;
  #endif
}

BLYNK_WRITE(InternalPinDBG) {     // Internal pin = V255 -> used for special commands such as reboot device
  const char* cmd = param.asStr()                 ;
  if (strcmp(cmd, "reboot") == 0) {
    #ifdef debug
      Serial.println(F("Rebooting..."))           ;
    #endif
    timer.setTimeout(500, [](){ ESP.restart(); }) ;
    for (;;) {}
  }
}


//--------------------------------------------
//  RTC from blynk
//--------------------------------------------
void get_Date() {
  // Obtain date and time from Blynk RTC and format it into Time[]

  // --- Option (1): Using sprintf (slower method):
  // sprintf(Time,"%04d-%02d-%02d / %02d:%02d", year(), month(), day(), hour(), minute());

  // --- Option (2): Using direct char manipulation (faster method):
  int yr = year()   ;
  byte mo = month() ;
  byte dy = day()   ;
  byte hh = hour()  ;
  byte mm = minute();

  // "'0' +" converts int to char: '0' = ASCII 48. So '0' + 1 = ASCII 49 = char '1'
  Time[0] = '0' + (yr / 1000) % 10;
  Time[1] = '0' + (yr / 100)  % 10;
  Time[2] = '0' + (yr / 10)   % 10;
  Time[3] = '0' + (yr % 10) ;
  Time[4] = '-'             ;
  Time[5] = '0' + (mo / 10) ;
  Time[6] = '0' + (mo % 10) ;
  Time[7] = '-'             ;
  Time[8]  = '0' + (dy / 10);
  Time[9]  = '0' + (dy % 10);
  Time[10] = ' '            ;
  Time[11] = '/'            ;
  Time[12] = ' '            ;
  Time[13] = '0' + (hh / 10);
  Time[14] = '0' + (hh % 10);
  Time[15] = ':'            ;
  Time[16] = '0' + (mm / 10);
  Time[17] = '0' + (mm % 10);
  Time[18] = '\0'           ;

  #ifdef debug
    Serial.print(F("Time: "));
    Serial.println(Time);
  #endif

  // if (year() > 2024) timer.deleteTimer(t_clock);
  if(!sync_time and year()  > 2024) {
    timer.deleteTimer(t_clock)          ;
    sync_time = 1                       ;
    #ifdef debug
       Serial.println(F("date sync'd")) ;
    #endif
  }
}


//--------------------------------------------
//  Send data to Blynk
//--------------------------------------------
void send_Blynk() {
// send readings from sensor to Blynk (<10 values per second).
  get_Date()                        ; // Refresh RTC time.
  Blynk.virtualWrite(V10, Time)     ; // V10 = Date and time (from RTC).
  #ifdef debug
    // Serial.println(Time)             ;
    Serial.print(F("Fbk: Run = "))  ;
    Serial.print(boiler)            ;
    Serial.print(F(" | Period = ")) ;
    Serial.print(Dt_control / 1000) ;
    Serial.print(F(" | Winter = ")) ;
    Serial.println(winter)          ;
  #endif
}


//--------------------------------------------
//  Synchronize on Blynk connection
//--------------------------------------------
BLYNK_CONNECTED() { // Synchronize time and mode on connection.
  Blynk.sendInternal("rtc", "sync") ; 
  Blynk.syncVirtual(vpin_run)       ;
  Blynk.syncVirtual(vpin_period)    ;
  Blynk.syncVirtual(vpin_winter)    ;
  #ifdef debug
    Serial.println(F("Blynk!"))     ;
  #endif
  send_Blynk()                      ;
}


//--------------------------------------------
//  Setup
//--------------------------------------------
void setup_Blynk() {
  Blynk.begin(auth, ssid, pass)                   ; // Connect with Blink Cloud.
  rtc.begin()                                     ; // Start RTC widget
  setSyncInterval(3600)                           ; // re-synch every hour
  sync_time = 0                                   ; // Reset sync time validation when Blynk RTC is used.
  t_clock = timer.setInterval(Dt_clock, get_Date) ; // "Fast" retrieve time during boot.
}

void loop_Blynk() {  Blynk.run(); }