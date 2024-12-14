/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Source file name
//            RX8900.cpp
//(2)Note
//            This library supports RTC of RX8900x series.
//(3)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

#include <string.h>
#include "RX8900.h"


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            RX8900 [Public]
//(2)Process
//            Setting initial values
//(3)Argument
//            none
//(4)Return
//            none
//(5)Note
//            Constructor
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
	
RX8900::RX8900()
{
	/* do nothing */
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            RX8900 [Public]
//(2)Process
//            none
//(3)Argument
//            none
//(4)Return
//            none
//(5)Note
//            Destructor
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

RX8900::~RX8900()
{
	/* do nothing */
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            GetAllData [Public]
//(2)Process
//            Copies the contents of the compatibility and extension registers to the
//            argument address.
//(3)Argument
//            allTable	Destination address
//(4)Return
//            none
//(5)Note
//            Getter method
//            Compatible registers and extended registers are the same except for
//            some registers.
//            Please refer to the data sheet for details.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::GetAllData(RegisterTable_t *allTable, bool isFormat)
{
	GetAllData((uint8_t*)allTable, isFormat);

	return;
}

void RX8900::GetAllData(uint8_t *allTable, bool isFormat)
{
	(void)memcpy(allTable, &this->rtValue.crt, sizeof(RegisterTable_t));

	if(isFormat)
	{
		for(uint8_t formatLoop = CO_SEC_FIELD; formatLoop < CURRENT_TIME_BYTE_SIZE; formatLoop++)
		{
			FormatCalendarValue(formatLoop, allTable);
			*(allTable + 16) = *allTable;
			allTable++;
		}
	}
	else
	{
		/* do nothing */
	}

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            GetCoData [Public]
//(2)Process
//            Copies the contents of the compatibility registers to the argument address.
//(3)Argument
//            coTable	Destination address
//(4)Return
//            none
//(5)Note
//            Getter method
//            Compatible registers and extended registers are the same except for
//            some registers.
//            Please refer to the data sheet for details.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::GetCoData(CoRegisterTable_t* coTable, bool isFormat)
{
	GetCoData((uint8_t*)coTable, isFormat);

	return;
}

void RX8900::GetCoData(uint8_t* coTable, bool isFormat)
{
	(void)memcpy(coTable, &this->rtValue.crt, sizeof(CoRegisterTable_t));

	if(isFormat)
	{
		for(uint8_t formatLoop = CO_SEC_FIELD; formatLoop < CURRENT_TIME_BYTE_SIZE; formatLoop++)
		{
			FormatCalendarValue(formatLoop, coTable);
			coTable++;
		}
	}
	else
	{
		/* do nothing */
	}

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            GetExData [Public]
//(2)Process
//            Copies the contents of the extension registers to the argument address.
//(3)Argument
//            exTable	Destination address
//(4)Return
//            none
//(5)Note
//            Getter method
//            Compatible registers and extended registers are the same except for
//            some registers.
//            Please refer to the data sheet for details.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::GetExData(ExRegisterTable_t* exTable, bool isFormat)
{
	GetExData((uint8_t*)exTable, isFormat);

	return;
}

void RX8900::GetExData(uint8_t* exTable, bool isFormat)
{
	(void)memcpy(exTable, &this->rtValue.ert, sizeof(ExRegisterTable_t));

	if(isFormat)
	{
		for(uint8_t formatLoop = EX_SEC_FIELD; formatLoop < CURRENT_TIME_BYTE_SIZE; formatLoop++)
		{
			FormatCalendarValue(formatLoop, exTable);
			exTable++;
		}
	}
	else
	{
		/* do nothing */
	}

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            GetAnyBit [Public]
//(2)Process
//            Returns the value of the specified bit position in the data given as
//            an argument.
//(3)Argument
//            data		Any 1 byte of data.
//            bitNum	Specify a bit number in the range 0 to 7.
//(4)Return
//            retValue				Bit data at the specified position.
//            E_INVALID_ARGUMENT	Returns if the argument is invalid.
//(5)Note
//            Provide the data read from a register.
//            For example, if you want to get the value of the "AF" bit in the
//            flag register, specify the return value of the "ReadFlagRegister" method
//            in "data" and specify "3" in "bitNum".
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::GetAnyBit(uint8_t data, uint8_t bitNum)
{
	uint8_t retValue;

	if(bitNum >= RX8900_BIT0 && bitNum <= RX8900_BIT7)
	{
		retValue = (data >> bitNum) & 0x01u;
	}
	else
	{
		retValue = E_INVALID_ARGUMENT;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            RX8900Init [Public]
//(2)Process
//            Write the initial value to each register.
//(3)Argument
//            none
//(4)Return
//            none
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::RX8900Init()
{
	uint8_t initValue[] = 
	{
		DEFAULT_SEC_REGISTER_VALUE,
		DEFAULT_MIN_REGISTER_VALUE,
		DEFAULT_HOUR_REGISTER_VALUE,
		DEFAULT_WEEK_REGISTER_VALUE,
		DEFAULT_DAY_REGISTER_VALUE,
		DEFAULT_MONTH_REGISTER_VALUE,
		DEFAULT_YEAR_REGISTER_VALUE,
		DEFAULT_RAM_REGISTER_VALUE,
		DEFAULT_MIN_ALARM_REGISTER_VALUE,
		DEFAULT_HOUR_ALARM_REGISTER_VALUE,
		DEFAULT_WEEK_DAY_ALARM_REGISTER_VALUE,
		DEFAULT_TIMER_COUNTER0_REGISTER_VALUE,
		DEFAULT_TIMER_COUNTER1_REGISTER_VALUE,
		DEFAULT_EXTENSION_REGISTER_VALUE,
		DEFAULT_FLAG_REGISTER_VALUE,
		DEFAULT_CONTROL_REGISTER_VALUE
	};

	(void)WriteAllCoRegisters(&initValue[0]);
	(void)WriteBackupFunctionRegister(DEFAULT_BACKUP_FUNCTION_REGISTER_VALUE);

	(void)ReadAllRegisters();

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ConvertTempValue [Public]
//(2)Process
//            Converts the value read from the TEMP register to an actual temperature.
//(3)Argument
//            targetValue	Specifies the value read from the "TEMP" register.
//(4)Return
//            retValue		Actual temperature.
//(5)Note
//            The value read from the TEMP register must be converted to an actual
//            temperature by this method.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

float RX8900::ConvertTempValue(uint8_t targetValue)
{
	float retValue;

	retValue = TEMP_CONVERSION_FORMULA(targetValue);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            JudgeInterruptSignalType [Public]
//(2)Process
//            The type of interrupt that occurred is stored in the argument "getFlagType".
//(3)Argument
//            getFlagType	Stores the type of interrupt that occurred.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            If "UF" changes from 0 to 1, bit2 of "getFlagType" is set to 1.
//            If "TF" changes from 0 to 1, bit1 of "getFlagType" is set to 1.
//            If "AF" changes from 0 to 1, bit0 of "getFlagType" is set to 1.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::JudgeInterruptSignalType(uint8_t *getFlagType)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t tempBuffer;

	tempBuffer = this->rtValue.crt.flag.UF;
	tempBuffer = (tempBuffer << 0x01u) | this->rtValue.crt.flag.TF;
	tempBuffer = (tempBuffer << 0x01u) | this->rtValue.crt.flag.AF;
	tempBuffer &= 0x07u;
	readBuffer = ReadFlagRegister();

	if(retValue == PROCESSING_OK)
	{
		readBuffer = this->rtValue.crt.flag.UF;
		readBuffer = (tempBuffer << 0x01u) | this->rtValue.crt.flag.TF;
		readBuffer = (tempBuffer << 0x01u) | this->rtValue.crt.flag.AF;
		readBuffer &= 0x07u;
		*getFlagType = (tempBuffer ^ readBuffer) & 0x07u;
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WDRegisterRoleChange [Public]
//(2)Process
//            Change the "WADA" bit in the "Extension" register.
//(3)Argument
//            wadaValid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_CONTROL_REGISTER_AIE_SET1	Returned when the AIE bit in the "Control" 
//                                        	register is set to 1.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "WADA" bit is 0, the week-day alarm register is treated as
//            the week alarm register.
//            When the "WADA" bit is 1, the week-day alarm register is treated as
//            the day alarm register.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WDRegisterRoleChange(bool wadaValid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	if(this->rtValue.crt.control.AIE == 0x00u)
	{
		extensionBuffer = this->rtValue.crt.extension;
		extensionBuffer.WADA = (uint8_t)wadaValid;
		(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

		retValue = WriteExtensionRegister(tempBuffer);
	}
	else
	{
		retValue = E_CONTROL_REGISTER_AIE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            UpdateInterruptTimingChange [Public]
//(2)Process
//            Change the "USEL" bit in the "Extension" register.
//(3)Argument
//            uselValid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_CONTROL_REGISTER_UIE_SET1	Returned when the UIE bit in the "Control" 
//                                        	register is set to 1.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "USEL" bit is 0, the time update interrupt updates every second.
//            When the "USEL" bit is 1, the time update interrupt will update every minute.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::UpdateInterruptTimingChange(bool uselValid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	if(this->rtValue.crt.control.UIE == 0x00u)
	{
		extensionBuffer = this->rtValue.crt.extension;
		extensionBuffer.USEL = (uint8_t)uselValid;
		(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

		retValue = WriteExtensionRegister(tempBuffer);
	}
	else
	{
		retValue = (uint8_t)E_CONTROL_REGISTER_UIE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            OutputFrequencyChange [Public]
//(2)Process
//            Change the "FSEL0" and "FSEL1" bit in the "Extension" register.
//(3)Argument
//            fsel0Valid		Specify the rewritten value.
//            fsel1Valid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "FSEL0" bit is 0 and "FSEL1" bit is 0, The output frequency will be 32.768kHz.
//            When the "FSEL0" bit is 0 and "FSEL1" bit is 1, The output frequency will be 1Hz.
//            When the "FSEL0" bit is 1 and "FSEL1" bit is 0, The output frequency will be 1,024kHz.
//            When the "FSEL0" bit is 1 and "FSEL1" bit is 1, The output frequency will be 32.768kHz.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::OutputFrequencyChange(bool fsel0Valid, bool fsel1Valid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	extensionBuffer = this->rtValue.crt.extension;
	extensionBuffer.FSEL0 = (uint8_t)fsel0Valid;
	extensionBuffer.FSEL1 = (uint8_t)fsel1Valid;
	(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

	retValue = WriteExtensionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            CountdownCycleChange [Public]
//(2)Process
//            Change the "TSEL0" and "TSEL1" bit in the "Extension" register.
//(3)Argument
//            tsel0Valid		Specify the rewritten value.
//            tsel1Valid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_EXTENSION_REGISTER_TE_SET1	Returned when the TE bit in the "Extension" 
//                                        	register is set to 1.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "TSEL0" bit is 0 and "TSEL1" bit is 0, The countdown cycle will be 244.14 us.
//            When the "TSEL0" bit is 0 and "TSEL1" bit is 1, The countdown cycle will be 1 s.
//            When the "TSEL0" bit is 1 and "TSEL1" bit is 0, The countdown cycle will be 15.625 ms.
//            When the "TSEL0" bit is 1 and "TSEL1" bit is 1, The countdown cycle will be 1 min.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::CountdownCycleChange(bool tsel0Valid, bool tsel1Valid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	if(this->rtValue.crt.extension.TE == 0x00u)
	{
		extensionBuffer = this->rtValue.crt.extension;
		extensionBuffer.TSEL0 = (uint8_t)tsel0Valid;
		extensionBuffer.TSEL1 = (uint8_t)tsel1Valid;
		(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

		retValue = WriteExtensionRegister(tempBuffer);
	}
	else
	{
		retValue = (uint8_t)E_EXTENSION_REGISTER_TE_SET1;
	}


	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            TimerCountDownStart [Public]
//(2)Process
//            Change the "TE" bit in the "Extension" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            Calling this method will cause the timer to start counting down.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::TimerCountDownStart()
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	extensionBuffer = this->rtValue.crt.extension;
	extensionBuffer.TE = (uint8_t)0x01u;
	(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

	retValue = WriteExtensionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            TimerCountDownStop [Public]
//(2)Process
//            Change the "TE" bit in the "Extension" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            Calling this method stops the timer from counting down.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::TimerCountDownStop()
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Extension_t extensionBuffer;

	extensionBuffer = this->rtValue.crt.extension;
	extensionBuffer.TE = (uint8_t)0x00u;
	(void)memcpy(&tempBuffer, &extensionBuffer, sizeof(Extension_t));

	retValue = WriteExtensionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ClearOccurrenceNotification [Public]
//(2)Process
//            Clear the "AF", "TF" and "UF" bit in the "Flag" register.
//(3)Argument
//            alarmNotifyClear		Specify "true" if you want to clear the "AF" bit.
//            timerNotifyClear		Specify "true" if you want to clear the "TF" bit.
//            updateNotifyClear		Specify "true" if you want to clear the "UF" bit.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            The "AF" bit is set to 1 when an alarm occurs.
//            To clear the alarm, the “AF” bit must be cleared.
//            The "TF" bit is set to 1 when the timer reaches 0.
//            The interrupt signal will return automatically, but you can also return it
//            immediately by clearing the "TF" bit to 0.
//            The "UF" bit is set to 1 when the time update has finished.
//            The interrupt signal will return automatically, but you can also return it
//            immediately by clearing the "UF" bit to 0.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ClearOccurrenceNotification(bool alarmNotifyClear, bool timerNotifyClear, bool updateNotifyClear)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Flag_t flagBuffer;

	flagBuffer = this->rtValue.crt.flag;

	if(alarmNotifyClear)
	{
		flagBuffer.AF = DETECTION_BIT_CLEAR_MASK;
	}
	else
	{
		/* do nothing */
	}

	if(timerNotifyClear)
	{
		flagBuffer.TF = DETECTION_BIT_CLEAR_MASK;
	}
	else
	{
		/* do nothing */
	}

	if(updateNotifyClear)
	{
		flagBuffer.UF = DETECTION_BIT_CLEAR_MASK;
	}
	else
	{
		/* do nothing */
	}

	(void)memcpy(&tempBuffer, &flagBuffer, sizeof(Flag_t));

	retValue = WriteFlagRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ClearVoltageNotification [Public]
//(2)Process
//            Clear the "VLF" and "VDET" bit in the "Flag" register.
//(3)Argument
//            lowNotifyClear		Specify "true" if you want to clear the "VLF" bit.
//            detectNotifyClear		Specify "true" if you want to clear the "VDET" bit.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            The "VLF" bit is set to 1 when a drop in the power supply voltage 
//            forthe oscillator circuit is detected.
//            The "VDET" bit is set to 1 if the temperature compensation operation
//            may have stopped.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ClearVoltageNotification(bool lowNotifyClear, bool detectNotifyClear)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Flag_t flagBuffer;

	flagBuffer = this->rtValue.crt.flag;

	if(lowNotifyClear)
	{
		flagBuffer.VLF = DETECTION_BIT_CLEAR_MASK;
	}
	else
	{
		/* do nothing */
	}

	if(detectNotifyClear)
	{
		flagBuffer.VDET = DETECTION_BIT_CLEAR_MASK;
	}
	else
	{
		/* do nothing */
	}

	(void)memcpy(&tempBuffer, &flagBuffer, sizeof(Flag_t));

	retValue = WriteFlagRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            CompensationIntervalChange [Public]
//(2)Process
//            Change the "CSEL0" and "CSEL1" bit in the "Control" register.
//(3)Argument
//            csel0Valid		Specify the rewritten value.
//            csel1Valid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "CSEL0" bit is 0 and "CSEL1" bit is 0, The compensation interval will be 0.5 seconds.
//            When the "CSEL0" bit is 0 and "CSEL1" bit is 1, The compensation interval will be 10 seconds.
//            When the "CSEL0" bit is 1 and "CSEL1" bit is 0, The compensation interval will be 2.0 seconds.
//            When the "CSEL0" bit is 1 and "CSEL1" bit is 1, The compensation interval will be 30 seconds.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::CompensationIntervalChange(bool csel0Valid, bool csel1Valid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Control_t controlBuffer;

	controlBuffer = this->rtValue.crt.control;
	controlBuffer.CSEL0 = (uint8_t)csel0Valid;
	controlBuffer.CSEL1 = (uint8_t)csel1Valid;
	(void)memcpy(&tempBuffer, &controlBuffer, sizeof(Control_t));

	retValue = WriteControlRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            InterruptSettings [Public]
//(2)Process
//            Clear the "AIE", "TIE" and "UIE" bit in the "Control" register.
//(3)Argument
//            alarmInterrupt	Specify "true" to enable interrupts, or "false" to disable them.
//            timerInterrupt	Specify "true" to enable interrupts, or "false" to disable them.
//            updateInterrupt	Specify "true" to enable interrupts, or "false" to disable them.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            If the "AIE" bit is 1, an interrupt signal is output when an alarm occurs.
//            If the "TIE" bit is 1, an interrupt signal is output when the timer value becomes 0.
//            If the "UIE" bit is 1, an interrupt signal is output when the time is updated.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::InterruptSettings(bool alarmInterrupt, bool timerInterrupt, bool updateInterrupt)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Control_t controlBuffer;

	controlBuffer = this->rtValue.crt.control;
	controlBuffer.AIE = (uint8_t)alarmInterrupt;
	controlBuffer.TIE = (uint8_t)timerInterrupt;
	controlBuffer.UIE = (uint8_t)updateInterrupt;
	(void)memcpy(&tempBuffer, &controlBuffer, sizeof(Control_t));

	retValue = WriteControlRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ResetSubSecondCounter [Public]
//(2)Process
//            Set the "RESET" bit in the "Control" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            The sub-second counter of the Clock & Calendar circuit will be reset.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ResetSubSecondCounter()
{
	uint8_t retValue;
	uint8_t tempBuffer;
	Control_t controlBuffer;

	controlBuffer = this->rtValue.crt.control;
	controlBuffer.RESET = (uint8_t)0x01u;
	(void)memcpy(&tempBuffer, &controlBuffer, sizeof(Control_t));

	retValue = WriteControlRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            VoltageDetectionCircuitSettings [Public]
//(2)Process
//            Change the "VDETOFF" bit in the "Backup Function" register.
//(3)Argument
//            vdcValid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            Specify "true" to disable the voltage detection circuit, or "false" to enable it.
//            The current consumption can be reduced by disabling the voltage detection circuit.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::VoltageDetectionCircuitSettings(bool vdcValid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	BackupFunction_t backupFunctionBuffer;

	backupFunctionBuffer = this->rtValue.ert.backupFunction;
	backupFunctionBuffer.VDETOFF = (uint8_t)vdcValid;
	(void)memcpy(&tempBuffer, &backupFunctionBuffer, sizeof(BackupFunction_t));

	retValue = WriteBackupFunctionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            PMosSwitchSettings [Public]
//(2)Process
//            Change the "SWOFF" bit in the "Backup Function" register.
//(3)Argument
//            swValid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            If you want the PMOS switch to always be ON, specify "true".
//            If you want the PMOS switch to always be OFF, specify "false".
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::PMosSwitchSettings(bool swValid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	BackupFunction_t backupFunctionBuffer;

	backupFunctionBuffer = this->rtValue.ert.backupFunction;
	backupFunctionBuffer.SWOFF = (uint8_t)swValid;
	(void)memcpy(&tempBuffer, &backupFunctionBuffer, sizeof(BackupFunction_t));

	retValue = WriteBackupFunctionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            VoltageDetectionMethodChange [Public]
//(2)Process
//            Change the "BKSMP0" and "BKSMP1" bit in the "Backup Function" register.
//(3)Argument
//            bksmp0Valid		Specify the rewritten value.
//            bksmp1Valid		Specify the rewritten value.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            If you want to set it to 0, specify "false".
//            If you want to set it to 1, specify "true".
//            When the "BKSMP0" bit is 0 and "BKSMP1" bit is 0, these operate with
//            intermittent drive of 2 milliseconds.
//            When the "BKSMP0" bit is 0 and "BKSMP1" bit is 1, these operate with
//            intermittent drive of 128 milliseconds.
//            When the "BKSMP0" bit is 1 and "BKSMP1" bit is 0, these operate with
//            intermittent drive of 16 milliseconds.
//            When the "BKSMP0" bit is 1 and "BKSMP1" bit is 1, these operate with
//            intermittent drive of 256 milliseconds.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::VoltageDetectionMethodChange(bool bksmp0Valid, bool bksmp1Valid)
{
	uint8_t retValue;
	uint8_t tempBuffer;
	BackupFunction_t backupFunctionBuffer;

	backupFunctionBuffer = this->rtValue.ert.backupFunction;
	backupFunctionBuffer.BKSMP0 = (uint8_t)bksmp0Valid;
	backupFunctionBuffer.BKSMP1 = (uint8_t)bksmp1Valid;
	(void)memcpy(&tempBuffer, &backupFunctionBuffer, sizeof(BackupFunction_t));

	retValue = WriteBackupFunctionRegister(tempBuffer);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteTimeRegisters [Public]
//(2)Process
//            Write the value of the "SEC", "MIN" and "HOUR" registers.
//(3)Argument
//            hour		Specify the hour to write to the register.
//            min		Specify the minutes to write to the register.
//            sec		Specify the seconds to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_TIME_SEC_OUT_OF_RANGE	Returned when "SEC" is out of range.
//            E_TIME_MIN_OUT_OF_RANGE	Returned when "MIN" is out of range.
//            E_TIME_HOUR_OUT_OF_RANGE	Returned when "HOUR" is out of range.
//(5)Note
//            "hour" must be in the range 0 to 23.
//            "min" must be in the range 0 to 59.
//            "sec" must be in the range 0 to 59.
//            Providing a value outside the range will result in an error.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteTimeRegisters(uint8_t hour, uint8_t min, uint8_t sec)
{
	uint8_t retValue;
	bool isInvalid = false;

	if(HOUR_LOWER_LIMIT <= hour && hour <= HOUR_UPPER_LIMIT)
	{
		if(SEC_MIN_LOWER_LIMIT <= min && min <= SEC_MIN_UPPER_LIMIT)
		{
			if(SEC_MIN_LOWER_LIMIT <= sec && sec <= SEC_MIN_UPPER_LIMIT)
			{
				/* do nothing */
			}
			else
			{
				isInvalid = true;
				retValue = E_TIME_SEC_OUT_OF_RANGE;
			}
		}
		else
		{
			isInvalid = true;
			retValue = E_TIME_MIN_OUT_OF_RANGE;
		}
	}
	else
	{
		isInvalid = true;
		retValue = E_TIME_HOUR_OUT_OF_RANGE;
	}

	if(!isInvalid)
	{
		retValue = ResetSubSecondCounter();

		if(retValue == PROCESSING_OK)
		{
			retValue = WriteSecRegister(sec);

			if(retValue == PROCESSING_OK)
			{
				retValue = WriteMinRegister(min);

				if(retValue == PROCESSING_OK)
				{
					retValue = WriteHourRegister(hour);
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteDateRegisters [Public]
//(2)Process
//            Write the value of the "YEAR", "MONTH", "DAY" and "WEEK" registers.
//(3)Argument
//            year		Specify the year to write to the register.
//            month		Specify the month to write to the register.
//            day		Specify the day to write to the register.
//            week		Specify the week to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_DATE_YEAR_OUT_OF_RANGE		Returned when "YEAR" is out of range.
//            E_DATE_MONTH_OUT_OF_RANGE		Returned when "MONTH" is out of range.
//            E_DATE_DAY_OUT_OF_RANGE		Returned when "DAY" is out of range.
//            E_DATE_WEEK_OUT_OF_RANGE		Returned when "WEEK" is out of range.
//(5)Note
//            "year" must be in the range 0 to 99.
//            "month" must be in the range 1 to 12.
//            "day" must be in the range 1 to 31.
//            "week" must be in the range 0 to 6.
//            Providing a value outside the range will result in an error.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteDateRegisters(uint8_t year, uint8_t month, uint8_t day, uint8_t week)
{
	uint8_t retValue;
	bool isInvalid = false;

	if(YEAR_LOWER_LIMIT <= year && year <= YEAR_UPPER_LIMIT)
	{
		if(MONTH_LOWER_LIMIT <= month && month <= MONTH_UPPER_LIMIT)
		{
			if(DAY_LOWER_LIMIT <= day && day <= DAY_UPPER_LIMIT)
			{
				if(SUNDAY <= week && week <= SATURDAY)
				{
					/* do nothing */
				}
				else
				{
					isInvalid = true;
					retValue = E_DATE_WEEK_OUT_OF_RANGE;
				}
			}
			else
			{
				isInvalid = true;
				retValue = E_DATE_DAY_OUT_OF_RANGE;
			}
		}
		else
		{
			isInvalid = true;
			retValue = E_DATE_MONTH_OUT_OF_RANGE;
		}
	}
	else
	{
		isInvalid = true;
		retValue = E_DATE_YEAR_OUT_OF_RANGE;
	}

	if(!isInvalid)
	{
		retValue = WriteYearRegister(year);

		if(retValue == PROCESSING_OK)
		{
			retValue = WriteMonthRegister(month);

			if(retValue == PROCESSING_OK)
			{
				retValue = WriteDayRegister(day);

				if(retValue == PROCESSING_OK)
				{
					retValue = WriteWeekRegister(week);
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteAllCoRegisters [Public]
//(2)Process
//            Write the value of the all compatibility registers.
//(3)Argument
//            writeData		Specify the data to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteAllCoRegisters(uint8_t *writeData)
{
	uint8_t retValue;
	uint8_t *p_dest;
	const uint16_t writeSize = 16;
	uint8_t maskCoArray[] = {
		SEC_MIN_REGISTER_BIT_MASK,
		SEC_MIN_REGISTER_BIT_MASK,
		HOUR_REGISTER_BIT_MASK,
		WEEK_REGISTER_BIT_MASK,
		DAY_REGISTER_BIT_MASK,
		MONTH_REGISTER_BIT_MASK,
		YEAR_REGISTER_BIT_MASK,
		RAM_REGISTER_BIT_MASK,
		MIN_ALARM_REGISTER_BIT_MASK,
		HOUR_ALARM_REGISTER_BIT_MASK,
		WEEK_DAY__ALARM_REGISTER_BIT_MASK,
		TIMER_COUNTER0_REGISTER_BIT_MASK,
		TIMER_COUNTER1_REGISTER_BIT_MASK,
		EXTENSION_REGISTER_BIT_MASK,
		FLAG_REGISTER_BIT_MASK,
		CONTROL_REGISTER_BIT_MASK
	};

	for(uint8_t maskLoop = 0; maskLoop < writeSize; maskLoop++)
	{
		writeData[maskLoop] &= maskCoArray[maskLoop];
	}

	retValue = WriteData((uint8_t)SEC_COMPATIBLE_REGISTER_ADDRESS, writeSize, writeData);

	if(retValue == PROCESSING_OK)
	{
		p_dest = (uint8_t*)&this->rtValue.crt;

		for(uint8_t copyLoop = CO_SEC_FIELD; copyLoop < (CO_CONTROL_FIELD + 1); copyLoop++)
		{
			*p_dest++ = *writeData++;
		}
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteAllExRegisters [Public]
//(2)Process
//            Write the value of the all expansion registers.
//(3)Argument
//            writeData		Specify the data to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteAllExRegisters(uint8_t *writeData)
{
	uint8_t retValue;
	uint8_t *p_dest;
	const uint16_t writeSize = 16;
	uint8_t maskExArray[] = {
		SEC_MIN_REGISTER_BIT_MASK,
		SEC_MIN_REGISTER_BIT_MASK,
		HOUR_REGISTER_BIT_MASK,
		WEEK_REGISTER_BIT_MASK,
		DAY_REGISTER_BIT_MASK,
		MONTH_REGISTER_BIT_MASK,
		YEAR_REGISTER_BIT_MASK,
		TEMP_REGISTER_BIT_MASK,
		BACKUP_FUNCTION_REGISTER_BIT_MASK,
		NOT_USE0_REGISTER_BIT_MASK,
		NOT_USE1_REGISTER_BIT_MASK,
		TIMER_COUNTER0_REGISTER_BIT_MASK,
		TIMER_COUNTER1_REGISTER_BIT_MASK,
		EXTENSION_REGISTER_BIT_MASK,
		FLAG_REGISTER_BIT_MASK,
		CONTROL_REGISTER_BIT_MASK
	};

	for(uint8_t maskLoop = 0; maskLoop < writeSize; maskLoop++)
	{
		writeData[maskLoop] &= maskExArray[maskLoop];
	}

	retValue = WriteData((uint8_t)SEC_EXPANSION_REGISTER_ADDRESS, writeSize, writeData);

	if(retValue == PROCESSING_OK)
	{
		p_dest = (uint8_t*)&this->rtValue.ert;

		for(uint8_t copyLoop = EX_SEC_FIELD; copyLoop < (EX_CONTROL_FIELD + 1); copyLoop++)
		{
			*p_dest++ = *writeData++;
		}
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteSecRegister [Public]
//(2)Process
//            Write the value of the "SEC" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteSecRegister(uint8_t writeData)
{
	return WriteSecRegister(writeData, false);
}

uint8_t RX8900::WriteSecRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)SEC_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_SEC_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)SEC_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_SEC_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteMinRegister [Public]
//(2)Process
//            Write the value of the "MIN" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteMinRegister(uint8_t writeData)
{
	return WriteMinRegister(writeData, false);
}

uint8_t RX8900::WriteMinRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)MIN_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_MIN_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)MIN_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_MIN_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteHourRegister [Public]
//(2)Process
//            Write the value of the "HOUR" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteHourRegister(uint8_t writeData)
{
	return WriteHourRegister(writeData, false);
}

uint8_t RX8900::WriteHourRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)HOUR_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_HOUR_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)HOUR_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_HOUR_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteWeekRegister [Public]
//(2)Process
//            Write the value of the "WEEK" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            The numbers 0 to 6 specified in the argument correspond to the following
//            days of the week.
//                0 : Sunday
//                1 : Monday
//                2 : Tuesday
//                3 : Wednesday
//                4 : Thursday
//                5 : Friday
//                6 : Saturday
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteWeekRegister(uint8_t writeData)
{
	return WriteWeekRegister(writeData, false);
}

uint8_t RX8900::WriteWeekRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)WEEK_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_WEEK_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)WEEK_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_WEEK_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteDayRegister [Public]
//(2)Process
//            Write the value of the "DAY" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteDayRegister(uint8_t writeData)
{
	return WriteDayRegister(writeData, false);
}

uint8_t RX8900::WriteDayRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)DAY_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_DAY_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)DAY_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_DAY_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteMonthRegister [Public]
//(2)Process
//            Write the value of the "MONTH" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteMonthRegister(uint8_t writeData)
{
	return WriteMonthRegister(writeData, false);
}

uint8_t RX8900::WriteMonthRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)MONTH_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_MONTH_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)MONTH_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_MONTH_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteYearRegister [Public]
//(2)Process
//            Write the value of the "YEAR" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteYearRegister(uint8_t writeData)
{
	return WriteYearRegister(writeData, false);
}

uint8_t RX8900::WriteYearRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)YEAR_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_YEAR_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)YEAR_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_YEAR_FIELD;
	}

	retValue = WriteCalendarRegister(fieldType, writeAddress, writeData, false);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteRamRegister [Public]
//(2)Process
//            Write the value of the "RAM" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteRamRegister(uint8_t writeData)
{
	uint8_t retValue;
	const uint16_t writeSize = 1;

	retValue = WriteData((uint8_t)RAM_COMPATIBLE_REGISTER_ADDRESS, writeSize, &writeData);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField((uint8_t)CO_RAM_FIELD, writeData);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteBackupFunctionRegister [Public]
//(2)Process
//            Write the value of the "Backup Function" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteBackupFunctionRegister(uint8_t writeData)
{
	uint8_t retValue;
	const uint16_t writeSize = 1;

	writeData &= BACKUP_FUNCTION_REGISTER_BIT_MASK;

	retValue = WriteData((uint8_t)BACKUP_FUNCTION_EXPANSION_REGISTER_ADDRESS, writeSize, &writeData);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField((uint8_t)EX_BACKUP_FUNCTION_FIELD, writeData);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteMinAlarmRegister [Public]
//(2)Process
//            Write the value of the "MIN Alarm" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            aeValid		Specifies whether the "AE" bit in the alarm-related register
//                   		is set.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_CONTROL_REGISTER_AIE_SET1	Returned when the AIE bit in the "Control" 
//                                        	register is set to 1.
//(5)Note
//            If you do not want to generate an alarm, set "aeValid" to "true."
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteMinAlarmRegister(uint8_t writeData, bool aeValid)
{
	uint8_t retValue;

	if(this->rtValue.crt.control.AIE == 0x00u)
	{
		retValue = WriteCalendarRegister((uint8_t)CO_MIN_ALARM_FIELD, (uint8_t)MIN_ALARM_COMPATIBLE_REGISTER_ADDRESS, writeData, aeValid);
	}
	else
	{
		retValue = E_CONTROL_REGISTER_AIE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteHourAlarmRegister [Public]
//(2)Process
//            Write the value of the "HOUR Alarm" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            aeValid		Specifies whether the "AE" bit in the alarm-related register
//                   		is set.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_CONTROL_REGISTER_AIE_SET1	Returned when the AIE bit in the "Control" 
//                                        	register is set to 1.
//(5)Note
//            If you do not want to generate an alarm, set "aeValid" to "true."
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteHourAlarmRegister(uint8_t writeData, bool aeValid)
{
	uint8_t retValue;

	if(this->rtValue.crt.control.AIE == 0x00u)
	{
		retValue = WriteCalendarRegister((uint8_t)CO_HOUR_ALARM_FIELD, (uint8_t)HOUR_ALARM_COMPATIBLE_REGISTER_ADDRESS, writeData, aeValid);
	}
	else
	{
		retValue = E_CONTROL_REGISTER_AIE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteWeekDayAlarmRegister [Public]
//(2)Process
//            Write the value of the "WEEK DAY Alarm" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            aeValid		Specifies whether the "AE" bit in the alarm-related register
//                   		is set.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_CONTROL_REGISTER_AIE_SET1	Returned when the AIE bit in the "Control" 
//                                        	register is set to 1.
//(5)Note
//            If you do not want to generate an alarm, set "aeValid" to "true."
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteWeekDayAlarmRegister(uint8_t writeData, bool aeValid)
{
	uint8_t retValue;

	if(this->rtValue.crt.control.AIE == 0x00u)
	{
		retValue = WriteCalendarRegister((uint8_t)CO_WEEK_DAY_ALARM_FIELD, (uint8_t)WEEK_DAY_ALARM_COMPATIBLE_REGISTER_ADDRESS, writeData, aeValid);
	}
	else
	{
		retValue = E_CONTROL_REGISTER_AIE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteTimerCounter [Public]
//(2)Process
//            Write the value of the "Timer Counter0" and "Timer Counter1" registers.
//(3)Argument
//            writeData		Specify the data to write to the register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_EXTENSION_REGISTER_TE_SET1	Returned when the TE bit in the "Extension" 
//                                        	register is set to 1.
//(5)Note
//            "writeData" must be in the range 0 to 4,095.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteTimerCounter(uint16_t writeData)
{
	uint8_t retValue;
	uint8_t tcWriteData[2];

	tcWriteData[0] = (uint8_t)(writeData & 0x00FFu);
	tcWriteData[1] = (uint8_t)((writeData >> 8) & 0x000Fu);

	if(this->rtValue.crt.extension.TE == 0x00u)
	{
		retValue = WriteTimerCounter0Register(tcWriteData[0]);

		if(retValue == PROCESSING_OK)
		{
			retValue = WriteTimerCounter1Register(tcWriteData[1]);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		retValue = (uint8_t)E_EXTENSION_REGISTER_TE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteTimerCounter0Register [Public]
//(2)Process
//            Write the value of the "Timer Counter0" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_EXTENSION_REGISTER_TE_SET1	Returned when the TE bit in the "Extension" 
//                                        	register is set to 1.
//(5)Note
//            "writeData" must be in the range 0 to 255.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteTimerCounter0Register(uint8_t writeData)
{
	return WriteTimerCounter0Register(writeData, false);
}

uint8_t RX8900::WriteTimerCounter0Register(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;
	const uint16_t writeSize = 1;

	if(this->rtValue.crt.extension.TE == 0x00u)
	{
		if(!selExpansion)
		{
			writeAddress = (uint8_t)TIMER_COUNTER0_COMPATIBLE_REGISTER_ADDRESS;
			fieldType = (uint8_t)CO_TIMER_COUNTER0_FIELD;
		}
		else
		{
			writeAddress = (uint8_t)TIMER_COUNTER0_EXPANSION_REGISTER_ADDRESS;
			fieldType = (uint8_t)EX_TIMER_COUNTER0_FIELD;
		}

		retValue = FormatSelectData(writeAddress, &writeData, false);

		if(retValue == PROCESSING_OK)
		{
			retValue = WriteData(writeAddress, writeSize, &writeData);

			if(retValue == PROCESSING_OK)
			{
				SetInstanceField(fieldType, writeData);
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		retValue = (uint8_t)E_EXTENSION_REGISTER_TE_SET1;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteTimerCounter1Register [Public]
//(2)Process
//            Write the value of the "Timer Counter1" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//            E_EXTENSION_REGISTER_TE_SET1	Returned when the TE bit in the "Extension" 
//                                        	register is set to 1.
//(5)Note
//            "writeData" must be in the range 0 to 15.
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteTimerCounter1Register(uint8_t writeData)
{
	return WriteTimerCounter1Register(writeData, false);
}

uint8_t RX8900::WriteTimerCounter1Register(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;
	const uint16_t writeSize = 1;

	if(this->rtValue.crt.extension.TE == 0x00u)
	{
		if(!selExpansion)
		{
			writeAddress = (uint8_t)TIMER_COUNTER1_COMPATIBLE_REGISTER_ADDRESS;
			fieldType = (uint8_t)CO_TIMER_COUNTER1_FIELD;
		}
		else
		{
			writeAddress = (uint8_t)TIMER_COUNTER1_EXPANSION_REGISTER_ADDRESS;
			fieldType = (uint8_t)EX_TIMER_COUNTER1_FIELD;
		}

		retValue = FormatSelectData(writeAddress, &writeData, false);

		if(retValue == PROCESSING_OK)
		{
			retValue = WriteData(writeAddress, writeSize, &writeData);

			if(retValue == PROCESSING_OK)
			{
				SetInstanceField(fieldType, writeData);
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		retValue = (uint8_t)E_EXTENSION_REGISTER_TE_SET1;
	}	

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteExtensionRegister [Public]
//(2)Process
//            Write the value of the "Extension" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteExtensionRegister(uint8_t writeData)
{
	return WriteExtensionRegister(writeData, false);
}

uint8_t RX8900::WriteExtensionRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;
	const uint16_t writeSize = 1;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)EXTENSION_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_EXTENSION_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)EXTENSION_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_EXTENSION_FIELD;
	}

	writeData &= EXTENSION_REGISTER_BIT_MASK;

	retValue = WriteData(writeAddress, writeSize, &writeData);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, writeData);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteFlagRegister [Public]
//(2)Process
//            Write the value of the "Flag" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteFlagRegister(uint8_t writeData)
{
	return WriteFlagRegister(writeData, false);
}

uint8_t RX8900::WriteFlagRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;
	const uint16_t writeSize = 1;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)FLAG_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_FLAG_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)FLAG_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_FLAG_FIELD;
	}

	writeData &= FLAG_REGISTER_BIT_MASK;

	retValue = WriteData(writeAddress, writeSize, &writeData);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, writeData);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteControlRegister [Public]
//(2)Process
//            Write the value of the "Control" register.
//(3)Argument
//            writeData		Specify the data to write to the register.
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteControlRegister(uint8_t writeData)
{
	return WriteControlRegister(writeData, false);
}

uint8_t RX8900::WriteControlRegister(uint8_t writeData, bool selExpansion)
{
	uint8_t retValue;
	uint8_t writeAddress;
	uint8_t fieldType;
	const uint16_t writeSize = 1;

	if(!selExpansion)
	{
		writeAddress = (uint8_t)CONTROL_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_CONTROL_FIELD;
	}
	else
	{
		writeAddress = (uint8_t)CONTROL_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_CONTROL_FIELD;
	}

	writeData &= CONTROL_REGISTER_BIT_MASK;

	retValue = WriteData(writeAddress, writeSize, &writeData);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, writeData);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadAllRegisters [Public]
//(2)Process
//            Read the value of the all registers.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadAllRegisters()
{
	uint8_t retValue;
	uint8_t readBuffer[FIELD_MAX];
	const uint16_t readSize = EXPANSION_REGISTER_ADDRESS_MAX;

	uint8_t *p_dest = (uint8_t*)&this->rtValue;

	retValue = ReadData(SEC_COMPATIBLE_REGISTER_ADDRESS, readSize, (uint8_t*)&readBuffer[0]);

	if(retValue == PROCESSING_OK)
	{
		for(uint8_t copyLoop = 0; copyLoop < FIELD_MAX; copyLoop++)
		{
			*p_dest++ = readBuffer[copyLoop];
		}

		retValue = ReadTempRegister();

		if(retValue == PROCESSING_OK)
		{
			retValue = ReadBackupFunctionRegister();
			this->rtValue.ert.reserved[0] = NOT_USE0_REGISTER_BIT_MASK;
			this->rtValue.ert.reserved[1] = NOT_USE1_REGISTER_BIT_MASK;
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadCurrentTime [Public]
//(2)Process
//            The current time is read from a register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadCurrentTime()
{
	uint8_t retValue;
	uint8_t readBuffer[CURRENT_TIME_BYTE_SIZE];
	const uint16_t readSize = CURRENT_TIME_BYTE_SIZE;

	uint8_t *p_dest = (uint8_t*)&this->rtValue;

	retValue = ReadData(SEC_COMPATIBLE_REGISTER_ADDRESS, readSize, (uint8_t*)&readBuffer[0]);

	for(uint8_t copyLoop = 0; copyLoop < CURRENT_TIME_BYTE_SIZE; copyLoop++)
	{
		*p_dest++ = readBuffer[copyLoop];
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadSecRegister [Public]
//(2)Process
//            Read the value of the "SEC" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadSecRegister()
{
	return ReadSecRegister(false);
}

uint8_t RX8900::ReadSecRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)SEC_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_SEC_FIELD;
	}
	else
	{
		readAddress = (uint8_t)SEC_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_SEC_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadMinRegister [Public]
//(2)Process
//            Read the value of the "MIN" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadMinRegister()
{
	return ReadMinRegister(false);
}

uint8_t RX8900::ReadMinRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)MIN_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_MIN_FIELD;
	}
	else
	{
		readAddress = (uint8_t)MIN_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_MIN_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadHourRegister [Public]
//(2)Process
//            Read the value of the "HOUR" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadHourRegister()
{
	return ReadHourRegister(false);
}

uint8_t RX8900::ReadHourRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)HOUR_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_HOUR_FIELD;
	}
	else
	{
		readAddress = (uint8_t)HOUR_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_HOUR_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadWeekRegister [Public]
//(2)Process
//            Read the value of the "WEEK" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadWeekRegister()
{
	return ReadWeekRegister(false);
}

uint8_t RX8900::ReadWeekRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)WEEK_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_WEEK_FIELD;
	}
	else
	{
		readAddress = (uint8_t)WEEK_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_WEEK_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadDayRegister [Public]
//(2)Process
//            Read the value of the "DAY" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadDayRegister()
{
	return ReadDayRegister(false);
}

uint8_t RX8900::ReadDayRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)DAY_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_DAY_FIELD;
	}
	else
	{
		readAddress = (uint8_t)DAY_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_DAY_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadMonthRegister [Public]
//(2)Process
//            Read the value of the "MONTH" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadMonthRegister()
{
	return ReadMonthRegister(false);
}

uint8_t RX8900::ReadMonthRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)MONTH_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_MONTH_FIELD;
	}
	else
	{
		readAddress = (uint8_t)MONTH_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_MONTH_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadYearRegister [Public]
//(2)Process
//            Read the value of the "YEAR" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadYearRegister()
{
	return ReadYearRegister(false);
}

uint8_t RX8900::ReadYearRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readAddress;
	uint8_t fieldType;

	if(!selExpansion)
	{
		readAddress = (uint8_t)YEAR_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_YEAR_FIELD;
	}
	else
	{
		readAddress = (uint8_t)YEAR_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_YEAR_FIELD;
	}

	retValue = ReadCalendarRegister(fieldType, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadRamRegister [Public]
//(2)Process
//            Read the value of the "RAM" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadRamRegister()
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	const uint16_t readSize = 1;

	retValue = ReadData((uint8_t)RAM_COMPATIBLE_REGISTER_ADDRESS, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField((uint8_t)CO_RAM_FIELD, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadMinAlarmRegister [Public]
//(2)Process
//            Read the value of the "MIN Alarm" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadMinAlarmRegister()
{
	uint8_t retValue;
	uint8_t readAddress;

	readAddress = (uint8_t)MIN_ALARM_COMPATIBLE_REGISTER_ADDRESS;

	retValue = ReadCalendarRegister((uint8_t)CO_MIN_ALARM_FIELD, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadHourAlarmRegister [Public]
//(2)Process
//            Read the value of the "HOUR Alarm" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadHourAlarmRegister()
{
	uint8_t retValue;
	uint8_t readAddress;

	readAddress = (uint8_t)HOUR_ALARM_COMPATIBLE_REGISTER_ADDRESS;

	retValue = ReadCalendarRegister((uint8_t)CO_HOUR_ALARM_FIELD, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadWeekDayAlarmRegister [Public]
//(2)Process
//            Read the value of the "WEEK DAY Alarm" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadWeekDayAlarmRegister()
{
	uint8_t retValue;
	uint8_t readAddress;

	readAddress = (uint8_t)WEEK_DAY_ALARM_COMPATIBLE_REGISTER_ADDRESS;

	retValue = ReadCalendarRegister((uint8_t)CO_WEEK_DAY_ALARM_FIELD, readAddress);

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadTempRegister [Public]
//(2)Process
//            Read the value of the "TEMP" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadTempRegister()
{
	uint8_t retValue;
	uint8_t readBuffer;
	const uint16_t readSize = 1;

	retValue = ReadData((uint8_t)TEMP_EXPANSION_REGISTER_ADDRESS, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField((uint8_t)EX_TEMP_FIELD, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadBackupFunctionRegister [Public]
//(2)Process
//            Read the value of the "Backup Function" register.
//(3)Argument
//            none
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadBackupFunctionRegister()
{
	uint8_t retValue;
	uint8_t readBuffer;
	const uint16_t readSize = 1;

	retValue = ReadData((uint8_t)BACKUP_FUNCTION_EXPANSION_REGISTER_ADDRESS, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField((int)EX_BACKUP_FUNCTION_FIELD, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadTimerCounter0Register [Public]
//(2)Process
//            Read the value of the "Timer Counter0" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadTimerCounter0Register()
{
	return ReadTimerCounter0Register(false);
}

uint8_t RX8900::ReadTimerCounter0Register(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	uint8_t fieldType;
	const uint16_t readSize = 1;

	if(!selExpansion)
	{
		readAddress = (uint8_t)TIMER_COUNTER0_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_TIMER_COUNTER0_FIELD;
	}
	else
	{
		readAddress = (uint8_t)TIMER_COUNTER0_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_TIMER_COUNTER0_FIELD;
	}

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadTimerCounter1Register [Public]
//(2)Process
//            Read the value of the "Timer Counter1" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadTimerCounter1Register()
{
	return ReadTimerCounter1Register(false);
}

uint8_t RX8900::ReadTimerCounter1Register(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	uint8_t fieldType;
	const uint16_t readSize = 1;

	if(!selExpansion)
	{
		readAddress = (uint8_t)TIMER_COUNTER1_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_TIMER_COUNTER1_FIELD;
	}
	else
	{
		readAddress = (uint8_t)TIMER_COUNTER1_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_TIMER_COUNTER1_FIELD;
	}

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadExtensionRegister [Public]
//(2)Process
//            Read the value of the "Extension" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadExtensionRegister()
{
	return ReadExtensionRegister(false);
}

uint8_t RX8900::ReadExtensionRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	uint8_t fieldType;
	const uint16_t readSize = 1;

	if(!selExpansion)
	{
		readAddress = (uint8_t)EXTENSION_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_EXTENSION_FIELD;
	}
	else
	{
		readAddress = (uint8_t)EXTENSION_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_EXTENSION_FIELD;
	}

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadFlagRegister [Public]
//(2)Process
//            Read the value of the "Flag" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadFlagRegister()
{
	return ReadFlagRegister(false);
}

uint8_t RX8900::ReadFlagRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	uint8_t fieldType;
	const uint16_t readSize = 1;

	if(!selExpansion)
	{
		readAddress = (uint8_t)FLAG_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_FLAG_FIELD;
	}
	else
	{
		readAddress = (uint8_t)FLAG_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_FLAG_FIELD;
	}

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadControlRegister [Public]
//(2)Process
//            Read the value of the "Control" register.
//(3)Argument
//            selExpansion	Specify "false" when reading from a compatible register.
//                        	Specify "true" when reading from an expansion register.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadControlRegister()
{
	return ReadControlRegister(false);
}

uint8_t RX8900::ReadControlRegister(bool selExpansion)
{
	uint8_t retValue;
	uint8_t readBuffer;
	uint8_t readAddress;
	uint8_t fieldType;
	const uint16_t readSize = 1;

	if(!selExpansion)
	{
		readAddress = (uint8_t)CONTROL_COMPATIBLE_REGISTER_ADDRESS;
		fieldType = (uint8_t)CO_CONTROL_FIELD;
	}
	else
	{
		readAddress = (uint8_t)CONTROL_EXPANSION_REGISTER_ADDRESS;
		fieldType = (uint8_t)EX_CONTROL_FIELD;
	}

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteCalendarRegister [Private]
//(2)Process
//            Write the value of the calendar registers.
//(3)Argument
//            fieldType		Specify the data type to be formatted.
//            writeAddress	Address you want to send.
//            writeData		Data you want to send.
//            aeValid		Specifies whether the "AE" bit in the alarm-related register
//                   		is set.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW		Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS		Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA			Returned when NACK is received when sending the data.
//            E_OTHER_ERROR					Returned when other errors occur.
//            E_I2C_TIME_OUT				Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL			Returned when there is no free space in the send buffer.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            If you do not want to generate an alarm, set "aeValid" to "true."
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteCalendarRegister(uint8_t fieldType, uint8_t writeAddress, uint8_t writeData, bool aeValid)
{
	uint8_t retValue;
	const uint16_t writeSize = 1;

	retValue = FormatSelectData(writeAddress, (uint8_t*)&writeData, aeValid);

	if(retValue == PROCESSING_OK)
	{
		retValue = WriteData(writeAddress, writeSize, &writeData);

		if(retValue == PROCESSING_OK)
		{
			SetInstanceField(fieldType, writeData);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadCalendarRegister [Private]
//(2)Process
//            Read the value of the calendar registers.
//(3)Argument
//            fieldType		Specify the data type to be formatted.
//            readAddress	Address you want to send.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadCalendarRegister(uint8_t fieldType, uint8_t readAddress)
{
	uint8_t retValue;
	uint8_t readBuffer;
	const uint16_t readSize = 1;

	retValue = ReadData(readAddress, readSize, (uint8_t*)&readBuffer);

	if(retValue == PROCESSING_OK)
	{
		SetInstanceField(fieldType, readBuffer);
	}
	else
	{
		/* do nothing */
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            FormatSelectData [Private]
//(2)Process
//            Select data format.
//(3)Argument
//            writeAddress	Specify the write destination address.
//            targetData	Data to format.
//            aeValid		Specifies whether the "AE" bit in the alarm-related register
//                   		is set.
//(4)Return
//            Result of operation.
//            PROCESSING_OK					Returned when processing ends normally.
//            E_TARGET_DATA_OUT_OF_RANGE	Returned when the value of the target
//                                      	data is out of range.
//            E_INVALID_REGISTER_ADDRESS	Returned when the register address is invalid.
//(5)Note
//            If you do not want to generate an alarm, set "aeValid" to "true."
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::FormatSelectData(uint8_t writeAddress, uint8_t *targetData, bool aeValid)
{
	uint8_t retValue = PROCESSING_OK;

	switch(writeAddress)
	{
		/* Max 10 group */
		case MONTH_COMPATIBLE_REGISTER_ADDRESS:
		case MONTH_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < MONTH_LOWER_LIMIT || *targetData > MONTH_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatTimeData(4, targetData);
				*targetData &= MONTH_REGISTER_BIT_MASK;
			}			
			break;

		/* Max 20 group */
		case HOUR_COMPATIBLE_REGISTER_ADDRESS:
		case HOUR_ALARM_COMPATIBLE_REGISTER_ADDRESS:
		case HOUR_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < HOUR_LOWER_LIMIT || *targetData > HOUR_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatTimeData(5, targetData);

				if(writeAddress != HOUR_ALARM_COMPATIBLE_REGISTER_ADDRESS)
				{
					*targetData &= HOUR_REGISTER_BIT_MASK;
				}
				else
				{
					if(aeValid)
					{
						*targetData |= 0x80u;
					}
					else
					{
						*targetData &= 0x7Fu;
					}
				}
			}
			break;
		case DAY_COMPATIBLE_REGISTER_ADDRESS:
		case DAY_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < DAY_LOWER_LIMIT || *targetData > DAY_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatTimeData(5, targetData);
				*targetData &= DAY_REGISTER_BIT_MASK;
			}
			break;

		/* Max 40 group */
		case SEC_COMPATIBLE_REGISTER_ADDRESS:
		case MIN_COMPATIBLE_REGISTER_ADDRESS:
		case MIN_ALARM_COMPATIBLE_REGISTER_ADDRESS:
		case SEC_EXPANSION_REGISTER_ADDRESS:
		case MIN_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < SEC_MIN_LOWER_LIMIT || *targetData > SEC_MIN_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatTimeData(6, targetData);

				if(writeAddress != MIN_ALARM_COMPATIBLE_REGISTER_ADDRESS)
				{
					*targetData &= SEC_MIN_REGISTER_BIT_MASK;
				}
				else
				{
					if(aeValid)
					{
						*targetData |= 0x80u;
					}
					else
					{
						*targetData &= 0x7Fu;
					}
				}
			}
			break;
		
		/* Max 80 group */
		case YEAR_COMPATIBLE_REGISTER_ADDRESS:
		case YEAR_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < YEAR_LOWER_LIMIT || *targetData > YEAR_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatTimeData(7, targetData);
			}
			break;

		/* Max 128 group */
		case TIMER_COUNTER0_COMPATIBLE_REGISTER_ADDRESS:
		case TIMER_COUNTER0_EXPANSION_REGISTER_ADDRESS:
		case TEMP_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < TIMER_COUNTER0_LOWER_LIMIT || *targetData > TIMER_COUNTER0_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				/* do nothing */
			}
			break;
		
		/* Max 2,048 group */
		case TIMER_COUNTER1_COMPATIBLE_REGISTER_ADDRESS:
		case TIMER_COUNTER1_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < TIMER_COUNTER1_LOWER_LIMIT || *targetData > TIMER_COUNTER1_UPPER_LIMIT)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				/* do nothing */
			}
			break;

		/* Week group */		
		case WEEK_COMPATIBLE_REGISTER_ADDRESS:
		case WEEK_EXPANSION_REGISTER_ADDRESS:
			if(*targetData < SUNDAY || *targetData > SATURDAY)
			{
				retValue = E_TARGET_DATA_OUT_OF_RANGE;
			}
			else
			{
				FormatWeekData(targetData);
				*targetData &= WEEK_REGISTER_BIT_MASK;
			}
			break;

		/* Anomaly group */
		case WEEK_DAY_ALARM_COMPATIBLE_REGISTER_ADDRESS:
			if(this->rtValue.crt.extension.WADA == 0)
			{
				if(*targetData < SUNDAY || *targetData > SATURDAY)
				{
					retValue = E_TARGET_DATA_OUT_OF_RANGE;
				}
				else
				{
					FormatWeekData(targetData);
				}
			}
			else
			{
				if(*targetData < DAY_LOWER_LIMIT || *targetData > DAY_UPPER_LIMIT)
				{
					retValue = E_TARGET_DATA_OUT_OF_RANGE;
				}
				else
				{
					FormatTimeData(5, targetData);
				}
			}

			if(aeValid)
			{
				*targetData |= 0x80u;
			}
			else
			{
				*targetData &= 0x7Fu;
			}
			
			break;

		default:
			retValue = E_INVALID_REGISTER_ADDRESS;
			break;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            FormatTimeData [Private]
//(2)Process
//            Format time data.
//(3)Argument
//            loopNum		Specify the number of times to process.
//            targetData	Data to format.
//(4)Return
//            none
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::FormatTimeData(uint8_t loopNum, uint8_t *targetData)
{
	uint8_t tempBuffer;
	uint8_t calcBinary = 0;
	const uint8_t array[] = {1, 2, 4, 8, 10, 20, 40, 80};

	tempBuffer = *targetData;

	for(int8_t formatLoop = loopNum; formatLoop >= 0; formatLoop--)
	{
		if(array[formatLoop] <= tempBuffer)
		{
			tempBuffer -= array[formatLoop];
			calcBinary |= (0x01u << formatLoop);
		}
		else
		{
			/* do nothing */
		}
	}

	*targetData = calcBinary;

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            FormatWeekData [Private]
//(2)Process
//            Format week data.
//(3)Argument
//            targetData	Data to format.
//(4)Return
//            none
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::FormatWeekData(uint8_t *targetData)
{
	*targetData = (0x01u << *targetData);

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            FormatCalendarValue [Private]
//(2)Process
//            Format the reading into time information.
//(3)Argument
//            fieldType		Specify the data type to be formatted.
//            targetData	Data to format.
//(4)Return
//            none
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::FormatCalendarValue(uint8_t fieldType, uint8_t *targetData)
{
	uint8_t tempBuffer = 0;
	uint8_t formatLimit = 0;
	bool isSkip = false;
	bool validBit;

	switch(fieldType)
	{
		case CO_YEAR_FIELD:
		case EX_YEAR_FIELD:
			formatLimit = 8;
			break;
		
		case CO_SEC_FIELD:
		case CO_MIN_FIELD:
		case CO_MIN_ALARM_FIELD:
		case EX_SEC_FIELD:
		case EX_MIN_FIELD:
			formatLimit = 7;
			break;

		case CO_HOUR_FIELD:
		case CO_DAY_FIELD:
		case CO_HOUR_ALARM_FIELD:
		case CO_WEEK_DAY_ALARM_FIELD:
		case EX_HOUR_FIELD:
		case EX_DAY_FIELD:
			formatLimit = 6;
			break;

		case CO_MONTH_FIELD:
		case EX_MONTH_FIELD:
			formatLimit = 5;
			break;

		case CO_WEEK_FIELD:
		case EX_WEEK_FIELD:
			isSkip = true;
			break;

		default:
			/* do nothing */
			break;
	}

	if(!isSkip)
	{
		for(int formatLoop = 0; formatLoop < formatLimit; formatLoop++)
		{
			validBit = (*targetData >> formatLoop) & 0x01u;

			if(validBit)
			{
				switch(formatLoop)
				{
					case 0:
						tempBuffer += 1;
						break;

					case 1:
						tempBuffer += 2;
						break;

					case 2:
						tempBuffer += 4;
						break;

					case 3:
						tempBuffer += 8;
						break;

					case 4:
						tempBuffer += 10;
						break;

					case 5:
						tempBuffer += 20;
						break;

					case 6:
						tempBuffer += 40;
						break;

					case 7:
						tempBuffer += 80;
						break;

					default:
						break;
				}
			}
			else
			{
				/* do nothing */
			}
		}

		*targetData = tempBuffer;
	}
	else
	{
		/* do nothing */
	}

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            SetInstanceField [Private]
//(2)Process
//            Set data in the instance's fields.
//(3)Argument
//            fieldType		Specify the instance field to set.
//            setData		The data to set on the instance.
//(4)Return
//            none
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

void RX8900::SetInstanceField(uint8_t fieldType, uint8_t setData)
{
	uint8_t copySize;
	uint8_t *p_dest[] = {NULL, NULL};

	switch(fieldType)
	{
		/* CoRegisterTable and common part with ExRegisterTable*/
		case CO_SEC_FIELD:
		case EX_SEC_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.sec;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.sec;
			copySize = sizeof(Sec_t);
			break;

		case CO_MIN_FIELD:
		case EX_MIN_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.min;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.min;
			copySize = sizeof(Min_t);
			break;

		case CO_HOUR_FIELD:
		case EX_HOUR_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.hour;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.hour;
			copySize = sizeof(Hour_t);
			break;

		case CO_WEEK_FIELD:
		case EX_WEEK_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.week;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.week;
			copySize = sizeof(Week_t);
			break;

		case CO_DAY_FIELD:
		case EX_DAY_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.day;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.day;
			copySize = sizeof(Day_t);
			break;

		case CO_MONTH_FIELD:
		case EX_MONTH_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.month;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.month;
			copySize = sizeof(Month_t);
			break;

		case CO_YEAR_FIELD:
		case EX_YEAR_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.year;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.year;
			copySize = sizeof(Year_t);
			break;

		case CO_TIMER_COUNTER0_FIELD:
		case EX_TIMER_COUNTER0_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.timerCounter0;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.timerCounter0;
			copySize = sizeof(TimerCounter0_t);
			break;

		case CO_TIMER_COUNTER1_FIELD:
		case EX_TIMER_COUNTER1_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.timerCounter1;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.timerCounter1;
			copySize = sizeof(TimerCounter1_t);
			break;

		case CO_EXTENSION_FIELD:
		case EX_EXTENSION_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.extension;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.extension;
			copySize = sizeof(Extension_t);
			break;

		case CO_FLAG_FIELD:
		case EX_FLAG_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.flag;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.flag;
			copySize = sizeof(Flag_t);
			break;

		case CO_CONTROL_FIELD:
		case EX_CONTROL_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.control;
			p_dest[1] = (uint8_t*)&this->rtValue.ert.control;
			copySize = sizeof(Control_t);
			break;

		/* CoRegisterTable only */
		case CO_RAM_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.ram;
			copySize = sizeof(uint8_t);
			this->rtValue.crt.ram = setData;
			break;

		case CO_MIN_ALARM_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.minAlarm;
			copySize = sizeof(MinAlarm_t);
			break;

		case CO_HOUR_ALARM_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.hourAlarm;
			copySize = sizeof(HourAlarm_t);
			break;

		case CO_WEEK_DAY_ALARM_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.crt.weekDayAlarm;
			copySize = sizeof(WeekDayAlarm_t);
			break;

		/* ExRegisterTable only */
		case EX_TEMP_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.ert.temp;
			copySize = sizeof(Temp_t);
			break;

		case EX_BACKUP_FUNCTION_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.ert.backupFunction;
			copySize = sizeof(BackupFunction_t);
			break;

		case EX_RESERVED0_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.ert.reserved[0];
			copySize = sizeof(uint8_t);
			break;

		case EX_RESERVED1_FIELD:
			p_dest[0] = (uint8_t*)&this->rtValue.ert.reserved[1];
			copySize = sizeof(uint8_t);
			break;

		default:
			break;
	}

	(void)memcpy(p_dest[0], &setData, copySize);

	if(p_dest[1] != NULL)
	{
		(void)memcpy(p_dest[1], &setData, copySize);
	}
	else
	{
		/* do nothing */
	}

	return;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            WriteData [Private]
//(2)Process
//            Write data to RX8900 ic.
//(3)Argument
//            address		Address you want to send.
//            writeSize		Size you want to write.
//            data			Data you want to write.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::WriteData(uint8_t address, const uint16_t writeSize, uint8_t *data)
{
	uint8_t retValue;

	Wire.beginTransmission(RX8900_I2C_ADDRESS);

	retValue = (uint8_t)Wire.write(address);

	if(retValue != SEND_BUFFER_IS_FULL)
	{
		for(uint8_t writeLoop = 0; writeLoop < writeSize; writeLoop++)
		{
			retValue = (uint8_t)Wire.write(*data);

			if(retValue != SEND_BUFFER_IS_FULL)
			{
				data++;
			}
			else
			{
				break;
			}
		}

		if(retValue != SEND_BUFFER_IS_FULL)
		{
			retValue = (uint8_t)Wire.endTransmission(true);
		}
		else
		{
			retValue = E_SEND_BUFFER_IS_FULL;
		}
	}
	else
	{
		retValue = E_SEND_BUFFER_IS_FULL;
	}

	return retValue;
}


/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/
//(1)Function name
//            ReadData [Private]
//(2)Process
//            Read data from RX8900 ic.
//(3)Argument
//            address		Address you want to send.
//            readSize		Size you want to read.
//            storeAddress	Address to store read data.
//(4)Return
//            Result of operation.
//            PROCESSING_OK				Returned when processing ends normally.
//            E_SEND_BUFFER_OVERFLOW	Returned when send buffer overflowed.
//            E_RECEIVE_NACK_ADDRESS	Returned when NACK is received when sending the address.
//            E_RECEIVE_NACK_DATA		Returned when NACK is received when sending the data.
//            E_OTHER_ERROR				Returned when other errors occur.
//            E_I2C_TIME_OUT			Returned when timeout occurs.
//            E_SEND_BUFFER_IS_FULL		Returned when there is no free space in the send buffer.
//            E_NO_RECEIVED_DATA		Returned when no received data.
//            E_READ_SIZE_OUT_OF_RANGE	Returned when specified read size is out of range.
//(5)Note
//            
//(6)History
//            Rev.0   2024/10/20   Keisuke Hamada
/*_(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)__(:3｣∠)_*/

uint8_t RX8900::ReadData(uint8_t address, const uint16_t readSize, uint8_t *storeAddress)
{
	uint16_t retValue;
	
	if(readSize >= READ_LOWER_LIMIT && readSize <= READ_UPPER_LIMIT)
	{
		int16_t receivedSize;

		Wire.beginTransmission(RX8900_I2C_ADDRESS);

		retValue = (uint8_t)Wire.write(address);

		if(retValue != SEND_BUFFER_IS_FULL)
		{
			retValue = (uint8_t)Wire.endTransmission(false);

			if(retValue == PROCESSING_OK)
			{
				receivedSize = (int16_t)Wire.requestFrom(RX8900_I2C_ADDRESS, readSize);

				if(receivedSize <= 0)
				{
					retValue = E_NO_RECEIVED_DATA;
				}
				else
				{
					for(uint8_t readLoop = 0; readLoop < receivedSize; readLoop++)
					{
						*storeAddress = (uint8_t)Wire.read();
						storeAddress++;
					}	
				}		
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			retValue = E_SEND_BUFFER_IS_FULL;
		}
	}
	else
	{
		retValue = E_READ_SIZE_OUT_OF_RANGE;
	}

	return retValue;
}
