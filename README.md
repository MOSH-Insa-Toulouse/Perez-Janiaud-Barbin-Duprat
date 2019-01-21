 __   __         _______  _______  __   __ 
|  |_|  |       |       ||       ||  | |  |
|       | ____  |   _   ||  _____||  |_|  |
|       ||____| |  | |  || |_____ |       |
|       |       |  |_|  ||_____  ||       |
| ||_|| |       |       | _____| ||   _   |
|_|   |_|       |_______||_______||__| |__|


/* Presentation of The RC Boat project */

Please make sure that you have all the following file :
	- Arduino Code (.ino)
	- MIT app inventor .apk file
	- 3D plan of the Boat with the .stl extension (made with Fusion360)
	- kicad file for the hardware part
	- Powerpoint presentation
	- Readme.md
	
	
/* Boat installation */

1. 3D printing of the different boat part :
	- Keep the proportion between all pieces (we printed the boat with a legnth or 27cm, the maximum possible with our 3D printer)
	- add a hole in the shell, for the motor axe

2. Motor/propeller axis
	- Our best solution was to buy a long metal tube. long enough for the motor to be over the flotation level.
	- The motor axis goes throught the tube. This way the water does not go into the boat
	
3. Rudder control
	- We extended the servomotor axis and added another metal axis to transmit the movement. (see slides)

4. Hardware
	- Follow the Kicad diagramms to place the different part
	- For a better result the PCB shield can be printed
	- Some amelioration can be made :
		- using a more powerfull motor (Brushless for waterproofing and power, ...) 
		- Changing the transistor to a MOSFET to handle higher current
		- Using a tension divider bridge to reduce the tension from 5v to 3.3V on the TX/RX pin of the HC05 BT module
	
	
/* Software */
The software is divided into two part:
	- The android application to communicate with the arduino uno and send control for the speed and position
	- The arduino software to recieve the instruction and control the hardware
Both should be used in parralel
	

/* Credits */
Property of Perez Sarah, Barbin Laure, Janiaud Corentin (with the mental support of Duprat Leo -- Computer Starter and Door Holder --)

 __________________________________
|                                  |
Don't compare your progress
to that of someone else
Everyone works at different speeds
You're doing great and I love you
|__________________________________|
(\__/) ||
(•?•) ||
/   ?