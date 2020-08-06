/* 
 * AMT102.h
 * 
 * Version: 1.00
 * Created: 2020/1/25
 * Author : Yuki Yoshida
 */

#ifndef AMT102_H
#define AMT102_H

#include <Arduino.h>

class AMT102 {
public:
  AMT102(uint8_t dipSwitch, int aInterruptNumber, int bInterruptNumber);

  void setup();

  double getRevolution();

  void interruptMethod();

private:
  int aInterruptNumber, bInterruptNumber;
  uint8_t dipSwitch;
  double revolution;
  double ppr; // pulses per revolution
  int prevState, currentState;

  void printError(const char *errorText);
  int getState();

};

inline double AMT102::getRevolution() {
  return revolution;
}

inline void AMT102::printError(const char *errorText) {
  Serial.println("--- Error ---");
  Serial.println("from AMT102 class");
  Serial.println(errorText);
}

#endif
