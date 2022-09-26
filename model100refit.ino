
// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for Schroedinger's cat (might need to be first)
#include "Kaleidoscope-Qukeys.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for keys that move the mouse
//#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
//#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
//#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
//#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
//#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Redial key
#include "Kaleidoscope-Redial.h"

#include "Kaleidoscope-Leader.h"

// Oneshot stuff
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

// TapDancing umlauts
#include "Kaleidoscope-TapDance.h"

// Dependencies for a whole heap of shit
#include "Kaleidoscope-Ranges.h"

// Support for OneShot modifiers (probably not needed)
// #include "Kaleidoscope-OneShot.h"
// #include "Kaleidoscope/hid.h"
// #include "Kaleidoscope-Escape-OneShot.h"

// Support for an "LED off mode"
// #include "LED-Off.h"









/** This 'enum' is a list of all the macros used by the Model 01's firmware
    The names aren't particularly important. What is important is that each
    is unique.

    These are the names of your macros. They'll be used in two places.
    The first is in your keymap definitions. There, you'll use the syntax
    `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`

    The second usage is in the 'switch' statement in the `macroAction` function.
    That switch statement actually runs the code associated with a macro when
    a macro key is pressed.
*/

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_COMMA,
       MACRO_EXCLAIM,
       MACRO_QUESTION,
       MACRO_SWAP,
       MACRO_PARAGRAPH,
       MACRO_ENTAB,
       MACRO_TOGGLE_QUKEYS
     };

/* Redial info

*/

// enum {                                                             (removed?)
//   REDIAL = kaleidoscope::ranges::SAFE_START,
// };
// #define Key_Redial (Key) {.raw = REDIAL}


bool kaleidoscope::plugin::Redial::shouldRemember(Key mapped_key) {
  if (mapped_key >= Key_A && mapped_key <= Key_Z)
    return true;
  return false;
}

/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
    keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
    keymap.

    Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
    of first the left hand's layout, followed by the right hand's layout.

    Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
    defined as part of the USB HID Keyboard specification. You can find the names
    (if not yet the explanations) for all the standard `Key_` defintions offered by
    Kaleidoscope in these files:
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h

    Additional things that should be documented here include
      using ___ to let keypresses fall through to the previously active layer
      using XXX to mark a keyswitch as 'blocked' on this layer
      using ShiftToLayer() and LockLayer() keys to change the active keymap.
      the special nature of the PROG key
      keeping NUM and FN consistent and accessible on all layers


    The "keymaps" data structure is a list of the keymaps compiled into the firmware.
    The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
    macros switch to key layers based on this list.



    A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
    Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
*/

/**
    Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
    The third one is layer 2.
    This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
    the numbers 0, 1 and 2.

*/

enum { SIRDP, SHIFT, NUMPAD, FUNCTION, QWERTY }; // layers

/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

// const Key keymaps[][ROWS][COLS] PROGMEM = {

