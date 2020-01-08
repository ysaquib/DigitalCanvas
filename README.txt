Digital Canvas
Authors: Yusuf Saquib and Sideeg Hassan
Course: 15-348 Embedded Systems

In order to run digitalcanvas.py, 
you must ensure you have tkinter, pyserial, and math libraries installed on your machine

In order to run the digital canvas project, connect your Tiva C board to you machine
and run the main.c file in Code Composer. Check that you're getting readable serial output
using PuTTY. The serial output should have lines in the following format.
Sensor  -  Num   -  Dist  -  Angle
SENSOR  -  ZERO  -  1500  -  42

Close Putty, and run the python script, then click "Run Digital Canvas" while making sure that
the object you are tracking is detected by both sensors in their initial states.
