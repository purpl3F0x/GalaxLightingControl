
# GalaxLightingControl
A simple c++ program that overrides GALAX/KFA2 Lighting service.


Currently I'm using prefixed memory addresses for the 3 values. I found on my system they are the same every time the program starts. But this may be os installation, GPU model dependant or something else. 
Luckily is very easy to find the 3 addresses that hold the RGB value of the card. *(Not actually on the card but on a refresh color service the Utulity uses and -re applies the color to the card, around 5 times per second I think)*

You can use Cheat Engine for this.

 1. Open Cheat Engine and load the XT+ Program.
 ![Open Cheat Engine and load the XT+ Program.](https://i.imgur.com/HUspNhG.png)





 2. Set the value of one of the Colors to some value you like. And then Scan the programm for that value.![enter image description here](https://i.imgur.com/iqRCzsr.png)
 
 
 

3. Then you will notice that when you change the slider one of those values changes accordingly. That value is not in our interest since it is used for the gui only. *But* if you hit apply you will notice a second memory cell changing it's value to the new value you have set. That's the memory address you want to modify

*Assuming you found the one value you have 2 more to go*😝
... or you can just add +4bytes for our dear u_int values 🤪 
... it first goes the blue then the green and so...RGB turns into BGR
