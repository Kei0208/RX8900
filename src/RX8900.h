/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Header name
//            RX8900.h
//(2)Note
//            This library supports RTC of RX8900x series.
//(3)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
#ifndef RX8900_H
#define RX8900_H


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//	Include
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
#include <Arduino.h>
#include <Wire.h>


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//	Definition
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
// RX8900 I2C address
#define RX8900_I2C_ADDRESS (0x32)

// Initial register value
/* 2000/1/1(Sat.) 00:00:00 */
#define DEFAULT_SEC_REGISTER_VALUE             (0b00000000)
#define DEFAULT_MIN_REGISTER_VALUE             (0b00000000)
#define DEFAULT_HOUR_REGISTER_VALUE            (0b00000000)
#define DEFAULT_WEEK_REGISTER_VALUE            (0b00000001)
#define DEFAULT_DAY_REGISTER_VALUE             (0b00000001)
#define DEFAULT_MONTH_REGISTER_VALUE           (0b00000001)
#define DEFAULT_YEAR_REGISTER_VALUE            (0b00000000)
#define DEFAULT_BACKUP_FUNCTION_REGISTER_VALUE (0b00001100)		/* VDETOFF:1, SWOFF:1, BKSMP1:0, BKSMP0:0 */
#define DEFAULT_RAM_REGISTER_VALUE             (0b00000000)
#define DEFAULT_MIN_ALARM_REGISTER_VALUE       (0b00000000)		/* AE:0 */
#define DEFAULT_HOUR_ALARM_REGISTER_VALUE      (0b00000000)		/* AE:0 */
#define DEFAULT_WEEK_DAY_ALARM_REGISTER_VALUE  (0b00000000)		/* AE:0 */
#define DEFAULT_TIMER_COUNTER0_REGISTER_VALUE  (0b00000000)
#define DEFAULT_TIMER_COUNTER1_REGISTER_VALUE  (0b00000000)
#define DEFAULT_EXTENSION_REGISTER_VALUE       (0b01000010)		/* TEST:0, WADA:1, USEL:0, TE:0, FSEL1:0, FSEL0:0, TSEL1:1, TSEL0:0 */
#define DEFAULT_FLAG_REGISTER_VALUE            (0b00000000)		/* UF:0, TF:0, AF:0, VLF:0, VDET:0 */
#define DEFAULT_CONTROL_REGISTER_VALUE         (0b01000000)		/* CSEL1:0, CSEL0:1, UIE:0, TIE:0, AIE:0, RESET:0 */

// "Reserved", "Not Write" and "TEST" bit "AND" mask
#define SEC_MIN_REGISTER_BIT_MASK         (0b01111111)
#define HOUR_REGISTER_BIT_MASK            (0b00111111)
#define WEEK_REGISTER_BIT_MASK            (0b01111111)
#define DAY_REGISTER_BIT_MASK             (0b00111111)
#define MONTH_REGISTER_BIT_MASK           (0b00011111)
#define YEAR_REGISTER_BIT_MASK            (0b11111111)
#define RAM_REGISTER_BIT_MASK             (0b11111111)
#define MIN_ALARM_REGISTER_BIT_MASK       (0b11111111)
#define HOUR_ALARM_REGISTER_BIT_MASK      (0b11111111)
#define WEEK_DAY__ALARM_REGISTER_BIT_MASK (0b11111111)
#define TEMP_REGISTER_BIT_MASK            (0b00000000)
#define BACKUP_FUNCTION_REGISTER_BIT_MASK (0b00001111)
#define NOT_USE0_REGISTER_BIT_MASK        (0b00000000)
#define NOT_USE1_REGISTER_BIT_MASK        (0b00000000)
#define TIMER_COUNTER0_REGISTER_BIT_MASK  (0b11111111)
#define TIMER_COUNTER1_REGISTER_BIT_MASK  (0b11111111)
#define EXTENSION_REGISTER_BIT_MASK       (0b01111111)
#define FLAG_REGISTER_BIT_MASK            (0b00111011)
#define CONTROL_REGISTER_BIT_MASK         (0b11111001)

// Temperature Conversion Formula
#define TEMP_CONVERSION_FORMULA(temp) (((temp * 2) - 187.19) / 3.218)

