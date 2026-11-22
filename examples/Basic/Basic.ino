#include <AButton.h>

// Connect the button between pin 2 and GND.
AButton button(2, true);

void setup() {
  Serial.begin(9600);
  button.begin();
}

void loop() {
  // Call update() on every loop iteration.
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
    Serial.println("Button has been held for at least 1 second");
  }
}
