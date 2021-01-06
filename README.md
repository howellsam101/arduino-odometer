# arduino-odometer
This code was designed for the use in a tractor on fencing jobs. 
This tracks distance traveled by tractor. An alarm can be set to sound 
at a specific distance if set, it then clears the distance traveled, but 
keeping the alarm distance the same. the use of this is for ramming in 
fence posts, and easily measuring the distance driving tractor to next
position. each time the distance reaches limit and resets it counts 1 
section. this can be used to caculate how much posts were rammed in. 
All this is printed to a ic2 lcd screen and is controlled by two buttons.
two make this code work you will need to add a calculation to find the distance
using a reed switch and magnet mounted to wheel or drive shaft ect...
Of course this code can be modifed for other applications such as for a 
bike etc... I would also recomed using ardunios EEPROM to store values
after ardunio is switch off/disconnected from power.

This code if far from refined so if you have any suggestions please comment them. 
