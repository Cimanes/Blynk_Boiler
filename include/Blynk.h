#pragma once

/*
 * The device sends data to the App using Blynk.virtualWrite(pin, value).
 * The device receives data from the App using BLYNK_WRITE(vPIN).
 */



// --------------------------------------------
//  BLYNK configuration
// --------------------------------------------
#define BLYNK_TEMPLATE_ID "TMPLc-2xzsN8"
#define BLYNK_TEMPLATE_NAME "Thermostat"
#define BLYNK_AUTH_TOKEN "0_F5qU0JwwjDi45OwxpJ3fVtkIdfiOdB"

#define BLYNK_FIRMWARE_VERSION "1.0"
#define BLYNK_USE_OTA

// #define BLYNK_DEBUG
// #define BLYNK_PRINT Serial

// --------------------------------------------
//  Function prototypes
// --------------------------------------------
void send_Blynk() ; // send readings from sensor to Blynk (<10 values per second).
void setup_Blynk(); // Setup Blynk connection and timers.
void loop_Blynk() ; // Blynk run function for loop.