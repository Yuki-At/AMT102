/* 
 * AMT102.cpp
 * 
 * Version: 1.01
 * Created: 2020/1/25
 * Author : Yuki Yoshida
 */

#include "AMT102.h"

namespace {
  AMT102 *encoder[3];
  int totalObjectNum = 0;

  void encoder1() {
    encoder[0]->interruptMethod();
  }
  void encoder2() {
    encoder[1]->interruptMethod();
  }
  void encoder3() {
    encoder[2]->interruptMethod();
  }
}

AMT102::AMT102(uint8_t dipSwitch, int aInterruptNumber, int bInterruptNumber) {
  this->dipSwitch = dipSwitch;
  this->aInterruptNumber = aInterruptNumber;
  this->bInterruptNumber = bInterruptNumber;
}

void AMT102::setup() {
  totalObjectNum++;
  switch (totalObjectNum) {
  case 1:
    encoder[0] = this;
    attachInterrupt(aInterruptNumber, encoder1, CHANGE);
    attachInterrupt(bInterruptNumber, encoder1, CHANGE);
    break;
  case 2:
    encoder[1] = this;
    attachInterrupt(aInterruptNumber, encoder2, CHANGE);
    attachInterrupt(bInterruptNumber, encoder2, CHANGE);
    break;
  case 3:
    encoder[2] = this;
    attachInterrupt(aInterruptNumber, encoder3, CHANGE);
    attachInterrupt(bInterruptNumber, encoder3, CHANGE);
    break;
  default:
    printError("You use too many encoder. You can use under three.");
    break;
  }

  switch (dipSwitch) {
  case 0b0000: ppr = 2048; break;
  case 0b0010: ppr = 1024; break;
  case 0b1000: ppr = 1000; break;
  case 0b0100: ppr =  800; break;
  case 0b0001: ppr =  512; break;
  case 0b1010: ppr =  500; break;
  case 0b0110: ppr =  400; break;
  case 0b1100: ppr =  384; break;
  case 0b0011: ppr =  256; break;
  case 0b1001: ppr =  250; break;
  case 0b0101: ppr =  200; break;
  case 0b1110: ppr =  192; break;
  case 0b1011: ppr =  125; break;
  case 0b0111: ppr =  100; break;
  case 0b1101: ppr =   96; break;
  case 0b1111: ppr =   48; break;
  default:
    printError("Not found number of dip switch.");
    break;
  }

  prevState = getState();
}

void AMT102::interruptMethod() {
  currentState = getState();

  if ((currentState == prevState - 1) || (currentState == 0 && prevState == 3)) {
    revolution -= 360.0 / ppr / 2;
  }
  else {
    revolution += 360.0 / ppr / 2;
  }

  prevState = currentState;
}

int AMT102::getState() {
  bool a = false, b = false;

  switch (aInterruptNumber) {
    case 2: a = (PIND & (1 << PIND0)); break;
    case 3: a = (PIND & (1 << PIND1)); break;
    case 4: a = (PIND & (1 << PIND2)); break;
    case 5: a = (PIND & (1 << PIND3)); break;
    case 0: a = (PINE & (1 << PINE4)); break;
    case 1: a = (PINE & (1 << PINE5)); break;
    default:
      printError("Not found a intterrupt pin");
  }
  switch (bInterruptNumber) {
    case 2: b = (PIND & (1 << PIND0)); break;
    case 3: b = (PIND & (1 << PIND1)); break;
    case 4: b = (PIND & (1 << PIND2)); break;
    case 5: b = (PIND & (1 << PIND3)); break;
    case 0: b = (PINE & (1 << PINE4)); break;
    case 1: b = (PINE & (1 << PINE5)); break;
    default:
      printError("Not found b intterrupt pin");
  }

  if (a) {
    // a: high, b: high
    if (b) {
      return 2;
    }
    // a: high, b: low
    else {
      return 1;
    }
  }
  else {
    // a: low, b: high
    if (b) {
      return 3;
    }
    // a: low, b: low
    else {
      return 0;
    }
  }
}

