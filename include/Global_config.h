#pragma once

// --------------------------------------------
//  Options
// --------------------------------------------
//**** Uncomment to allow serial print debug.
#define debug

//**** Choose the correct board (ESP01 or ESP01S)
#define ESP01     // Enable logic fror LED flashing
// #define ESP01S // LED cannot flash (built in led = GPIO2 = Winter / summer output)

//**** Choose the correct location for wifi credentials.
// #define Cespedal
// #define Barrioscuro
#define Toledo


// --------------------------------------------
//  Global Variables declarations
// --------------------------------------------
// extern bool sync_time ; // time synch done after boot (used with Blynk RTC).
extern bool boiler    ; // Select ON / OFF operation (Relay output to disconnect boiler).
extern bool winter    ; // Select summer/winter operation (Relay output to change mode).
extern bool refresh_dt; // Detect when period change is required.