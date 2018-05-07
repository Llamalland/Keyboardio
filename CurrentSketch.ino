
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

// let's fucking see, huh? Support for Schroedinger's cat
#include "Kaleidoscope-Qukeys.h"

// Redial key
#include "Kaleidoscope-Redial.h"

// Flippity Flop, flips a key's shifted and unshifted outputs
#include "Kaleidoscope-TopsyTurvy.h"

// Oneshot stuff
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

// Dependencies for Redial, OneShot(etc.)
#include "Kaleidoscope-Ranges.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for OneShot modifiers
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope/hid.h"
#include "Kaleidoscope-Escape-OneShot.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
//#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for Odo
#include "Kaleidoscope-ShapeShifter.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
// #include "Kaleidoscope-LED-AlphaSquare.h"

// Support for Keyboardio's internal keyboard testing mode - ADD BACK IN BEFORE FINALLY FLASHING
// #include "Kaleidoscope-Model01-TestMode.h"


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
       MACRO_FULLSTOP,
       MACRO_COMMA,
       MACRO_EXCLAIM,
       MACRO_QUESTION,
       MACRO_SWAP,
       MACRO_PARAGRAPH,
       MACRO_TOGGLE_QUKEYS
     };

/* Redial info

*/

enum {
  REDIAL = kaleidoscope::ranges::SAFE_START,
};
#define Key_Redial (Key) {.raw = REDIAL}

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

enum { NEROFIST, NUMPAD, FUNCTION, QWERTY }; // layers

/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [NEROFIST] = KEYMAP_STACKED
  (Key_RightBracket, Key_1, Key_2, Key_3, Key_4, Key_5,     Key_Escape,
   Key_LeftBracket,  Key_G, Key_U, Key_B, Key_F, Key_Quote, Key_RightAlt, 
   LSHIFT(Key_9),    Key_T, Key_I, Key_S, Key_D, Key_P,
   LSHIFT(Key_0),    Key_Z, Key_Y, Key_X, Key_C, Key_V,     Key_Equals, 
   M(MACRO_QUESTION), M(MACRO_EXCLAIM), Key_Spacebar, Key_Backspace, 
   ShiftToLayer(NUMPAD),

   Key_Escape,         Key_6, Key_7, Key_8,     Key_9,      Key_0, LSHIFT(Key_Tab),
   LSHIFT(Key_Quote),  Key_M, Key_H, Key_O,     Key_Redial, Key_W, Key_Tab,
                       Key_L, Key_N, Key_E,     Key_A,      Key_R, TOPSY(Semicolon),   
   LSHIFT(Key_Equals), Key_Q, Key_J, Key_Slash, Key_Minus,  Key_K, M(MACRO_SWAP), 
   Key_Delete, M(MACRO_PARAGRAPH), M(MACRO_FULLSTOP), M(MACRO_COMMA),
   ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,  
   ___,                ___,           Consumer_VolumeDecrement, Key_UpArrow,   Consumer_VolumeIncrement, ___, ___,
   LSHIFT(Key_Comma),  Consumer_Mute, Key_LeftArrow,            Key_DownArrow, Key_RightArrow,           ___,
   LSHIFT(Key_Period), ___,           ___,                      ___,           ___,                      ___, ___,
   LSHIFT(Key_1), LSHIFT(Key_Slash), LSHIFT(LCTRL(Key_Spacebar)), LCTRL(Key_Backspace), 
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,     Key_KeypadAdd,      ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,     Key_KeypadSubtract, LSHIFT(Key_4),
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,     Key_KeypadDivide,   Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadEnter, Key_KeypadMultiply, Key_KeypadEquals,
   LCTRL(Key_Delete), Key_LeftGui, Key_RightAlt, Key_RightShift,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___, Key_F1, Key_F2,                     Key_F3,       Key_F4,                 Key_F5, Key_LEDEffectNext,
   ___, ___,    Consumer_ScanPreviousTrack, Key_PageUp,   Consumer_ScanNextTrack, ___,    ___,
   ___, ___,    Key_Home,                   Key_PageDown, Key_End,                ___,
   ___, ___,    ___,                      ___,          ___,                      ___,    M(MACRO_TOGGLE_QUKEYS),
   Key_LeftControl, Key_LeftShift, LCTRL(LSHIFT(Key_Spacebar)), LCTRL(Key_Backspace), 
   ___,

   M(MACRO_ANY), Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
   Key_RightAlt,  ___,    ___,    ___,    ___,    ___,     Key_F12,
                  ___,    ___,    ___,    ___,    ___,     ___,
   LockLayer(QWERTY), ___,    ___,    ___,    ___,    ___,     ___,
   LCTRL(Key_Delete), Key_Enter, Key_Period, Key_Comma,
   ___),

  [QWERTY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_LeftShift, Key_Spacebar, Key_Backspace, 
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),      Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NEROFIST),
   Key_Enter,         Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   LockLayer(QWERTY), Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_Delete, Key_LeftGui, Key_RightAlt, Key_RightShift,
   ShiftToLayer(FUNCTION)),
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** Shapeshifter dictionary
    {intercepted, sent} when shifted
*/

