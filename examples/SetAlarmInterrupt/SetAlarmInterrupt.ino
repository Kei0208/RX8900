/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This program will make the RX8900 output an alarm interrupt signal at 7:15 every
//  morning.
//  When an alarm interrupt occurs, the RX8900's "INT" pin goes to the LOW state.
//  The microcontroller monitors the receiving terminal for the interrupt signal, and
//  if it detects a LOW state, it clears the RX8900's "AF" bit to 0 and resets the
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

  /* Use the "WEEK DAY Alarm" register as the "WEEK Alarm". */
  (void)rx8900.WDRegisterRoleChange(false);

  /* Example set alarm every day at 7:15 */
  (void)rx8900.WriteMinAlarmRegister(0x15, false);    // Setting Value, "AE" bit
  (void)rx8900.WriteHourAlarmRegister(0x07, false);   // Setting Value, "AE" bit
  (void)rx8900.WriteWeekDayAlarmRegister(0x80, true); // Setting Value, "AE" bit

  /* An interrupt signal is output due to an alarm interrupt. */
  (void)rx8900.InterruptSettings(true, false, false);   // "AIE", "TIE", "UIE"
}


void loop()
{
  uint8_t flagChange;

  if(isInterrupt)
  {
    isInterrupt = false;

    /* Since the "AF" bit has changed from 0 to 1, "flagChange" is set to 0x01. */
    rx8900.JudgeInterruptSignalType(&flagChange);
    Serial.print("flagChange:");
    Serial.println(flagChange, BIN);

    /* Clear the "AF" bit to 0. */
    rx8900.ClearOccurrenceNotification(true, false, false);
    
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
