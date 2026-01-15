#include "0_Global_Config.h"    // Options and globals

// --------------------------------------------
//  Global Variables definitions
// --------------------------------------------
bool boiler     = 0 ; // Select ON / OFF operation (Relay output to disconnect boiler).
bool winter     = 0 ; // Select summer/winter operation (Relay output to change mode).
bool refresh_dt = 0 ; // Detect when period change is required.