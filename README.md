*This project has been created as part of the 42 curriculum by [aginiaux](https://github.com/One-GoodKnight).*

# Description

This project consists of creating a system to make multiple coders share a quantum compiler  
on different thread without corrupting the data of the system.  
  
There is as usb dongle between each coder and a coder needs 2 to compile it's program  
on the quantum compiler.  
After compiling, the coder puts back the dongles and starts debugging and refactoring.  
Other coders can pickup the dongles after Xms (set by a parameter to send to the program).  
  
The program either results in the burnout of a coder because of lack of compiling,  
or every coder compiled to code enough times for the simulation to end.  

The goal is to create a system robust enough to run simulations without deadlocks, dataraces  
and that is able to print coherent messages give the parameters given.  
