#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola MyDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int yesButtonPin = 8;
const int noButtonPin = 9;
const char* question = "Porposal Question";

void setup() {
  pinMode(yesButtonPin, INPUT_PULLUP); 
  pinMode(noButtonPin, INPUT_PULLUP); 

  MyDisplay.begin();
  MyDisplay.setIntensity(4);
  MyDisplay.displayClear();
  MyDisplay.displayScroll(question, PA_CENTER, PA_SCROLL_LEFT, 100);
}

void loop() {
  if (digitalRead(yesButtonPin) == HIGH) {
    delay(100); // debouncing
    if (digitalRead(yesButtonPin) == HIGH) {
      MyDisplay.displayClear();
      MyDisplay.displayScroll("Yes = answer to ptoposal", PA_CENTER, PA_SCROLL_LEFT, 100);
      while (!MyDisplay.displayAnimate()); // wait for the message to finish scrolling
    }
  } else if (digitalRead(noButtonPin) == HIGH) {
    delay(100); // debouncing
    if (digitalRead(noButtonPin) == HIGH) {
      MyDisplay.displayClear();
      MyDisplay.displayScroll("No = Try Again (funny argument)", PA_CENTER, PA_SCROLL_LEFT, 100);
      while (!MyDisplay.displayAnimate()); // wait for "Try Again" to finish scrolling
      delay(2000); // wait a bit before showing the question again
      MyDisplay.displayScroll(question, PA_CENTER, PA_SCROLL_LEFT, 100);
    }
  }

  if (MyDisplay.displayAnimate())
    MyDisplay.displayReset();
}
