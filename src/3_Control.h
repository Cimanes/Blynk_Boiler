#pragma once

/*
 * Operate two digital outputs to change boiler operation (GPIO0 = On / Off) and boiler mode (GPIO2 = summer / winter).
 * Change delay time between samples when requested via Blynk.
 * Commands are received from Blynk. BLynk is updated with feedback.
*/

// --------------------------------------------
//  Libraries
// --------------------------------------------
#include "0_Global_Config.h"    // Options and globals

// --------------------------------------------
//  Pin definitions
// --------------------------------------------
#define pin_run 0     // ESP-01 GPIO0 digital output pin to energize the relay that makes the boiler run.
#define pin_winter 2  // ESP-01 GPIO2 digital output pin to energize the relay that changes mode summer/winter.

// ESP-01 GPIO1 (TX) = onboard LED, active LOW.
// Only used if debug is not selected (Serial port).
// Not used in ESP-01S (onboard LED is driven by GPIO2)
#if defined(ESP01) && !defined(debug) && !defined(pin_led)
  #define pin_led 1   
#endif


// --------------------------------------------
//  Function Prototypes
// --------------------------------------------
void control();   // Function to control boiler operation and mode.
void setup_control();
#ifdef pin_led
    void flash_OFF();// Function to switch OFF the LED (only for ESP01 with no debug)
#endif