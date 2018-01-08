/*
This file is part of Ionlib.  Copyright (C) 2016  Tim Sweet

Ionlib is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ionlib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ionlib.If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ION_TIMER_H_
#define ION_TIMER_H_
#include <Arduino.h>
#include "iondef.h"
//Typedefs
typedef struct PerfMon_s
{
    uint32_t num_samples;
    float mean;
    float var_sum;
    uint32_t min;
    uint32_t max;
    uint32_t start;
} PerfMon_t;

//Prototypes

void InitPerf(PerfMon_t* perf);
void AddPerfSample(uint32_t val, PerfMon_t* perf);
void StartTimer(PerfMon_t* perf);
void StopTimer(PerfMon_t* perf);
void PrintPerf(HardwareSerial* ser_out, PerfMon_t perf);
//void PrintPerf(SoftwareSerial* ser_out, PerfMon_t perf);

#endif //ION_TIMER_H_