/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This program will make the RX8900 output a timer update interrupt signal every 1 seconds.
//  When a timer interrupt occurs, the RX8900's "INT" pin goes to a LOW state.
//  The microcontroller monitors the receiving terminal for the interrupt signal, and
//  if it detects a LOW state, it clears the RX8900's "TF" bit to 0 and resets the
//  interrupt signal to a HIGH state.
//  For details on each register, please refer to the data sheet.
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

#include "RX8900.h"

#define RECEIVE_PIN (18)

RX8900 rx8900;

volatile bool isInterrupt = false;


void setup()
{
  Serial.begin(115200);
  Wire.begin();

  pinMode(RECEIVE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RECEIVE_PIN), ReceivedInterrupt, FALLING);

  /* Initialization */
  rx8900.RX8900Init();

  /* Sets the timing for the time update interrupt to occur. */
  // False : 1[seconds], True : 1[Minutes]
  (void)rx8900.UpdateInterruptTimingChange(false);

  /* An interrupt signal is output by the time update interrupt. */
  (void)rx8900.InterruptSettings(false, false, true);   // "AIE", "TIE", "UIE"
}


void loop()
{
  uint8_t flagChange;

  if(isInterrupt)
  {
    isInterrupt = false;

    /* Since the "UF" bit has changed from 0 to 1, "flagChange" is set to 0x04. */
    rx8900.JudgeInterruptSignalType(&flagChange);
    Serial.print("flagChange:");
    Serial.println(flagChange, BIN);

    /* Clear the "UF" bit to 0. */
    rx8900.ClearOccurrenceNotification(false, false, true);
    
    attachInterrupt(digitalPinToInterrupt(RECEIVE_PIN), ReceivedInterrupt, FALLING);
  }
  else
  {
    /* do nothing */
  }

  delay(10);
}


void ReceivedInterrupt()
{
  isInterrupt = true;

  detachInterrupt(digitalPinToInterrupt(RECEIVE_PIN));
}