static const kaleidoscope::ShapeShifter::dictionary_t shape_shift_dictionary[] PROGMEM = {
  {Key_Slash, Key_8},
  {Key_1, Key_Backslash},
  {Key_8, Key_Backtick},
  //  {Key_Minus, Key_Equals},
  {Key_Equals, Key_Minus},
  // {Key_9, Key_MAKEBACKSLASHWORK},
  // {Key_0, Key_MAKEBACKTICKWORK},
  {Key_NoKey, Key_NoKey},
};

/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.

   When the 'any key' macro is toggled on, a random alphanumeric key is
   selected. While the key is held, the function generates a synthetic
   keypress event repeating that randomly selected key.

*/

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}

// my attempt at this thing. the "Key punctuation" bit didn't make sense but I have
// tried other permutations in its place like Key_Period, Key Period etc., with the similar result

const macro_t *fullStopMacro(Key punctuation) {
  handleKeyswitchEvent(punctuation, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED);
  kaleidoscope::hid::sendKeyboardReport();
  handleKeyswitchEvent(punctuation, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED);
  kaleidoscope::hid::sendKeyboardReport();

  handleKeyswitchEvent(Key_Spacebar, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED);
  kaleidoscope::hid::sendKeyboardReport();
  handleKeyswitchEvent(Key_Spacebar, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED);
  kaleidoscope::hid::sendKeyboardReport();

  //  handleKeyswitchEvent(OSM(LeftShift), UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED);
  //  handleKeyswitchEvent(OSM(LeftShift), UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED);
  OneShot.inject(OSM(LeftShift), IS_PRESSED);
  OneShot.inject(OSM(LeftShift), WAS_PRESSED);

  return MACRO_NONE;
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

*/

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

    case MACRO_VERSION_INFO:
      versionInfoMacro(keyState);
      break;

    case MACRO_ANY:
      anyKeyMacro(keyState);
      break;

    case MACRO_FULLSTOP:
      if (keyToggledOn(keyState)) {
        return fullStopMacro(Key_Period);
      }
      return MACRO_NONE;
    // use the below when you want something instead that works but no OSM(LeftShift) functionality
    //    return MACRODOWN(I(25),T(Period), T(Spacebar));
    //    break;

    case MACRO_COMMA:
      return MACRODOWN(I(25), T(Comma), T(Spacebar));
      break;

    case MACRO_EXCLAIM:
      return MACRODOWN(I(25),
                       D(LeftShift), T(1), U(LeftShift), T(Spacebar));
      break;

    case MACRO_QUESTION:
      return MACRODOWN(I(25),
                       D(LeftShift), T(Slash), U(LeftShift), T(Spacebar));
      break;

    case MACRO_PARAGRAPH:
      return MACRODOWN(I(25),
                       T(Period), T(Enter), T(Enter));
      break;

    case MACRO_SWAP:
      return MACRODOWN(I(25),
                       D(LeftShift), T(LeftArrow), U(LeftShift), D(LeftControl), T(X), U(LeftControl), T(RightArrow), D(LeftControl), T(V), U(LeftControl)
                      );
      break;
    case MACRO_TOGGLE_QUKEYS:
      if (keyToggledOn(keyState))
        Qukeys.toggle();
      break;
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(255, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(255, 127, 0);
static kaleidoscope::LEDSolidColor solidYellow(255, 255, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 255, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 135, 255);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 255);
static kaleidoscope::LEDSolidColor solidViolet(255, 0, 255);
static kaleidoscope::LEDSolidColor solidPurple(127, 0, 255);



/** The 'setup' function is one of the two standard Arduino sketch functions.
    It's called when your keyboard first powers up. This is where you set up
    Kaleidoscope and any plugins.
*/

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // Schroedinger's cat
    &Qukeys,

    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    //&BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time. - ADD BACK IN BEFORE FINALLY FLASHING
    //&TestMode,

    // Odo
    &ShapeShifter,

    // Flippity floppity, swap shifted and unshifted output
    &TopsyTurvy,

    // Support for OneShot for dem macros
    &OneShot,
    &EscapeOneShot,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    //&LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet, &solidPurple,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    // &AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumPad,

    // The macros plugin adds support for macros
    &Macros,

    // Support for redial
    &Redial,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys
  );

  //Qukeys Dictionaries
  QUKEYS(
    kaleidoscope::Qukey(0, 1, 8, Key_RightAlt),     //.(Macro) Alt
    kaleidoscope::Qukey(0, 0, 8, Key_RightShift),   //,(Macro) Shift
    kaleidoscope::Qukey(0, 1, 7, Key_LeftShift),    //?(Macro) Shift
    kaleidoscope::Qukey(0, 0, 7, Key_LeftControl),  //!(Macro) Ctrl
    kaleidoscope::Qukey(0, 2, 8, Key_LeftGui),      //Enter Win
  )
  Qukeys.setTimeout(150);
  Qukeys.setReleaseDelay(20);

  //Tell the redial plugin which key should have redial functionality, I guess?
  Redial.key = Key_Redial;

  //Tell Odo where his dictionary is
  ShapeShifter.dictionary = shape_shift_dictionary;

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use GREEN letters
  //AlphaSquare.color = { 0, 255, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(255);
  LEDRainbowWaveEffect.brightness(255);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();
}

