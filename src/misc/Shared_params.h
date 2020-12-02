#pragma once

#include <WString.h>

#define MAX_DATA_ARGUMENT_AMOUNT 32

//POST
extern String args[MAX_DATA_ARGUMENT_AMOUNT];
extern String argVals[MAX_DATA_ARGUMENT_AMOUNT];
extern int argLen;

//server
extern bool update; //catches info updates from server
extern bool updateHW; //settings updates

//detecs
extern String pulseRaw;
extern uint8_t pulseUint;
extern uint16_t pulse_summ;
extern uint16_t pulse_measures;
