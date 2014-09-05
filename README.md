# Big Green Egg Temperature controller
## by Brian Granaghan

FreeRTOS port based on https://github.com/jameswalmsley/RaspberryPi-FreeRTOS

Note: I'm currently working on the board for this project and learning to design boards in the first place, so source updates will be more sparse until I get boards in and built.

####Some notes on C++ support:
* Since we have no runtime, exceptions and RTTI are disabled.
* Static object initialization works, but happens in a critical section. Initializations should be fast.
* Static objects are always marked as successfully created
* Pure virtual functions are not yet supported, but adding support shouldn't be a problem.
* new and delete are not defined and likely will not be.
* Placement new appears to work, just remember to #include <new>
* I've added a section to the link script for global constructors, but haven't implemented the code to call them yet.

###Build requirements:
* Python must be in the system path.
* Mako templates python extension must be installed.
* arm-none-eabi-gcc toolchain must be in the system path.

###Source Overview
* Register access functions are generated from *.rm files in source/regmaps/. They are parsed using PLY (Python Lex/Yacc) and generated using mako templates.
* Drivers in source/Drivers/ correpsond to on-chip peripherals and abstract the register maps. You should never need to write a register directly; all functiontality should be exposed through the drivers.
* External peripherals such as the LCD and thermocouple interface are expsoed through classes in source/Peripherals/. These classes are written around the drivers provided in source/Drivers/.
* Application tasks are contained in tasks.cpp and all hardware access comes through chip drivers or peripheral libraries.