KEYMAPS(

  [SIRDP] = KEYMAP_STACKED
  (Key_Escape,       Key_1, Key_2, Key_3, Key_4, Key_5, Key_Escape,
   Key_Tab,          Key_X, Key_U, Key_F, Key_G, Key_B, Key_Enter, 
   LSHIFT(Key_9),    Key_R, Key_I, Key_S, Key_D, Key_P,
   LSHIFT(Key_0),    Key_Z, Key_Y, Key_V, Key_C, Key_W, M(MACRO_SWAP), 
   M(MACRO_EXCLAIM), M(MACRO_QUESTION), Key_Spacebar, Key_Backspace,
   ShiftToLayer(FUNCTION),

   Key_Escape,         Key_6,     Key_7, Key_8,     Key_9,      Key_0, Key_LeftBracket,
   LSHIFT(Key_Quote),  Key_Minus, Key_H, Key_O,     Key_Redial, Key_Q, Key_RightBracket,
                       Key_L,     Key_N, Key_E,     Key_A,      Key_T, LSHIFT(Key_Semicolon),
   LSHIFT(Key_Equals), Key_J,     Key_M, Key_Slash, Key_Quote,  Key_K, Key_Equals, 
   Key_Delete, M(MACRO_COMMA), LEAD(0), M(MACRO_PARAGRAPH),
   ShiftToLayer(NUMPAD)),

   [SHIFT] = KEYMAP_STACKED
  (Key_Escape,         LSHIFT(Key_Backslash), LSHIFT(Key_2), LSHIFT(Key_3), LSHIFT(Key_4), LSHIFT(Key_5), Key_Escape,
   LSHIFT(Key_Tab),    LSHIFT(Key_X),         LSHIFT(Key_U), LSHIFT(Key_F), LSHIFT(Key_G), LSHIFT(Key_B), Key_Enter,
   LSHIFT(Key_Comma),  LSHIFT(Key_R),         LSHIFT(Key_I), LSHIFT(Key_S), LSHIFT(Key_D), LSHIFT(Key_P),
   LSHIFT(Key_Period), LSHIFT(Key_Z),         LSHIFT(Key_Y), LSHIFT(Key_V), LSHIFT(Key_C), LSHIFT(Key_W), ___, 
   M(MACRO_EXCLAIM), M(MACRO_QUESTION), LSHIFT(Key_Spacebar), LCTRL(Key_Backspace),
   ShiftToLayer(FUNCTION),

   Key_Escape, LSHIFT(Key_6),     LSHIFT(Key_7), ___,           Key_Backslash, Key_Backtick,  LSHIFT(Key_LeftBracket),
   ___,        LSHIFT(Key_Minus), LSHIFT(Key_H), LSHIFT(Key_O), ___,           LSHIFT(Key_Q), LSHIFT(Key_RightBracket),
               LSHIFT(Key_L),     LSHIFT(Key_N), LSHIFT(Key_E), LSHIFT(Key_A), LSHIFT(Key_T), Key_Semicolon,  
   ___,        LSHIFT(Key_J),     LSHIFT(Key_M), LSHIFT(Key_8), ___,           LSHIFT(Key_K), LSHIFT(Key_Backtick), 
   LSHIFT(Key_Delete), M(MACRO_COMMA), ___, M(MACRO_PARAGRAPH),
   ShiftToLayer(NUMPAD)),

  [NUMPAD] =  KEYMAP_STACKED
  (___,                       Key_F1, Key_F2,                     Key_F3,       Key_F4,                 Key_F5,          Key_LEDEffectNext,
   ___,                       ___,    Consumer_ScanPreviousTrack, Key_PageUp,   Consumer_ScanNextTrack, Key_Insert,      ___,
   LCTRL(LSHIFT(Key_Comma)),  ___,    Key_Home,                   Key_PageDown, Key_End,                Key_PrintScreen,
   LCTRL(LSHIFT(Key_Period)), ___,    ___,                        ___,          ___,                    Key_Pause,       LockLayer(QWERTY),
   Key_RightControl, ___, LSHIFT(LCTRL(Key_Spacebar)), Key_Backspace, 
   ___,

   M(MACRO_VERSION_INFO),  ___,                Key_KeypadAdd, Key_KeypadSubtract, Key_KeypadEnter, ___,                ___,
   LockLayer(NUMPAD),      Key_KeypadSubtract, Key_Keypad7,   Key_Keypad8,        Key_Keypad9,     Key_KeypadMultiply, LSHIFT(Key_4),
                           Key_KeypadDot,      Key_Keypad4,   Key_Keypad5,        Key_Keypad6,     Key_KeypadDivide,   ___, 
   ___,                    Key_Keypad0,        Key_Keypad1,   Key_Keypad2,        Key_Keypad3,     Key_Equals,         Key_Quote,
   Key_Delete, Key_LeftGui, Key_Period, Key_LeftAlt,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,                Key_F1,        Key_F2,                   Key_F3,        Key_F4,                   Key_F5,          Key_LEDEffectNext,
   ___,                Consumer_Mute, Consumer_VolumeDecrement, Key_UpArrow,   Consumer_VolumeIncrement, ___,             ___,
   LSHIFT(Key_Comma),  ___,           Key_LeftArrow,            Key_DownArrow, Key_RightArrow,           Key_PrintScreen,
   LSHIFT(Key_Period), ___,           ___,                      ___,           ___,                      ___,             M(MACRO_TOGGLE_QUKEYS),
   LSHIFT(Key_1), LSHIFT(Key_Slash), LCTRL(LSHIFT(Key_Spacebar)), Key_Delete,
   ___,

   M(MACRO_ANY), Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
   LockLayer(NUMPAD), ___,    ___,    ___,    ___,    ___,     Key_F12,
                      ___,    ___,    ___,    ___,    ___,     Key_Semicolon,
   ___,               ___,    ___,    ___,    ___,    ___,     ___,
   LCTRL(Key_Delete), Key_Comma, Key_RightShift, M(MACRO_ENTAB),
   ___),

  [QWERTY] = KEYMAP_STACKED
  (Key_Escape,      Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Tab,         Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_LeftShift,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_LeftControl, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_LeftShift, Key_Spacebar, Key_LeftAlt, 
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),      Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(SIRDP),
   Key_Enter,         Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   LockLayer(QWERTY), Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_Delete, Key_LeftGui, Key_RightAlt, Key_RightShift,
   ShiftToLayer(NUMPAD)),
);

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

auto &serial_port = Kaleidoscope.serialPort();

