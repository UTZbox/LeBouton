# LeBouton (v1.1)
The LeBouton, is a single Button Cue-Controller, with multiple options for controlling software like:
QLAB®, GO-Button®, Ableton© Live®, Microsoft PowerPoint, Apple Keynote, PDF Readers or Apple PhotoBoth.
Simple to use and no needs of drivers or software setup.

![LeBoutonTopViewSmall](https://github.com/user-attachments/assets/c380fbdd-f181-4a9e-9e22-fe326e6d1962)


Based on a TeensyLC or Teensy 4.0
The unit has an USB-Port and a standard MIDI port.
On USB the device work as HID keyboard, which sends selectable types of keystrokes especially dedicated for the softwares listed above. Choose between one of follow keystrokes:
SPACE, ENTER, Arrow Up, Arrow Down, Arrow Left, Arrow Right, Page Up, Page Down, a, 1, TAB, F5
Media Key Start, ALT+CMD+P, CMD +SHIFT +ENTER.

On the same time it works as USB-MIDI interface and send selectable events like Midi-Notes, 
 Midi-Programm Change or Midi-Show-Control. 
Also it sends out the MIDI Events to the standard MIDI Port. (Controlling a backup machine).
You can also choose between two Midi Channels (1 or 2).

For the knob on top, :-) you can use big, illuminated , tactile momentary Button.
At the Back there is a 6.3mm Jack, to connect an External Switch, which is parallel to the GO.
With the DIP-Switches, you can set the different Modes for Keyboard and MIDI.
Two LEDs shows the Power/Run and Transmitting State. (Power/Run LED at the GO Button)
The Unit is powered by the USB Port and can run without a PC, as bare MIDI Controller.
(At the folder ExampleDevice you find my Hardware Version I did.)

The Schematics and code is very well tested and many times used in theaters or as custom solution for different artists.
I share all this experience and work, because I just will be happy, if I can support other artists or creative people with this.
