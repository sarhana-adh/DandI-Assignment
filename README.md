# Our_project  
This project provides source code that can be uploaded to M5 Stack atom matrix. The project is divided into 3 sub-projects: Brakelight, Temperature and Spinner-Dice game. 

![90678172-1f84-48b4-bfbc-395a59e8a656](https://user-images.githubusercontent.com/72303952/121396444-6f879080-c964-11eb-850e-3ac86e6a3e5a.jpeg)

### Brakelight - 

On uploading the source code on the M5 atom matrix, The M5 atom matrix can be imagined as a brake light that switches through 4 mode when button is pressed. 
1. OFF: Initially all leds are turned off.
2. Manual Rear strobe : On button pressed, Red LEDs strobe at a predetermined interval
3. Manual Front strobe :On button pressed for the second time, White LEDs strobe at a predetermined interval
4. Automatic Rear Mode Rear: On button pressed for the third time, LEDs are solid and red during a braking event. Return to strobe when riding.
5. Automatic Front Mode Rear: On button pressed for the fourth time, LEDs are solid and white during a braking event. Return to strobe when riding. 

On button pressed, the M5 atom cycles back to number 1 and runs through the cycle again.

### Temperature - 

On uploading the source code on the M5 atom matrix, The M5 atom matrix can be imagined as a device that is carried by a person whole day. When holding the device in the hand with the screen facing relatively upwards, and pressing the button, the m5 atom is activated/ turned on. The modes on which the atom device is can be changed by tilting it right or left (right to increase the mode number, left to go back to the decrese the mode number.) The mode number is displayed in the device and the button can be pressed inorder to switch into the mode. 

Modes (with respective mode number):
1. Show Active temperature + Units
2. Show average of last 24 hours of temperature + Units
3. Show color scale of temperature range + current temperature as color
4. Show graph of temperature across a predefined range.
5. Changes units 
 
### Spinner and Dice Game - 

On uploading the code to an M5 Stack atom matrix and supllying the Atom Matrix with power, the matrix creates a wifi access point. The wifi named "Group-10" can be connect using any device that can be connected to a wifi server. The password for this server is: 
##### 12345678 
On connecting the device to this wifi server, open http://192.168.4.1/ on a browser in this device. THe webpage displays dice number as shown below and works simulataneously with the atom (same number is displayed on the atom). 


<img width="383" alt="Screen Shot 2021-06-08 at 12 21 45" src="https://user-images.githubusercontent.com/72303952/121395074-12d7a600-c963-11eb-9b22-980c8e03901b.png">

#### (fig. The webpage displaying number 3 [the number displayed depends on the angle made by the rotation ])

 
The atom could be spinned with the atom facing side-ways and the axis of its rotation horizontal. The spin changes the number displayed on the webpage as well as the atom. This is on the dice mode. 

To change the mode, click on spinner button displayed on the webpage. 
This displays a matrix resembling the atom on the webpage, and the all the leds lights up with a color at a time. WIth rotation/spin, the atom and the matrix in the webpge cycles through 6 different colors: red, orange, yellow, green, blue and purple. 

<img width="390" alt="Screen Shot 2021-06-08 at 12 22 31" src="https://user-images.githubusercontent.com/72303952/121395872-e40dff80-c963-11eb-93ef-b11ded4ce0d1.png">

#### (fig. The webpage displaying yellow matrix [the color displayed depends on the angle made by the rotation ])

The spinner and dice button can be clicked on to change to mode as accord to user's wish. 

## Installation 

Open terminal on MacOS or Command Prompt on Windows. Type in:
```
 git clone https://github.com/sarhana-adh/our_project
```

Search for our_project folder in your computer. Open the folder. To install the 3 different programs:

### Brakelight
1. Open the Brakelight folder.
2. Open the first_arduino.ino file in Arduino. 
3. On Arduino application being opened, go to tools make sure the board is "M5 Stack Atom" and the M5 Stack Atom is connected to the device. 
4. Upload the first_arduino.ino by pressing on the upload button (upward-facing arrow).

### Temperature 
1. Open the M5Atom_Part_1_Temperature folder.
2. Open the M5Atom_Part_1_Temperature.ino file in Arduino. 
3. On Arduino application being opened, go to tools make sure the board is "M5 Stack Atom" and the M5 Stack Atom is connected to the device. 
4. Upload the M5Atom_Part_1_Temperature.ino by pressing on the upload button (upward-facing arrow).


### Spinner and Dice Game 
1. Open the SpinnerAndDice folder.
2. Open the SpinnerAndDice.ino file in Arduino. 
3. On Arduino application being opened, go to tools make sure the board is "M5 Stack Atom" and the M5 Stack Atom is connected to the device. 
4. Upload the SpinnerAndDice.ino by pressing on the upload button (upward-facing arrow).

##### Recommended: Spinner housing and PCB that can spin the M5 atom and supply it with power. 

### Supply the M5 Stack Atom Matrix with power inorder to run the program.
