#include "AButton.h"

AButton::AButton(uint8_t pin, bool pullup)
  : _pin(pin),
    _inverted(pullup),
    _state(false),
    _previousState(false),
    _reading(false),
    _previousReading(false),
    _debounceStart(0),
    _pressStart(0),
    _longPressTrigered(false),
    _debounceInterval(50),
    _waitingForSecondClick(false),
    _doubleClickEvent(false),
    _lastClickTime(0),
    _doubleClickInterval(400) {}

void AButton::begin() {
  pinMode(_pin, _inverted ? INPUT_PULLUP : INPUT);

  _reading = digitalRead(_pin);
  if (_inverted) {
    _reading = !_reading;
  }

  // Initialize the debounced state to the pin's current state.
  _state = _reading;
  _previousState = _reading;
  _previousReading = _reading;

  _debounceStart = millis();
  if (_state) {
    _pressStart = millis();
  }

  _waitingForSecondClick = false;
  _doubleClickEvent = false;
  _longPressTriggered = false;
}

void AButton::update() {
  _previousState = _state;
  _doubleClickEvent = false;

  _reading = digitalRead(_pin);
  if (_inverted) {
    _reading = !_reading;
  }

  if (_reading != _previousReading) {
    _debounceStart = millis();
  }

  if ((millis() - _debounceStart >= _debounceInterval) &&
      (_state != _reading)) {
    _state = _reading;

    _longPressTriggered = false;
    
    if (_state) {
      // A new press can complete a double click.
      if (_waitingForSecondClick) {
        if (millis() - _lastClickTime <= _doubleClickInterval) {
          _doubleClickEvent = true;
          _waitingForSecondClick = false;
        } else {
          // The previous click timed out; this press starts a new sequence.
          _waitingForSecondClick = false;
        }
      }

      _pressStart = millis();
    } else {
      // Start (or restart) the waiting period after a released click.
      if (!_doubleClickEvent) {
        _waitingForSecondClick = true;
        _lastClickTime = millis();
      }
    }
  }

  // Expire an unmatched first click.
  if (_waitingForSecondClick &&
      millis() - _lastClickTime > _doubleClickInterval) {
    _waitingForSecondClick = false;
  }

  _previousReading = _reading;
}

bool AButton::click() {
  return _state && !_previousState;
}

bool AButton::unclick() {
  return !_state && _previousState;
}

bool AButton::doubleClick() {
  return _doubleClickEvent;
}

bool AButton::pressed() {
  return _state;
}

bool AButton::press(unsigned long duration) {
  if (_state && 
      !_longPressTrigered && 
      (millis() - _pressStart >= duration)){
        
        _longPressTrigered = true;
        return true;
      }

  return false;
}

void AButton::setDebounce(unsigned long ms) {
  _debounceInterval = ms;
}

void AButton::setDoubleClickInterval(unsigned long ms) {
  _doubleClickInterval = ms;
}
