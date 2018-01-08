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
#ifndef ION_LOG_H_
#define ION_LOG_H_
#include <Arduino.h>
#include <stdint.h>
#include "memory.h"
#define LOGFATAL(errnum) {\
  pinMode(13, OUTPUT); \
  while(true) {\
    for(uint8_t index=0;index<errnum;++index) {\
      digitalWrite(13,HIGH);\
      delay(100);\
      digitalWrite(13,LOW);\
      delay(100);\
    }\
    delay(500);\
  }\
}

namespace ion
{
    typedef const char PROGMEM ProgramStr; // PROGMEM/flash-resident string
    typedef const __FlashStringHelper FlashStr; // PROGMEM/flash-resident string
    void LogEnable(void);
    void LogDisable(void);
    void LogPrintf(const char* file, uint32_t line, FlashStr* log_type, FlashStr* format, ...);
}
#ifdef _VMICRO_INTELLISENSE
//The VMICRO environment doesn't have an completely visual studio-compatible F definition, so replace it here to make intellisense happy
#undef F
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))
#endif

#ifdef LOG_ENABLE
//Note that ##__VA_ARGS__ is a GCC-specific extension to allow an empty variable argument list (i.e. LOGINFO("No parameters");) since otherwise there would be a trailing comma in the macro
#define LOGINFO(format,...)  ion::LogPrintf(__FILE__, __LINE__, F("INFO: "),F(format), ##__VA_ARGS__)
//#define LOGINFO(format,...)  ion::LogPrintf(__FILE__, __LINE__, F("INFO: "),F(format), __VA_ARGS__)
#define LOGSRAM() ion::LogPrintf(__FILE__,__LINE__,F("SRAM Available: "),F("%u"),ion::FreeRam())
#else
#define LOGINFO(...)
#endif
#endif //ION_LOG_H_