# XO Game using Tiva C TM4C123G
This project implements an XO game (also known as Tic-Tac-Toe) on the Tiva C TM4C123G microcontroller.
The game is played on a 3x3 grid matrix using a switches for input and a Nokia screen or UART terminal for output.
# Hardware Requirements
- Tiva C TM4C123G microcontroller
- Nokia5110 Screen (Blue)
- 5 switches
- 3 LEDs
-  Male-Female Jumbers (connectors)
- 470 ohm, 10k Resistors
- Breadboard
- UART terminal (such as PuTTY or TeraTerm)
##### Nokia 5110 Connections

| Signal       | (Nokia 5110) LaunchPad pin                                   |
| ------------ | ------------------------------------------------------------ |
| 3.3V         | (Vcc, pin 1) power                                           |
| Ground       | (Gnd, pin 8) ground                                          |
| SSI0Fss      | (CE,  pin 3) connected to PA3                                |
| Reset        | (RST, pin 4) connected to PA7                                |
| Data/Command | (DC,  pin 5) connected to PA6                                |
| SSI0Tx       | (Din, pin 6) connected to PA5                                |
| SSI0Clk      | (Clk, pin 7) connected to PA2                                |
| back light   | (BL,  pin 8) not connected, consists of 4 white LEDs which draw ~80mA total |
# Software Requirements
- Micro vision Keil
# Installation
1. Clone or download this repository to your computer.
2. Open the project in Keil.
3. Include the TivaWare C Series SDK in the project build path.
4. Build and flash the project to the Tiva C TM4C123G microcontroller.
# Usage
1. Connect the switches,LEDs and Nokia screen to the appropriate GPIO pins on the Tiva C TM4C123G microcontroller.
2. Connect the UART terminal to the appropriate UART pins on the Tiva C TM4C123G microcontroller.
3. Power on the Tiva C TM4C123G microcontroller.
4. Launch the UART terminal and configure it to the desired baud rate (115200 by default).
5. Play the game by following the prompts on the UART terminal or Nokia Screen and using the swiches for input.
# Game Rules
The XO game is played on a 3x3 grid matrix. Two players take turns placing their symbol (X or O) on the matrix.
The player who succeeds in placing three of their symbols in a horizontal, vertical, or diagonal row wins the game.
If all nine squares on the matrix are filled and no player has achieved a row of three symbols, the game is a draw.
# Project done Under Supervision of
- Dr.Ahmed Fares
- Eng.Mahmoud Nawar
- Eng.Mohamed Abdelmegid
# Credits
This project was developed by
- Mohamed Hesham
- Mohamed Abdallatif
- Mohamed Mamdouh
- Mostafa Mohamed
- Michael Mettry
as a final project for the Lab 3 course at Shoubra Faculty of Engineering.
The project is based on the TivaWare C Series SDK examples and uses external libraries for GPIO and UART communication.