// Limit value
#define YEAR_LOWER_LIMIT           (uint8_t)(0)
#define YEAR_UPPER_LIMIT           (uint8_t)(99)
#define MONTH_LOWER_LIMIT          (uint8_t)(1)
#define MONTH_UPPER_LIMIT          (uint8_t)(12)
#define DAY_LOWER_LIMIT            (uint8_t)(1)
#define DAY_UPPER_LIMIT            (uint8_t)(31)
#define HOUR_LOWER_LIMIT           (uint8_t)(0)
#define HOUR_UPPER_LIMIT           (uint8_t)(23)
#define SEC_MIN_LOWER_LIMIT        (uint8_t)(0)
#define SEC_MIN_UPPER_LIMIT        (uint8_t)(59)
#define TIMER_COUNTER0_LOWER_LIMIT (uint8_t)(0x00)
#define TIMER_COUNTER0_UPPER_LIMIT (uint8_t)(0xFF)
#define TIMER_COUNTER1_LOWER_LIMIT (uint8_t)(0x00)
#define TIMER_COUNTER1_UPPER_LIMIT (uint8_t)(0x0F)
#define READ_LOWER_LIMIT           (uint16_t)(0)
#define READ_UPPER_LIMIT           (uint16_t)(260)

// Detection bit clear mask
#define DETECTION_BIT_CLEAR_MASK (uint8_t)(0x00)

#define SEND_BUFFER_IS_FULL    (0)
#define CURRENT_TIME_BYTE_SIZE (7)

// Return value
#define PROCESSING_OK                (0x00)
#define E_SEND_BUFFER_OVERFLOW       (0xE1)
#define E_RECEIVE_NACK_ADDRESS       (0xE2)
#define E_RECEIVE_NACK_DATA          (0xE3)
#define E_OTHER_ERROR                (0xE4)
#define E_I2C_TIME_OUT               (0xE5)
#define E_SEND_BUFFER_IS_FULL        (0xE6)
#define E_NO_RECEIVED_DATA           (0xE7)
#define E_READ_SIZE_OUT_OF_RANGE     (0xE8)
#define E_TIME_SEC_OUT_OF_RANGE      (0xE9)
#define E_TIME_MIN_OUT_OF_RANGE      (0xEA)
#define E_TIME_HOUR_OUT_OF_RANGE     (0xEB)
#define E_DATE_YEAR_OUT_OF_RANGE     (0xEC)
#define E_DATE_MONTH_OUT_OF_RANGE    (0xED)
#define E_DATE_DAY_OUT_OF_RANGE      (0xEE)
#define E_DATE_WEEK_OUT_OF_RANGE     (0xEF)
#define E_INVALID_ARGUMENT           (0xF0)
#define E_TARGET_DATA_OUT_OF_RANGE   (0xF1)
#define E_INVALID_REGISTER_ADDRESS   (0xF2)
#define E_EXTENSION_REGISTER_TE_SET1 (0xF3)
#define E_CONTROL_REGISTER_UIE_SET1  (0xF4)
#define E_CONTROL_REGISTER_AIE_SET1  (0xF5)


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//	Struct  Union
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
typedef struct Sec
{
	uint8_t sec1     : 1;	/* LSB */
	uint8_t sec2     : 1;
	uint8_t sec4     : 1;
	uint8_t sec8     : 1;
	uint8_t sec10    : 1;
	uint8_t sec20    : 1;
	uint8_t sec40    : 1;
	uint8_t reserved : 1;	/* MSB */
} Sec_t;


typedef struct Min
{
	uint8_t min1     : 1;	/* LSB */
	uint8_t min2     : 1;
	uint8_t min4     : 1;
	uint8_t min8     : 1;
	uint8_t min10    : 1;
	uint8_t min20    : 1;
	uint8_t min40    : 1;
	uint8_t reserved : 1;	/* MSB */
} Min_t;


typedef struct Hour
{
	uint8_t hour1    : 1;	/* LSB */
	uint8_t hour2    : 1;
	uint8_t hour4    : 1;
	uint8_t hour8    : 1;
	uint8_t hour10   : 1;
	uint8_t hour20   : 1;
	uint8_t reserved : 2;	/* MSB */
} Hour_t;


typedef struct Week
{
	uint8_t sunday    : 1;	/* LSB */
	uint8_t monday    : 1;
	uint8_t tuesday   : 1;
	uint8_t wednesday : 1;
	uint8_t thursday  : 1;
	uint8_t friday    : 1;
	uint8_t saturday  : 1;
	uint8_t reserved  : 1;	/* MSB */
} Week_t;


typedef struct Day
{
	uint8_t day1     : 1;	/* LSB */
	uint8_t day2     : 1;
	uint8_t day4     : 1;
	uint8_t day8     : 1;
	uint8_t day10    : 1;
	uint8_t day20    : 1;
	uint8_t reserved : 2;	/* MSB */
} Day_t;


