#include "Shared_params.h"

String args[MAX_DATA_ARGUMENT_AMOUNT] = "";
String argVals[MAX_DATA_ARGUMENT_AMOUNT] = "";
int argLen = 0;
bool update = false;
bool updateHW = false;
String pulseRaw = "";
uint8_t pulseUint = 0;
uint16_t pulse_summ = 0;
uint16_t pulse_measures = 0;