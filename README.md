# AButton

A lightweight Arduino library for handling push buttons with software debouncing.

## Features

- Software debouncing
- Button press detection (`click()`)
- Button release detection (`unclick()`)
- Double-click detection (`doubleClick()`)
- Hold-duration detection (`press()`)
- Current button state detection (`pressed()`)
- Configurable debounce and double-click intervals
- Support for `INPUT` and `INPUT_PULLUP`
- Non-blocking operation using `millis()`

## Installation

In the Arduino IDE, open **Tools > Manage Libraries...** (or click the Library Manager icon), search for **AButton**, and click **Install**.

Then include the library in your sketch:

```cpp
#include <AButton.h>
```

## Wiring

The library supports two input configurations:

- **External pull-up or pull-down resistor:** create the `AButton` object with `false` (the default). Use an external resistor to ensure the input has a defined logic level when the button is not pressed.
- **Internal pull-up resistor:** create the object with `true`. Connect one side of the button to the pin and the other side to GND.

When using `INPUT_PULLUP`, the library automatically inverts the pin reading. A pressed button is represented internally as `true`.

## Basic usage

```cpp
#include <AButton.h>

AButton button(2, true);

void setup() {
  Serial.begin(9600);
  button.begin();
}

void loop() {
  button.update();

  if (button.click()) {
    Serial.println("Button pressed");
  }

  if (button.unclick()) {
    Serial.println("Button released");
  }

  if (button.doubleClick()) {
    Serial.println("Double click detected");
  }

  if (button.press(1000)) {
    Serial.println("Button held for at least 1 second");
  }
}
```

**Important:** Call `update()` on every iteration of `loop()`. The event methods depend on it.

## API reference

| Method | Description |
| --- | --- |
| `AButton(pin, pullup)` | Creates a button instance. `pullup` defaults to `false`. |
| `begin()` | Configures the pin and initializes the button state. |
| `update()` | Reads the input and updates the debounced state. Call it repeatedly in `loop()`. |
| `click()` | Returns `true` during the update cycle in which the button becomes pressed. |
| `unclick()` | Returns `true` during the update cycle in which the button becomes released. |
| `doubleClick()` | Returns `true` during the update cycle in which a second press is detected within the configured interval after the first release. |
| `press(duration)` | Returns `true` only once when the button has been held for the specified duration. It will not trigger again until the button is released and pressed again. |
| `pressed()` | Returns the current debounced button state. |
| `setDebounce(ms)` | Sets the debounce interval in milliseconds. The default is 50 ms. |
| `setDoubleClickInterval(ms)` | Sets the maximum time, in milliseconds, between the first release and the second press. The default is 400 ms. |

## Double-click behavior

A double click is detected when the second press begins within the configured interval after the first click has been released. The `doubleClick()` event is reported on that second press.

The existing `click()` event is still reported immediately on every press. Therefore, `click()` does not wait to determine whether the press will become part of a double click.

## Notes

- `press(duration)` is a level-style check, not a one-time event. It remains `true` on every call while the button stays pressed after the duration has elapsed.
- The default debounce interval is 50 ms.
- The default double-click interval is 400 ms.
- When using `INPUT`, provide an external resistor so the input does not float.
- The library uses `millis()` and does not use blocking delays.

## Example

See [`examples/Basic/Basic.ino`](examples/Basic/Basic.ino).
