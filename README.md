# IOT-based-temperature-datalogger-using-TIVA
This project makes use of TIVA C series TM4C1294NCPDT connected launchpad ,Vb.net based user interface and temperature sensor TMP36.

Description
Firmware:
  1) This project was compiled using code composer studio v8.
  2) Tweaked the default example program tcpecho.
  3) Added temperature sensor.c and temperature sensor.h file which is called when there is TCP packet > 0 bytes.
  
  Software:
   1) UI was made using vb.net.
   2) Used timer function to send/ receivepackets via TCP to firmware.
