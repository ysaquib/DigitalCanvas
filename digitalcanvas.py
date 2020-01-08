# Author:                         Yusuf Saquib
# Project:                        Digital Canvas
# Date Created:                   09/12/2019
# Date Modified:                  --/--/----

# This python script is used to read serial 
# and to graph the coordinates it reads as a line

import serial
import math
# import networkx as nx
# import matplotlib.pyplot as plt

import tkinter as tk


def openSerial(com, speed):
    # Open the serial port and return it
    ser = serial.Serial(
        com, 
        speed
        # ,
        # timeout = 0, 
        # parity = serial.PARITY_EVEN, 
        # rtscts=1
        )
    return ser


def posToRadians (position):
    # Change position from servo motor to radians
    # Change these values for tuning
    return (((position-750) / 1500)*180) * (math.pi)

# Requires:  angle in radians, distance > 0, width > 0
# Ensures:   result is x and y components of vector
def triangulateX(angle, distance, width):
    if angle > (math.pi/2):
        return(math.sin (angle - math.pi/2) * distance + (width/2), 
               math.cos (angle - math.pi/2) * distance)
    else:
        return((width/2) - math.cos (angle) * distance,
               math.sin (angle) * distance)

# Requires:  angle in radians, distance > 0, height > 0
# Ensures:   result is x and y components of vector
def triangulateY(angle, distance, height):
    if angle < (math.pi/2):
        return(math.sin (angle - math.pi/2) * distance, 
               math.cos (angle - math.pi/2) * distance + (height/2))
    else:
        return(math.cos (angle) * distance,
              (height/2) - math.sin (angle) * distance)

def readAndWrite(canvas):
    # Change these for different COM if needed. Speed is fine as is
    ser = openSerial("COM3", 115200)
    # Add the canvas to the tkinter window
    canvas.pack()

    # Set height and width bounds of the surface
    height = 500
    width  = 500

    # Infinite while loop to keep reading serial port lines
    # And draw the graph

    serl_zero = ""
    serl_one = ""

    # Tune this if drawing too far
    dist_lim = 40


    # Setup previous x y coordinates
    x_previous = 0
    y_previous = 0

    # This is the distance from the sensor-motor device to the
    # upper left corner of the drawing area
    dist = 8

    # Loop that continues running to update the interface
    while (True):
        # Read one line from the serial port
        serl_zero = ser.readline().decode("utf-8")

        # The following code requires that the serial output be in the form:
        #        - SENSOR # - ANGLE - DISTANCE
        # SENSOR - ZERO     - 1800  - 42
        # SENSOR - ONE      - 1800  - 42
        # SENSOR - TWO      - 1800  - 42
        # SENSOR - THREE    - 1800  - 42

        # This is also under the assumption that sensors
        # zero and one are on the x axis
        # two and three are on the y axis

        if "ZERO" in serl_zero:
            # Read the next three lines
            serl_one = ser.readline().decode("utf-8")
            serl_two = ser.readline().decode("utf-8")
            serl_three = ser.readline().decode("utf-8")

            zero_list = serl_one.split("-")
            one_list = serl_one.split("-")
            two_list = serl_one.split("-")
            three_list = serl_one.split("-")

            if len(zero_list) == len(one_list) == len(two_list) == len(three_list) == 4:
                # Get the distance output by the sensor and set it to a variable
                delta_x0 = int(zero_list[3].strip())
                delta_x1 = int(one_list[3].strip())

                delta_y0 = int(two_list[3].strip())
                delta_y1 = int(three_list[3].strip())

                if abs(delta_x0 - delta_x1) <= 2 and delta_x0 < dist_lim and delta_x1 < dist_lim and abs(delta_y0 - delta_y1) <= 2 and delta_y0 < dist_lim and delta_y1 < dist_lim:
                    # Get the angle output by the sensor (IN RADIANS)
                    theta0 = posToRadians(int(zero_list[2].strip()))
                    theta1 = posToRadians(int(one_list[2].strip()))

                    phi0 = posToRadians(int(two_list[2].strip())) - (math.pi / 2)
                    phi1 = posToRadians(int(three_list[2].strip())) - (math.pi / 2)

                    # Triangulate to find the point using a and b. 
                    # REQUIRES theta and phi are in radians!
                    
                    x_0 = math.sin (theta0) * delta_x0
                    x_1 = math.sin (theta0) * delta_x1

                    y_0 = math.cos (theta0) * delta_x0
                    y_1 = math.cos (theta0) * delta_x1

                    x_2 = math.sin (phi0) * delta_y0
                    x_3 = math.sin (phi0) * delta_y1

                    y_2 = math.cos (phi0) * delta_y0
                    y_3 = math.cos (phi0) * delta_y1


                    # (x_a0, x_b0) = (, math.cos (angle - math.pi/2) * distance + (height/2))
                    # (x_a1, x_b1) = triangulateX(theta1, delta_x1, width)

                    # (y_a0, y_b0) = triangulateY(phi0, delta_y0, height)
                    # (y_a1, y_b1) = triangulateY(phi1, delta_y1, height)

                    #print ("Coords")
                    #print (x_0,x_1, y_0, y_1)
                    #print (x_2,x_3, y_2, y_3)

                    # Take the average of the legs of the triangle
                    y_coord = abs(min(x_2, x_3))*20 #abs((x_a0 + x_a1)//2) * 20
                    #x_a0, x_a1, 
                    x_coord = abs(min(y_2, y_3))*20 #abs((x_b0 + x_b1)//2) * 20
                    #, y_b0, y_b1
                    print (x_coord, y_coord)

                    # Here we draw the new line using the old 
                    # and the new coordinates we are given
                    #canvas.create_line(x_previous, y_previous, x_coord, y_coord) # , fill="#ff0000"
                    canvas.create_oval(
                        x_coord - 20, y_coord - 20,
                        x_coord + 20, y_coord + 20,
                        fill="#0000ff", outline = ""
                        )

                    #canvas.create_line(x_previous, y_previous, x_coord, y_coord)
                    x_previous = x_coord
                    y_previous = y_coord
                    canvas.update()

    
# Placeholder make function to make the interface
# Might have to put this in a new file?

def make():
    window = tk.Tk()

    startButton = tk.Button(window, text="Start Digital Canvas")

    # This may be very stupid, but it is what it is.
    # This function will remove the button on the homescreen and
    # Call the readAndWrite function.
    def removeButton(binst):
        binst.destroy()
        readAndWrite(canvas)

    startButton['command'] = lambda binst=startButton: removeButton(binst)
    startButton.grid(column=1, row=1)

    window.title("Digital Canvas Interface")
    window.geometry('1200x750')
    canvas = tk.Canvas(window, width="1200", height="750")
    window.mainloop()


# Call the main function
# Placeholder make function
make()