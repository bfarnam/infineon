
#include <stdint.h>
#include "infineon.hpp"
#include <Arduino.h>	// for pin functions

// type alias for older c++ to be removed in IDE
using uint16_t = unsigned short;
using uint8_t = int;

using namespace infineon;

btx::btx()
{
	// constructor
}

btx::~btx()
{
	// de-constructor
}

/**
 * Read ADC value for IS which is the calculated current, which is depending on the IS signal.
 * Returns the Value of the current flowing through the switch in [A]
 */
float btx::readIs(BTxChip_t *btxchip, uint8_t pin, uint8_t den, uint8_t dsel=0)
{
	uint16_t adcVal = 0;
	float isVoltage = 0.0;
	float isCurrent = 0.0;

	enableDiag(den);
	if (dsel != 0) { digitalWrite(dsel, 0x0); }			//setDiagCh(dsel);

	delay(1); 											//timer->delayMilli(1);
	adcVal = analogRead(pin); 							//adcVal = is->ADCRead();
	isVoltage = (adcVal/1024.0)*5.0;
	isCurrent = ((isVoltage*btxchip->kilis)/btxchip->rSense) - currentOffset;
	currentFilter->input(isCurrent);

	if (dsel != 0) { digitalWrite(dsel, 0x1); }
	disableDiag(den);

	return currentFilter->output();
}

/**
 * Diagnosis of the Output pin
 * Returns DiagStatus_t
 * = 0   Everything works correctly
 * = 2   Short to ground
 * = 4   Short to battery
 * = 5   Open load
 */
DiagStatus_t btx::readDiagX(BTxChip_t *btxchip, uint8_t pin, uint8_t den, uint8_t dsel=0)
{
	DiagStatus_t diagStatus = NORMAL;
	float currentOn = 0.0;

	enableDiag(den); 									//switches[hss]->enableDiag();

	if(getSwitchStatus(pin) == POWER_ON)
	{
		currentOn = readIs(btxchip, pin, den, dsel=0);
		diagStatus = diagRead(currentOn, btxchip);
	}
	else
	{
		// switch off read diagnosis
	}

	disableDiag(den); 									//switches[hss]->disableDiag();

	return diagStatus;
}

/**
 * Diagnosis of the Output - This function is using the IS signal to determine the state of the switch.
 * Returns DiagStatus_t
 * = 0  Switch is working fine
 * = 1  Fault condition detected
 * = 2  Open Load during ON or Inverse Current
 */
DiagStatus_t btx::diagRead(float senseCurrent, BTxChip_t *btxchip)
{
	if(senseCurrent >= (btxchip->iisFault * btxchip->kilis)){
        diagStatus = FAULT;
    }
    else if((btxchip->family == BTS700X) && (senseCurrent <= (btxchip->iisEn * btxchip->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else if((btxchip->family == BTS5001X) && (senseCurrent <= (btxchip->iisO * btxchip->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else if((btxchip->family == BTT60X0) && (senseCurrent <= (btxchip->iisOl * btxchip->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else{
        diagStatus = NORMAL;
    }

    return diagStatus;
}

/**
 * Get the switch status
 *  = 2   Power on
 *  = 3   Power off
 */
Status_t btx::getSwitchStatus(uint8_t pin)
{
    uint8_t status = digitalRead(pin);

    if (status == 2)
    {
    	status = POWER_ON;
    }
    else
    {
    	status = POWER_OFF;
    }
	return status;
}

/**
 * Set current offset - This function can be used to change the value of the internal variable of the current offset (in A)
 */
void btx::setCurrentOffset(float offset)
{
    currentOffset = offset;
}

Error_t btx::enableDiag(uint8_t den)
{
    Error_t err = OK;

    if(den != 0)
    {
        digitalWrite(den, 0x1); 						//err = den->enable();
        diagEnb = DIAG_EN;
    }
    else
    {
        err = INIT_ERROR;
    }

    return err;
}

Error_t btx::disableDiag(uint8_t den)
{
	Error_t err = OK;

	if(den != 0)
	{
		digitalWrite(den, 0x0); 						//err = den->enable();
		diagEnb = DIAG_DIS;
	}
	else
	{
		err = INIT_ERROR;
	}

	return err;
}

Error_t btx::setDsel(uint8_t dsel=0)
{
	Error_t err = OK;

	if(dsel != 0)
	{
		digitalWrite(dsel, 0x0);
	}
	else
	{
		return INVALID_CH_ERROR;
	}

	return err;
}
