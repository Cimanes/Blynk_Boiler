## Introduction
Board: ESP-01 or ESP-01S.
Coded in Arduino enviroment using VS code.
Device to operate a boiler remotely using Blynk as interface.
The user can turn the boiler ON/OFF and change the operation mode from Summer/Winter.
The ESP will operate two relays.
Optional debug via serial port.

### Components
  - ESP-01 or ESP-01S board
  - Two relays to drive the "ON/OFF" and the "Summer/Winter" operation of the system (boiler).
  - Blynk is the user interface:
      Commands can be sent from Blynk ("ON/OFF" and "Summer/Winter" pushbuttons).
      Actual position is sent back to Blynk as feedback.
      The sampling time can also be changed via Blynk (Slider bar).
      Timestamp is received via Blynk RTC Widget

  Send and receive data to Blynk (operation and monitor in remote mode). In this case, retrieve time and date from Blynk cloud.
  (optional): serial printer for debug and troubleshooting.
 
### Libraries
- [Time Library](https://github.com/PaulStoffregen/Time)
- [Blynk library](https://github.com/blynkkk/blynk-library)