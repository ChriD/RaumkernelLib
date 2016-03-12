# Raumkernel

A C/C++ Library which can be used to control the Raumfeld Multiroom System
There will be makefiles for Windows x86 / Linux x86 / linux ARMV6 / linux ARMV7

# State
In initial development. 

# Known Bugs:
Currently there is something like a bug on updateing the zone list and the states of the room it contains. 
But this is due the fact that the RF-System does not remove renderers very fast when they are shut off in the "hard way" 
This is a very tricky situation. I have to think it over how to handle such situation

