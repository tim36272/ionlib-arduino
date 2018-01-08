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
#include <stdarg.h>
#include <arduino.h>
#include "log.h"
#define IONLOG_MAX_MESSAGE_LENGTH (128)
static uint8_t log_state = 0;
namespace ion
{
    void LogEnable()
    {
        log_state = 1;
    }
    void LogDisable()
    {
        log_state = 0;
    }
    void LogPrintf(const char* file, uint32_t line, FlashStr* log_type, FlashStr* format, ...)
    {
        if (log_state == 1)
        {
            va_list args;
            va_start(args, format);
            char buffer[IONLOG_MAX_MESSAGE_LENGTH] = { 0 };
            //advance the file name pointer to the letter right after the last slash
            const char* cursor = file;
            while (*cursor != '\0')
            {
                if (*cursor == '\\')
                {
                    file = cursor + 1;
                }
                cursor++;
            }
            float time_now = millis() / 1000.0;
            uint16_t upper_time = (uint16_t)time_now;
            uint16_t lower_time = time_now * 1000 - ((uint16_t)(time_now)) * 1000;
            (void)snprintf_P(buffer, IONLOG_MAX_MESSAGE_LENGTH, PSTR("%3u.%03u %s:%d "), upper_time, lower_time, file, line);
            Serial.print(buffer);
            Serial.print(log_type);
            (void)vsnprintf_P(buffer, IONLOG_MAX_MESSAGE_LENGTH, (PGM_P)format, args);
            Serial.println(buffer);
            va_end(args);
        }
    }
};