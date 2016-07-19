The projet aims to tune and test the motor drivers used for 3d printers
We should be able at some point to integrate the results of this tests into future 3d printer fimrwares,
in order to fine adjust the head movement on the fly, based on what is printing.

So we're trying to auto-calibrate the printing process and motors speed related to a printed model and it's
characteristics at print time

For example you wold like to print at maximum speed when printing straight lines and the same time you would like to reduce the speed when printing curves and corners. The overall result will be an improved printing speed without lowering the print quality

-------------------------------------------------------------------------------------------------------

At the moment the project consists of 3 parts
- Serial_Updater - a project developed with VC2015, which is a communication interface between an ARM processor and a GUI application
- PC-Controller  - the GUI application which allows one to control and manually test a 3d printer motor driver 
- GUI-interface-STM32F407VG-discovery - a firmware for a discovery board STM32F407, which reads the commands from
  the PC-Controller and adjusts a PWM port along with the other connections to the motor driver
  the board also has a LCD module (3.2", with touchscreen) attached and initializes a serial terminal for debugging purpose



