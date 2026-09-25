# virtual-hourglass

A virtual hourglass built on an OLED QVGA 2.2 TFT SPI 240x320 and an Arduino Uno.

# wiring

(I used 2k transistors instead of 1K8 and 51 ohm resistor instead of 56)

UNO +5V to display pin 1 (VCC)
UNO +5V through a 56 Ohm resistor to display pin 8 (LED)
UNO 0V (GND) to display pin 2 (GND)
UNO digital pin 7 through a 1K2 resistor to display pin 4 (RESET), add a 1K8 resistor from display pin 4 to GND
UNO digital pin 8 through a 1K2 resistor to display pin 5 (DC/RS), add a 1K8 resistor from display pin 5 to GND
UNO digital pin 9 through a 1K2 resistor to display pin 3 (CS), add a 1K8 resistor from display pin 3 to GND
UNO digital pin 11 through a 1K2 resistor to display pin 6 (SDI/MOSI), add a 1K8 resistor from display pin 6 to GND
UNO digital pin 13 through a 1K2 resistor to display pin 7 (SCK), add a 1K8 resistor from display pin 7 to GND
