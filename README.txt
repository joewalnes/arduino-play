Edit common/devices.mk to set Arduino specific settings

==== Building ====

From the specific project sub directory:

  make compile : Compile app into AVR .hex file (Default make rule)
  make upload  : Upload .hex to Arduino
  make serial  : Connect to device serial port
  make clean   : Delete compile output

