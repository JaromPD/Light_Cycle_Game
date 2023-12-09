/*
 * input.cpp
 *
 *  Created on: Dec 8, 2023
 *      Author: jarom
 */

#include <input.h>

#define positiveThreshold 2000
#define negativeThreshold 1000

void Input::inputStart()
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start(&hadc3);
};

bool Input::isLeft()
{
	if(getXMeasurement() < negativeThreshold)
		return true;
	else
		return false;
};
bool Input::isRight()
{
	if(getXMeasurement() > positiveThreshold)
		return true;
	else
		return false;
};
bool Input::isDown()
{
	if(getYMeasurement() > positiveThreshold)
		return true;
	else
		return false;
};
bool Input::isUp()
{
	if(getYMeasurement() < negativeThreshold)
		return true;
	else
		return false;
};


