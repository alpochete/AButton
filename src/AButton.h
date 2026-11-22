#ifndef ABUTTON_H
#define ABUTTON_H

#include <Arduino.h>

class AButton {
public:
  // Set pullup to true to use INPUT_PULLUP (connect the button to GND).
  explicit AButton(uint8_t pin, bool pullup = false);

  void begin();
  void update();  // Call on every loop() iteration.

  bool click();                        // True when the button is pressed.
  bool unclick();                      // True when the button is released.
  bool doubleClick();                  // True when a second click is detected.
  bool press(unsigned long duration);  // True while held for at least duration ms.
  bool pressed();                      // Returns the current debounced state.

  void setDebounce(unsigned long ms);
  void setDoubleClickInterval(unsigned long ms);

private:
  uint8_t _pin;
  bool _inverted;

  bool _state;
  bool _previousState;
  bool _reading;
  bool _previousReading;
  bool _longPressTrigered;

  unsigned long _debounceStart;
  unsigned long _pressStart;
  unsigned long _debounceInterval;

  bool _waitingForSecondClick;
  bool _doubleClickEvent;
  unsigned long _lastClickTime;
  unsigned long _doubleClickInterval;
};

#endif