// static void leaderTestA(uint8_t seq_index) {    new example
//   serial_port.println(F("leaderTestA"));
// }

// static void leaderFSA(uint8_t seq_index) {     old example
//   Macros.type(PSTR(". A"));  
// }




static void leaderFSA(uint8_t seq_index) {
  serial_port.println(F(". A"));  
}
static void leaderFSB(uint8_t seq_index) {
  serial_port.println(F(". B"));  
}
static void leaderFSC(uint8_t seq_index) {
  serial_port.println(F(". C"));  
}
static void leaderFSD(uint8_t seq_index) {
  serial_port.println(F(". D"));  
}
static void leaderFSE(uint8_t seq_index) {
  serial_port.println(F(". E"));  
}
static void leaderFSF(uint8_t seq_index) {
  serial_port.println(F(". F"));  
}
static void leaderFSG(uint8_t seq_index) {
  serial_port.println(F(". G"));  
}
static void leaderFSH(uint8_t seq_index) {
  serial_port.println(F(". H"));  
}
static void leaderFSI(uint8_t seq_index) {
  serial_port.println(F(". I"));  
}
static void leaderFSJ(uint8_t seq_index) {
  serial_port.println(F(". J"));  
}
static void leaderFSK(uint8_t seq_index) {
  serial_port.println(F(". K"));  
}
static void leaderFSL(uint8_t seq_index) {
  serial_port.println(F(". L"));  
}
static void leaderFSM(uint8_t seq_index) {
  serial_port.println(F(". M"));  
}
static void leaderFSN(uint8_t seq_index) {
  serial_port.println(F(". N"));  
}
static void leaderFSO(uint8_t seq_index) {
  serial_port.println(F(". O"));  
}
static void leaderFSP(uint8_t seq_index) {
  serial_port.println(F(". P"));  
}
static void leaderFSQ(uint8_t seq_index) {
  serial_port.println(F(". Q"));  
}
static void leaderFSR(uint8_t seq_index) {
  serial_port.println(F(". R"));  
}
static void leaderFSS(uint8_t seq_index) {
  serial_port.println(F(". S"));  
}
static void leaderFST(uint8_t seq_index) {
  serial_port.println(F(". T"));  
}
static void leaderFSU(uint8_t seq_index) {
  serial_port.println(F(". U"));  
}
static void leaderFSV(uint8_t seq_index) {
  serial_port.println(F(". V"));  
}
static void leaderFSW(uint8_t seq_index) {
  serial_port.println(F(". W"));  
}
static void leaderFSX(uint8_t seq_index) {
  serial_port.println(F(". X"));  
}
static void leaderFSY(uint8_t seq_index) {
  serial_port.println(F(". Y"));  
}
static void leaderFSZ(uint8_t seq_index) {
  serial_port.println(F(". Z"));  
}
static void leaderFS(uint8_t seq_index) {
  serial_port.println(F(". "));  
}

// static const kaleidoscope::Leader::dictionary_t leader_dictionary[] PROGMEM =        (old probably broken)
static const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
LEADER_DICT({LEADER_SEQ(LEAD(0), Key_A), leaderFSA},
            {LEADER_SEQ(LEAD(0), Key_B), leaderFSB},
            {LEADER_SEQ(LEAD(0), Key_C), leaderFSC},
            {LEADER_SEQ(LEAD(0), Key_D), leaderFSD},
            {LEADER_SEQ(LEAD(0), Key_E), leaderFSE},
            {LEADER_SEQ(LEAD(0), Key_F), leaderFSF},
            {LEADER_SEQ(LEAD(0), Key_G), leaderFSG},
            {LEADER_SEQ(LEAD(0), Key_H), leaderFSH},
            {LEADER_SEQ(LEAD(0), Key_I), leaderFSI},
            {LEADER_SEQ(LEAD(0), Key_J), leaderFSJ},
            {LEADER_SEQ(LEAD(0), Key_K), leaderFSK},
            {LEADER_SEQ(LEAD(0), Key_L), leaderFSL},
            {LEADER_SEQ(LEAD(0), Key_M), leaderFSM},
            {LEADER_SEQ(LEAD(0), Key_N), leaderFSN},
            {LEADER_SEQ(LEAD(0), Key_O), leaderFSO},
            {LEADER_SEQ(LEAD(0), Key_P), leaderFSP},
            {LEADER_SEQ(LEAD(0), Key_Q), leaderFSQ},
            {LEADER_SEQ(LEAD(0), Key_R), leaderFSR},
            {LEADER_SEQ(LEAD(0), Key_S), leaderFSS},
            {LEADER_SEQ(LEAD(0), Key_T), leaderFST},
            {LEADER_SEQ(LEAD(0), Key_U), leaderFSU},
            {LEADER_SEQ(LEAD(0), Key_V), leaderFSV},
            {LEADER_SEQ(LEAD(0), Key_W), leaderFSW},
            {LEADER_SEQ(LEAD(0), Key_X), leaderFSX},
            {LEADER_SEQ(LEAD(0), Key_Y), leaderFSY},
            {LEADER_SEQ(LEAD(0), Key_Z), leaderFSZ},
            {LEADER_SEQ(LEAD(0), Key_Spacebar), leaderFS});


