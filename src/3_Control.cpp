#include "3_Control.h"

/*
 * Operate two digital outputs to change boiler operation (GPIO0 = On / Off) and boiler mode (GPIO2 = summer / winter).
 * Change delay time between samples when requested via Blynk.
 * Commands are received from Blynk. BLynk is updated with feedback.
*/

// --------------------------------------------
//  Libraries
// --------------------------------------------
#include "1_Timers.h"
#include "2_Blynk.h"


//--------------------------------------------
//  Function to switch OFF the LED (only for ESP01 with no debug)
//--------------------------------------------
// Function defined to be used with Timer.
#ifdef pin_led
    void flash_OFF() { digitalWrite(pin_led, HIGH); }
#endif


//--------------------------------------------
//  Control operation of boiler mode
//--------------------------------------------
void control() {
  #ifdef debug
    Serial.println(F("Start Control"))  ;
  #endif
  if (boiler != boiler_old) {
    digitalWrite(pin_run, !boiler)      ; // Operate relay (relay is energized when pin is LOW).
    boiler_old = boiler                 ; // Refresh "previous condition" as new condition.
    #ifdef debug
      Serial.print(F("Run> "))          ;
      Serial.println(boiler)            ;
    #else
      #ifdef ESP01
        digitalWrite(pin_led, LOW)                  ; // Flash LED ON.
        t_LED = timer.setTimeout(Dt_LED, flash_OFF) ; // Flash LED OFF after time delay.
      #endif
    #endif
  }

  if (winter != winter_old) {
    digitalWrite(pin_winter, !winter) ; // Operate relay (relay is energized when pin is LOW).
    winter_old = winter               ; // Refresh "previous condition" as new condition.
    #ifdef debug
      Serial.print(F("Winter> "))     ;
      Serial.println(winter)          ;
    #else
      #ifdef ESP01
        digitalWrite(pin_led, LOW)                  ; // Flash LED ON.
        t_LED = timer.setTimeout(Dt_LED, flash_OFF) ; // Flash LED OFF after time delay.
      #endif
    #endif
  }

  if (refresh_dt) {
    timer.deleteTimer(t_control)                      ; // Delete the periodical data retrieval to change rate.
    t_control = timer.setInterval(Dt_control, control); // Re-initiate periodical operation with new timer.
    refresh_dt = 0                                    ; // Refresh "previous condition" as new condition.
    #ifdef debug
      Serial.print(F("Period> "))                     ;
      Serial.println(Dt_control / 1000)               ;
    #else
      #ifdef ESP01
        digitalWrite(pin_led, LOW)                  ; // Flash LED ON.
        t_LED = timer.setTimeout(Dt_LED, flash_OFF) ; // Flash LED OFF after time delay.
      #endif
    #endif
  }

  #ifdef debug
    Serial.println(F("Control done "));
  #endif
  send_Blynk()                        ;
}

//--------------------------------------------
//  Setup
//--------------------------------------------
void setup_control() {
  pinMode(pin_winter, OUTPUT)   ;
  digitalWrite(pin_winter, HIGH); // De-energize "Winter" relay (relay is energized when pin is LOW).
  pinMode(pin_run, OUTPUT)      ;
  digitalWrite(pin_run, HIGH)   ; // De-energize "Run" relay (relay is energized when pin is LOW).
  
  #ifdef pin_led                          // Board ESP-01, with no debug
    pinMode(pin_led, OUTPUT)    ;
    digitalWrite(pin_led, HIGH) ; // Turn built-in LED off.
  #endif

  control()                     ;
  t_control = timer.setInterval(Dt_control, control); // Periodically perform boiler control.
}