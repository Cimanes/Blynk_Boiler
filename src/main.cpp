/* ESP01 with Relay module to change boiler mode summer/winter.
 *
 * Board connected to two relay modules, using GPIO0 and GPIO2 to operate them.
 * The contacts "COM" & "N.O." of the relays are connected in parallel with the "On/Off" and "Summer/winter" switches on the boiler.
 * Blynk virtual pin vpin_run --> control GPIO0 (pulled up) ==> LOW will energize the relay (Run Boiler).
 * Blynk virtual pin vpin_winter --> control GPIO2 (pulled up) ==> LOW will energize the relay (winter mode).
 * Blynk virtual pin vpin_period --> adjust period of boiler control loop (in seconds).
 * The timestamp is obtained from Blynk cloud RTC (real time clock).
 * The timestamp is sent to Blynk V10 for display.
 * Remote command to reboot device can be sent from Blynk console.
 *
 * The library <SimpleTimer.h> is used to handle the timers for the periodic actions (sensing, control and remote update).
 * Send and receive data to Blynk (operation and monitor in remote).
 * Retrieve time and date from Blynk cloud RTC.
 * (optional): Serial printer for debug and troubleshooting.
 * Note: Serial printer not working when code is loaded via VS Code. Working OK when code loaded from Arduino IDE.
 *
 * Note:  Jumper GPIO0 and Ground to start ESP01 in "programming" mode.
 *        Remove Jumper to allow normal operation.
 *        If using "upgraded" UART adapter: 
 *            - Switch = "ON" to start in "programming" mode. 
 *            - Switch = "1" for normal operation.
 */


// --------------------------------------------
//  Libraries
// --------------------------------------------
#include <Global_config.h>
#include <Timers.h>
#include <Blynk.h>
#include <Control.h>


// --------------------------------------------
//  Setup
// --------------------------------------------
void setup() {
  #ifdef debug
    Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  #endif
  setup_Blynk()   ;
  setup_control() ;
  #ifdef debug
    Serial.println(F("Setup done"));
  #endif
}


// --------------------------------------------
//  Loop
// --------------------------------------------
void loop() {
  loop_Blynk();
  loop_timer();
}
