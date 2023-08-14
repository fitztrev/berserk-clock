#define _USING_HID

#include <Keyboard.h>
#include <Button2.h>

// Define the button pins
const int ClockLeftPin = 6;
const int ClockRightPin = 10;
const int BerserkLeftPin = 8;
const int BerserkRightPin = 4;

// Create Button2 objects for each button
Button2 clockLeftButton(ClockLeftPin);
Button2 clockRightButton(ClockRightPin);
Button2 berserkLeftButton(BerserkLeftPin);
Button2 berserkRightButton(BerserkRightPin);

void setup() {
  delay(2 * 1000);

  // Initialize the Keyboard library
  Keyboard.begin();
  
  // Configure buttons
  clockLeftButton.setPressedHandler([](Button2 &btn) {
    Keyboard.write('1');
  });
  
  clockRightButton.setPressedHandler([](Button2 &btn) {
    Keyboard.write('2');
  });
  
  berserkLeftButton.setPressedHandler([](Button2 &btn) {
    Keyboard.write('3');
  });
  
  berserkRightButton.setPressedHandler([](Button2 &btn) {
    Keyboard.write('4');
  });
  
  // Start checking button states
  clockLeftButton.setDebounceTime(50);  // Adjust debounce time as needed
  clockRightButton.setDebounceTime(50);
  berserkLeftButton.setDebounceTime(50);
  berserkRightButton.setDebounceTime(50);
}

void loop() {
  // Update button states
  clockLeftButton.loop();
  clockRightButton.loop();
  berserkLeftButton.loop();
  berserkRightButton.loop();
}