typedef struct Month
{
	uint8_t month1   : 1;	/* LSB */
	uint8_t month2   : 1;
	uint8_t month4   : 1;
	uint8_t month8   : 1;
	uint8_t month10  : 1;
	uint8_t reserved : 3;	/* MSB */
} Month_t;


typedef struct Year
{
	uint8_t year1  : 1;	/* LSB */
	uint8_t year2  : 1;
	uint8_t year4  : 1;
	uint8_t year8  : 1;
	uint8_t year10 : 1;
	uint8_t year20 : 1;
	uint8_t year40 : 1;
	uint8_t year80 : 1;	/* MSB */
} Year_t;


typedef struct MinAlarm
{
	uint8_t minAlarm1  : 1;	/* LSB */
	uint8_t minAlarm2  : 1;
	uint8_t minAlarm4  : 1;
	uint8_t minAlarm8  : 1;
	uint8_t minAlarm10 : 1;
	uint8_t minAlarm20 : 1;
	uint8_t minAlarm40 : 1;
	uint8_t AE         : 1;	/* MSB */
} MinAlarm_t;


typedef struct HourAlarm
{
	uint8_t hourAlarm1  : 1;	/* LSB */
	uint8_t hourAlarm2  : 1;
	uint8_t hourAlarm4  : 1;
	uint8_t hourAlarm8  : 1;
	uint8_t hourAlarm10 : 1;
	uint8_t hourAlarm20 : 1;
	uint8_t reserved    : 1;
	uint8_t AE          : 1;	/* MSB */
} HourAlarm_t;


typedef struct WeekAlarm
{
	uint8_t sunday    : 1;	/* LSB */
	uint8_t monday    : 1;
	uint8_t tuesday   : 1;
	uint8_t wednesday : 1;
	uint8_t thursday  : 1;
	uint8_t friday    : 1;
	uint8_t saturday  : 1;
	uint8_t AE        : 1;	/* MSB */
} WeekAlarm_t;


typedef struct DayAlarm
{
	uint8_t dayAlarm1  : 1;	/* LSB */
	uint8_t dayAlarm2  : 1;
	uint8_t dayAlarm4  : 1;
	uint8_t dayAlarm8  : 1;
	uint8_t dayAlarm10 : 1;
	uint8_t dayAlarm20 : 1;
	uint8_t ramArea    : 1;
	uint8_t AE         : 1;	/* MSB */
} DayAlarm_t;


typedef struct TimerCounter0
{
	uint8_t timerCounter1   : 1;	/* LSB */
	uint8_t timerCounter2   : 1;
	uint8_t timerCounter4   : 1;
	uint8_t timerCounter8   : 1;
	uint8_t timerCounter16  : 1;
	uint8_t timerCounter32  : 1;
	uint8_t timerCounter64  : 1;
	uint8_t timerCounter128 : 1;	/* MSB */
} TimerCounter0_t;


typedef struct TimerCounter1
{
	uint8_t timerCounter256  : 1;	/* LSB */
	uint8_t timerCounter512  : 1;
	uint8_t timerCounter1024 : 1;
	uint8_t timerCounter2048 : 1;
	uint8_t ramArea          : 4;	/* MSB */
} TimerCounter1_t;


typedef struct Temp
{
	uint8_t temp1   : 1;	/* LSB */
	uint8_t temp2   : 1;
	uint8_t temp4   : 1;
	uint8_t temp8   : 1;
	uint8_t temp16  : 1;
	uint8_t temp32  : 1;
	uint8_t temp64  : 1;
	uint8_t temp128 : 1;	/* MSB */
} Temp_t;


typedef struct BackupFunction
{
	uint8_t BKSMP0   : 1;	/* LSB */
	uint8_t BKSMP1   : 1;
	uint8_t SWOFF    : 1;
	uint8_t VDETOFF  : 1;
	uint8_t reserved : 4;	/* MSB */
} BackupFunction_t;


typedef struct Extension
{
	uint8_t TSEL0 : 1;	/* LSB */
	uint8_t TSEL1 : 1;
	uint8_t FSEL0 : 1;
	uint8_t FSEL1 : 1;
	uint8_t TE    : 1;
	uint8_t USEL  : 1;
	uint8_t WADA  : 1;
	uint8_t TEST  : 1;	/* MSB */
} Extension_t;


