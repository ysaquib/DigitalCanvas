Digital Canvas
Authors: Yusuf Saquib and Sideeg Hassan
Course: 15-348 Embedded Systems

We are claiming the following points:
70 - The project does something
3 - Creating a Circuit
4 - New sensor
5 - implementation of a novel algorithm
3 - Custom code to communicate with a sensor
4 - Signal Modulation
4 - Pulse Width Modulation
4 - Interface with PC
3 - Syncronized usage of sensor and servo motor
2 - Implementation of an existing protocol
3 - Using multiple timers
2 - Usage of new hardware feature (PWM) 

In order to run digitalcanvas.py, 
you must ensure you have tkinter, pyserial, and math libraries installed on your machine

In order to run the digital canvas project, connect your Tiva C board to you machine
and run the main.c file in Code Composer. Check that you're getting readable serial output
using Putty. The serial output should have lines in the following format.

SENSOR  -  ZERO  -  1500  -  42

Close Putty, and run the python script, then click "Run Digital Canvas" while making sure that
the object you are tracking is detected by both sensors in their initial states.
