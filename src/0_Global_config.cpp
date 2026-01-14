#include "0_Global_Config.h"    // Options and globals

//--------------------------------------------
//  Global Variables definitions
//--------------------------------------------

// ------------ WiFi Credentials ------------
#if defined(Cespedal) || defined(Barrioscuro)
  const char ssid[] = "Pepe_Cimanes";
  const char pass[] = "Cimanes7581" ;
#elif defined(Toledo)
  const char ssid[] = "MIWIFI_HtR7" ;
  const char pass[] = "TdQTDf3H"    ; //
#endif

//  --------  Control Variables   -----------
bool sync_time  = 0 ; // time synch done after boot (used with Blynk RTC).
bool boiler     = 0 ; // Select ON / OFF operation (Relay output to disconnect boiler).
bool boiler_old = 0 ; // Record "previous condition" of ON / OFF operation.
bool winter     = 0 ; // Select summer/winter operation (Relay output to change mode).
bool winter_old = 0 ; // Record "previous condition" of summer/winter operation.
bool refresh_dt = 0 ; // Detect when period change is required.
