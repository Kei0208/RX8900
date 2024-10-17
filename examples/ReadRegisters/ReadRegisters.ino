/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//  This sample program demonstrates how to read data from the RX8900 registers using I2C.
//  The data read from the register is stored in the instance's internal variables.
//  After reading, use the various getter methods to retrieve the values.
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

  /* Reads values ​​from registers into member variables of an instance. */
  /* Read the values ​​of all registers. */
  (void)rx8900.ReadAllRegisters();

  /* Reads the values ​​of the "YEAR", "MONTH", "DAY", "WEEK", "HOUR", "MIN", and "SEC" registers. */
  (void)rx8900.ReadCurrentTime();

  /* Reads the specified register. */
  (void)rx8900.ReadSecRegister();
  (void)rx8900.ReadMinRegister();
  (void)rx8900.ReadHourRegister();
  (void)rx8900.ReadWeekRegister();
  (void)rx8900.ReadDayRegister();
  (void)rx8900.ReadMonthRegister();
  (void)rx8900.ReadYearRegister();
  (void)rx8900.ReadRamRegister();
  (void)rx8900.ReadMinAlarmRegister();
  (void)rx8900.ReadHourAlarmRegister();
  (void)rx8900.ReadWeekDayAlarmRegister();
  (void)rx8900.ReadTempRegister();
  (void)rx8900.ReadBackupFunctionRegister();
  (void)rx8900.ReadTimerCounter0Register();
  (void)rx8900.ReadTimerCounter1Register();
  (void)rx8900.ReadExtensionRegister();
  (void)rx8900.ReadFlagRegister();
  (void)rx8900.ReadControlRegister();


  /* After reading the register, you retrieve the data with these methods. */
  /* Specify "false" to retrieve the register value as is, or specify "true" to retrieve the time converted to a decimal number. */
  /* Gets the values ​​of all registers. */
  uint8_t allData[32];
  rx8900.GetAllData(&allData[0], true);
  /* Overload method */
  RegisterTable_t rt;
  rx8900.GetAllData(&rt, true);

  /* Gets the values ​​of registers except for the "BackupFunction" and "TEMP" registers. */
  uint8_t coData[16];
  rx8900.GetCoData(&coData[0], true);
  /* Overload method */
  CoRegisterTable_t crt;
  rx8900.GetCoData(&crt, true);

  /* Gets the values ​​of registers except for the "xxAlarm" and "RAM" registers. */
  uint8_t exData[16];
  rx8900.GetExData(&exData[0], true);
  /* Overload method */
  ExRegisterTable_t ert;
  rx8900.GetExData(&ert, true);

  /* The value read from the "TEMP" register must be converted to the actual temperature using this method. */
  float acTemp;
  uint8_t *p_temp;
  p_temp = (uint8_t*)&ert.temp;
  acTemp = rx8900.ConvertTempValue(*p_temp);

  /* This method returns 0 if the specified bit is 0, and 1 if the specified bit is 1. */
  uint8_t bitState;
  uint8_t *p_ext;
  p_ext = (uint8_t*)&crt.extension;
  bitState = rx8900.GetAnyBit(*p_ext, (uint8_t)4);   // Returns the state of the "TE" bit.

  /* If the "UF", "TF", or "AF" bit has changed from the previously read value of 0 to 1, the corresponding bit is set to 1. */
  uint8_t interruptState;
  (void)rx8900.JudgeInterruptSignalType(&interruptState);   // Example interruptState = 0x03 : UF:0 to 0, TF:0 to 1, AF:0 to 1
}


void loop()
{
  delay(10);
}
