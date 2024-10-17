/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This sample program shows an example of writing data to a RX8900 register using I2C.
//  Use the various methods according to your needs.
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

  /* Example set 2024/10/20(Tue) 16:30:50 */
  (void)rx8900.WriteYearRegister(24);   // 0 to 99
  (void)rx8900.WriteMonthRegister(10);  // 1 to 12
  (void)rx8900.WriteDayRegister(20);    // 1 to 31
  (void)rx8900.WriteWeekRegister(2);    // 0 to 6
  (void)rx8900.WriteHourRegister(16);   // 0 to 23
  (void)rx8900.WriteMinRegister(30);    // 0 to 59
  (void)rx8900.WriteSecRegister(50);    // 0 to 59

  /* You can achieve the same setup this way too. */
  (void)rx8900.WriteDateRegisters(24, 10, 20, 2);   // Year, Month, Day, Week
  (void)rx8900.WriteTimeRegisters(16, 30, 50);      // Hour, Minutes, Seconds

  /* Example set alarm every day at 7:15 */
  (void)rx8900.WriteMinAlarmRegister(0x15, false);    // Setting Value, "AE" bit
  (void)rx8900.WriteHourAlarmRegister(0x07, false);   // Setting Value, "AE" bit
  (void)rx8900.WriteWeekDayAlarmRegister(0x80, true); // Setting Value, "AE" bit

  /* You can freely write one byte of data. */
  (void)rx8900.WriteRamRegister(0xA5);

  /* TimerCounter register */
  (void)rx8900.WriteTimerCounter0Register(0x5A);  // 0x00 to 0xFF
  (void)rx8900.WriteTimerCounter1Register(0x05);  // 0x00 to 0x0F

  /* BackupFunction register */
  (void)rx8900.WriteBackupFunctionRegister(0x0C); // 0x00 to 0x0F

  /* Extension register */
  (void)rx8900.WriteExtensionRegister(0x42);  // 0x00 to 0x7F

  /* Flag register */
  (void)rx8900.WriteFlagRegister(0x00); // Valid bits are bits 0, 1, 3, 4, and 5.

  /* Control register */
  (void)rx8900.WriteControlRegister(0x40); // Valid bits are bits 0, 3, 4, 5, 6 and 7.

  /* Write all writable registers except the BackupFunction register. */
  /* The data is stored in ascending address order. */
  /* Please refer to the datasheet for details of the register table. */
  uint8_t coReg[16] = {16, 30, 50, 2, 20, 10, 24, 0xA5, 0x15, 0x07, 0x80, 0x5A, 0x05, 0x42, 0x00, 0x40};
  (void)rx8900.WriteAllCoRegisters(&coReg[0]);

  /* Writes all writable registers except xxAlarm registers and RAM registers. */
  /* The data is stored in ascending address order. */
  /* Please refer to the datasheet for details of the register table. */
  uint8_t exReg[16] = {16, 30, 50, 2, 20, 10, 24, 0x00, 0x0C, 0x00, 0x00, 0x5A, 0x05, 0x42, 0x00, 0x40};
  (void)rx8900.WriteAllExRegisters(&exReg[0]);
}


void loop()
{
  delay(10);
}
