# kaylas_arduino_gift
Just a fun project. A 'smart picture frame' built on Arduino for my girlfriend Kayla. I made this in 2016.

# Documentation
Uses some pretty simple logic.

##Required devices: 
7-segment, 4 digit LED screen
thermometor sensor (3 pin)
LEDS

###Printing Method:
bool drawString(const char word[], int frames)
... where word is a char array of size 4,
frames is the number off frames to be displayed. In this case, I chose a constant WORDTIME of 60 for the typical case.

###Main method
loop()
Loops the jingles as well as displays the degrees

###Draw Integer
drawInt()
writes a digit (integer) to the screen

###Write Digit
writeDig()
writes a specific digit [[0-9999]]

###Write Character
whiteChar()
writes a specific character [[aA-zZ]]

###Animation
animation()
a little cleaning/start animation to play :)

###Swirl
swirl()
swirl effect

greetings()
greetings upon launch
