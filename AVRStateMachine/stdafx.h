#pragma once

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#define  F_CPU			4000000UL
#include <util/delay.h>
#define DELAY_TIME		500
#define PERIOD_EXAMPLE_VALUE			(0x0271)
#define DUTY_CYCLE_EXAMPLE_VALUE		(0x0068)		
#include <stdlib.h>
#include "Bluetooth.h"
#include "usart.h"
#include "Pwm.h"
