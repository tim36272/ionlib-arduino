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
#include "timer.h"
void InitPerf(PerfMon_t* perf)
{
    memset(perf, 0, sizeof(PerfMon_t));
    perf->min = (uint32_t)(-1); //uint32 max
}
void AddPerfSample(uint32_t val, PerfMon_t* perf)
{
    perf->num_samples++;
    float delta = val - perf->mean;
    perf->mean += delta / perf->num_samples;
    perf->var_sum += delta * (val - perf->mean);
    if (val > perf->max)
    {
        perf->max = val;
    }
    if (val < perf->min)
    {
        perf->min = val;
    }
}
void StartTimer(PerfMon_t* perf)
{
    perf->start = micros();
}
void StopTimer(PerfMon_t* perf)
{
    uint32_t now = micros();
    uint32_t diff;
    if (now >= perf->start)
    {
        diff = now - perf->start;
    } else
    {
        //The clock wrapped around, fix it
        //This computes (UINT32_MAX - perf->start) + now;
        diff = (uint32_t)(-1) - perf->start + now;
    }
    AddPerfSample(diff, perf);
}
void PrintPerf(HardwareSerial* ser_out, PerfMon_t perf)
{
    ser_out->print(F("N="));
    ser_out->print(perf.num_samples);
    ser_out->print(F(",mean="));
    ser_out->print(perf.mean * MICROSECONDS_TO_MILLISECONDS);
    ser_out->print(F(",min="));
    ser_out->print(perf.min * MICROSECONDS_TO_MILLISECONDS);
    ser_out->print(F(",max="));
    ser_out->print(perf.max * MICROSECONDS_TO_MILLISECONDS);
    ser_out->print(F(",std="));
    ser_out->println(sqrt(perf.var_sum / (perf.num_samples)) * MICROSECONDS_TO_MILLISECONDS);
}
// void PrintPerf(SoftwareSerial* ser_out, PerfMon_t perf)
// {
    // ser_out->print(F("N="));
    // ser_out->print(perf.num_samples);
    // ser_out->print(F(",mean="));
    // ser_out->print(perf.mean * MICROSECONDS_TO_MILLISECONDS);
    // ser_out->print(F(",min="));
    // ser_out->print(perf.min * MICROSECONDS_TO_MILLISECONDS);
    // ser_out->print(F(",max="));
    // ser_out->print(perf.max * MICROSECONDS_TO_MILLISECONDS);
    // ser_out->print(F(",std="));
    // ser_out->println(sqrt(perf.var_sum / (perf.num_samples)) * MICROSECONDS_TO_MILLISECONDS);
// }