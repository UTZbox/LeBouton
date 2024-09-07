/* LeBouton (One Knob CUE Controller with flexible Settings)
   Created by Mike Utz
  
   Contains 1 push button for sending Keystrokes and MIDI over USB plus MIDI messages,
   Mode Switches for setting different Keystroke and Midi functions
   Two Outputs shows if the Deice is started up (Ready) and one while Midi Commands will be sent (Transmit)

   The Cue Input is connected to input pin 2.
   The Keyboard Mode Switches are connected to Pin 6 -9
   The Midi Mode switch is connected to input pin 14 + 15
   The USB-MIDI ON/OFF switch is connected to input pin 20
   The USB Channel Switch is connected to imput pin 21
   The Outputs are connected to Pin 16 for RUN and 17 for Transmit LED.
   The Midi Interface is connected to the pins 0 and 1
   
   You must select Board: Teensy-LC and USB-Type: Keyboard+MIDI+Serial from the "Tools menu.
   If this option is not available, replace the adapted files "board.txt" and "usb_desc.h" within Teensduino
  
   History:
   Version 1.0 / LeBouton based in LetsGO 1.3)
   Version 1.1 / Add 4th DIP Switch for more Keyboard Options.
*/

#include <Bounce2.h>
#include <MIDI.h>

// Created and binds the MIDI interface to the default hardware Serial port
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// Attach the Input Button to the Bounce Library
Bounce2::Button LeBouton = Bounce2::Button();

//button debounce time
const int DEBOUNCE_TIME = 5;

// Define the Input Pin2 as LeBouton
byte leBoutonPin = 2;

// Timer for delay a next Cue, if one has sent.
elapsedMillis sinceLastCue;

//Variable that stores the current MIDI or keyboard mode of the device (what type of messages the push buttons send).
int midiMode = 0;
int keyMode = 0;
// Variable to Store the State of USB MIDI Send ON/OFF
int usbMidiState = 0;
//Variable to Store the chosen MIDI Channel
int MIDI_CHAN = 1;

//Variable which store the exact MIDI messages each push button will send.
const int MIDI_NOTE_NUM = 60;
const int MIDI_NOTE_VEL = 110;
const int MIDI_PRG_NUM = 0;

const int MIDI_MSC_LENGHT = 7;
const int HW_MIDI_MSC_LENGHT = 6;
byte MIDI_MSC_COMMAND[] = {0xf0, 0x7f, 0x7f, 0x02, 0x7f, 0x01, 0xf7};
byte MIDI_MSC_VALUE = 0x01;


//Arrays that stores the Keystrokes
const int KEY_STROKE[13] = {KEY_SPACE, KEY_ENTER, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_A, KEY_1, KEY_TAB, KEY_F5, KEY_MEDIA_PLAY};  

//==============================================================================
//The setup function. Called once when the Teensy is turned on or restarted

void setup() {

  //Configure Mode Inputs
    pinMode (6, INPUT_PULLUP);
    pinMode (7, INPUT_PULLUP);
    pinMode (8, INPUT_PULLUP);
    pinMode (9, INPUT_PULLUP);
    pinMode (14, INPUT_PULLUP);
    pinMode (15, INPUT_PULLUP);
    pinMode (20, INPUT_PULLUP);
    pinMode (21, INPUT_PULLUP);

  // Configure Output pins for Ready and Transmit LED
  pinMode (16, OUTPUT);
  pinMode (17, OUTPUT);

  // Setup and Assign the Go Button to the Bounce Library
    LeBouton.attach(leBoutonPin, INPUT );
    LeBouton.interval(DEBOUNCE_TIME);

  // Start the Hardware MIDI Output
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  // Set Ready Output (LED)
  digitalWrite(16, HIGH);
}


//==============================================================================

