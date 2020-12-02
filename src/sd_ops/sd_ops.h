#pragma once

/*  CURRENTLY NOT USED
 *
 *  Use only for detting
 *  data for charts
 *
*/


#include "SD.h"
#include <WString.h>

//------------------ [HIERARCHY] -------------
//root
//  |
//  | ODO.txt (number)
//  | Data (folder)
//      |
//      | dd.mm.yy DayOfTheWeek (folder)
//          |
//          | Combined_CadPulSpd.csv
//          | Statistics.txt
//              {
//                  Average speed = x km/h
//                  Average pulse = x bpm
//                  Average cadence = x rpm
//                  Total trip = x km
//                  ODO = x km
//              }
//          | Separated (folder)
//              |
//              | Cadence.csv
//              | Pulse.csv
//              | Speed.csv
//              | Trip.csv
//              | 
//  | Web (folder)
//      | charts.js
//      | 
//  | Logs (folder)
//      | dd.mm.yy.log
//      |