typedef struct Flag
{
	uint8_t VDET      : 1;	/* LSB */
	uint8_t VLF       : 1;
	uint8_t reserved0 : 1;
	uint8_t AF        : 1;
	uint8_t TF        : 1;
	uint8_t UF        : 1;
	uint8_t reserved1 : 2;	/* MSB */
} Flag_t;


typedef struct Control
{
	uint8_t RESET    : 1;	/* LSB */
	uint8_t reserved : 2;
	uint8_t AIE      : 1;
	uint8_t TIE      : 1;
	uint8_t UIE      : 1;
	uint8_t CSEL0    : 1;
	uint8_t CSEL1    : 1;	/* MSB */
} Control_t;


typedef union WeekDayAlarm
{
	WeekAlarm_t weekAlarm;
	DayAlarm_t  dayAlarm;
} WeekDayAlarm_t;


typedef struct CoRegisterTable
{
	Sec_t sec;
	Min_t min;
	Hour_t hour;
	Week_t week;
	Day_t day;
	Month_t month;
	Year_t year;
	uint8_t ram;
	MinAlarm_t minAlarm;
	HourAlarm_t hourAlarm;
	WeekDayAlarm_t weekDayAlarm;
	TimerCounter0_t timerCounter0;
	TimerCounter1_t timerCounter1;
	Extension_t extension;
	Flag_t flag;
	Control_t control;
} CoRegisterTable_t;


typedef struct ExRegisterTable
{
	Sec_t sec;
	Min_t min;
	Hour_t hour;
	Week_t week;
	Day_t day;
	Month_t month;
	Year_t year;
	Temp_t temp;
	BackupFunction_t backupFunction;
	uint8_t reserved[2];
	TimerCounter0_t timerCounter0;
	TimerCounter1_t timerCounter1;
	Extension_t extension;
	Flag_t flag;
	Control_t control;
} ExRegisterTable_t;


typedef struct RegisterTable
{
	CoRegisterTable_t crt;
	ExRegisterTable_t ert;
} RegisterTable_t;


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//	Enum
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
typedef enum CoRegisterTableAddress
{
	/* Compatiable register table */
	SEC_COMPATIBLE_REGISTER_ADDRESS = 0x00,
	MIN_COMPATIBLE_REGISTER_ADDRESS,
	HOUR_COMPATIBLE_REGISTER_ADDRESS,
	WEEK_COMPATIBLE_REGISTER_ADDRESS,
	DAY_COMPATIBLE_REGISTER_ADDRESS,
	MONTH_COMPATIBLE_REGISTER_ADDRESS,
	YEAR_COMPATIBLE_REGISTER_ADDRESS,
	RAM_COMPATIBLE_REGISTER_ADDRESS,
	MIN_ALARM_COMPATIBLE_REGISTER_ADDRESS,
	HOUR_ALARM_COMPATIBLE_REGISTER_ADDRESS,
	WEEK_DAY_ALARM_COMPATIBLE_REGISTER_ADDRESS,
	TIMER_COUNTER0_COMPATIBLE_REGISTER_ADDRESS,
	TIMER_COUNTER1_COMPATIBLE_REGISTER_ADDRESS,
	EXTENSION_COMPATIBLE_REGISTER_ADDRESS,
	FLAG_COMPATIBLE_REGISTER_ADDRESS,
	CONTROL_COMPATIBLE_REGISTER_ADDRESS,
	COMPATIBLE_REGISTER_ADDRESS_MAX
} CoRegisterTableAddress_t;


typedef enum ExRegisterTableAddress
{
	/* Expansion register table */
	SEC_EXPANSION_REGISTER_ADDRESS = 0x10,
	MIN_EXPANSION_REGISTER_ADDRESS,
	HOUR_EXPANSION_REGISTER_ADDRESS,
	WEEK_EXPANSION_REGISTER_ADDRESS,
	DAY_EXPANSION_REGISTER_ADDRESS,
	MONTH_EXPANSION_REGISTER_ADDRESS,
	YEAR_EXPANSION_REGISTER_ADDRESS,
	TEMP_EXPANSION_REGISTER_ADDRESS,
	BACKUP_FUNCTION_EXPANSION_REGISTER_ADDRESS,
	NOT_USE0_EXPANSION_REGISTER_ADDRESS,
	NOT_USE1_EXPANSION_REGISTER_ADDRESS,
	TIMER_COUNTER0_EXPANSION_REGISTER_ADDRESS,
	TIMER_COUNTER1_EXPANSION_REGISTER_ADDRESS,
	EXTENSION_EXPANSION_REGISTER_ADDRESS,
	FLAG_EXPANSION_REGISTER_ADDRESS,
	CONTROL_EXPANSION_REGISTER_ADDRESS,
	EXPANSION_REGISTER_ADDRESS_MAX
} ExRegisterTableAddress_t;


