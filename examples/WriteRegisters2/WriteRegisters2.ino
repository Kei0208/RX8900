/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This sample program shows an example of writing data to a RX8900 register using I2C.
//  Some register bits can be controlled by dedicated methods.
//  For details on each register, please refer to the data sheet.
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

#include "RX8900.h"

RX8900 rx8900;


void setup()
{
  Serial.begin(115200);
  Wire.begin();

  /* Initialization */
  rx8900.RX8900Init();

  /* Extension register */
  /* You can control the "WADA" bit. */
  (void)rx8900.WDRegisterRoleChange(true);
  /* You can control the "USEL" bit. */
  (void)rx8900.UpdateInterruptTimingChange(true);
  /* You can control the "TE" bit. */
  (void)rx8900.TimerCountDownStart();
  (void)rx8900.TimerCountDownStop();
  /* You can control the "FSEL0" and "FSEL1" bits. */
  (void)rx8900.OutputFrequencyChange(true, true);   // "FSEL0", "FSEL1"
  /* You can control the "TSEL0" and "TSEL1" bits. */
  (void)rx8900.CountdownCycleChange(true, true);    // "TSEL0", "TSEL1"


  /* Flag register */
  /* You can control the "AF", "TF" and "UF" bits. */
  (void)rx8900.ClearOccurrenceNotification(true, true, true);   // "AF", "TF", "UF"
  /* You can control the "VLF" and "VDET" bits. */
  (void)rx8900.ClearVoltageNotification(true, true);    // "VLF", "VDET"


  /* Control register */
  /* You can control the "CSEL0" and "CSEL1" bits. */
  (void)rx8900.CompensationIntervalChange(true, true);    // "CSEL0", "CSEL1"
  /* You can control the "AIE", "TIE" and "UIE" bits. */
  (void)rx8900.InterruptSettings(true, true, true);   // "AIE", "TIE", "UIE"
  /* You can control the "RESET" bit. */
  (void)rx8900.ResetSubSecondCounter();


  /* BackupFunction register */
  /* You can control the "VDETOFF" bit. */
  (void)rx8900.VoltageDetectionCircuitSettings(true);
  /* You can control the "SWOFF" bit. */
  (void)rx8900.PMosSwitchSettings(true);
  /* You can control the "BKSMP0" and "BKSMP1" bits. */
  (void)rx8900.VoltageDetectionMethodChange(true, true);    // "BKSMP0", "BKSMP1"
}


void loop()
{
  delay(10);
}
