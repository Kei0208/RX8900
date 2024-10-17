/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This program will make the RX8900 output a timer interrupt signal every 1,445 seconds.
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

  /* Sets the downcount frequency. */
  // False, False : 4,096[Hz], True, False : 64[Hz]
  // False, True  : 1[Hz]    , True, True  : 1/60[Hz]
  (void)rx8900.CountdownCycleChange(false, true);

  /* A timer interrupt occurs every 1,445 seconds. */
  (void)rx8900.WriteTimerCounter0Register(0x5A);  // 0x00 to 0xFF
  (void)rx8900.WriteTimerCounter1Register(0x05);  // 0x00 to 0x0F

  /* An interrupt signal is output by the timer interrupt. */
  (void)rx8900.InterruptSettings(false, true, false);   // "AIE", "TIE", "UIE"

  /* Start the countdown. */
  (void)rx8900.TimerCountDownStart();
  //(void)rx8900.TimerCountDownStop();
}


void loop()
{
  uint8_t flagChange;

  if(isInterrupt)
  {
    isInterrupt = false;

    /* Since the "TF" bit has changed from 0 to 1, "flagChange" is set to 0x02. */
    rx8900.JudgeInterruptSignalType(&flagChange);
    Serial.print("flagChange:");
    Serial.println(flagChange, BIN);

    /* Clear the "TF" bit to 0. */
    rx8900.ClearOccurrenceNotification(false, true, false);
    
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