typedef enum RegisterTableField
{
	/* CoRegisterTableField */
	CO_SEC_FIELD = 0x00,
	CO_MIN_FIELD,
	CO_HOUR_FIELD,
	CO_WEEK_FIELD,
	CO_DAY_FIELD,
	CO_MONTH_FIELD,
	CO_YEAR_FIELD,
	CO_RAM_FIELD,
	CO_MIN_ALARM_FIELD,
	CO_HOUR_ALARM_FIELD,
	CO_WEEK_DAY_ALARM_FIELD,
	CO_TIMER_COUNTER0_FIELD,
	CO_TIMER_COUNTER1_FIELD,
	CO_EXTENSION_FIELD,
	CO_FLAG_FIELD,
	CO_CONTROL_FIELD,

	/* ExRegisterTableField */
	EX_SEC_FIELD,
	EX_MIN_FIELD,
	EX_HOUR_FIELD,
	EX_WEEK_FIELD,
	EX_DAY_FIELD,
	EX_MONTH_FIELD,
	EX_YEAR_FIELD,
	EX_TEMP_FIELD,
	EX_BACKUP_FUNCTION_FIELD,
	EX_RESERVED0_FIELD,
	EX_RESERVED1_FIELD,
	EX_TIMER_COUNTER0_FIELD,
	EX_TIMER_COUNTER1_FIELD,
	EX_EXTENSION_FIELD,
	EX_FLAG_FIELD,
	EX_CONTROL_FIELD,

	FIELD_MAX
} RegisterTableField_t;


typedef enum weekRegisterTable
{
	/* Week register table */
	SUNDAY = 0x00,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	WEEK_MAX
} weekRegisterTable_t;


typedef enum bitNumTable
{
	/* Bit number table */
	RX8900_BIT0 = 0x00,
	RX8900_BIT1,
	RX8900_BIT2,
	RX8900_BIT3,
	RX8900_BIT4,
	RX8900_BIT5,
	RX8900_BIT6,
	RX8900_BIT7,
	RX8900_BIT_MAX
} bitNumTable_t;


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//
//	Class
//
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
class RX8900
{
	public:
		/* Constructor */
		RX8900();
		
		/* Destructor */
		~RX8900();
		
		/* Getter method */
		void GetAllData(RegisterTable_t*, bool);
		void GetCoData(CoRegisterTable_t*, bool);
		void GetExData(ExRegisterTable_t*, bool);

		/* Initialization operation method */
		void RX8900Init(void);

		/* Conversion method */
		uint8_t GetAnyBit(uint8_t, uint8_t);
		float ConvertTempValue(uint8_t);

		/* Determine method */
		uint8_t JudgeInterruptSignalType(uint8_t*);

		/* Register parameter individual setting method */
		uint8_t WDRegisterRoleChange(bool);
		uint8_t UpdateInterruptTimingChange(bool);
		uint8_t OutputFrequencyChange(bool, bool);
		uint8_t CountdownCycleChange(bool, bool);
		uint8_t ClearOccurrenceNotification(bool, bool, bool);
		uint8_t ClearVoltageNotification(bool, bool);
		uint8_t CompensationIntervalChange(bool, bool);
		uint8_t InterruptSettings(bool, bool, bool);
		uint8_t ResetSubSecondCounter(void);
		uint8_t VoltageDetectionCircuitSettings(bool);
		uint8_t PMosSwitchSettings(bool);
		uint8_t VoltageDetectionMethodChange(bool, bool);

		/* Timer counter operation methods */
		uint8_t TimerCountDownStart(void);
		uint8_t TimerCountDownStop(void);

