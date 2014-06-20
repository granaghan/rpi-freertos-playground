# FreeRTOS Ported to Raspberry Pi

based on https://github.com/jameswalmsley/RaspberryPi-FreeRTOS

Provides some extended functionality to James Walmsley's port.

This is my playground repo, so I make no promises about what's in it. :)

Please check my rpi-freetos repo instead.

Some notes on C++ support:
Since we have no runtime, exceptions and RTTI are disabled.
Static object initialization works, but happens in a critical section. So initializations should be fast.
Static objects are always marked as successfully created
Pure virtual functions are not yet supported, but adding support shouldn't be a problem.
new and delete are not defined and likely will not be.
Placement new appears to work, just remember to #include <new>
Global objects will compile, but their constructors won't get called so you'll need to call placement new. It's easier than me implementing that feature.