void loop()
{
  // Update the Go Button. 
  LeBouton.update();

  //==============================================================================
  // Check  button for "rising" edge and if the timer is reached its value.
    
    if (LeBouton.rose() and sinceLastCue >=50 ) {
      //Send Keystroke on related Mode.
      if (keyMode == 1) {
        Keyboard.press (KEY_STROKE[0]);
      }

      if (keyMode == 2) {
        Keyboard.press (KEY_STROKE[1]);
      }

      if (keyMode == 3) {
        Keyboard.press (KEY_STROKE[2]);
      }

      if (keyMode == 4) {
        Keyboard.press (KEY_STROKE[3]);
      }
      
      if (keyMode == 5) {
        Keyboard.press (KEY_STROKE[4]);
      }
      
      if (keyMode == 6) {
        Keyboard.press (KEY_STROKE[5]);
      }
      
      if (keyMode == 7) {
        Keyboard.press (KEY_STROKE[6]);
      }
      
      if (keyMode == 8) {
        Keyboard.press (KEY_STROKE[7]);
      }
      
      if (keyMode == 9) {
        Keyboard.press (KEY_STROKE[8]);
      }
      
      if (keyMode == 10) {
        Keyboard.press (KEY_STROKE[9]);
      }
      
      if (keyMode == 11) {
        Keyboard.press (KEY_STROKE[10]);
      }
      
      if (keyMode == 12) {
        Keyboard.press (KEY_STROKE[11]);
      }
      
      if (keyMode == 13) {
        Keyboard.press (KEY_STROKE[12]);
      }
      
      if (keyMode == 14) {
        Keyboard.press(MODIFIERKEY_ALT);
        delay(5);
        Keyboard.press(MODIFIERKEY_GUI);
        delay(5);    
        Keyboard.press (KEY_P);
      }
      
      if (keyMode == 15) {
        Keyboard.press(MODIFIERKEY_GUI);
        delay(5);
        Keyboard.press(MODIFIERKEY_SHIFT);
        delay(5);
        Keyboard.press (KEY_ENTER);
      }
            
      // Send Midi Message on related Mode.
      if (midiMode == 1) {
        MIDI.sendNoteOn (MIDI_NOTE_NUM, MIDI_NOTE_VEL, MIDI_CHAN);
        if (usbMidiState == 1){
          usbMIDI.sendNoteOn (MIDI_NOTE_NUM, MIDI_NOTE_VEL, MIDI_CHAN);
        }
      }
      
      if (midiMode == 2) {
        MIDI_MSC_COMMAND[5] = MIDI_MSC_VALUE;
        MIDI.sendSysEx (HW_MIDI_MSC_LENGHT, MIDI_MSC_COMMAND, true);
        if (usbMidiState == 1){
          usbMIDI.sendSysEx (MIDI_MSC_LENGHT, MIDI_MSC_COMMAND, true);
        }
      }

      if (midiMode == 3) {
        MIDI.sendProgramChange (MIDI_PRG_NUM, MIDI_CHAN);
        if (usbMidiState == 1){
          usbMIDI.sendProgramChange (MIDI_PRG_NUM, MIDI_CHAN);
        }
      }
      
      // Turn the Transmit Output (LED) on
      digitalWrite(17, HIGH);
      
      // Reset Timer
      sinceLastCue = 0;
    }

    //========================================
    // Check each button for "falling" edge
    
    else if (LeBouton.fell() and sinceLastCue >=25 ) {
      //Send Keystroke or Midi Message on related Mode.
     
      if (midiMode == 1) { 
        MIDI.sendNoteOff (MIDI_NOTE_NUM, 0, MIDI_CHAN);
        if (usbMidiState == 1){
          usbMIDI.sendNoteOff (MIDI_NOTE_NUM, 0, MIDI_CHAN);
        }
      }
      
      if (keyMode == 1) {
        Keyboard.release (KEY_STROKE[0]);
      }

      if (keyMode == 2) {
        Keyboard.release (KEY_STROKE[1]);
      }

      if (keyMode == 3) {
        Keyboard.release (KEY_STROKE[2]);
      }

      if (keyMode == 4) {
        Keyboard.release (KEY_STROKE[3]);
      }

      if (keyMode == 5) {
        Keyboard.release (KEY_STROKE[4]);
      }

      if (keyMode == 6) {
        Keyboard.release (KEY_STROKE[5]);
      }

      if (keyMode == 7) {
        Keyboard.release (KEY_STROKE[6]);
      }

      if (keyMode == 8) {
        Keyboard.release (KEY_STROKE[7]);
      }

      if (keyMode == 9) {
        Keyboard.release (KEY_STROKE[8]);
      }

      if (keyMode == 10) {
        Keyboard.release (KEY_STROKE[9]);
      }

      if (keyMode == 11) {
        Keyboard.release (KEY_STROKE[10]);
      }

      if (keyMode == 12) {
        Keyboard.release (KEY_STROKE[11]);
      }

       if (keyMode == 13) {
        Keyboard.release (KEY_STROKE[12]);
      }

      if (keyMode == 14) {
        Keyboard.release (KEY_P);
        Keyboard.release(MODIFIERKEY_GUI);
        Keyboard.release(MODIFIERKEY_ALT);
        }

      if (keyMode == 15) {
        Keyboard.release (KEY_ENTER);
        Keyboard.release(MODIFIERKEY_SHIFT);
        Keyboard.release(MODIFIERKEY_GUI);
        }
      
      // Turn the Transmit Output (LED) off
      digitalWrite(17, LOW);
      
      // Reset Timer
      sinceLastCue = 0;
    }

  //==============================================================================
  // Check the status of the Mode Switches and set the desired Device Mode.

  // Mode Switch for Keboard (BCD Logic)
  if (digitalRead(6) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) == LOW) {
    keyMode = 15;
  }
  else if (digitalRead(7) == LOW && digitalRead(8) == LOW&& digitalRead(9) == LOW) {
    keyMode = 14;
  }
  else if (digitalRead(6) == LOW && digitalRead(8) == LOW&& digitalRead(9) == LOW) {
    keyMode = 13;
  }
  else if (digitalRead(8) == LOW && digitalRead(9) == LOW) {
    keyMode = 12;
  }
  else if (digitalRead(6) == LOW && digitalRead(7) == LOW&& digitalRead(9) == LOW) {
    keyMode = 11;
  }
  else if (digitalRead(7) == LOW && digitalRead(9) == LOW) {
    keyMode = 10;
  }
  else if (digitalRead(6) == LOW && digitalRead(9) == LOW) {
    keyMode = 9;
  }
  else if (digitalRead(9) == LOW) {
    keyMode = 8;
  }
  else if (digitalRead(6) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW) {
    keyMode = 7;
  }
  else if (digitalRead(7) == LOW && digitalRead(8) == LOW) {
    keyMode = 6;
  }  
  else if (digitalRead(6) == LOW && digitalRead(8) == LOW) {
    keyMode = 5;
  }
  else if (digitalRead(8) == LOW) {
    keyMode = 4;
  }
  else if (digitalRead(6) == LOW && digitalRead(7) == LOW) {
    keyMode = 3;
  }      
  else if (digitalRead(7) == LOW) {
    keyMode = 2;
  }
  else if (digitalRead(6) == LOW) {
    keyMode =1;
  }
  else {
    keyMode = 0; // No Keyboard Action
  }

  // Mode Switch for MIDI (BCD Logic)
  if (digitalRead(14) == LOW && digitalRead(15) == LOW) {
    midiMode = 3;
  }
  else if (digitalRead(15) == LOW) {
    midiMode = 2;
  }
  else if (digitalRead(14) == LOW) {
    midiMode = 1;
  }
  else {
    midiMode = 0; // No Midi Action
  }
  
  // Mode Switch for USB-MIDI ON/OFF
  if (digitalRead(20) == LOW) {
    usbMidiState = 1;
  }
  else {
    usbMidiState = 0;
  }

  // Channel Switch for MIDI Channel
  if (digitalRead(21) == LOW) {
    MIDI_CHAN = 2;
  }
  else {
    MIDI_CHAN = 1;
  }
  //==============================================================================
  // MIDI Controllers should discard incoming MIDI messages to prevent buffer overflow
  while (MIDI.read()) {
    // read & ignore incoming messages
  }
  while (usbMIDI.read()) {
    // read & ignore incoming messages
  }
  //==============================================================================

}
