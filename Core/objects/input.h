/*
 * input.h
 *
 *  Created on: Dec 8, 2023
 *      Author: jarom
 */

#ifndef OBJECTS_INPUT_H_
#define OBJECTS_INPUT_H_

#include "stm32l4xx_hal.h"

class Input {
public:
	// Constructor
	Input(ADC_HandleTypeDef &hadc1, ADC_HandleTypeDef &hadc3)
	: hadc1(hadc1), hadc3(hadc3) {};

	void inputStart();
	bool isLeft();
	bool isRight();
	bool isDown();
	bool isUp();

private:
	uint16_t getXMeasurement()
	{
		//HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		return HAL_ADC_GetValue(&hadc1);
	};
	uint16_t getYMeasurement()
	{
		//HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
		return HAL_ADC_GetValue(&hadc3);
	};
	ADC_HandleTypeDef& hadc1;
	ADC_HandleTypeDef& hadc3;
};

#endif /* OBJECTS_INPUT_H_ */