/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.

   When the 'any key' macro is toggled on, a random alphanumeric key is
   selected. While the key is held, the function generates a synthetic
   keypress event repeating that randomly selected key.

*/

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

*/

const macro_t *macroAction(uint8_t macroIndex, KeyEvent &event) {
  switch (macroIndex) {

    case MACRO_VERSION_INFO:
      versionInfoMacro(event.state);
      break;

    case MACRO_ANY:
      anyKeyMacro(event);
      break;
    // use the below when you want something instead that works but no OSM(LeftShift) functionality
    //    return MACRO(I(25),T(Period), T(Spacebar));
    //    break;

    case MACRO_COMMA:
      return MACRO(I(25), T(Comma), T(Spacebar));
      break;

    case MACRO_EXCLAIM:
      return MACRO(I(25), D(LeftShift), T(1), U(LeftShift), T(Spacebar));
      break;

    case MACRO_QUESTION:
      return MACRO(I(25), D(LeftShift), T(Slash), U(LeftShift), T(Spacebar));
      break;

    case MACRO_PARAGRAPH:
      return MACRO(I(25), T(Period), T(Enter), T(Enter));
      break;

    case MACRO_ENTAB:
      return MACRO(I(25), T(Period), T(Enter), T(Tab));
      break;

    case MACRO_SWAP:
      return MACRO(I(25), D(LeftShift), T(LeftArrow), U(LeftShift), D(LeftControl), T(X), U(LeftControl), T(RightArrow), D(LeftControl), T(V), U(LeftControl));
      break;
      
    case MACRO_TOGGLE_QUKEYS:
      if (keyToggledOn(event.state)) 
        Qukeys.toggle();
      break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


//static kaleidoscope::plugin::LEDSolidColor solidRed(255, 0, 0);
//static kaleidoscope::plugin::LEDSolidColor solidOrange(255, 127, 0);
//static kaleidoscope::plugin::LEDSolidColor solidYellow(255, 255, 0);
//static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 255, 0);
//static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 135, 255);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 255);
//static kaleidoscope::plugin::LEDSolidColor solidViolet(255, 0, 255);
static kaleidoscope::plugin::LEDSolidColor solidPurple(127, 0, 255);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}


/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
}, {
  .action = enterHardwareTestMode,
  // Left Fn + Prog + LED
  .keys = { R3C6, R0C0, R0C6 }
});



// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
  KALEIDOSCOPE_INIT_PLUGINS(
    // Schroedinger's cat
    Qukeys,
    Leader,
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  //Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  //FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
// FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  // BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

    // Support for OneShot for dem macros
    //OneShot,
    //EscapeOneShot,

    // LEDControl provides support for other LED modes
    LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    //LEDRainbowEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    //NumPad,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    // LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    //solidRed, solidOrange, solidYellow, solidGreen, solidBlue, 
    solidIndigo, 
    //solidViolet, 
    solidPurple,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    //LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    // AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  // NumPad,

    // The macros plugin adds support for macros
    Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  // MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

    // Support for redial
    Redial

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    // MouseKeys
  );

void setup() {
  // apparently needs to be first
  Kaleidoscope.serialPort().begin(9600);
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  //Qukeys Dictionaries
  QUKEYS(
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 8), ShiftToLayer(SHIFT)),     //Full Stop leader Shift 
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 8), Key_RightAlt),   //enter macro Alt
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 7), Key_LeftShift),    //?(Macro) Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 7), Key_LeftControl),  //!(Macro) Ctrl
//  kaleidoscope::plugin::Qukey(0, KeyAddr(2, 8), Key_LeftGui),      //comma macro Win
  )
//  Qukeys.setHoldTimeout(300);
//  Qukeys.setReleaseDelay(200); (removed)

  //Tell the redial plugin which key should have redial functionality, I guess?
//  Redial.key = Key_Redial; (no longer needed, I guess?)

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  //NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  Leader.dictionary = leader_dictionary;
  // Leader.time_out = 5000;

  // We configure the AlphaSquare effect to use GREEN letters.
  //AlphaSquare.color = { 0, 255, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(255);
  LEDRainbowWaveEffect.brightness(255);

  StalkerEffect.variant = STALKER(Rainbow);
  StalkerEffect.step_length = 400;

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  //EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  //ColormapEffect.max_layers(5);
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();
}
