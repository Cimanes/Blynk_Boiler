#include "1_Timers.h"    // Options and globals

//--------------------------------------------
//  Timers (definitions)
//--------------------------------------------
BlynkTimer timer    ; // Timer object from Blynktimer.

int t_clock   = -1  ; // Timer for date & time refresh from Blynk or NTP.
int t_LED     = -1  ; // Timer to show change of mode.
int t_control = -1  ; // Timer for data and thermostat control.

unsigned long Dt_control = 10000UL; // interval (ms) for refresh.

//--------------------------------------------
//  Timer function for loop 
//--------------------------------------------
void loop_timer() { timer.run()  ; }


/*
* Using BlynkTimer (a modified SimpleTimer) for timers.
* BlynkTimer: https://github.com/blynkkk/blynk-library/blob/master/src/Blynk/BlynkTimer.h
* Reference: https://playground.arduino.cc/Code/SimpleTimer/
*
* Functions:
* SimpleTimer() / BlynkTimer()       --> constructor to create the object
* setInterval(d, f)   --> Call function "f" periodically, every "d" ms. // d is "long".
* setTimeout(d, f)    --> Call function "f" only ONCE after "d" milliseconds. // d is "long"  // "f" is void().
* setTimer(d, f, n)   --> Call function "f" every "d" milliseconds for "n" times.
* enable(t_xxx)       --> Enables that timer.
* disable(t_xxx)      --> Disables that timer.
* toggle(t_xxx)       --> Toggles status of that timer (enable / disable).
* restartTimer(t_xxx) --> The timer starts counting from now, although the corresponding function has not been triggered (Watchdog...).
* deleteTimer(t_xxx)  --> Stop using this timer slot.
* n = getNumTimers()  --> Return the number of used slots in a timer object
*
* Define actions instead of calling function:
* t_flash = timer.setTimeout(d, []() { digitalWrite(flash_Pin, LOW);  } );
*/