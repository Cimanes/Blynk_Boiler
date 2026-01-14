#pragma once

#include <Blynk/BlynkTimer.h>   // Use BlynkTimer for timers.

//--------------------------------------------
//  Timers (declarations)
//--------------------------------------------
extern BlynkTimer timer ; // Simpletimer function to control all timer id's.

extern int t_clock  ; // Timer for date & time refresh from Blynk or NTP.
extern int t_LED    ; // Timer to show change of mode.
extern int t_control; // Timer for data and thermostat control.

//--------------------------------------------
//  Timer intervals
//--------------------------------------------
constexpr unsigned long Dt_clock  = 5000UL; // time interval (ms) for blynk-clock refresh during boot (5000).
constexpr unsigned long Dt_LED    =  500UL; // LED on timer (ms) to show that it has changed mode.
extern unsigned long Dt_control           ; // dynamic time interval (ms) for refresh.

//--------------------------------------------
//  Function prototypes
//--------------------------------------------
void loop_timer()  ;