		/* Register write method */
		uint8_t WriteTimeRegisters(uint8_t, uint8_t, uint8_t);
		uint8_t WriteDateRegisters(uint8_t, uint8_t, uint8_t, uint8_t);
		uint8_t WriteAllCoRegisters(uint8_t*);
		uint8_t WriteAllExRegisters(uint8_t*);
		uint8_t WriteSecRegister(uint8_t, bool);
		uint8_t WriteMinRegister(uint8_t, bool);
		uint8_t WriteHourRegister(uint8_t, bool);
		uint8_t WriteWeekRegister(uint8_t, bool);
		uint8_t WriteDayRegister(uint8_t, bool);
		uint8_t WriteMonthRegister(uint8_t, bool);
		uint8_t WriteYearRegister(uint8_t, bool);
		uint8_t WriteRamRegister(uint8_t);
		uint8_t WriteBackupFunctionRegister(uint8_t);
		uint8_t WriteMinAlarmRegister(uint8_t, bool);
		uint8_t WriteHourAlarmRegister(uint8_t, bool);
		uint8_t WriteWeekDayAlarmRegister(uint8_t, bool);
		uint8_t WriteTimerCounter(uint16_t);
		uint8_t WriteTimerCounter0Register(uint8_t, bool);
		uint8_t WriteTimerCounter1Register(uint8_t, bool);
		uint8_t WriteExtensionRegister(uint8_t, bool);
		uint8_t WriteFlagRegister(uint8_t, bool);
		uint8_t WriteControlRegister(uint8_t, bool);

		/* Register read method */
		uint8_t ReadAllRegisters(void);
		uint8_t ReadCurrentTime(void);
		uint8_t ReadSecRegister(bool);
		uint8_t ReadMinRegister(bool);
		uint8_t ReadHourRegister(bool);
		uint8_t ReadWeekRegister(bool);
		uint8_t ReadDayRegister(bool);
		uint8_t ReadMonthRegister(bool);
		uint8_t ReadYearRegister(bool);
		uint8_t ReadRamRegister(void);
		uint8_t ReadMinAlarmRegister(void);
		uint8_t ReadHourAlarmRegister(void);
		uint8_t ReadWeekDayAlarmRegister(void);
		uint8_t ReadTempRegister(void);
		uint8_t ReadBackupFunctionRegister(void);
		uint8_t ReadTimerCounter0Register(bool);
		uint8_t ReadTimerCounter1Register(bool);
		uint8_t ReadExtensionRegister(bool);
		uint8_t ReadFlagRegister(bool);
		uint8_t ReadControlRegister(bool);

		/* Overload method */
		void GetAllData(uint8_t*, bool);
		void GetCoData(uint8_t*, bool);
		void GetExData(uint8_t*, bool);
		uint8_t WriteSecRegister(uint8_t);
		uint8_t WriteMinRegister(uint8_t);
		uint8_t WriteHourRegister(uint8_t);
		uint8_t WriteWeekRegister(uint8_t);
		uint8_t WriteDayRegister(uint8_t);
		uint8_t WriteMonthRegister(uint8_t);
		uint8_t WriteYearRegister(uint8_t);
		uint8_t WriteMinAlarmRegister(uint8_t);
		uint8_t WriteHourAlarmRegister(uint8_t);
		uint8_t WriteWeekDayAlarmRegister(uint8_t);
		uint8_t WriteTimerCounter0Register(uint8_t);
		uint8_t WriteTimerCounter1Register(uint8_t);
		uint8_t WriteExtensionRegister(uint8_t);
		uint8_t WriteFlagRegister(uint8_t);
		uint8_t WriteControlRegister(uint8_t);
		uint8_t ReadSecRegister(void);
		uint8_t ReadMinRegister(void);
		uint8_t ReadHourRegister(void);
		uint8_t ReadWeekRegister(void);
		uint8_t ReadDayRegister(void);
		uint8_t ReadMonthRegister(void);
		uint8_t ReadYearRegister(void);
		uint8_t ReadTimerCounter0Register(void);
		uint8_t ReadTimerCounter1Register(void);
		uint8_t ReadExtensionRegister(void);
		uint8_t ReadFlagRegister(void);
		uint8_t ReadControlRegister(void);

	private:
		/* Register value */
		RegisterTable_t rtValue;

		/* Register operation method */
		uint8_t WriteCalendarRegister(uint8_t, uint8_t, uint8_t, bool);
		uint8_t ReadCalendarRegister(uint8_t, uint8_t);

		/* Format data method */
		uint8_t FormatSelectData(uint8_t, uint8_t*, bool);
		void FormatTimeData(uint8_t, uint8_t*);
		void FormatWeekData(uint8_t*);
		void FormatCalendarValue(uint8_t, uint8_t*);

		/* I2C communication method */
		uint8_t WriteData(uint8_t, const uint16_t, uint8_t*);
		uint8_t ReadData(uint8_t, const uint16_t, uint8_t*);

		/* Instance manipulation methods */
		void SetInstanceField(uint8_t, uint8_t);
};

#endif	/* RX8900_H */
